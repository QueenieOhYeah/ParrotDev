/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "drone_controller/drone_controller.pb.h"

namespace pomp {
	class Conn;
}

namespace DroneController {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "DroneController.Messages.Command";

	CommandSender();

	virtual void beforeSend(DroneController::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const DroneController::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent all events
	 */
	int requestAllEvents(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent full steady state
	 */
	int requestFullSteadyState(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Select drone estimation mode according to the drone state.
	 */
	int setEstimationMode(
		::ColibryLite::Messages::EstimationMode::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Disable horizontal closed loop control.
	 */
	int disableHorizontalControl(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Modify horizontal reference.
	 */
	int setHorizontalReference(
		const ::DroneController::Messages::HorizontalReference &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Disable vertical closed loop control.
	 */
	int disableVerticalControl(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Modify vertical reference.
	 */
	int setVerticalReference(
		const ::DroneController::Messages::VerticalReference &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Disable yaw closed loop control.
	 */
	int disableYawControl(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Modify yaw reference.
	 */
	int setYawReference(
		const ::DroneController::Messages::YawReference &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Enable or disable angle control loop integral reset.
	 * This reset should be activated when the drone model is false (for example during takeoff).
	 */
	int resetQuaternionLoopIntegral(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Switch control to 3 motor mode in case of motor failure.
	 * This is effective only if 'enableMotorDownControl' is true in configuration.
	 * Once activated it is not possible to go back to 4 motor control mode.
	 */
	int activateMotorDownControl(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Start all motors. The service will reply with either
	 * {motors_started} or {motors_start_failure}.
	 */
	int startMotors(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Stop all motors. The service will reply with {motors_stopped}.
	 */
	int stopAllMotors(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Stop the specified motor.
	 */
	int stopMotor(
		::ColibryLite::Messages::DefectiveMotorId::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Configure notification of internal 'ticks' of the processing loop
	 */
	int setTickNotificationConfig(
		const ::DroneController::Messages::TickNotificationConfig &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Clients can send this message to notify they are still
	 * alive when they have no particular reference to send.
	 * This is used to avoid entering emergency mode.
	 */
	int keepAlive(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Enable magic carpet sensor.
	 */
	int setVisionCarpet(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Change value of internal debug value
	 * Useful only for debug purposes
	 */
	int setNavDebug(
		const ::DroneController::Messages::NavDebug &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Change how the drone should react in case of future loss of control
	 */
	int setEmergencyBehavior(
		::DroneController::Messages::EmergencyBehavior::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set position velocity targets.
	 */
	int setPositionVelocityTargets(
		const ::DroneController::Messages::PositionVelocityTargets &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Reset all targets (horizontal/vertical/yaw position/velocity).
	 */
	int resetAllTargets(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Clear queue of commands waiting for the 'tick' (previous commands
	 * with a {tick_num} value not yet reached)
	 */
	int clearCommandQueue(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Activate magnetometer rejection for a nominal duration
	 * (see timeHeadingLockedAfterMagnetoLoss in common/estimator.cfg).
	 */
	int setMagnetoRejectionNominal(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Activate magnetometer rejection for an unlimited time.
	 */
	int setMagnetoRejectionUnlimited(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set the heading angle to a given external value [rad].
	 */
	int setExternalHeading(
		float arg,
		pomp::Connection *conn=nullptr);

	/**
	 * After an external heading has been set, reallow the usage of internal
	 * sensors (magnetometer) to correct the heading immediately
	 */
	int stopExternalHeadingMode(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Unlock the heading (being set either internally or externally)
	 */
	int unlockHeading(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "DroneController.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const DroneController::Messages::Command &arg);

	/**
	 * Sent all events
	 */
	virtual void requestAllEvents(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent full steady state
	 */
	virtual void requestFullSteadyState(
		const ::google::protobuf::Empty &msg);

	/**
	 * Select drone estimation mode according to the drone state.
	 */
	virtual void setEstimationMode(
		::ColibryLite::Messages::EstimationMode::Enum msg);

	/**
	 * Disable horizontal closed loop control.
	 */
	virtual void disableHorizontalControl(
		const ::google::protobuf::Empty &msg);

	/**
	 * Modify horizontal reference.
	 */
	virtual void setHorizontalReference(
		const ::DroneController::Messages::HorizontalReference &msg);

	/**
	 * Disable vertical closed loop control.
	 */
	virtual void disableVerticalControl(
		const ::google::protobuf::Empty &msg);

	/**
	 * Modify vertical reference.
	 */
	virtual void setVerticalReference(
		const ::DroneController::Messages::VerticalReference &msg);

	/**
	 * Disable yaw closed loop control.
	 */
	virtual void disableYawControl(
		const ::google::protobuf::Empty &msg);

	/**
	 * Modify yaw reference.
	 */
	virtual void setYawReference(
		const ::DroneController::Messages::YawReference &msg);

	/**
	 * Enable or disable angle control loop integral reset.
	 * This reset should be activated when the drone model is false (for example during takeoff).
	 */
	virtual void resetQuaternionLoopIntegral(
		bool msg);

	/**
	 * Switch control to 3 motor mode in case of motor failure.
	 * This is effective only if 'enableMotorDownControl' is true in configuration.
	 * Once activated it is not possible to go back to 4 motor control mode.
	 */
	virtual void activateMotorDownControl(
		const ::google::protobuf::Empty &msg);

	/**
	 * Start all motors. The service will reply with either
	 * {motors_started} or {motors_start_failure}.
	 */
	virtual void startMotors(
		const ::google::protobuf::Empty &msg);

	/**
	 * Stop all motors. The service will reply with {motors_stopped}.
	 */
	virtual void stopAllMotors(
		const ::google::protobuf::Empty &msg);

	/**
	 * Stop the specified motor.
	 */
	virtual void stopMotor(
		::ColibryLite::Messages::DefectiveMotorId::Enum msg);

	/**
	 * Configure notification of internal 'ticks' of the processing loop
	 */
	virtual void setTickNotificationConfig(
		const ::DroneController::Messages::TickNotificationConfig &msg);

	/**
	 * Clients can send this message to notify they are still
	 * alive when they have no particular reference to send.
	 * This is used to avoid entering emergency mode.
	 */
	virtual void keepAlive(
		const ::google::protobuf::Empty &msg);

	/**
	 * Enable magic carpet sensor.
	 */
	virtual void setVisionCarpet(
		bool msg);

	/**
	 * Change value of internal debug value
	 * Useful only for debug purposes
	 */
	virtual void setNavDebug(
		const ::DroneController::Messages::NavDebug &msg);

	/**
	 * Change how the drone should react in case of future loss of control
	 */
	virtual void setEmergencyBehavior(
		::DroneController::Messages::EmergencyBehavior::Enum msg);

	/**
	 * Set position velocity targets.
	 */
	virtual void setPositionVelocityTargets(
		const ::DroneController::Messages::PositionVelocityTargets &msg);

	/**
	 * Reset all targets (horizontal/vertical/yaw position/velocity).
	 */
	virtual void resetAllTargets(
		const ::google::protobuf::Empty &msg);

	/**
	 * Clear queue of commands waiting for the 'tick' (previous commands
	 * with a {tick_num} value not yet reached)
	 */
	virtual void clearCommandQueue(
		const ::google::protobuf::Empty &msg);

	/**
	 * Activate magnetometer rejection for a nominal duration
	 * (see timeHeadingLockedAfterMagnetoLoss in common/estimator.cfg).
	 */
	virtual void setMagnetoRejectionNominal(
		const ::google::protobuf::Empty &msg);

	/**
	 * Activate magnetometer rejection for an unlimited time.
	 */
	virtual void setMagnetoRejectionUnlimited(
		const ::google::protobuf::Empty &msg);

	/**
	 * Set the heading angle to a given external value [rad].
	 */
	virtual void setExternalHeading(
		float msg);

	/**
	 * After an external heading has been set, reallow the usage of internal
	 * sensors (magnetometer) to correct the heading immediately
	 */
	virtual void stopExternalHeadingMode(
		const ::google::protobuf::Empty &msg);

	/**
	 * Unlock the heading (being set either internally or externally)
	 */
	virtual void unlockHeading(
		const ::google::protobuf::Empty &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "DroneController.Messages.Event";

	EventSender();

	virtual void beforeSend(DroneController::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const DroneController::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motion state changed (steady, moving).
	 */
	int motionStateChanged(
		::ColibryLite::Messages::MotionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when a moving ground has been detected.
	 */
	int movingGroundStateChanged(
		::ColibryLite::Messages::EventDetectionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone has entered into a freefall phase.
	 */
	int freefallDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone has landed.
	 */
	int landedDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the given thrust target has been reached.
	 */
	int thrustRampDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone is steady in the horizontal plan.
	 */
	int horizontalSteady(
		::ColibryLite::Messages::EventDetectionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone is steady on the vertical axis.
	 */
	int verticalSteady(
		::ColibryLite::Messages::EventDetectionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone is steady on the yaw axis.
	 */
	int yawSteady(
		::ColibryLite::Messages::EventDetectionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone is steady on all axes (horizontal/vertical/yaw).
	 */
	int fullSteadyOk(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone is not steady on all axes (horizontal/vertical/yaw).
	 */
	int fullSteadyKo(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when sensors detected too much pitch/roll angle.
	 */
	int tooMuchAngleDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when sensors detected too much pitch/roll angle, near ground.
	 */
	int tooMuchAngleDetectedAtLowAltitude(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the pitch/roll angle is nominal.
	 */
	int nominalAngleDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the pitch/roll angle is nominal, near ground.
	 */
	int nominalAngleDetectedAtLowAltitude(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when a vertical flyaway is detected.
	 * TODO: find a better name
	 */
	int flyawayDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when flying far from earth poles, where horizontal magnetic field is high enough.
	 */
	int magnetoFarEnoughFromEarthPoles(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when flying near the earth poles, where horizontal magnetic field is too small.
	 */
	int magnetoTooCloseToEarthPoles(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when sensor magnetic norm is not coherent with earth magnetic norm.
	 */
	int magneticInterferenceDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when sensor magnetic norm is coherent with earth magnetic norm.
	 */
	int noMagneticInterference(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the drone is not in a freefall phase.
	 */
	int freefallNotDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motors are started (requested `start_motors` ok).
	 */
	int motorsStarted(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motors failed to start (requested `start_motors` ko).
	 */
	int motorsStartFailure(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when at least one motor stopped spinning after `stop_motors` was requested.
	 */
	int motorsStopped(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when at least one motor stopped spinning, but no request was made to stop motors.
	 */
	int motorsCutout(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motors reached their target speed before taking off.
	 */
	int motorsRampingDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motor errors changed.
	 */
	int motorsErrors(
		const ::DroneController::Messages::MotorsErrorsChanged &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent at init with motors version.
	 */
	int motorsVersion(
		const ::DroneController::Messages::MotorsVersion &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motors flight info changed.
	 */
	int motorsFlightInfo(
		const ::DroneController::Messages::MotorsFlightInfo &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when one or more target references are reached.
	 */
	int targetReached(
		const ::DroneController::Messages::TargetReached &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when pitch/roll angle is low enough after hand takeoff.
	 */
	int handTakeoffLowAngle(
		::ColibryLite::Messages::EventDetectionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the vertical speed error is low enough after hand takeoff.
	 */
	int handTakeoffLowVerticalSpeedError(
		::ColibryLite::Messages::EventDetectionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the angular velocity on both horizontal plane and
	 * yaw axis are low enough after hand takeoff.
	 */
	int handTakeoffLowAngularVelocity(
		::ColibryLite::Messages::EventDetectionState::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when velocity estimation is reliable enough.
	 */
	int linearVelocityReliable(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when velocity estimation is not reliable.
	 */
	int linearVelocityUnreliable(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when ground distance sensors are defective.
	 */
	int groundDistanceDefective(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when at least one ground distance sensor is not defective.
	 */
	int groundDistanceFunctional(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motors provide the thrust required to enable angle control.
	 */
	int thrustForAngleReached(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when everything is ready for GPS navigation. The GPS has fixed
	 * a location and the geographic north is known.
	 */
	int gpsNavigationReady(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when GPS navigation is unavailable. Either the GPS has not fixed
	 * a location or the geographic north is unknown.
	 */
	int gpsNavigationUnavailable(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when GPS sensor has fixed a location.
	 */
	int gpsSensorOk(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when GPS sensor has not fixed a location.
	 */
	int gpsSensorKo(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when geographic north is known.
	 */
	int headingLockedOk(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when geographic north is unknown.
	 */
	int headingLockedKo(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the number of detected satellites changed.
	 */
	int gpsSatellites(
		uint32_t arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when everything is ready for vision navigation.
	 */
	int visionNavigationReady(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when vision navigation is unavailable.
	 */
	int visionNavigationUnavailable(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the wind status changed.
	 */
	int windStatusChanged(
		::ColibryLite::Messages::WindStatus::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the defective motor status changed.
	 */
	int defectiveMotorIdChanged(
		::ColibryLite::Messages::DefectiveMotorId::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the defective motor failure changed.
	 */
	int defectiveMotorFailureTypeChanged(
		::ColibryLite::Messages::DefectiveMotorFailureType::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on IMU vibration level changed.
	 */
	int vibrationLevelChanged(
		::ColibryLite::Messages::ThreeLevelStatus::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on propeller icing level changed.
	 */
	int propellerIcingLevelChanged(
		::ColibryLite::Messages::ThreeLevelStatus::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoNotCalibrated(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationXDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationYDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationZDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationAborted(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationFailed(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationRequired(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent on specific magneto calibration state.
	 */
	int magnetoCalibrationAdvised(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when requested to go below minimum altitude.
	 */
	int minAltitudeConstrained(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when exiting `min_altitude_constrained` condition.
	 */
	int minAltitudeNotConstrained(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the state of defective sensors changed.
	 */
	int defectiveSensorsStateChanged(
		uint32_t arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the battery state changed.
	 */
	int batteryStateChanged(
		const ::DroneController::Messages::BatteryState &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the battery role changed.
	 */
	int batteryRoleChanged(
		const ::DroneController::Messages::BatteryRole &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the battery is too hot.
	 */
	int batteryAlertTooHot(
		::DroneController::Messages::BatteryAlert::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the battery is too cold.
	 */
	int batteryAlertTooCold(
		::DroneController::Messages::BatteryAlert::Enum arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when the battery health changed.
	 */
	int batteryHealth(
		const ::DroneController::Messages::BatteryHealth &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Notify ticks of the processing loop. It is only sent if a client
	 * configured it with {set_tick_notification_config}.
	 */
	int tick(
		const ::DroneController::Messages::Tick &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motor down control is available.
	 */
	int motorDownControlReady(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when motor down control becomes unavailable.
	 */
	int motorDownControlUnavailable(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when ESC single stall becomes available.
	 */
	int singleStallAvailable(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent when ESC single stall becomes unavailable.
	 */
	int singleStallUnavailable(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Sent at startup when all estimators (etc.) are initialized.
	 */
	int initOk(
		const ::DroneController::Messages::InitStatus &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "DroneController.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const DroneController::Messages::Event &arg);

	/**
	 * Sent when motion state changed (steady, moving).
	 */
	virtual void motionStateChanged(
		::ColibryLite::Messages::MotionState::Enum msg);

	/**
	 * Sent when a moving ground has been detected.
	 */
	virtual void movingGroundStateChanged(
		::ColibryLite::Messages::EventDetectionState::Enum msg);

	/**
	 * Sent when the drone has entered into a freefall phase.
	 */
	virtual void freefallDetected(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the drone has landed.
	 */
	virtual void landedDetected(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the given thrust target has been reached.
	 */
	virtual void thrustRampDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the drone is steady in the horizontal plan.
	 */
	virtual void horizontalSteady(
		::ColibryLite::Messages::EventDetectionState::Enum msg);

	/**
	 * Sent when the drone is steady on the vertical axis.
	 */
	virtual void verticalSteady(
		::ColibryLite::Messages::EventDetectionState::Enum msg);

	/**
	 * Sent when the drone is steady on the yaw axis.
	 */
	virtual void yawSteady(
		::ColibryLite::Messages::EventDetectionState::Enum msg);

	/**
	 * Sent when the drone is steady on all axes (horizontal/vertical/yaw).
	 */
	virtual void fullSteadyOk(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the drone is not steady on all axes (horizontal/vertical/yaw).
	 */
	virtual void fullSteadyKo(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when sensors detected too much pitch/roll angle.
	 */
	virtual void tooMuchAngleDetected(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when sensors detected too much pitch/roll angle, near ground.
	 */
	virtual void tooMuchAngleDetectedAtLowAltitude(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the pitch/roll angle is nominal.
	 */
	virtual void nominalAngleDetected(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the pitch/roll angle is nominal, near ground.
	 */
	virtual void nominalAngleDetectedAtLowAltitude(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when a vertical flyaway is detected.
	 * TODO: find a better name
	 */
	virtual void flyawayDetected(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when flying far from earth poles, where horizontal magnetic field is high enough.
	 */
	virtual void magnetoFarEnoughFromEarthPoles(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when flying near the earth poles, where horizontal magnetic field is too small.
	 */
	virtual void magnetoTooCloseToEarthPoles(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when sensor magnetic norm is not coherent with earth magnetic norm.
	 */
	virtual void magneticInterferenceDetected(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when sensor magnetic norm is coherent with earth magnetic norm.
	 */
	virtual void noMagneticInterference(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the drone is not in a freefall phase.
	 */
	virtual void freefallNotDetected(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when motors are started (requested `start_motors` ok).
	 */
	virtual void motorsStarted(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when motors failed to start (requested `start_motors` ko).
	 */
	virtual void motorsStartFailure(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when at least one motor stopped spinning after `stop_motors` was requested.
	 */
	virtual void motorsStopped(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when at least one motor stopped spinning, but no request was made to stop motors.
	 */
	virtual void motorsCutout(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when motors reached their target speed before taking off.
	 */
	virtual void motorsRampingDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when motor errors changed.
	 */
	virtual void motorsErrors(
		const ::DroneController::Messages::MotorsErrorsChanged &msg);

	/**
	 * Sent at init with motors version.
	 */
	virtual void motorsVersion(
		const ::DroneController::Messages::MotorsVersion &msg);

	/**
	 * Sent when motors flight info changed.
	 */
	virtual void motorsFlightInfo(
		const ::DroneController::Messages::MotorsFlightInfo &msg);

	/**
	 * Sent when one or more target references are reached.
	 */
	virtual void targetReached(
		const ::DroneController::Messages::TargetReached &msg);

	/**
	 * Sent when pitch/roll angle is low enough after hand takeoff.
	 */
	virtual void handTakeoffLowAngle(
		::ColibryLite::Messages::EventDetectionState::Enum msg);

	/**
	 * Sent when the vertical speed error is low enough after hand takeoff.
	 */
	virtual void handTakeoffLowVerticalSpeedError(
		::ColibryLite::Messages::EventDetectionState::Enum msg);

	/**
	 * Sent when the angular velocity on both horizontal plane and
	 * yaw axis are low enough after hand takeoff.
	 */
	virtual void handTakeoffLowAngularVelocity(
		::ColibryLite::Messages::EventDetectionState::Enum msg);

	/**
	 * Sent when velocity estimation is reliable enough.
	 */
	virtual void linearVelocityReliable(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when velocity estimation is not reliable.
	 */
	virtual void linearVelocityUnreliable(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when ground distance sensors are defective.
	 */
	virtual void groundDistanceDefective(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when at least one ground distance sensor is not defective.
	 */
	virtual void groundDistanceFunctional(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when motors provide the thrust required to enable angle control.
	 */
	virtual void thrustForAngleReached(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when everything is ready for GPS navigation. The GPS has fixed
	 * a location and the geographic north is known.
	 */
	virtual void gpsNavigationReady(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when GPS navigation is unavailable. Either the GPS has not fixed
	 * a location or the geographic north is unknown.
	 */
	virtual void gpsNavigationUnavailable(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when GPS sensor has fixed a location.
	 */
	virtual void gpsSensorOk(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when GPS sensor has not fixed a location.
	 */
	virtual void gpsSensorKo(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when geographic north is known.
	 */
	virtual void headingLockedOk(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when geographic north is unknown.
	 */
	virtual void headingLockedKo(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the number of detected satellites changed.
	 */
	virtual void gpsSatellites(
		uint32_t msg);

	/**
	 * Sent when everything is ready for vision navigation.
	 */
	virtual void visionNavigationReady(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when vision navigation is unavailable.
	 */
	virtual void visionNavigationUnavailable(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the wind status changed.
	 */
	virtual void windStatusChanged(
		::ColibryLite::Messages::WindStatus::Enum msg);

	/**
	 * Sent when the defective motor status changed.
	 */
	virtual void defectiveMotorIdChanged(
		::ColibryLite::Messages::DefectiveMotorId::Enum msg);

	/**
	 * Sent when the defective motor failure changed.
	 */
	virtual void defectiveMotorFailureTypeChanged(
		::ColibryLite::Messages::DefectiveMotorFailureType::Enum msg);

	/**
	 * Sent on IMU vibration level changed.
	 */
	virtual void vibrationLevelChanged(
		::ColibryLite::Messages::ThreeLevelStatus::Enum msg);

	/**
	 * Sent on propeller icing level changed.
	 */
	virtual void propellerIcingLevelChanged(
		::ColibryLite::Messages::ThreeLevelStatus::Enum msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoNotCalibrated(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationXDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationYDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationZDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationAborted(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationFailed(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationRequired(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent on specific magneto calibration state.
	 */
	virtual void magnetoCalibrationAdvised(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when requested to go below minimum altitude.
	 */
	virtual void minAltitudeConstrained(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when exiting `min_altitude_constrained` condition.
	 */
	virtual void minAltitudeNotConstrained(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when the state of defective sensors changed.
	 */
	virtual void defectiveSensorsStateChanged(
		uint32_t msg);

	/**
	 * Sent when the battery state changed.
	 */
	virtual void batteryStateChanged(
		const ::DroneController::Messages::BatteryState &msg);

	/**
	 * Sent when the battery role changed.
	 */
	virtual void batteryRoleChanged(
		const ::DroneController::Messages::BatteryRole &msg);

	/**
	 * Sent when the battery is too hot.
	 */
	virtual void batteryAlertTooHot(
		::DroneController::Messages::BatteryAlert::Enum msg);

	/**
	 * Sent when the battery is too cold.
	 */
	virtual void batteryAlertTooCold(
		::DroneController::Messages::BatteryAlert::Enum msg);

	/**
	 * Sent when the battery health changed.
	 */
	virtual void batteryHealth(
		const ::DroneController::Messages::BatteryHealth &msg);

	/**
	 * Notify ticks of the processing loop. It is only sent if a client
	 * configured it with {set_tick_notification_config}.
	 */
	virtual void tick(
		const ::DroneController::Messages::Tick &msg);

	/**
	 * Sent when motor down control is available.
	 */
	virtual void motorDownControlReady(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when motor down control becomes unavailable.
	 */
	virtual void motorDownControlUnavailable(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when ESC single stall becomes available.
	 */
	virtual void singleStallAvailable(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent when ESC single stall becomes unavailable.
	 */
	virtual void singleStallUnavailable(
		const ::google::protobuf::Empty &msg);

	/**
	 * Sent at startup when all estimators (etc.) are initialized.
	 */
	virtual void initOk(
		const ::DroneController::Messages::InitStatus &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace DroneController
