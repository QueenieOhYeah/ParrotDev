/*
 * @file
 * @copyright Copyright (c) 2020 Parrot Drones SAS
 */

#pragma once

#include <flightplan/flightplan.pb.h>
#include <parrot-physics/coordinates.hpp>

namespace flightplan
{
/**
 * @brief Camera 3D orientation and zoom factor behaviors to adopt while joining a waypoint
 * @details Derived from the protobuf message ViewMode, see its definition for more details
 */
class ViewMode : public ::Flightplan::Messages::ViewMode
{
public:
    typedef ::Flightplan::Enums::ViewMode::Yaw::Enum Yaw;
    typedef ::Flightplan::Enums::ViewMode::Pitch::Enum Pitch;
    typedef ::Flightplan::Enums::ViewMode::Roll::Enum Roll;
    typedef ::Flightplan::Enums::ViewMode::Zoom::Enum Zoom;

    ViewMode();

    ViewMode(const ::Flightplan::Messages::ViewMode& viewMode);

    ViewMode(Yaw yawMode,
             Pitch pitchMode,
             Roll rollMode,
             Zoom zoomMode,
             const physics::CoordGeo3& poiGeo);

    physics::CoordGeo3 getPoiPositionGeo() const; // TODO NED getter + handle origin/no origin?
};
} // namespace flightplan
