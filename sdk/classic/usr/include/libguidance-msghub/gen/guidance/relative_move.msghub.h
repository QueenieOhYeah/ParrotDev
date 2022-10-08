/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/relative_move.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace RelativeMove {
namespace Messages {
namespace msghub {

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.RelativeMove.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::RelativeMove::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::RelativeMove::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Send effective displacement when done and is last_move
	 */
	int done(
		const ::Guidance::RelativeMove::Messages::Displacement &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Send effective displacement when done and is not last_move
	 */
	int moveValidated(
		const ::Guidance::RelativeMove::Messages::Displacement &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Drone blocked (obstacle, strong front wind, ...)
	 */
	int stuck(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.RelativeMove.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::RelativeMove::Messages::Event &arg);

	/**
	 * Send effective displacement when done and is last_move
	 */
	virtual void done(
		const ::Guidance::RelativeMove::Messages::Displacement &msg);

	/**
	 * Send effective displacement when done and is not last_move
	 */
	virtual void moveValidated(
		const ::Guidance::RelativeMove::Messages::Displacement &msg);

	/**
	 * Drone blocked (obstacle, strong front wind, ...)
	 */
	virtual void stuck(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace RelativeMove
} // namespace Guidance
