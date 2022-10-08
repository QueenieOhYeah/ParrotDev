/**
 *  @brief Compute the angle of a drone from a horizontal speed input or an
 *  horizontal speed from and an angle.
 *
 *  @details The model uses a linear relation between the aerodynamic
 *  coefficient of the drone on X and Y axis, to compute the angle such as
 *  the drone is in equilibrium, or the air speed of a drone for a given angle.
 *
 *  @details Mass drag coefficients apply to the drone body frame, so
 *           Cx is used for pitch and Cy is used for roll
 *
 *  Copyright (c) 2019 Parrot Drones SAS
 */

#pragma once

#include <Eigen/Eigen>

namespace physics
{
namespace aero_model
{
/**
 * @brief Compute absolute speed value at equilibrium for a given tilt angle
 *
 * @param angle Drone angle
 * @param aeroCoef Mass drag coefficient
 * @return Horizontal airspeed
 */
float angleToAbsAirspeed(float angle, const Eigen::Vector2f& aeroCoef);

/**
 * @brief Compute speed values at equilibrium for 2 given angles
 *
 * @param angles: angles(ROLL), angles(PITCH)
 * @param cx Mass drag coefficient for drone X axis
 * @param cy Mass drag coefficient for drone Y axis
 * @return Horizontal airspeed
 */
Eigen::Vector2f angleToAirspeed(const Eigen::Vector2f& angles,
                                const Eigen::Vector2f& cx,
                                const Eigen::Vector2f& cy);

/**
 * @brief Compute absolute tilt angle at equilibrium for a given airspeed
 *
 * @param airspeedHoriz Horizontal drone airspeed
 * @param aeroCoef Mass drag coefficient
 * @return Drone angle
 */
float airspeedToAbsAngle(float airspeedHoriz, const Eigen::Vector2f& aeroCoef);

/**
 * @brief Convert acceleration and airspeed to angle using quadratic model
 *
 * @param accelerationHoriz Horizontal drone acceleration
 * @param airspeedHoriz Horizontal drone airspeed
 * @param cx Mass drag coefficient for drone X axis
 * @param cy Mass drag coefficient for drone Y axis
 * @return Euler angles (roll, pitch)
 */
Eigen::Vector2f accAndAirspeedToAngle(const Eigen::Vector2f& accelerationHoriz,
                                      const Eigen::Vector2f& airspeedHoriz,
                                      const Eigen::Vector2f& cx,
                                      const Eigen::Vector2f& cy);

/**
 * @brief Convert airspeed to angle using quadratic model
 *
 * @param airspeedHoriz Horizontal drone airspeed
 * @param cx Mass drag coefficient for drone X axis
 * @param cy Mass drag coefficient for drone Y axis
 * @return Euler angles (roll, pitch)
 */
Eigen::Vector2f airspeedToAngle(const Eigen::Vector2f& airspeedHoriz,
                                const Eigen::Vector2f& cx,
                                const Eigen::Vector2f& cy);

/**
 * @brief Convert angle and airspeed to acceleration using quadratic model
 *
 * @param eulerAngles Drone angle (roll, pitch)
 * @param cx Mass drag coefficient for drone X axis
 * @param cy Mass drag coefficient for drone Y axis
 * @param airspeed Horizontal drone airspeed
 * @return Horizontal drone acceleration
 */
Eigen::Vector2f angleAndAirspeedToAcc(const Eigen::Vector2f& eulerAngles,
                                      const Eigen::Vector2f& cx,
                                      const Eigen::Vector2f& cy,
                                      const Eigen::Vector2f& airspeed);

/**
 * @brief Compute Acceleration from Airspeed in body using quadratic model
 *
 * @param cx Mass drag coefficient for drone X axis
 * @param cy Mass drag coefficient for drone Y axis
 * @param airspeedBody Drone airspeed in body frame
 * @return Drone acceleration in body frame
 */
Eigen::Vector2f airspeedToAcc(const Eigen::Vector2f& cx,
                              const Eigen::Vector2f& cy,
                              const Eigen::Vector2f& airspeedBody);

} // namespace aero_model
} // namespace physics
