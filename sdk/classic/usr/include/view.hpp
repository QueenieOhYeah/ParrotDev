/*
 * @file
 * @copyright Copyright (c) 2020 Parrot Drones SAS
 */

#pragma once

#include <flightplan/flightplan.pb.h>
#include <guidance_types.hpp>
#include <parrot-physics/coordinates.hpp>

namespace flightplan
{
/**
 * @brief 7D viewpoint: 3D position, 3D orientation, 1D zoom factor
 * @details Derived from the protobuf message View, see its definition for more details
 */
class View : public ::Flightplan::Messages::View
{
public:
    View();

    View(const physics::CoordGeo3& coordGeo);

    View(const physics::CoordNed3& coordNed);

    View(const physics::CoordGeo3& coordGeo,
         const guidance::EulerAnglesZyx& angles,
         float zoomFactor);

    View(const physics::CoordNed3& coordNed,
         const guidance::EulerAnglesZyx& angles,
         float zoomFactor);
};
} // namespace flightplan