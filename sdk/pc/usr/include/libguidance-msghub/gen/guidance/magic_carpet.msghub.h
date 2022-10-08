/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/magic_carpet.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace MagicCarpet {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.MagicCarpet.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::MagicCarpet::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::MagicCarpet::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Perform given trajectory
	 */
	int setTrajectory(
		const ::Guidance::MagicCarpet::Messages::Trajectory &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Unused
	 */
	int setForceHeading(
		const ::Guidance::MagicCarpet::Messages::ForceHeading &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.MagicCarpet.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::MagicCarpet::Messages::Command &arg);

	/**
	 * Perform given trajectory
	 */
	virtual void setTrajectory(
		const ::Guidance::MagicCarpet::Messages::Trajectory &msg);

	/**
	 * Unused
	 */
	virtual void setForceHeading(
		const ::Guidance::MagicCarpet::Messages::ForceHeading &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.MagicCarpet.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::MagicCarpet::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::MagicCarpet::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	int empty(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.MagicCarpet.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::MagicCarpet::Messages::Event &arg);

	virtual void empty(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace MagicCarpet
} // namespace Guidance
