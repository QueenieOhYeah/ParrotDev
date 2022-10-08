/*
 * @file
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#pragma once

#include "camera_waypoint.hpp"
#include <flightplan/flightplan.pb.h>
#include <Eigen/Dense>
#include <vector>

namespace flightplan
{
/**
 * @brief Camera flight plan class for flight plans
 * @details 7D flight plan for cinematography consisting in a series of 7D waypoints to join
 *          - 3D positions
 *          - 3D attitudes
 *          - zoom factors
 */
class CameraFlightPlan : public Flightplan::Messages::WaypointPath
{
public:
    /**
     * @brief Default constructor
     */
    CameraFlightPlan();

    /**
     * @brief Constructor from protobuf
     */
    CameraFlightPlan(const ::Flightplan::Messages::WaypointPath& waypointPath);

    /**
     * @brief Return the current amount of waypoints
     */
    std::size_t getWaypointsCount() const;

    /**
     * @brief Return a pointer to the first waypoint, or nullptr if the flight plan is empty
     */
    const CameraWaypoint* getFirstWaypoint() const;

    /**
     * @brief Return a pointer to the last waypoint, or nullptr if the flight plan is empty
     */
    const CameraWaypoint* getLastWaypoint() const;

    /**
     * @brief Return a pointer to the waypoint of specified index, or nullptr if no waypoint is
     *        associated to this index
     */
    const CameraWaypoint* getWaypoint(std::size_t waypointIndex) const;

    /**
     * @brief Add a waypoint to the flight plan
     */
    void addWaypoint(const CameraWaypoint& waypoint);

    /**
     * @brief Returns true if the input index corresponds to the last waypoint
     */
    bool isLastWaypoint(std::size_t waypointIndex) const;

    /**
     * @brief Return true if all waypoints have NED coordinates, false otherwise
     */
    bool areAllWaypointsNed() const;

    /**
     * @brief Return true if all waypoints have valid coordinates, false otherwise
     */
    bool allWaypointsValid() const;

    /*
     * @brief Insert waypoint at index 'index'
     * return index of the inserted waypoint in case of success
     *        -1 in case of invalid index
     */
    int32_t insertWaypoint(int32_t index, const CameraWaypoint& waypoint);

    /**
     * @brief Remove waypoint at index 'index'
     * return index of the removed waypoint in case of success
     *        -1 in case of invalid index
     */
    int32_t removeWaypoint(int32_t index);

    /**
     * @brief Replace waypoint at index 'index' by given waypoint
     * return index of the replaced waypoint in case of success
     *        -1 in case of invalid index
     */
    int32_t replaceWaypoint(int32_t index,
                            const CameraWaypoint& waypoint,
                            bool keepOriginalId = false);
}; // class CameraFlightPlan
} // namespace flightplan
