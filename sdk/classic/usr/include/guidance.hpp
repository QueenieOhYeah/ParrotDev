/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#ifndef GUIDANCE_HPP
#define GUIDANCE_HPP

#include <stdint.h>

#include <string>

#include <google/protobuf/any.pb.h>

#include <axes_cam_controller/axes_cam_controller.pb.h>
#include <colibrylite/types.pb.h>
#include <futils/timetools.h>
#include <guidance/guidance.pb.h>
#include <guidance/guidance.msghub.h>
#include <drone_controller/drone_controller.pb.h>
#include <zoom_cam_controller/zoom_cam_controller.pb.h>
#include <guidance_types.hpp>

/*

The guidance program is responsible for taking commands from the
Flight Supervisor, compute trajectories, and emit simple control
commands to the Drone Controller. For example, it can take a
flightplan as an input, i.e. a sequence of waypoints, and periodically
send flight commands to the drone to match the desired trajectory,
while taking into account obstacle avoidance and manual commands
(e.g. adjust camera orientation).

Each behaviour in the guidance application is associated with a Mode:
there is at most one Mode active at all time during the execution of
the program.

The main event loop connects MsgHub channels with the Flight
Supervisor and the Drone Controller. Messages are defined by Protocol
Buffer descriptions. Guidance is also a client for video frames
(stereo cameras), in order to compute the occupancy grid that makes
obstacle avoidance possible (computations are done in a worker
thread).

The program has access to configuration files and telemetry sections
(drones, cameras), and communicates with other systems either by
sending protobuf messages (Drone Controller), or by producing values
in a telemetry section (cameras).

Guidance is also a Python interpreter, which allows modes to be
written in Python.

During initialization, Guidance loads a set of C++/C/Python plugins
from predefined directories; each plugin may register zero, one or
more "Modes". When Guidance is properly initialized, it sends an
init_ok messages containing all the properly loaded modes.

Modes must implement the "Mode" interface, and may override various
methods that are called at different time during the lifecycle of the
mode (see below).

*/

/* Forward declarations */
namespace pomp {
class Loop;
}

namespace msghub {
class Channel;
class MessageSender;
class MessageHub;
} // namespace msghub

struct vipc_frame;

namespace cfgreader {
class ConfigReader;
}

namespace boonta {
class IElcanoMpc;
class ILazyAttitudeBehavior;
class ICrabAttitudeBehavior;
} // namespace boonta

namespace telemetry {
class Consumer;
class Producer;
}; // namespace telemetry

namespace guidance {

class Guidance;
class Mode;
class SpatialPerception;
class Geofence;

/*! A Guidance Mode can specify at which rate their step() method should
be called. This is done through the guidance::Mode::getTriggers method, which
returns a timeout T, a period N and a bitmask build from the following
values. Each enum value correspond to a possible event that triggers
the step() method. TRIGGER_TIMER and TRIGGER_TICK cannot both be
set. */
enum Trigger {
	/*! Fired after T ms after the last trigger, if no other trigger happen
	 */
	TRIGGER_TIMER = 1 << 0,
	/*! Every N ticks as computed by Drone Controller */
	TRIGGER_TICK = 1 << 1,
	/*! A new depth map is computed */
	TRIGGER_DEPTH_MAP = 1 << 2,
};

/*! Each enum value identifies one predefined Channel */
enum ChannelKind {
	/*! Server channel (normally the client is Flight Supervisor) */
	CHANNEL_KIND_GUIDANCE,
	/*! Client channel connected to Drone Controller. */
	CHANNEL_KIND_DRONE_CONTROLLER,
};

/*! Each enum identifies a Sender object, i.e. an interface through
which protobuf messages can be sent (see libmsghub). */
enum SenderKind {
	SENDER_KIND_DRONE_CONTROLLER,
	SENDER_KIND_FRONT_CAM_CONTROLLER,
	SENDER_KIND_FRONT_ZOOM_CAM_CONTROLLER,
	SENDER_KIND_STEREO_CAM_CONTROLLER,
	SENDER_KIND_GUIDANCE,
};

enum class OutputPart : unsigned {
	REFERENCES = 1 << 0,
	CAMERA_AXES_CONFIG = 1 << 1,
	DRONE_TARGET_CONFIG = 1 << 2
};

/**
 * Guidance interface
 *
 * This is the Guidance interface as seen from modes.
 *
 */
class Guidance {
public:
	inline Guidance() {}
	inline virtual ~Guidance() {}

	/**
	 * Return the POMP loop owned by this guidance instance. This
	 * event base is used to aggregate events from external and
	 * internal messages (see libpomp.hpp). */
	virtual pomp::Loop *getLoop() = 0;

	/**
	 * Return the current MessageHub instance, which is
	 * responsible for managing channels, handlers and senders for
	 * protocol buffer messages (see libmsghub). */
	virtual msghub::MessageHub *getMessageHub() = 0;

	/**
	 * Get the instance of Channel associated with an identifier
	 * @param kind identifies the kind of channel to access.
	 */
	virtual msghub::Channel *getChannel(ChannelKind kind) = 0;

	/**
	 * Get the MessageSender associated with an identifier.
	 * @param kind identifies the kind of sender to access.
	 */
	virtual msghub::MessageSender *getSender(SenderKind kind) = 0;

	/**
	 * Get the current ConfigReader instance, which holds static
	 * configuration values for the current drone hardware.
	 */
	virtual cfgreader::ConfigReader *getConfig() = 0;

	/**
	 * Get the SpatialPerception instance owned by the guidance
	 * object. This gives access to the occupancy grid and the
	 * spherical map.
	 */
	virtual const SpatialPerception *getSpatialPerception() const = 0;

	/**
	 * Get the Geofence instance owned by the guidance object. This gives
	 * access to the geofence getter, setter and process methods.
	 */
	virtual Geofence *getGeofence() = 0;

	/**
	 * Get the guidance FDR-lite data instance owned by the guidance object.
	 */
	virtual GuidanceFdrLiteData *getFdrLiteData() = 0;

	/**
	 * Register a Mode
	 * @param mode non-null pointer to a Mode instance
	 * @returns true if the operation succeeded.
	 *
	 * The mode's name is used as a key to identify it. Two modes
	 * cannot have the same name. If the name already exists, the
	 * current mode is NOT replaced by the new one. The mode name
	 * cannot be empty, or equal to "null".
	 */
	virtual bool addMode(Mode *mode) = 0;

	/**
	 * Unregister a Mode
	 * @param mode non-null pointer to a Mode instance
	 * @returns true if the mode was registered and is
	 * successfully unregistered.
	 */
	virtual bool removeMode(Mode *mode) = 0;

	/**
	 * Called internally by guidance to update the triggers that
	 * wake up the current mode. This calls the mode's
	 * getTriggers() method.
	 */
	virtual void updateModeTriggers() = 0;

	/**
	 * A tick is sent from drone_controller at regular intervals.
	 * getTickNum() returns the latest tick received. The tick is
	 * a strictly increasing number starting from zero.
	 */
	virtual uint32_t getTickNum() = 0;

	/**
	 * Return the configuration directory associated with the
	 * plugin currently being loaded (for example missions are all
	 * located in distinct directories and can use specific
	 * configuration files).
	 *
	 * Calling this method is only valid while a plugin is being
	 * initialized. More precisely, it corresponds to the extent
	 * of a call to guidance::Plugin::init().
	 *
	 * In practice, that means that Python modes can only access
	 * this path from inside Mode constructors, and C++ modes can
	 * only access it during the extent of guidance_plugin_init().
	 *
	 * The resulting string is a copy, the caller owns the value.
	 * The string is empty if the method is called outside of its
	 * valid usage.
	 */
	virtual std::string getConfigDir() = 0;

	/**
	   Called by a mode mode to signal an error; when called,
	   guidance sends a ::Guidance::Messages::Error message to all
	   clients. The "message" parameter is an optional string
	   (defaulting to the empty string) used for debugging and
	   sent along the protobuf Error message.

	   An error in a mode means that the current configuration of
	   the mode, or the current inputs sent to the mode, made it
	   reach a bad state: the mode is exited but might be
	   re-entered later. The mode is NOT disabled/removed from
	   guidance.

	   Once setError() is called, guidance avoids calling any
	   other method from the mode except its exit() method.

	   More precisely, if a mode calls setError() in any other
	   method than exit() (even in enter()), then guidance calls
	   exit() for this mode and reverts to the empty mode. If the
	   mode's exit() method itself calls setError(), this call is
	   ignored (the mode is already treated as errorneous).

	   That means the exit() method must be robust enough to
	   handle errors in any other method of the mode, and clean
	   the resources allocated in configure()/enter() even if they
	   fail to complete.

	   The guidance object never calls setError() by itself.

	   If setError() is called during the extent of setMode(),
	   i.e. either in configure() or enter(), then: (1) the error
	   message is sent, (2) ModeChanged with ok=false is sent (in
	   other words, ModeChanged is always sent).

	   Messages associated with the mode's Outputs at one step are
	   sent only when no error happened at that step (but guidance
	   cannot prevent the mode to explicitly send other messages).
	*/
	virtual void setError(const std::string &message) = 0;
};

/**
 * Guidance input
 *
 * The active mode has access to an instance of Input, which holds the
 * current inputs at each step.
 */
class Input {
public:
	using Pcmd = ::Guidance::Messages::Pcmd;
	const struct vipc_frame *mDepthMap;
	Pcmd mPcmd;

public:
	inline Input()
	{
		clearDepthMap();
	}

	/**
	 * Clear members
	 */
	inline void clearDepthMap()
	{
		mDepthMap = nullptr;
	}

	inline void clearPcmds()
	{
		mPcmd.Clear();
	}
};

/**
 * Guidance output
 *
 * At each step of execution the active mode can update an instance of
 * Output, which holds different drone and camera references expressed
 * as protobuf messages.
 *
 * Each output is associated with a boolean flag for that output that
 * indicates if the output is present at this step or not. At the
 * beginning of a step, all flags are false.
 */
class Output {
public:
	/* Camera and drone references */
	using HorizontalReference =
		DroneController::Messages::HorizontalReference;
	using VerticalReference = DroneController::Messages::VerticalReference;
	using YawReference = DroneController::Messages::YawReference;

	using FrontCamReference = AxesCamController::Messages::Reference;
	using FrontCamZoom = ZoomCamController::Messages::Zoom;

	using StereoCamReference = AxesCamController::Messages::Reference;

	/* Camera configuration */
	using FrontCamReferenceConfig = AxesCamController::Messages::Config;
	using FrontCamZoomConfig = ZoomCamController::Messages::Config;
	using StereoCamReferenceConfig = AxesCamController::Messages::Config;

	using VerticalPositionTarget =
		ColibryLite::Messages::VerticalPositionTarget;
	using VerticalVelocityTarget =
		ColibryLite::Messages::VerticalVelocityTarget;

	using HorizontalPositionTarget =
		ColibryLite::Messages::HorizontalPositionTarget;
	using HorizontalVelocityTarget =
		ColibryLite::Messages::HorizontalVelocityTarget;

	using YawPositionTarget = ColibryLite::Messages::YawPositionTarget;
	using YawVelocityTarget = ColibryLite::Messages::YawVelocityTarget;

public:
	/* REFERENCES */
	/* Drone reference */
	HorizontalReference mHorizontalReference;
	bool mHasHorizontalReference;

	VerticalReference mVerticalReference;
	bool mHasVerticalReference;

	YawReference mYawReference;
	bool mHasYawReference;

	/* Front camera reference */
	FrontCamReference mFrontCamReference;
	bool mHasFrontCamReference;

	FrontCamZoom mFrontCamZoom;
	bool mHasFrontCamZoom;

	/* Stereo camera reference */
	StereoCamReference mStereoCamReference;
	bool mHasStereoCamReference;

	/* CONFIGURATION */
	/* Front camera reference configuration */
	FrontCamReferenceConfig mFrontCamReferenceConfig;
	bool mHasFrontCamReferenceConfig;

	/* Front camera zoom configuration */
	FrontCamZoomConfig mFrontCamZoomConfig;
	bool mHasFrontCamZoomConfig;

	/* Stereo camera reference configuration */
	StereoCamReferenceConfig mStereoCamReferenceConfig;
	bool mHasStereoCamReferenceConfig;

	/* Drone vertical target */
	VerticalPositionTarget mVerticalPositionTarget;
	bool mHasVerticalPositionTarget;
	VerticalVelocityTarget mVerticalVelocityTarget;
	bool mHasVerticalVelocityTarget;

	/* Drone horizontal target */
	HorizontalPositionTarget mHorizontalPositionTarget;
	bool mHasHorizontalPositionTarget;
	HorizontalVelocityTarget mHorizontalVelocityTarget;
	bool mHasHorizontalVelocityTarget;

	/* Drone yaw target */
	YawPositionTarget mYawPositionTarget;
	bool mHasYawPositionTarget;
	YawVelocityTarget mYawVelocityTarget;
	bool mHasYawVelocityTarget;

	/* Optional tick of application in drone controller */
	uint32_t mTickNum;

public:
	inline Output()
	{
		clear();
	}

	/**
	 * Clear members
	 */
	inline void clear()
	{
		mHasHorizontalReference = false;
		mHorizontalReference.Clear();
		mHasVerticalReference = false;
		mVerticalReference.Clear();
		mHasYawReference = false;
		mYawReference.Clear();
		mHasFrontCamReference = false;
		mFrontCamReference.Clear();
		mHasFrontCamZoom = false;
		mFrontCamZoom.Clear();
		mHasStereoCamReference = false;
		mStereoCamReference.Clear();
		mTickNum = 0;

		mHasFrontCamReferenceConfig = false;
		mFrontCamReferenceConfig.Clear();
		mHasFrontCamZoomConfig = false;
		mFrontCamZoomConfig.Clear();
		mHasStereoCamReferenceConfig = false;
		mStereoCamReferenceConfig.Clear();

		mHasVerticalPositionTarget = false;
		mVerticalPositionTarget.Clear();
		mHasVerticalVelocityTarget = false;
		mVerticalVelocityTarget.Clear();
		mHasHorizontalPositionTarget = false;
		mHorizontalPositionTarget.Clear();
		mHasHorizontalVelocityTarget = false;
		mHorizontalVelocityTarget.Clear();
		mHasYawPositionTarget = false;
		mYawPositionTarget.Clear();
		mHasYawVelocityTarget = false;
		mYawVelocityTarget.Clear();
	}
};

/**
 * Guidance Mode
 *
 * At each step (with registered triggers) the methods will be called in this
 * order:
 *
 * - beginStep
 * - generateDroneReference
 * - correctDroneReference
 * - generateAttitudeReferences
 * - endStep
 *
 */
class Mode {
public:
	inline Mode(Guidance *guidance) : mGuidance(guidance) {}
	inline virtual ~Mode() {}

	/**
	 * Get the name of the guidance mode (shall be unique in the system).
	 */
	virtual const std::string &getName() = 0;

	/**
	 * Get the triggers for the mode
	 * @param triggers: mask of Trigger values. TRIGGER_TICK can not be
	 *        combined with TRIGGER_TIMER.
	 * @param timeout: if no frames received during this time (in ms),
	 *        force a step.
	 * @param period: if a timer is required, its period (in ms). If there
	 *        is also a trigger on frame with a timeout specified, it will
	 *        only be called when there is no frame.
	 *        For tick trigger, this is the period of wakeup measured in
	 *        ticks of the Drone Controller. For a 200Hz tick in drone
	 *        controller this means a increment of 5ms per tick.
	 */
	virtual void getTriggers(uint32_t *triggers,
		uint32_t *timeout,
		uint32_t *period) = 0;

	/**
	 * Called when the mode is set with a configuration
	 */
	virtual void configure(const ::google::protobuf::Any &config,
		bool disableObstacleAvoidance,
		bool override_front_camera,
		bool override_stereo_camera)
	{
	}

	/**
	 * Return whether the mode implements obstacle avoidance
	 * Unless this function is overriden, modes do not
	 * advertise they implement obstacle avoidance.
	 * TODO: Add to mode descriptor
	 */
	virtual bool hasObstacleAvoidance()
	{
		return false;
	}

	/**
	 * Return whether the mode implements geofence
	 * Unless this function is overriden, modes do not
	 * advertise they implement geofence.
	 * TODO: Add to mode descriptor
	 */
	virtual bool hasGeofence()
	{
		return false;
	}

	/**
	 * Called when the mode is activated and become the current one.
	 */
	virtual void enter() {}

	/**
	 * Called when the mode is de-activated.
	 */
	virtual void exit() {}

	/**
	 * Start a new step of the guidance
	 * The input data is valid at this point
	 */
	virtual void beginStep() {}

	/**
	 * Finish a step of the guidance
	 * Output data shall be valid after this point
	 */
	virtual void endStep() {}

	/**
	 * Generate the drone trajectory reference (horizontal and vertical).
	 */
	virtual void generateDroneReference() {}

	/**
	 * Correct the generated trajectory using obstacle avoidance data.
	 */
	virtual void correctDroneReference() {}

	/**
	 * Generate the front camera, stereo camera and drone attitudes
	 * references. The camera references do not depend on the drone
	 * ones, but will be saturated if not reachable.
	 */
	virtual void generateAttitudeReferences() {}

	/**
	 * Handle TargetReached message.
	 */
	virtual void onTargetReached(
		const ::DroneController::Messages::TargetReached &msg)
	{
	}

	/**
	 * Send optional drone/camera references and/or camera configuration
	 */
	virtual bool sendOutput(OutputPart part)
	{
		return false;
	}

	inline void setInput(const Input *input)
	{
		mInput = input;
	}

	inline const Input *getInput() const
	{
		return mInput;
	}

	inline void setOutput(Output *output)
	{
		mOutput = output;
	}

	inline Output *getOutput()
	{
		return mOutput;
	}

	/**
	 * Report an error in this mode. The error message is logged
	 * and sent back to the Flight Supervisor. Guidance will call
	 * the exit() method (in case we are not already in exit()),
	 * and deactivate the current mode.
	 */
	inline void setError(const std::string &message)
	{
		if (mGuidance)
			mGuidance->setError(message);
	}

	inline Guidance *getGuidance()
	{
		return mGuidance;
	}

protected:
	Guidance *const mGuidance;
	const Input *mInput = nullptr;
	Output *mOutput = nullptr;
};

class TrajectoryFcamMode : public Mode {

	/**
	 * @brief Handle guidance commands
	 */
	class GuidanceCommandHandler
		: public ::Guidance::Messages::msghub::CommandHandler {
	public:
		inline GuidanceCommandHandler(TrajectoryFcamMode *mode)
			: mMode(mode)
		{
		}
		virtual void setObstacleAvoidance(bool enabled) override;

	private:
		TrajectoryFcamMode *mMode;
	};

public:
	TrajectoryFcamMode(Guidance *guidance, const std::string &name);
	virtual ~TrajectoryFcamMode() override;

public:
	/**
	 * Set nominal global drone trajectory (to be called from
	 * generateDroneReference)
	 * Will be adjusted in correctDroneReference if obstable avoidance is
	 * enabled.
	 */
	void setDroneNominalPositionTrajectoryGlobal(
		const guidance::PositionTrajectoryPoint &point);

	/**
	 * Set nominal local drone trajectory (to be called from
	 * generateDroneReference)
	 * Will be adjusted in correctDroneReference if obstable avoidance is
	 * enabled
	 */
	void setDroneNominalPositionTrajectoryLocal(
		const guidance::PositionTrajectoryPoint &point);

	/**
	 * Set front camera angles and derivative angles (to be called from
	 * generateFcamAttitudeReference) in NED
	 * @param angles are euler angles
	 * @param derivatives are 1st derivatives of euler angles
	 */
	void setFcamEulerAnglesZyxNed(const guidance::EulerAnglesZyx &angles,
		const guidance::EulerAnglesZyx &derivatives);

	/**
	 * Set front camera angles and derivative angles (to be called from
	 * generateFcamAttitudeReference) in NED Start
	 * @param angles are euler angles
	 * @param derivatives are 1st derivatives of euler angles
	 */
	void setFcamEulerAnglesZyxNedStart(
		const guidance::EulerAnglesZyx &angles,
		const guidance::EulerAnglesZyx &derivatives);

	/**
	 * Called at the beginning of generateAttitudeReference to let
	 * derived class to fill mFcamEulerAnglesNedStartRef,
	 * mFcamEulerAnglesDerivativesNedStartRef, mFcamAcceleration and
	 * mFcamZoom.
	 */
	virtual void generateFcamAttitudeReference() = 0;

	/**
	 * Process obstacle avoidance algorithm.
	 * This method is usually called by correctDroneReference.
	 * It can be overrided to change obstacle avoidance behavior.
	 */
	virtual const guidance::PositionTrajectoryPoint &
	processObstacleAvoidance();

	/**
	 * Enable or disable obstacle avoidance
	 * @param enable true to enable obstacle avoidance, false otherwise
	 */
	void enableObstacleAvoidance(bool enable);

	/**
	 * Get obstacle avoidance status
	 * @return True if obstacle avoidance is enabled
	 */
	bool isObstacleAvoidanceEnabled();

	inline uint32_t getTickPeriod() const
	{
		return sTickPeriod;
	}

	inline float getTimePeriod() const
	{
		return sTimePeriod;
	}

	inline const PositionTrajectoryPoint &
	getDroneNominalPositionTrajectoryLocal() const
	{
		return sDronePositionStateLocalNom;
	}

	inline const PositionTrajectoryPoint &
	getDroneReferencePositionTrajectoryLocal() const
	{
		return sDronePositionStateLocalRef;
	}

	/**
	 * @brief Return the maximum admissible horizontal speed [m/s] (> 0)
	 */
	float getMaxHorizontalSpeed() const;

	/**
	 * @brief Return the maximum admissible descent speed [m/s] (> 0)
	 */
	float getMaxDescentSpeed() const;

	/**
	 * @brief Return the maximum admissible ascent speed [m/s] (> 0)
	 */
	float getMaxAscentSpeed() const;

	static int init(Guidance *guidance);
	static void destroy();

public:
	/* Methods overriden from base Mode class */

	virtual bool hasObstacleAvoidance() override;

	virtual void getTriggers(uint32_t *triggers,
		uint32_t *timeout,
		uint32_t *period) override;

	virtual void configure(const ::google::protobuf::Any &config,
		bool disableObstacleAvoidance,
		bool overrideFrontCamera,
		bool overrideStereoCamera) override;

	virtual void enter() override;
	virtual void beginStep() override;
	virtual void correctDroneReference() override;
	virtual void generateAttitudeReferences() override;
	virtual void endStep() override;
	virtual void exit() override;

private:
	/* Internal functions to fill output from intermediate values */

	void setOutputDroneReference(
		::ColibryLite::Messages::ReferencePropagationModel::Enum
			referencePropagationModel);
	void setOutputFcamReference();
	void setOutputStcamReference();
	void setOutputDroneYawReference(
		::ColibryLite::Messages::ReferencePropagationModel::Enum
			referencePropagationModel);

	/*
	 * @brief Update the obstacle avoidance dedicated debug data
	 */
	void updateDebugData();

	/**
	 * @brief Update and send guidance event messages
	 */
	void updateAlerts();

	/**
	 * @brief Clear and send guidance event messages
	 */
	void clearAlerts();

protected:
	/* Timestamp of the last call of a TrajectoryFcamMode mode */
	static timespec sLastCallTimestamp;

	/* Local trajectory replanner for obstacle avoidance */
	static std::unique_ptr<boonta::IElcanoMpc> sReplannerLocal;
	/* Obstacle avoidance trajectory status */
	static unsigned int sReplannerReferenceStatus;
	/* True if the replanner is stuck against a forbidden region */
	static bool sIsReplannerStuck;
	/* True if the replanner failed computing trajectories */
	static bool sHasReplannerFailed;
	/* Local coordinates of the closest obstacle */
	static Eigen::Vector3f sClosestObstaclePositionLocal;
	/* Signed distance to the closest obstacle in [m] */
	static float sClosestObstacleSignedDistance;

	/* True if the init method was called */
	static bool sIsInitialized;

	/* Drone estimated 3D position, velocity and acceleration in local
	 * frame */
	static guidance::PositionTrajectoryPoint sDronePositionStateLocalEst;
	/* Drone nominal 3D position, velocity and acceleration in local
	 * frame */
	static guidance::PositionTrajectoryPoint sDronePositionStateLocalNom;
	/* Drone reference 3D position, velocity and acceleration in local
	 * frame */
	static guidance::PositionTrajectoryPoint sDronePositionStateLocalRef;
	/* Drone estimated orientation in NED vector basis - as Euler angles
	 * ZYX */
	static guidance::EulerAnglesZyx sDroneEulerAnglesNedEst;
	/* Drone estimated orientation in NED start vector basis - as Euler
	 * angles ZYX */
	static guidance::EulerAnglesZyx sDroneEulerAnglesNedStartEst;
	/* Drone yaw angle, rate and acceleration references in NED start vector
	 * basis */
	static Eigen::Vector3f sDroneYawStateNedStartRef;

	/* Drone maximal horizontal speed allowed */
	static float sDroneMaxHorizSpeed;
	/* Drone minimal vertical speed allowed */
	static float sDroneMinVerticalSpeed;
	/* Drone maximal vertical speed allowed */
	static float sDroneMaxVerticalSpeed;

	/* Allow ground constraint */
	bool mFcamGroundConstraintEnabled;
	/* Front camera yaw angle acceleration in NED start vector basis */
	float mFcamYawAccelerationNedStartRef;
	/* Front camera zoom factor reference */
	float mFcamZoom;

	/* Horizontal control config */
	::ColibryLite::Messages::HorizontalControlConfig::Enum
		mDroneHorizontalControlConfig;

	/* Vertical control config */
	::ColibryLite::Messages::VerticalControlConfig::Enum
		mDroneVerticalControlConfig;

	/* Yaw control config */
	::ColibryLite::Messages::YawControlConfig::Enum mDroneYawControlConfig;

	/* Stereo camera reference orientation in NED start vector basis - as
	 * Euler angles ZYX */
	static guidance::EulerAnglesZyx sStcamEulerAnglesNedStartRef;

	/**
	 * @brief Update the timer for checking if a mode should be reset
	 * @details This function should be called in each TrajectoryFcamMode
	 * mode
	 *          - in the configure() function to decide wether the mode
	 *            should be reset
	 *          - in the beginStep() function to update the timer
	 * @return true if the mode should be reset
	 */
	bool updateResetStatus();

	/**
	 * @brief Update variables from latest telemetry
	 * @details Convert estimated position trajectory point from global to
	 * local. Convert estimated drone Euler angles from NED start to NED.
	 */
	void updateTelemetry();

private:
	/* Guidance mode period in [tick] */
	static uint32_t sTickPeriod;
	/* Guidance mode period in [s] */
	static float sTimePeriod;

	/* Handler for guidance messages */
	GuidanceCommandHandler mGuidanceCommandHandler;
	/* Guidance event messages sender */
	::Guidance::Messages::msghub::EventSender mGuidanceEventSender;

	/* Obstacle avoidance */
	bool mIsObstacleAvoidanceEnabled;
	std::unique_ptr<boonta::ILazyAttitudeBehavior> mStcamLazyBehaviorNed;
	std::unique_ptr<boonta::ICrabAttitudeBehavior> mStcamCrabBehaviorNed;

	/* Telemetry */
	static telemetry::Consumer *sTlmConsumer;
	static telemetry::Producer *sTlmDbgProducer;
	/* 2D position offset between local and global frames */
	static Eigen::Vector2f sPositionOffsetLocalToGlobal;

	static PositionTrajectoryPoint sDronePositionStateGlobalEst;
	static float sYawOffsetNedStartToNed;

	/* Vector basis in which the front camera reference has been set */
	guidance::VectorBasis mFcamRefVectorBasis;
	/* Front camera reference orientation in NED vector basis - as
	 * Euler angles ZYX */
	EulerAnglesZyx mFcamEulerAnglesNedRef;
	/* Front camera reference orientation in NED start vector basis - as
	 * Euler angles ZYX, and their time derivatives */
	EulerAnglesZyx mFcamEulerAnglesNedStartRef;
	EulerAnglesZyx mFcamEulerAnglesDerivativesNedStartRef;
};

class TrajectoryStcamMode : public Mode {
public:
	TrajectoryStcamMode(Guidance *guidance, const std::string &name);
	virtual ~TrajectoryStcamMode() override;

public:
	/**
	 * Set nominal global drone trajectory (to be called from
	 * generateDroneReference)
	 */
	void setDroneNominalPositionTrajectoryGlobal(
		const guidance::PositionTrajectoryPoint &point);

	/**
	 * Set nominal local drone trajectory (to be called from
	 * generateDroneReference)
	 */
	void setDroneNominalPositionTrajectoryLocal(
		const guidance::PositionTrajectoryPoint &point);

	/**
	 * Set front camera angles and derivative angles (to be called from
	 * generateFcamAttitudeReference) in NED
	 * @param angles are euler angles
	 * @param derivatives are 1st derivatives of euler angles
	 */
	void setFcamEulerAnglesZyxNed(const guidance::EulerAnglesZyx &angles,
		const guidance::EulerAnglesZyx &derivatives);

	/**
	 * Set front camera angles and derivative angles (to be called from
	 * generateFcamAttitudeReference) in NED Start
	 * @param angles are euler angles
	 * @param derivatives are 1st derivatives of euler angles
	 */
	void setFcamEulerAnglesZyxNedStart(
		const guidance::EulerAnglesZyx &angles,
		const guidance::EulerAnglesZyx &derivatives);

	/**
	 * Set stereo camera angles and derivative angles (to be called from
	 * generateStcamAttitudeReference) in NED
	 * @param angles are euler angles
	 * @param derivatives are 1st derivatives of euler angles
	 */
	void setStcamEulerAnglesZyxNed(const guidance::EulerAnglesZyx &angles,
		const guidance::EulerAnglesZyx &derivatives);

	/**
	 * Set stereo camera angles and derivative angles (to be called from
	 * generateStcamAttitudeReference) in NED Start
	 * @param angles are euler angles
	 * @param derivatives are 1st derivatives of euler angles
	 */
	void setStcamEulerAnglesZyxNedStart(
		const guidance::EulerAnglesZyx &angles,
		const guidance::EulerAnglesZyx &derivatives);

	/**
	 * @brief Return the maximum admissible horizontal speed [m/s] (> 0)
	 */
	float getMaxHorizontalSpeed() const;

	/**
	 * @brief Return the maximum admissible descent speed [m/s] (> 0)
	 */
	float getMaxDescentSpeed() const;

	/**
	 * @brief Return the maximum admissible ascent speed [m/s] (> 0)
	 */
	float getMaxAscentSpeed() const;

	/**
	 * Called at the beginning of generateAttitudeReferences to let
	 * derived class to fill mFcamEulerAnglesNedStartRef,
	 * mFcamEulerAnglesDerivativesNedStartRef, mFcamAcceleration and
	 * mFcamZoom.
	 */
	virtual void generateFcamAttitudeReference() = 0;

	/**
	 * Called at the beginning of generateAttitudeReferences to let
	 * derived class to fill mStcamEulerAnglesNedStartRef,
	 * mStcamEulerAnglesDerivativesNedStartRef and mStcamAcceleration.
	 */
	virtual void generateStcamAttitudeReference() = 0;

	inline uint32_t getTickPeriod() const
	{
		return mTickPeriod;
	}

	inline float getTimePeriod() const
	{
		return mTimePeriod;
	}

	inline const PositionTrajectoryPoint &
	getDroneNominalPositionTrajectoryLocal() const
	{
		return mDronePositionStateLocalNom;
	}

	inline const PositionTrajectoryPoint &
	getDroneReferencePositionTrajectoryLocal() const
	{
		return mDronePositionStateLocalRef;
	}

public:
	/* Methods overriden from base Mode class */

	virtual bool hasObstacleAvoidance() override;

	virtual void getTriggers(uint32_t *triggers,
		uint32_t *timeout,
		uint32_t *period) override;

	virtual void configure(const ::google::protobuf::Any &config,
		bool disableObstacleAvoidance,
		bool overrideFrontCamera,
		bool overrideStereoCamera) override;

	virtual void beginStep() override;
	virtual void correctDroneReference() override;
	virtual void generateAttitudeReferences() override;
	virtual void endStep() override;

private:
	/* Internal functions to fill output from intermediate values */

	void setOutputDroneReference(
		::ColibryLite::Messages::ReferencePropagationModel::Enum
			referencePropagationModel);
	void setOutputFcamReference();
	void setOutputStcamReference();
	void setOutputDroneYawReference(
		::ColibryLite::Messages::ReferencePropagationModel::Enum
			referencePropagationModel);

protected:
	/* Allow ground constraint */
	bool mStcamGroundConstraintEnabled;

	/* Stereo camera yaw angle acceleration to fill in
	 * generateStcamAttitudeReference */
	float mStcamYawAccelerationNedStartRef;

	/* Front camera zoom to fill in generateFcamAttitudeReference */
	float mFcamZoom;

private:
	/* Guidance mode period in [tick] */
	uint32_t mTickPeriod;

	/* Guidance mode period in [s] */
	float mTimePeriod;

	/* Telemetry */
	telemetry::Consumer *mTlmConsumer;
	PositionTrajectoryPoint mDronePositionStateGlobalEst;
	EulerAnglesZyx mDroneEulerAnglesNedEst;
	EulerAnglesZyx mDroneEulerAnglesNedStartEst;
	float mYawOffsetNedStartToNed;

	/* Drone estimated 3D position, velocity and acceleration in local
	 * frame */
	PositionTrajectoryPoint mDronePositionStateLocalEst;

	/* Drone nominal 3D position, velocity and acceleration in local
	 * frame */
	PositionTrajectoryPoint mDronePositionStateLocalNom;

	/* Drone reference 3D position, velocity and acceleration in local
	 * frame */
	PositionTrajectoryPoint mDronePositionStateLocalRef;

	/* Drone yaw angle, rate and acceleration references in NED start vector
	 * basis */
	Eigen::Vector3f mDroneYawStateNedStartRef;

	/* Vector basis in which the front camera reference has been set */
	guidance::VectorBasis mFcamRefVectorBasis;
	/* Front camera reference orientation in NED vector basis - as
	 * Euler angles ZYX, and their time derivatives */
	EulerAnglesZyx mFcamEulerAnglesNedRef;
	/* Front camera reference orientation in NED start vector basis - as
	 * Euler angles ZYX, and their time derivatives */
	EulerAnglesZyx mFcamEulerAnglesNedStartRef;
	EulerAnglesZyx mFcamEulerAnglesDerivativesNedStartRef;

	/* Vector basis in which the stereo camera reference has been set */
	guidance::VectorBasis mStcamRefVectorBasis;
	/* Stereo camera reference orientation in NED vector basis - as
	 * Euler angles ZYX, and their time derivatives */
	EulerAnglesZyx mStcamEulerAnglesNedRef;
	/* Stereo camera reference orientation in NED start vector basis - as
	 * Euler angles ZYX, and their time derivatives */
	EulerAnglesZyx mStcamEulerAnglesNedStartRef;
	EulerAnglesZyx mStcamEulerAnglesDerivativesNedStartRef;

	/* Drone maximal horizontal speed allowed */
	float mDroneMaxHorizSpeed;
	/* Drone minimal vertical speed allowed */
	float mDroneMinVerticalSpeed;
	/* Drone maximal vertical speed allowed */
	float mDroneMaxVerticalSpeed;
};

} /* namespace guidance */

/* plugin C interface */
extern "C" void guidance_plugin_init(guidance::Guidance *guidance);

extern "C" void guidance_plugin_shutdown(guidance::Guidance *guidance);

#endif /* GUIDANCE_HPP !*/
