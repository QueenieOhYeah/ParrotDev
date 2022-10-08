/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/hand_grab.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace HandGrab {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.HandGrab.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::HandGrab::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::HandGrab::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	int empty(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.HandGrab.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::HandGrab::Messages::Command &arg);

	virtual void empty(
		const ::google::protobuf::Empty &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.HandGrab.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::HandGrab::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::HandGrab::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Request to go to hand point completed.
	 */
	int done(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Request to go to hand point aborted.
	 */
	int abort(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.HandGrab.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::HandGrab::Messages::Event &arg);

	/**
	 * Request to go to hand point completed.
	 */
	virtual void done(
		const ::google::protobuf::Empty &msg);

	/**
	 * Request to go to hand point aborted.
	 */
	virtual void abort(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace HandGrab
} // namespace Guidance
