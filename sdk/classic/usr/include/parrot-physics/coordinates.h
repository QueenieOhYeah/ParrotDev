/**
 * @file
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef LIBPARROT_PHYSICS_COORDINATES
#define LIBPARROT_PHYSICS_COORDINATES

#include <parrot-math/core.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* IMPORTANT NOTE - BEWARE */
/* The following functions DO NOT CHECK FOR NULL POINTERS INPUTS
 * The user of these functions is responsible for checking the relevance of the
 * input variables */

/* FIXME: use arrays for NED coordinates arguments rather than one variable per dimension */

/**
 * @brief Container for 2D geographic coordinates
 */
struct coord_geo
{
    double lat_north_deg; /* Latitude (North) [degree] */
    double long_east_deg; /* Longitude (East) [degree] */
};

/**
 * @brief Convert geographic coordinates into North-East (NED xy) coordinates
 * @details IMPORTANT NOTE - BEWARE
 *          On poles, the wrapping of the longitude in ]-180°, 180°] can lead
 *          to discontinuous NED coordinates
 *
 *          Edge cases
 *          Any input has NaN or Inf values -> Undefined behavior
 * @param geo Geographic coordinates to convert
 * @param ned_origin Geographic coordinates of the origin of the NED frame
 * @param nedx Updated with the corresponding x coordinate in NED
 * @param nedy Updated with the corresponding y coordinate in NED
 */
void coord_geo_to_ned_f(const struct coord_geo* geo,
                        const struct coord_geo* ned_origin,
                        float* nedx,
                        float* nedy);
void coord_geo_to_ned_d(const struct coord_geo* geo,
                        const struct coord_geo* ned_origin,
                        double* nedx,
                        double* nedy);

/**
 * @brief Convert North-East (NED xy) coordinates into geographic coordinates
 * @details IMPORTANT NOTE - BEWARE
 *          Longitude is singular on the poles (gimbal lock)
 *          This function is inaccurate for NED frames origins close to the
 *          poles
 *
 *          Edge cases
 *          Any input has NaN or Inf values -> Undefined behavior
 *          NED origin is on a pole -> return NaN for the longitude coordinate
 * @param nedx x coordinate in NED to convert
 * @param nedy y coordinate in NED to convert
 * @param ned_origin Geographic coordinates of the origin of the NED frame
 * @param geo Updated with the corresponding geographic coordinates
 */
void coord_ned_to_geo_f(const float nedx,
                        const float nedy,
                        const struct coord_geo* ned_origin,
                        struct coord_geo* geo);
void coord_ned_to_geo_d(const double nedx,
                        const double nedy,
                        const struct coord_geo* ned_origin,
                        struct coord_geo* geo);

/**
 * @brief Compute geodetic distance between two geographic coordinates [m]
 * @details Any input has NaN or Inf values -> Undefined behavior
 * @param geo_a Geographic coordinates to measure
 * @param geo_b Geographic coordinates to measure
 * @return geodetic distance between the input coordinates [m]
 */
double coord_geo_distance(const struct coord_geo* geo_a, const struct coord_geo* geo_b);

/**
 * @brief Convert Down (NED z) coordinate into altitude
 * @details Any input has NaN or Inf values -> Undefined behavior
 * @param nedz nedz z coordinate in NED to convert
 * @param ned_origin_altitude NED origin altitude (reference altitude)
 * @param altitude Updated with the corresponding altitude
 */
void coord_ned_to_altitude_f(const float nedz, const double ned_origin_altitude, double* altitude);
void coord_ned_to_altitude_d(const double nedz, const double ned_origin_altitude, double* altitude);

/**
 * @brief Convert altitude into Down (NED z) coordinate
 * @details Any input has NaN or Inf values -> Undefined behavior
 * @param altitude Altitude to to convert
 * @param ned_origin_altitude NED origin altitude (reference altitude)
 * @param nedz Updated with the corresponding z coordinate in NED
 */
void coord_altitude_to_ned_f(const double altitude, const double ned_origin_altitude, float* nedz);
void coord_altitude_to_ned_d(const double altitude, const double ned_origin_altitude, double* nedz);

/*
 * Vector basis
 *     * NED: x axis = North direction at first GPS fix position
 *            y axis = East direction at first GPS fix position
 *            z axis = Down direction at first GPS fix position
 *
 *     * NED_start: x axis = arbitrary in the horizontal plane (normal to z axis)
 *                  y axis = given by the cross product of z and x axes' unit vectors
 *                  z axis = NED z axis
 *
 *     * NED is fixed in time, so the estimated drone yaw in this basis can jump in case of
 *       large estimator realignment e.g. due to a precise input measurement.
 *       NED_start has a rotation offset around the z axis relatively to NED. The estimated
 *       drone yaw in this basis does not jump in case of large estimator realignment,
 *       instead, the yaw offset between NED and NED_start jumps in order to ensure the
 *       continuity of the drone yaw estimate in this basis. This yaw offset is constant most
 *       of the time, but can jump during the flight.
 *
 * Frame of reference
 *     * Global: origin = position of first GPS fix
 *               vector basis = NED
 *
 *     * Local: origin = arbitrary horizontal origin, vertical position at take off
 *              vector basis = NED
 *
 *     * Global is fixed in time, so the estimated drone position in this frame of reference
 *       can jump in case of large estimator realignment e.g. due to a precise input
 *       measurement. Local has a x/y horizontal position offset relatively to Global. The
 *       estimated drone position in this frame of reference does not jump in case of large
 *       estimator realignment, instead, the x/y position offset between Global and Local
 *       jumps in order to ensure the continuity of the drone position estimate in this frame
 *       of reference. This horizontal position offset is constant most of the time, but can
 *       jump during the flight.
 */
/* TODO: make Local frame use a NED_start vector basis */

/**
 * @brief Convert a yaw relatively to the NED_start vector basis into a yaw relatively to the NED
 *        vector basis
 * @details "yaw" designates the z-axis angle of the ZYX Euler decomposition of an attitude
 *          yaw_NED = yaw_NED_start + yaw_offset
 *
 *          IMPORTANT NOTE - BEWARE
 *          the output yaw NED is wrapped in ]-pi, pi]
 *
 * @param yaw_ned_start Yaw angle relatively to the NED_start vector basis
 * @param yaw_offset_ned_start_to_ned Yaw angle offset from NED_start to NED vector bases
 * @return Yaw angle relatively to the NED vector basis
 */
float coord_yaw_ned_start_to_yaw_ned_f(const float yaw_ned_start,
                                       const float yaw_offset_ned_start_to_ned);
double coord_yaw_ned_start_to_yaw_ned_d(const double yaw_ned_start,
                                        const double yaw_offset_ned_start_to_ned);

/**
 * @brief Convert a yaw relatively to the NED vector basis into a yaw relatively to the NED_start
 *        vector basis
 * @details "yaw" designates the z-axis angle of the ZYX Euler decomposition of an attitude
 *          yaw_NED_start = yaw_NED - yaw_offset
 *
 *          IMPORTANT NOTE - BEWARE
 *          the output yaw NED_start is wrapped in ]-pi, pi]
 *
 * @param yaw_ned Yaw angle relatively to the NED vector basis
 * @param yaw_offset_ned_start_to_ned Yaw angle offset from NED_start to NED vector bases
 * @return Yaw angle relatively to the NED_start vector basis
 */
float coord_yaw_ned_to_yaw_ned_start_f(const float yaw_ned,
                                       const float yaw_offset_ned_start_to_ned);
double coord_yaw_ned_to_yaw_ned_start_d(const double yaw_ned,
                                        const double yaw_offset_ned_start_to_ned);

/* FIXME: use NED_start vector basis in local frame of reference */

/**
 * @brief Convert a 2D position relatively to the local frame of reference into a position
 *        relatively to the global frame of reference
 * @details position_global = position_local + position_offset
 *          - the conversion does not affect the z-axis, hence the 2D input
 *          - the function is robust to aliasing, i.e. coord_local and coord_global can be the
 *            same variables
 *
 * @param coord_local Position relatively to the local frame of reference
 * @param yaw_offset_ned_start_to_ned Yaw angle offset from NED_start to NED vector bases
 * @param position_offset_local_to_global Position offset from local to global reference frames
 * @param coord_global Updated with the position relatively to the global frame of reference
 */
void coord_position_local_to_position_global_f(const float coord_local[2],
                                               const float yaw_offset_ned_start_to_ned,
                                               const float position_offset_local_to_global[2],
                                               float coord_global[2]);
void coord_position_local_to_position_global_d(const double coord_local[2],
                                               const double yaw_offset_ned_start_to_ned,
                                               const double position_offset_local_to_global[2],
                                               double coord_global[2]);

/**
 * @brief Convert a 2D position relatively to the global frame of reference into a position
 *        relatively to the local frame of reference
 * @details position_local = position_global - position_offset
 *          - the conversion does not affect the z-axis, hence the 2D input
 *          - the function is robust to aliasing, i.e. coord_local and coord_global can be the
 *            same variables
 *
 * @param coord_global Position relatively to the global frame of reference
 * @param yaw_offset_ned_start_to_ned Yaw angle offset from NED_start to NED vector bases
 * @param position_offset_local_to_global Position offset from local to global reference frames
 * @param coord_local Updated with the position relatively to the local frame of reference
 */
void coord_position_global_to_position_local_f(const float coord_global[2],
                                               const float yaw_offset_ned_start_to_ned,
                                               const float position_offset_local_to_global[2],
                                               float coord_local[2]);
void coord_position_global_to_position_local_d(const double coord_global[2],
                                               const double yaw_offset_ned_start_to_ned,
                                               const double position_offset_local_to_global[2],
                                               double coord_local[2]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBPARROT_PHYSICS_COORDINATES */
