/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/descent.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace Descent {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Descent.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::Descent::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Descent::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	int empty(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Descent.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::Descent::Messages::Command &arg);

	virtual void empty(
		const ::google::protobuf::Empty &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Descent.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::Descent::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Descent::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Descent has been completed successfully
	 */
	int done(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Descent has been aborted
	 */
	int aborted(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Descent.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::Descent::Messages::Event &arg);

	/**
	 * Descent has been completed successfully
	 */
	virtual void done(
		const ::google::protobuf::Empty &msg);

	/**
	 * Descent has been aborted
	 */
	virtual void aborted(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace Descent
} // namespace Guidance
