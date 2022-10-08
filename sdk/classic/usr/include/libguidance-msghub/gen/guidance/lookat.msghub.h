/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/lookat.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace LookAt {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.LookAt.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::LookAt::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::LookAt::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set the framing offset of the target in the image.
	 */
	int setFramingOffset(
		const ::Guidance::LookAt::Messages::FramingOffset &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.LookAt.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::LookAt::Messages::Command &arg);

	/**
	 * Set the framing offset of the target in the image.
	 */
	virtual void setFramingOffset(
		const ::Guidance::LookAt::Messages::FramingOffset &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.LookAt.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::LookAt::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::LookAt::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	int empty(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.LookAt.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::LookAt::Messages::Event &arg);

	virtual void empty(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace LookAt
} // namespace Guidance
