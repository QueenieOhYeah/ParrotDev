/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "samples/hello/cv-service/messages.pb.h"

namespace pomp {
	class Conn;
}

namespace samples {
namespace hello {
namespace cv_service {
namespace messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "samples.hello.cv_service.messages.Command";

	CommandSender();

	virtual void beforeSend(samples::hello::cv_service::messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const samples::hello::cv_service::messages::Command &msg,
		pomp::Connection *conn=nullptr);

	int processingStart(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	int processingStop(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "samples.hello.cv_service.messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const samples::hello::cv_service::messages::Command &arg);

	virtual void processingStart(
		const ::google::protobuf::Empty &msg);

	virtual void processingStop(
		const ::google::protobuf::Empty &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "samples.hello.cv_service.messages.Event";

	EventSender();

	virtual void beforeSend(samples::hello::cv_service::messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const samples::hello::cv_service::messages::Event &msg,
		pomp::Connection *conn=nullptr);

	int close(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	int far(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	int depthMean(
		float arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "samples.hello.cv_service.messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const samples::hello::cv_service::messages::Event &arg);

	virtual void close(
		const ::google::protobuf::Empty &msg);

	virtual void far(
		const ::google::protobuf::Empty &msg);

	virtual void depthMean(
		float msg);

};

} // namespace msghub
} // namespace messages
} // namespace cv_service
} // namespace hello
} // namespace samples
