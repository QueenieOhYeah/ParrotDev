/**
 *  @brief Get air density
 *
 *  Copyright (c) 2020 Parrot Drones SAS
 */

#pragma once
namespace physics
{
class AirDensity
{
public:
    AirDensity();
    ~AirDensity();
    /**
     * @brief Compute the air density at the specified atmospheric pressure
     * @param[in] pressure in [Pa]
     * @return Air density value in [kg/m^3]
     */
    static float computeAirDensity(float pressure);
};
} // namespace physics
