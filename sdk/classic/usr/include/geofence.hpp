/**
 * Copyright (C) 2021 Parrot Drones SAS
 */

#pragma once

#include <geofence/i_geofence_angle.hpp>
#include <guidance_types.hpp>
#include <parrot-physics/coordinates.h>

namespace guidance {

class Geofence {
public:
	/*
	 * @brief set the center of the goefence cylinder
	 * @detail Geofence won't saturate pcmd unless the center is set
	 *
	 * @param geofenceCenter geographic coordinate of the cylinder center
	 */
	virtual void setGeofenceCenter(const coord_geo &geofenceCenter) = 0;

	/**
	 * @brief Set geofence radius [m] (>0)
	 *
	 * @param radius Geofence radius
	 */
	virtual void setGeofenceRadius(float radius) = 0;

	/**
	 * @brief Set geofence max altitude [m] (>0)
	 *
	 * @param height Geofence max Altitude
	 */
	virtual void setGeofenceHeight(float height) = 0;

	/**
	 * @brief Enable/disable geofence limitation
	 *
	 * @param enable True to enable geofence limitation
	 */
	virtual void enableGeofence(bool enable) = 0;

	/*
	 * @brief publish current state to connected peers
	 */
	virtual void publishCurrentState() = 0;

	/*
	 * @brief Saturate pcmds to keep the drone inside
	 *        geofence boundaries
	 * @detail Geofence won't saturate pcmd unless the center is set
	 *
	 * @param pcmdsNom nominal pcmd
	 * @param pcmdsOutput pcmd that have been saturated
	 */
	virtual void process(const guidance::PilotingCommands &pcmdsNom,
		guidance::PilotingCommands &pcmdsOutput) = 0;

	/**
	 * @brief return True if the drone has reached the geofence horizontal
	 * limit
	 */
	virtual bool isGeofenceHorizontalLimitReached() const = 0;

	/**
	 * @brief return True if the drone has reached the geofence vertical
	 * limit
	 */
	virtual bool isGeofenceVerticalLimitReached() const = 0;

	/**
	 * @brief return True if the geofence center has been setted.
	 */
	virtual bool isGeofenceCenterSet() const = 0;

	/**
	 * @brief return True if the geofence is enabled
	 */
	virtual bool isGeofenceEnabled() const = 0;

	/**
	 * @brief return the geofence center position
	 */
	virtual const coord_geo &getGeofenceCenter() const = 0;

	/**
	 * @brief return the geofence radius
	 */
	virtual float getGeofenceRadius() const = 0;

	/**
	 * @brief return the geofence altitude
	 */
	virtual float getGeofenceAltitude() const = 0;

	/**
	 * @brief Set geofence operating mode
	 *
	 * @param isOaEnabled True if the obstacle avoidance is enabled.
	 */
	virtual void setMode(bool isOaEnabled) = 0;

	/**
	 * @brief Geofence destructor
	 */
	virtual ~Geofence() {}
};

} // namespace guidance
