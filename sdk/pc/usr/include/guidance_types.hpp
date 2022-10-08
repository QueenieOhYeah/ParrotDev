/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#pragma once

#include <Eigen/Core>

#define COST_COMPONENTS_MAX 10

/* Data structures common to guidance libraries to standardize data exchange */

namespace guidance {

enum Axis { X = 0, Y, Z };

/**
 * @brief Guidance vector bases
 * @details https://developer.parrot.com/docs/airsdk/glossary.html
 */
enum class VectorBasis { NED, NED_START, BODY, HORIZ };

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Container for a 3D position, a 3D velocity and a 3D acceleration
 */
struct PositionTrajectoryPoint {
	Eigen::Vector3f position;
	Eigen::Vector3f velocity;
	Eigen::Vector3f acceleration;

	PositionTrajectoryPoint();

	PositionTrajectoryPoint(const Eigen::Vector3f &position,
		const Eigen::Vector3f &velocity,
		const Eigen::Vector3f &acceleration);

	/**
	 * @brief Convert the position trajectory point relatively to
	 * the global frame into a position trajectory point relatively to the
	 * local frame.
	 */
	PositionTrajectoryPoint globalToLocal(float yawOffsetNedStartToNed,
		const Eigen::Vector2f &positionOffsetLocalToGlobal) const;

	/**
	 * @brief Convert the position trajectory point relatively to
	 * the local frame into a position trajectory point relatively to the
	 * global frame.
	 */
	PositionTrajectoryPoint localToGlobal(float yawOffsetNedStartToNed,
		const Eigen::Vector2f &positionOffsetLocalToGlobal) const;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Container for ZYX Euler angles
 */
struct EulerAnglesZyx {
	/* Yaw - Rotation angle on the z axis (yaw/pan axis) [rad] */
	float yaw;
	/* Pitch - Rotation angle on the y axis (pitch/tilt axis) [rad] */
	float pitch;
	/*  Roll - Rotation angle on the x axis (roll axis) [rad] */
	float roll;

	/**
	 * @brief Default constructor
	 */
	EulerAnglesZyx();

	/**
	 * @brief Constructor
	 */
	EulerAnglesZyx(float yaw, float pitch, float roll);

	/**
	 * @brief Convert Euler angles relatively to the NED vector basis into
	 * Euler angles relatively to the NED-start vector basis
	 * @details WARNING The yaw of the output Euler angles in NED start is
	 * wrapped in ]-pi, pi]
	 */
	EulerAnglesZyx nedToNedStart(float yawOffsetNedStartToNed) const;

	/**
	 * @brief Convert Euler angles relatively to the NED-start vector basis
	 * into Euler angles relatively to the NED vector basis
	 * @details WARNING The yaw of the output Euler angles in NED is wrapped
	 * in ]-pi, pi]
	 */
	EulerAnglesZyx nedStartToNed(float yawOffsetNedStartToNed) const;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Container for guidance user debug data
 */
struct GuidanceFdrLiteData {
	/* Counter of the solver cost function evaluations (iterations) */
	unsigned int solverItCount;
	/* Counter of numerical errors occurred between two updates */
	unsigned int numericalErrorCount;
	/* Obstacle avoidance algorithm cost components */
	float costComponents[COST_COMPONENTS_MAX];

	GuidanceFdrLiteData()
	{
		setZero();
	}

	/**
	 * @brief Reset all values to zero
	 */
	void setZero()
	{
		solverItCount = 0;
		numericalErrorCount = 0;
		for (float &c : costComponents)
			c = 0.f;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Container for manual piloting command
 */
struct PilotingCommands {
	/* Roll angle (x axis of Euler angles ZYX) in NED [rad] */
	float rollAngleNed;
	/* Pitch angle (y axis of Euler angles ZYX) in NED [rad] */
	float pitchAngleNed;
	/* Yaw angular velocity (z axis of Euler angles ZYX) in NED [rad/s] */
	float yawRateNed;
	/* Vertical velocity in NED [m/s] */
	float verticalVelocityNed;

	PilotingCommands();
	PilotingCommands(float rollAngleNed,
		float pitchAngleNed,
		float yawRateNed,
		float verticalVelocityNed);
	void clear();
};

} /* namespace guidance */
