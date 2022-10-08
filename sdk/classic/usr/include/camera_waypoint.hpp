/*
 * @file
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#pragma once

#include "view.hpp"
#include "viewmode.hpp"

#include <flightplan/flightplan.pb.h>
#include <guidance_types.hpp>
#include <parrot-physics/coordinates.hpp>

#include <Eigen/Dense>
#include <memory>

namespace flightplan
{
/**
 * @brief Camera waypoint class for flight plans
 * @details Waypoint containing
 *          - A View to join (camera position, attitude and zoom factor)
 *          - A camera behavior to adopt while joining the waypoint
 *          - A speed reference to respect while joining the waypoint
 *          - A type of validation (specifying the criterion to validate the waypoint)
 *          - A validation radius
 *
 *          Derived from the protobuf message Waypoint, see its definition for more details
 */
class CameraWaypoint : public ::Flightplan::Messages::Waypoint
{
public:
    typedef ::Flightplan::Enums::ValidationType::Enum ValidationType;
    /**
     * @brief Constructor
     */
    CameraWaypoint(const View& view,
                   const ViewMode& viewMode,
                   float speed,
                   const ValidationType& validationType,
                   float validationRadius);

    /**
     * @brief Constructor from protobuf
     */
    CameraWaypoint(const ::Flightplan::Messages::Waypoint& wp_pb);

    /**
     * @brief Default destructor
     */
    ~CameraWaypoint();

    /**
     * @brief Return the geographic coordinates of the waypoint
     */
    physics::CoordGeo3 getPositionGeo() const; // TODO? overload with a NED origin argument?

    // TODO: return a coordNed, NaN coords if could not generate NED?
    // TODO: remove version with reference?
    /**
     * @brief Set the NED coordinates of the waypoint, when possible
     * @param nedOriginPositionGeo Geographic coordinates of the NED frame origin
     * @return nullptr if no NED coordinate is available/computable
     *         unique_ptr to the coordinate otherwise
     */
    std::unique_ptr<physics::CoordNed3> getPositionNed() const;
    std::unique_ptr<physics::CoordNed3> getPositionNed(
      const physics::CoordGeo3* nedOriginPositionGeo) const;
    std::unique_ptr<physics::CoordNed3> getPositionNed(
      const physics::CoordGeo3& nedOriginPositionGeo) const;

    /**
     * @brief Return the validation type of the waypoint
     */
    ValidationType getValidationType() const;

    /**
     * @brief Return the name of the validation type of the waypoint
     */
    std::string getValidationTypeName() const;

    /**
     * @brief Return the validation radius of the waypoint
     */
    float getValidationRadius() const;

    /**
     * @brief Return the view on the waypoint
     */
    const View& getView() const;

    /**
     * @brief Return the view mode to follow while joining the waypoint
     */
    const ViewMode& getViewMode() const;

    /**
     * @brief Return the speed reference while joining the waypoint
     */
    float getSpeed() const;

    // TODO: overload of isOverlapped with ned origin argument to compare a geo with a ned waypoint?
    /**
     * @brief Return true if the distance between the center of the waypoint and the input waypoint
     *        is below a given threshold
     */
    bool isOverlapped(const CameraWaypoint* otherWaypoint, float threshold) const;

    /**
     * @brief Return true if at least one coordinate (currently geographic and NED) is valid
     */
    bool isValid() const;
}; // class CameraWaypoint

} // namespace flightplan
