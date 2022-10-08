/**
 * GENERATED FILE, DO NOT EDIT.
 */

#include "samples/hello/cv-service/messages.msghub.h"

namespace samples {
namespace hello {
namespace cv_service {
namespace messages {
namespace msghub {

template<typename T>
inline static T *remove_const(const T &val)
{
	return const_cast<T *>(&val);
}

CommandSender::CommandSender()
	: ::msghub::MessageSender(sServiceName)
{
}

void CommandSender::beforeSend(samples::hello::cv_service::messages::Command &msg)
{
}

int CommandSender::send(
	const samples::hello::cv_service::messages::Command &msg,
	pomp::Connection *conn)
{
	return ::msghub::MessageSender::send(
		static_cast<uint16_t>(msg.id_case()),
		msg,
		conn);
}

int CommandSender::processingStart(
	const ::google::protobuf::Empty &arg,
	pomp::Connection *conn)
{
	samples::hello::cv_service::messages::Command msg;
	msg.set_allocated_processing_start(remove_const(arg));
	beforeSend(msg);
	int res = send(msg, conn);
	msg.release_processing_start();
	return res;
}

int CommandSender::processingStop(
	const ::google::protobuf::Empty &arg,
	pomp::Connection *conn)
{
	samples::hello::cv_service::messages::Command msg;
	msg.set_allocated_processing_stop(remove_const(arg));
	beforeSend(msg);
	int res = send(msg, conn);
	msg.release_processing_stop();
	return res;
}

CommandHandler::CommandHandler()
	: ::msghub::MessageHandler(sServiceName)
{
}

void CommandHandler::handle(
	const ::msghub::Message &msg)
{
	samples::hello::cv_service::messages::Command m;
	if (!m.ParseFromArray(msg.getData(), msg.getLen()))
		return;
	this->handleCommand(m);
}

void CommandHandler::handleCommand(
	const samples::hello::cv_service::messages::Command &msg)
{
	switch (msg.id_case()) {
	case samples::hello::cv_service::messages::Command::kProcessingStart:
		this->processingStart(msg.processing_start());
		break;

	case samples::hello::cv_service::messages::Command::kProcessingStop:
		this->processingStop(msg.processing_stop());
		break;

	default:
		break;
	}
}

void CommandHandler::processingStart(
	const ::google::protobuf::Empty &arg)
{
}

void CommandHandler::processingStop(
	const ::google::protobuf::Empty &arg)
{
}

EventSender::EventSender()
	: ::msghub::MessageSender(sServiceName)
{
}

void EventSender::beforeSend(samples::hello::cv_service::messages::Event &msg)
{
}

int EventSender::send(
	const samples::hello::cv_service::messages::Event &msg,
	pomp::Connection *conn)
{
	return ::msghub::MessageSender::send(
		static_cast<uint16_t>(msg.id_case()),
		msg,
		conn);
}

int EventSender::close(
	const ::google::protobuf::Empty &arg,
	pomp::Connection *conn)
{
	samples::hello::cv_service::messages::Event msg;
	msg.set_allocated_close(remove_const(arg));
	beforeSend(msg);
	int res = send(msg, conn);
	msg.release_close();
	return res;
}

int EventSender::far(
	const ::google::protobuf::Empty &arg,
	pomp::Connection *conn)
{
	samples::hello::cv_service::messages::Event msg;
	msg.set_allocated_far(remove_const(arg));
	beforeSend(msg);
	int res = send(msg, conn);
	msg.release_far();
	return res;
}

int EventSender::depthMean(
	float arg,
	pomp::Connection *conn)
{
	samples::hello::cv_service::messages::Event msg;
	msg.set_depth_mean(arg);
	beforeSend(msg);
	int res = send(msg, conn);
	return res;
}

EventHandler::EventHandler()
	: ::msghub::MessageHandler(sServiceName)
{
}

void EventHandler::handle(
	const ::msghub::Message &msg)
{
	samples::hello::cv_service::messages::Event m;
	if (!m.ParseFromArray(msg.getData(), msg.getLen()))
		return;
	this->handleEvent(m);
}

void EventHandler::handleEvent(
	const samples::hello::cv_service::messages::Event &msg)
{
	switch (msg.id_case()) {
	case samples::hello::cv_service::messages::Event::kClose:
		this->close(msg.close());
		break;

	case samples::hello::cv_service::messages::Event::kFar:
		this->far(msg.far());
		break;

	case samples::hello::cv_service::messages::Event::kDepthMean:
		this->depthMean(msg.depth_mean());
		break;

	default:
		break;
	}
}

void EventHandler::close(
	const ::google::protobuf::Empty &arg)
{
}

void EventHandler::far(
	const ::google::protobuf::Empty &arg)
{
}

void EventHandler::depthMean(
	float arg)
{
}

} // namespace msghub
} // namespace messages
} // namespace cv_service
} // namespace hello
} // namespace samples
