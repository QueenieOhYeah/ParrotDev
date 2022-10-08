/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/ascent.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace Ascent {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Ascent.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::Ascent::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Ascent::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	int empty(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Ascent.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::Ascent::Messages::Command &arg);

	virtual void empty(
		const ::google::protobuf::Empty &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.Ascent.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::Ascent::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::Ascent::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Ascent is completed.
	 */
	int done(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Ascent is completed and drone is immobile
	 */
	int doneWithImmobility(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Ascent is completed and drone is not immobile
	 */
	int doneWithoutImmobility(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.Ascent.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::Ascent::Messages::Event &arg);

	/**
	 * Ascent is completed.
	 */
	virtual void done(
		const ::google::protobuf::Empty &msg);

	/**
	 * Ascent is completed and drone is immobile
	 */
	virtual void doneWithImmobility(
		const ::google::protobuf::Empty &msg);

	/**
	 * Ascent is completed and drone is not immobile
	 */
	virtual void doneWithoutImmobility(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace Ascent
} // namespace Guidance
