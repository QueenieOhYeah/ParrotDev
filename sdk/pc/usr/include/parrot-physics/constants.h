/**
 *  Copyright (c) 2019 Parrot Drones SAS
 */

#pragma once

/** This value can be quite different depending on the point on Earth.
 *  By only keeping two decimals the error might already be significant between
 *  the equator (g = 9.780 m/s²) and the poles (g = 9.832 m/s²).
 *  Thus, keeping 9.81 m/s² should be enough.
 */
#define GRAVITY 9.81f

/* Earth mean radius [m] */
#define R_EARTH 6371000.f

// Standard atmosphere constants
#define ATM_RHO_0 1.225f                 // [kg/m^3] Air density at 1013.25hP and 15°C
#define PRESSURE_SEA_LEVEL 101325.f      // [Pa]
#define ATM_TEMPERATURE_SEA_LEVEL 288.15 // [K]
#define ATM_TEMPERATURE_RATE 0.00649f    // [K/m] up to 11000m high
#define MOLAR_AIR_MASS 0.0289644f        // [kg/mol]
#define SPECIFIC_GAS_CONSTANT 8.3144621  // [J·K-1·mol-1]
