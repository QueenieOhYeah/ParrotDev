/**
 *  Copyright (c) 2020 Parrot Drones SAS
 */

#pragma once

#include <Eigen/Core>

#define INVALID_GEO_COORD 500.f

namespace physics
{
/* C++ binding for coordinates conversion functions (in C). See coordinates.h for details.
 * We assume Geo coordinates will be double, and NED float.
 * The main referential frames involved are the following
 *
 * Geographic = classical geographic frame, spherical coordinates with radius offset (altitude)
 *              latitude north deg, longitude east deg, [altitude above sea level]
 *
 * NED = ground fixed frame, cartesian coordinates, cartesian coordinates
 *       origin: given by first fix of geolocation sensor
 *       axes: x axis = North direction at NED origin
 *             y axis = East direction at NED origin
 *             z axis = Down direction at NED origin
 *
 * Body = drone body fixed frame, cartesian coordinates
 *        origin: drone center of mass
 *        axes: x axis = longitudinal axis toward front (nose)
 *              y axis = lateral axis (rightside as seen from above, z cross x)
 *              z axis = vertical axis of the drone, downward
 *
 * Horizontal = NED frame rotated with Body frame's yaw relatively to NED, cartesian coordinates
 *              origin: same as NED frame
 *              axes: x axis = given by the projection of the Body frame x axis on the
 *                             horizontal (xy) plane of the NED frame, normalized
 *                    y axis = z cross x
 *                    z axis = same as NED
 *
 * NED_start = ground fixed frame, especially used until NED is available, cartesian coordinates
 *             origin: given by take off position
 *             axes: x axis = Horizontal frame x axis at take off
 *                   y axis = Horizontal frame y axis at take off
 *                   z axis = Horizontal frame z axis at take off
 */

class CoordNed3;
class CoordGeo3;

Eigen::Vector2d ned2ToGeo2(const Eigen::Vector2f& ned, const Eigen::Vector2d& nedOrigin);
Eigen::Vector2f geo2ToNed2(const Eigen::Vector2d& geo, const Eigen::Vector2d& nedOrigin);

CoordGeo3 ned3ToGeo3(const Eigen::Vector3f& ned, const Eigen::Vector3d& nedOrigin);
CoordNed3 geo3ToNed3(const Eigen::Vector3d& geo, const Eigen::Vector3d& nedOrigin);

CoordNed3 horizontalToNed3(const Eigen::Vector3f& horizontal, float yaw);

/**
 *  @brief Rotation matrix from the NED frame to the body frame
 */
Eigen::Matrix3f eulerAnglesZyxToRotationMatrix(float roll, float pitch, float yaw);

class CoordGeo3 : public Eigen::Vector3d
{
public:
    using Eigen::Vector3d::Vector3d; // expose Eigen::Vector3d constructors
    using Eigen::Vector3d::Zero;

    template<typename OtherDerived>
    CoordGeo3& operator=(const Eigen::MatrixBase<OtherDerived>& other)
    {
        this->Eigen::Vector3d::operator=(other);
        return *this;
    }

    double distance(const CoordGeo3& other) const;
    CoordNed3 toNed(const CoordGeo3& nedOrigin) const;
    double latitude() const;
    double longitude() const;
    double altitude() const;

    void setLatitude(double latitudeNorthDeg);
    void setLongitude(double longitudeEastDeg);
    void setAltitude(double altitudeAsl);
    bool operator==(const CoordGeo3& other) const;
    bool isValid() const;
    static CoordGeo3 invalid();
};

class CoordNed3 : public Eigen::Vector3f
{
public:
    using Eigen::Vector3f::Vector3f; // expose Eigen::Vector3f constructors
    using Eigen::Vector3f::Zero;

    template<typename OtherDerived>
    CoordNed3& operator=(const Eigen::MatrixBase<OtherDerived>& other)
    {
        this->Eigen::Vector3f::operator=(other);
        return *this;
    }

    /** @brief convert NED coordinate to horizontal frame
     *  @param yaw drone yaw [rad]
     */
    Eigen::Vector3f toHorizontal(float yaw);

    CoordGeo3 toGeo(const CoordGeo3& nedOrigin) const;
    bool operator==(const CoordNed3& other) const;

    float x() const;
    float y() const;
    float z() const;

    void setX(float n);
    void setY(float e);
    void setZ(float d);
};
} // namespace physics
