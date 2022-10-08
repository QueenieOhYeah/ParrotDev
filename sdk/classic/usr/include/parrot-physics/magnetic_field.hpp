/**
 *  Copyright (c) 2020 Parrot Drones SAS
 */

#pragma once

#include <stdint.h>

namespace physics
{
/**
 * @brief This class allows to access to local Earth magnetic field Inclination, Declination and
 *        Norm
 */
class MagneticField
{
public:
    /**
     * Return the value issued from the bilinear interpolation of a given table
     */
    template<typename T>
    static float getFromTable(const float longitudeDeg, const float latitudeDeg, const T* table);

    /**
     * Return the magnetic inclination, in degrees.
     */
    static float getInclination(const float longitudeDeg, const float latitudeDeg);

    /**
     * Return the magnetic declination, in degrees.
     */
    static float getDeclination(const float longitudeDeg, const float latitudeDeg);

    /**
     * Return the magnetic norm, in mG.
     */
    static float getMagneticEarthNorm(const float longitudeDeg, const float latitudeDeg);

protected:
    // The number of steps for the latitude.
    static const int latitudeSteps = 179;
    // The number of steps for the longitude.
    static const int longitudeSteps = 360;
    // The array containing the magnetic inclination at the different locations.
    static const int8_t inclination[latitudeSteps][longitudeSteps];
    // The array containing the magnetic declination at the different locations.
    static const int16_t declination[latitudeSteps][longitudeSteps];
    // The array containing the magnetic field norm at different locations.
    static const int16_t norm[latitudeSteps][longitudeSteps];
};

} // namespace physics
