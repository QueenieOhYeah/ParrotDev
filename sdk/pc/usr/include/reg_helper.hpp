/**
 * Copyright (C) 2020 Parrot Drones SAS
 */

#ifndef REG_HELPER_HPP
#define REG_HELPER_HPP

#include <Eigen/Core>
#include <guidance_types.hpp>
#include <libtelemetry.hpp>
#include <parrot-physics/coordinates.h>
#include <libquaternion.h>

#include <array>
#include <string>
#include <vector>

namespace guidance {

/**
 * @brief Register Eigen::Vector2f into telemetry
 * @details Suffixes are "x, y".
 */
template <typename TLM>
inline void regTlmVar(TLM *tlm, Eigen::Vector2f &var, const std::string &name)
{
	tlm->reg(var(0), name + ".x");
	tlm->reg(var(1), name + ".y");
}

/**
 * @brief Register Eigen::Vector3f into telemetry
 * @details Suffixes are "x, y, z".
 */
template <typename TLM>
inline void regTlmVar(TLM *tlm, Eigen::Vector3f &var, const std::string &name)
{
	tlm->reg(var(0), name + ".x");
	tlm->reg(var(1), name + ".y");
	tlm->reg(var(2), name + ".z");
}

/**
 * @brief Register Eigen::Vector3f into telemetry
 * @details Suffixes are "x, y, z".
 */
template <typename TLM>
inline void
regTlmVar(TLM *tlm, const Eigen::Vector3f &var, const std::string &name)
{
	tlm->reg(var(0), name + ".x");
	tlm->reg(var(1), name + ".y");
	tlm->reg(var(2), name + ".z");
}

/**
 * @brief Register libquaternion's quaternion into telemetry
 * @details Suffixes are "w, x, y, z"
 */
template <typename TLM>
inline void regTlmVar(TLM *tlm,
	quaternion &var,
	const std::string &name,
	const std::string &separator = ".")
{
	tlm->reg(var.w, name + separator + "w");
	tlm->reg(var.x, name + separator + "x");
	tlm->reg(var.y, name + separator + "y");
	tlm->reg(var.z, name + separator + "z");
}

/**
 * @brief Register libparrot-physics' coord_geo into telemetry
 * @details Suffixes are "latitude, longitude".
 */
template <typename TLM>
inline void regTlmVar(TLM *tlm, coord_geo &var, const std::string &name)
{
	tlm->reg(var.lat_north_deg, name + ".latitude_north_deg");
	tlm->reg(var.long_east_deg, name + ".longitude_east_deg");
}

/**
 * @brief Register EulerAnglesZyx into telemetry
 * @details Suffixes are "yaw, pitch, roll"
 */
template <typename TLM>
inline void regTlmVar(TLM *tlm,
	EulerAnglesZyx &var,
	const std::string &name,
	const std::string &separator = ".")
{
	tlm->reg(var.yaw, name + separator + "yaw");
	tlm->reg(var.pitch, name + separator + "pitch");
	tlm->reg(var.roll, name + separator + "roll");
}

/**
 * @brief Register PositionTrajectoryPoint into telemetry
 * @details Suffixes are "position, velocity, acceleration"
 */
template <typename TLM>
inline void
regTlmVar(TLM *tlm, PositionTrajectoryPoint &var, const std::string &name)
{
	regTlmVar(tlm, var.position, name + ".position");
	regTlmVar(tlm, var.velocity, name + ".velocity");
	regTlmVar(tlm, var.acceleration, name + ".acceleration");
}

/**
 * @brief Register PositionTrajectoryPoint into telemetry
 * @details Suffixes are "position, velocity, acceleration"
 */
template <typename TLM>
inline void
regTlmVar(TLM *tlm, const PositionTrajectoryPoint &var, const std::string &name)
{
	regTlmVar(tlm, var.position, name + ".position");
	regTlmVar(tlm, var.velocity, name + ".velocity");
	regTlmVar(tlm, var.acceleration, name + ".acceleration");
}

/**
 * @brief Register PositionTrajectoryPoint into telemetry
 * @details Suffixes are "position, velocity, acceleration"
 */
template <typename TLM>
inline void regTlmVar(TLM *tlm, PilotingCommands &var, const std::string &name)
{
	tlm->reg(var.rollAngleNed, name + ".roll");
	tlm->reg(var.pitchAngleNed, name + ".pitch");
	tlm->reg(var.yawRateNed, name + ".yaw_rate");
	tlm->reg(var.verticalVelocityNed, name + ".vertical_velocity");
}
} // namespace guidance

#endif // REG_HELPER_HPP
