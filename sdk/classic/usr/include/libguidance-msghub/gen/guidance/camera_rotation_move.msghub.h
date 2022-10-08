/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/camera_rotation_move.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace CameraRotationMove {
namespace Messages {
namespace msghub {

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.CameraRotationMove.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::CameraRotationMove::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::CameraRotationMove::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Send when displacement is done
	 */
	int moveValidated(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Send when displacement is not validated
	 */
	int timeOut(
		const ::google::protobuf::Empty &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.CameraRotationMove.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::CameraRotationMove::Messages::Event &arg);

	/**
	 * Send when displacement is done
	 */
	virtual void moveValidated(
		const ::google::protobuf::Empty &msg);

	/**
	 * Send when displacement is not validated
	 */
	virtual void timeOut(
		const ::google::protobuf::Empty &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace CameraRotationMove
} // namespace Guidance
