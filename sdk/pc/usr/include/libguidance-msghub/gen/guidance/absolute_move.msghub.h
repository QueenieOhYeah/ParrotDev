/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/absolute_move.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace AbsoluteMove {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.AbsoluteMove.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::AbsoluteMove::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::AbsoluteMove::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * New destination
	 */
	int setNewDestination(
		const ::Guidance::AbsoluteMove::Messages::Destination &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.AbsoluteMove.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::AbsoluteMove::Messages::Command &arg);

	/**
	 * New destination
	 */
	virtual void setNewDestination(
		const ::Guidance::AbsoluteMove::Messages::Destination &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.AbsoluteMove.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::AbsoluteMove::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::AbsoluteMove::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Send movement completed
	 */
	int done(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.AbsoluteMove.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::AbsoluteMove::Messages::Event &arg);

	/**
	 * Send movement completed
	 */
	virtual void done(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace AbsoluteMove
} // namespace Guidance
