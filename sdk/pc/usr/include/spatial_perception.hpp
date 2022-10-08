/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#pragma once

#include <libmoser_occupancy_grid.h>
#include <array>

namespace guidance {

class SpatialPerception {
public:
	/* Matrix type used when receiving debugging data for spatial
	 * perception */
	typedef Eigen::Matrix<float, 3, -1, Eigen::RowMajor> PointsVector;

	// TODO const struct moser_occupancy_grid *
	virtual struct moser_occupancy_grid *getOccupancyGrid() const = 0;
	// TODO const struct moser_spherical_map *
	virtual struct moser_spherical_map *getStereoSphericalMap() const = 0;

	virtual void publishMiscDebugData(const PointsVector &nominalTraj,
		const std::array<float, 4> &nominalTrajColor,
		const PointsVector &referenceTraj,
		const std::array<float, 4> &referenceTrajColor) const = 0;
};

} // namespace guidance
