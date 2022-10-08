/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/zoom_cam_controller.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace ZoomCamController {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.ZoomCamController.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::ZoomCamController::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::ZoomCamController::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Reset camera zoom level.
	 */
	int reset(
		const ::Guidance::ZoomCamController::Messages::Reset &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set camera zoom level.
	 */
	int setZoom(
		const ::Guidance::ZoomCamController::Messages::Zoom &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set camera zoom configuration.
	 */
	int setConfig(
		const ::Guidance::ZoomCamController::Messages::Config &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.ZoomCamController.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::ZoomCamController::Messages::Command &arg);

	/**
	 * Reset camera zoom level.
	 */
	virtual void reset(
		const ::Guidance::ZoomCamController::Messages::Reset &msg);

	/**
	 * Set camera zoom level.
	 */
	virtual void setZoom(
		const ::Guidance::ZoomCamController::Messages::Zoom &msg);

	/**
	 * Set camera zoom configuration.
	 */
	virtual void setConfig(
		const ::Guidance::ZoomCamController::Messages::Config &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.ZoomCamController.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::ZoomCamController::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::ZoomCamController::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Camera zoom configuration advertised after a mode change.
	 */
	int config(
		const ::Guidance::ZoomCamController::Messages::Config &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.ZoomCamController.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::ZoomCamController::Messages::Event &arg);

	/**
	 * Camera zoom configuration advertised after a mode change.
	 */
	virtual void config(
		const ::Guidance::ZoomCamController::Messages::Config &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace ZoomCamController
} // namespace Guidance
