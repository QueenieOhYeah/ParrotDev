/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/guidance.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set guidance mode.
	 */
	int setMode(
		const ::Guidance::Messages::SetMode &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set piloting commands.
	 */
	int setPcmd(
		const ::Guidance::Messages::Pcmd &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Load mission guidance modes.
	 * TODO: use uid string directly
	 */
	int loadMission(
		const ::Guidance::Messages::Mission &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Unload mission guidance modes.
	 * TODO: use uid string directly
	 */
	int unloadMission(
		const ::Guidance::Messages::Mission &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Enable or disable obstacle avoidance.
	 */
	int setObstacleAvoidance(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Enable or disable geofence.
	 */
	int setGeofence(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set geofence center.
	 */
	int setGeofenceCenter(
		const ::Guidance::Messages::GeofenceCenter &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::Messages::Command &arg);

	/**
	 * Set guidance mode.
	 */
	virtual void setMode(
		const ::Guidance::Messages::SetMode &msg);

	/**
	 * Set piloting commands.
	 */
	virtual void setPcmd(
		const ::Guidance::Messages::Pcmd &msg);

	/**
	 * Load mission guidance modes.
	 * TODO: use uid string directly
	 */
	virtual void loadMission(
		const ::Guidance::Messages::Mission &msg);

	/**
	 * Unload mission guidance modes.
	 * TODO: use uid string directly
	 */
	virtual void unloadMission(
		const ::Guidance::Messages::Mission &msg);

	/**
	 * Enable or disable obstacle avoidance.
	 */
	virtual void setObstacleAvoidance(
		bool msg);

	/**
	 * Enable or disable geofence.
	 */
	virtual void setGeofence(
		bool msg);

	/**
	 * Set geofence center.
	 */
	virtual void setGeofenceCenter(
		const ::Guidance::Messages::GeofenceCenter &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Send a list of loaded modes after init.
	 */
	int initOk(
		const ::Guidance::Messages::ModeList &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Acknowledgment of `set_mode` command.
	 */
	int modeChanged(
		const ::Guidance::Messages::ModeChanged &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Error message returned by a guidance mode via `guidance::Mode::setError`.
	 */
	int error(
		const ::Guidance::Messages::Error &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * List of loaded modes changed.
	 */
	int modeListChanged(
		const ::Guidance::Messages::ModeList &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Distance from nominal trajectory exceeds threshold.
	 */
	int highTrajectoryDeviation(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Drone is stuck by a presumably large obstacle.
	 */
	int obstacleAvoidanceStuck(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Obstacle avoidance fails to compute trajectories.
	 */
	int obstacleAvoidanceFailure(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Drone is moving in blind direction.
	 */
	int obstacleAvoidanceBlindMotionDirection(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Request to go to fixed point completed.
	 */
	int gotofixDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Request to go to freeze point completed.
	 */
	int gotofreezeDone(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Indicate if the drone has reached the geofence horizontal limit
	 */
	int horizontalGeofenceReached(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Indicate if the drone has reached the geofence vertical limit
	 */
	int verticalGeofenceReached(
		bool arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Indicate that the center of the geofence changed.
	 */
	int geofenceCenterChanged(
		const ::Guidance::Messages::GeofenceCenter &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::Messages::Event &arg);

	/**
	 * Send a list of loaded modes after init.
	 */
	virtual void initOk(
		const ::Guidance::Messages::ModeList &msg);

	/**
	 * Acknowledgment of `set_mode` command.
	 */
	virtual void modeChanged(
		const ::Guidance::Messages::ModeChanged &msg);

	/**
	 * Error message returned by a guidance mode via `guidance::Mode::setError`.
	 */
	virtual void error(
		const ::Guidance::Messages::Error &msg);

	/**
	 * List of loaded modes changed.
	 */
	virtual void modeListChanged(
		const ::Guidance::Messages::ModeList &msg);

	/**
	 * Distance from nominal trajectory exceeds threshold.
	 */
	virtual void highTrajectoryDeviation(
		bool msg);

	/**
	 * Drone is stuck by a presumably large obstacle.
	 */
	virtual void obstacleAvoidanceStuck(
		bool msg);

	/**
	 * Obstacle avoidance fails to compute trajectories.
	 */
	virtual void obstacleAvoidanceFailure(
		bool msg);

	/**
	 * Drone is moving in blind direction.
	 */
	virtual void obstacleAvoidanceBlindMotionDirection(
		bool msg);

	/**
	 * Request to go to fixed point completed.
	 */
	virtual void gotofixDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Request to go to freeze point completed.
	 */
	virtual void gotofreezeDone(
		const ::google::protobuf::Empty &msg);

	/**
	 * Indicate if the drone has reached the geofence horizontal limit
	 */
	virtual void horizontalGeofenceReached(
		bool msg);

	/**
	 * Indicate if the drone has reached the geofence vertical limit
	 */
	virtual void verticalGeofenceReached(
		bool msg);

	/**
	 * Indicate that the center of the geofence changed.
	 */
	virtual void geofenceCenterChanged(
		const ::Guidance::Messages::GeofenceCenter &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace Guidance
