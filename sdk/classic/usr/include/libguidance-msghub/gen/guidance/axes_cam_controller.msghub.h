/**
 * GENERATED FILE, DO NOT EDIT.
 */

#pragma once

#include <msghub.hpp>
#include "guidance/axes_cam_controller.pb.h"

namespace pomp {
	class Conn;
}

namespace Guidance {
namespace AxesCamController {
namespace Messages {
namespace msghub {

class CommandSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.AxesCamController.Messages.Command";

	CommandSender();

	virtual void beforeSend(Guidance::AxesCamController::Messages::Command &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::AxesCamController::Messages::Command &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Reset camera axes reference.
	 */
	int reset(
		const ::Guidance::AxesCamController::Messages::Reset &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set camera axes reference.
	 */
	int setReference(
		const ::Guidance::AxesCamController::Messages::Reference &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Set camera axes configuration.
	 */
	int setConfig(
		const ::Guidance::AxesCamController::Messages::Config &arg,
		pomp::Connection *conn=nullptr);

};

class CommandHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.AxesCamController.Messages.Command";

	CommandHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleCommand(
		const Guidance::AxesCamController::Messages::Command &arg);

	/**
	 * Reset camera axes reference.
	 */
	virtual void reset(
		const ::Guidance::AxesCamController::Messages::Reset &msg);

	/**
	 * Set camera axes reference.
	 */
	virtual void setReference(
		const ::Guidance::AxesCamController::Messages::Reference &msg);

	/**
	 * Set camera axes configuration.
	 */
	virtual void setConfig(
		const ::Guidance::AxesCamController::Messages::Config &msg);

};

class EventSender : public ::msghub::MessageSender {
public:
	static constexpr const char *sServiceName = "Guidance.AxesCamController.Messages.Event";

	EventSender();

	virtual void beforeSend(Guidance::AxesCamController::Messages::Event &msg);

	using ::msghub::MessageSender::send;

	virtual int send(
		const Guidance::AxesCamController::Messages::Event &msg,
		pomp::Connection *conn=nullptr);

	/**
	 * Camera axes configuration advertised after a mode change.
	 */
	int config(
		const ::Guidance::AxesCamController::Messages::Config &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Camera axes reference status
	 */
	int referenceStatus(
		const ::Guidance::AxesCamController::Messages::ReferenceStatus &arg,
		pomp::Connection *conn=nullptr);

	/**
	 * Camera axes capabilities advertised when a client connects.
	 */
	int capabilities(
		const ::Guidance::AxesCamController::Messages::Capabilities &arg,
		pomp::Connection *conn=nullptr);

};

class EventHandler : public ::msghub::MessageHandler {
public:
	static constexpr const char *sServiceName = "Guidance.AxesCamController.Messages.Event";

	EventHandler();

	virtual void handle(
		const ::msghub::Message &msg) override;

	virtual void handleEvent(
		const Guidance::AxesCamController::Messages::Event &arg);

	/**
	 * Camera axes configuration advertised after a mode change.
	 */
	virtual void config(
		const ::Guidance::AxesCamController::Messages::Config &msg);

	/**
	 * Camera axes reference status
	 */
	virtual void referenceStatus(
		const ::Guidance::AxesCamController::Messages::ReferenceStatus &msg);

	/**
	 * Camera axes capabilities advertised when a client connects.
	 */
	virtual void capabilities(
		const ::Guidance::AxesCamController::Messages::Capabilities &msg);

};

} // namespace msghub
} // namespace Messages
} // namespace AxesCamController
} // namespace Guidance
