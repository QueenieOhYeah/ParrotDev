/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/flightplan.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace Flightplan {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Flightplan.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::Flightplan::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Flightplan::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Pause current flightplan, brake and go to fixed point.
	 */
	int pause(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Resume flightplan
	 */
	int resume(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Insert waypoint at given index
	 * The waypoint that formerly had index i will be shifted to i+1.
	 * All subsequent waypoints will be shifted in the same way.
	 */
	int insertWaypoint(
		const ::Guidance::Flightplan::Messages::InsertWaypoint &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Remove waypoint at given index.
	 */
	int removeWaypoint(
		int32_t arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Replace waypoint at given index with another waypoint.
	 */
	int replaceWaypoint(
		const ::Guidance::Flightplan::Messages::ReplaceWaypoint &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Change current waypoint index.
	 */
	int setCurrentIndex(
		uint32_t arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Flightplan.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::Flightplan::Messages::Command &arg);

	/**
	 * Pause current flightplan, brake and go to fixed point.
	 */
	virtual void pause(
		const ::google::protobuf::Empty &msg);

	/**
	 * Resume flightplan
	 */
	virtual void resume(
		const ::google::protobuf::Empty &msg);

	/**
	 * Insert waypoint at given index
	 * The waypoint that formerly had index i will be shifted to i+1.
	 * All subsequent waypoints will be shifted in the same way.
	 */
	virtual void insertWaypoint(
		const ::Guidance::Flightplan::Messages::InsertWaypoint &msg);

	/**
	 * Remove waypoint at given index.
	 */
	virtual void removeWaypoint(
		int32_t msg);

	/**
	 * Replace waypoint at given index with another waypoint.
	 */
	virtual void replaceWaypoint(
		const ::Guidance::Flightplan::Messages::ReplaceWaypoint &msg);

	/**
	 * Change current waypoint index.
	 */
	virtual void setCurrentIndex(
		uint32_t msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Flightplan.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::Flightplan::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Flightplan::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * The waypoint list has been completed.
	 */
	int done(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * A waypoint has been validated.
	 */
	int waypointValidated(
		const ::Guidance::Flightplan::Messages::WaypointValidated &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * A waypoint has been skipped
	 */
	int waypointSkipped(
		const ::Guidance::Flightplan::Messages::WaypointSkipped &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Flightplan modifications have been accepted
	 * return new flightplan
	 */
	int changed(
		const ::Flightplan::Messages::WaypointPath &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Flightplan modifications have been rejected
	 */
	int rejected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * An obstacle was detected.
	 * TODO: is it obsoleted by guidance::obstacle_avoidance_stuck
	 */
	int blockageDetected(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Flightplan.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::Flightplan::Messages::Event &arg);

	/**
	 * The waypoint list has been completed.
	 */
	virtual void done(
		const ::google::protobuf::Empty &msg);

	/**
	 * A waypoint has been validated.
	 */
	virtual void waypointValidated(
		const ::Guidance::Flightplan::Messages::WaypointValidated &msg);

	/**
	 * A waypoint has been skipped
	 */
	virtual void waypointSkipped(
		const ::Guidance::Flightplan::Messages::WaypointSkipped &msg);

	/**
	 * Flightplan modifications have been accepted
	 * return new flightplan
	 */
	virtual void changed(
		const ::Flightplan::Messages::WaypointPath &msg);

	/**
	 * Flightplan modifications have been rejected
	 */
	virtual void rejected(
		const ::google::protobuf::Empty &msg);

	/**
	 * An obstacle was detected.
	 * TODO: is it obsoleted by guidance::obstacle_avoidance_stuck
	 */
	virtual void blockageDetected(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace Flightplan
} // namespace Guidance
