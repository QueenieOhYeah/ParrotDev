/**
 * Copyright (C) 2019 Parrot Drones SAS
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in
 *  the documentation and/or other materials provided with the
 *  distribution.
 *  * Neither the name of Parrot nor the names
 *  of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written
 *  permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */

#ifndef MSGHUB_H
#define MSGHUB_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "msghub_exports.h"
#include "msghub_utils.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Forward declarations */

struct ProtobufCMessage;

struct pomp_conn;
struct pomp_loop;

struct msghub;
struct msghub_channel;
struct msghub_handler;
struct msghub_sender;

/**
 * Structure wrapping a message consisting of a 32-bit Id and a payload.
 * The 32-bit Id is split in 2 fields
 * - high 16-bit: service Id. Used to route messages in the system
 * - low 16-bit: message number. Used to route message in a service
 */
struct msghub_msg {
	/** 32-bit message Id */
	uint32_t msg_id;
	/** Pointer to the data buffer */
	const void *const_data;
	/** Size of the data buffer */
	uint32_t len;
};

/** Operations to be implemented fo a message handler */
struct msghub_handler_ops {
	void (*dispose)(struct msghub_handler *base);

	/**
	 * Function called when a message needs to be processed
	 * @param base base object of the handler.
	 * @param msg message received
	 */
	void (*handle)(struct msghub_handler *base,
		const struct msghub_msg *msg);
};

/**
 * Callbacks for the main message hub object.
 */
struct msghub_conn_handler_cbs {
	/**
	 * Function called when a remote peer is connected.
	 * @param hub message hub object.
	 * @param channel associated Channel object.
	 * @param conn associated 'pomp' Connection object.
	 * @param userdata user data associated with the callback
	 */
	void (*connected)(struct msghub *hub,
		struct msghub_channel *channel,
		struct pomp_conn *conn,
		void *userdata);

	/**
	 * Function called when a remote peer is disconnected.
	 * @param hub message hub object.
	 * @param channel associated Channel object.
	 * @param conn associated 'pomp' Connection object.
	 * @param userdata user data associated with the callback
	 */
	void (*disconnected)(struct msghub *hub,
		struct msghub_channel *channel,
		struct pomp_conn *conn,
		void *userdata);
};

/**
 * Create a new message hub object.
 * @param loop 'pomp' Loop object to use for internal sockets.
 * @param cbs optional callback for connection/disconnection events.
 * @param userdata user data associated with the callback
 * @param ret_obj pointer to returned object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_new(struct pomp_loop *loop,
	const struct msghub_conn_handler_cbs *cbs,
	void *userdata,
	struct msghub **ret_obj);

/**
 * Destroy a message hub object.
 * @param hub message hub object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_destroy(struct msghub *hub);

/**
 * Create and start a server channel.
 * @param hub message hub object.
 * @param addr address to listen to.
 * @param ret_obj pointer to returned channel object that can then be used to
 *                attach senders/handlers.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_start_server_channel(struct msghub *hub,
	const char *addr,
	struct msghub_channel **ret_obj);

/**
 * Create and start a server channel.
 * Similar to 'msghub_start_server_channel' but with an additional 'mode'
 * parameter to configure access mode of unix socket.
 * @param hub message hub object.
 * @param addr address to listen to.
 * @param mode access mode for unix sockets
 * @param ret_obj pointer to returned channel object that can then be used to
 *                attach senders/handlers.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_start_server_channel_with_access_mode(struct msghub *hub,
	const char *addr,
	uint32_t mode,
	struct msghub_channel **ret_obj);

/**
 * Create and start a client channel.
 * @param hub message hub object.
 * @param addr address to listen to.
 * @param ret_obj pointer to returned channel object that can then be used to
 *                attach senders/handlers.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_start_client_channel(struct msghub *hub,
	const char *addr,
	struct msghub_channel **ret_obj);

/**
 * Stop and destroy all channels.
 * @param hub message hub object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_stop(struct msghub *hub);

/**
 * Enable the dump of sent/received messages in logging system.
 * @param hub message hub object.
 * @param channel if a channel is given only its messages are dumped
 *                otherwise all messages are dumped.
 */
MSGHUB_API
int msghub_enable_dump(struct msghub *hub, struct msghub_channel *channel);

/**
 * Send a message.
 * @param hub message hub object.
 * @param channel channel on which the message shall be sent.
 * @param msg message to send.
 * @param conn remote connection to target. If NULL, and it will
 *        broadcast the message to all peers connected to the
 *        associated channel.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_send_msg(struct msghub *hub,
	struct msghub_channel *channel,
	const struct msghub_msg *msg,
	struct pomp_conn *conn);

/**
 * Attach a message sender to a channel. All message sent with the given
 * sender will go through the given channel.
 * @param hub message hub object.
 * @param sender message sender to attach.
 * @param channel channel to attach.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_attach_sender(struct msghub *hub,
	struct msghub_sender *sender,
	struct msghub_channel *channel);

/**
 * Detach a message sender.
 * @param hub message hub object.
 * @param msgsender message sender to detach.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_detach_sender(struct msghub *hub, struct msghub_sender *sender);

/**
 * Attach a message handler. Any message received on any channel with a
 * service Id matching the one in the handler will be routed.
 * @param hub message hub object.
 * @param handler message handler to attach.
 * @return 0 in case of success, negative errno in case of error.
 *
 * @remarks if the given message handler has an empty service name it
 *          will be attached as a 'generic' handler and will receive all
 *          messages regarding of their message Id.
 */
MSGHUB_API
int msghub_attach_handler(struct msghub *hub, struct msghub_handler *handler);

/**
 * Detach a message handler.
 * @param hub message hub object.
 * @param handler message handler to detach.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_detach_handler(struct msghub *hub, struct msghub_handler *handler);

/**
 * During the processing of an incoming message (in any of the 'handle'
 * method of an attached handler), get the 'pomp' connection object on
 * which the message was actually received. Can be used to reply only to
 * this connection.
 * @param hub message hub object.
 * @return 'pomp' connection object of the current processed message.
 */
MSGHUB_API
struct pomp_conn *msghub_get_current_msg_conn(struct msghub *hub);

/**
 * Get the service Id from a service name.
 * @param hub message hub object.
 * @param name service name.
 * @return service Id associated with the given service name.
 */
MSGHUB_API
uint16_t msghub_get_service_id(struct msghub *hub, const char *name);

/**
 * Initialize a message structure with empty fields.
 * @param msg message.
 */
static inline void msghub_msg_init(struct msghub_msg *msg)
{
	memset(msg, 0, sizeof(*msg));
}

/**
 * Initialize a message structure with payload.
 * @param msg message.
 * @param msg_id 32-bit message Id.
 * @param const_data pointer to the data buffer.
 * @param len size of the data buffer.
 *
 * @remarks no copy of the data is done, ownership is still on the caller.
 */
static inline void msghub_msg_init_with_payload(struct msghub_msg *msg,
	uint32_t msg_id,
	const void *data,
	uint32_t len)
{
	memset(msg, 0, sizeof(*msg));
	msg->msg_id = msg_id;
	msg->const_data = data;
	msg->len = len;
}

/**
 * Clone a message.
 * @param msg source message.
 * @param ret_msg pointer tio cloned message.
 * @return 0 in case of success, negative errno in case of error.
 *
 * @remarks msghub_msg_destroy shall be called to free memory.
 */
MSGHUB_API
int msghub_msg_clone(const struct msghub_msg *msg, struct msghub_msg **ret_msg);

/**
 * Clear the message structure (by simply reseting to 0)
 * @param msg message.
 */
MSGHUB_API
void msghub_msg_clear(struct msghub_msg *msg);

/**
 * Destroy the message and free memory.
 * @param msg message.
 */
MSGHUB_API
void msghub_msg_destroy(struct msghub_msg *msg);

/**
 * Get the service Id of the message.
 * @param msg message.
 * @return 16-bit service of the message
 *         (high 16-bit of the message Id).
 */
static inline uint16_t msghub_msg_get_service_id(const struct msghub_msg *msg)
{
	return msghub_utils_extract_service_id(msg->msg_id);
}

/**
 * Get the message number of the message.
 * @param msg message.
 * @return 16-bit message number of the message
 *         (low 16-bit of the message Id).
 */
static inline uint16_t msghub_msg_get_msg_num(const struct msghub_msg *msg)
{
	return msghub_utils_extract_msg_num(msg->msg_id);
}

/**
 * Create a new message sender object.
 * @param service_name service name. Used to get the associated service Id.
 * @param ret_obj pointer to returned message sender object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_sender_new(const char *service_name, struct msghub_sender **ret_obj);

/**
 * Destroy message sender object.
 * @param sender message sender object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_sender_destroy(struct msghub_sender *sender);

/**
 * Get the service name associated with the message sender.
 * @param sender message sender object.
 * @return service name.
 */
MSGHUB_API
const char *msghub_sender_get_service_name(struct msghub_sender *sender);

/**
 * Send a message.
 * @param sender message sender object.
 * @param msg message to send.
 * @param conn remote connection to target. If NULL, it will
 *        broadcast the message to all peers connected to the
 *        associated channel.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_sender_send(struct msghub_sender *sender,
	const struct msghub_msg *msg,
	struct pomp_conn *conn);

/**
 * Send a message.
 * @param sender message sender object.
 * @param msg_num message number. The full message Id will be computed
 *        using the service Id itself computed from the service name.
 * @param data data buffer of the payload.
 * @param len size of the payload.
 * @param conn remote connection to target. If NULL, it will
 *        broadcast the message to all peers connected to the
 *        associated channel.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_sender_send_payload(struct msghub_sender *sender,
	uint16_t msg_num,
	const void *data,
	uint32_t len,
	struct pomp_conn *conn);

/**
 * Send a message.
 * @param sender message sender object.
 * @param msg_num message number. The full message Id will be computed
 *        using the service Id itself computed from the service name.
 * @param pb_msg message to send as a protobuf object. This method will
 *         serialize the message and send it.
 * @param conn remote connection to target. If NULL, and it will
 *        broadcast the message to all peers connected to the
 *        associated channel.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_sender_send_protobuf(struct msghub_sender *sender,
	uint16_t msg_num,
	const struct ProtobufCMessage *pb_msg,
	struct pomp_conn *conn);

/**
 * Create a new message handler object.
 * @param child pointer to child object (in the inheritance tree)
 * @param ops: pointer to specific operations of the handler.
 * @param service_name service name. Used to get the associated service Id.
 * @param ret_obj pointer to returned message handler object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_handler_new(void *child,
	const struct msghub_handler_ops *ops,
	const char *service_name,
	struct msghub_handler **ret_obj);

/**
 * Destroy message handler object.
 * @param handler message handler object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_handler_destroy(struct msghub_handler *handler);

/**
 * Get the service name associated with the message handler.
 * @param handler message handler object.
 * @return service name.
 */
MSGHUB_API
const char *msghub_handler_get_service_name(struct msghub_handler *handler);

/**
 * Get the child object associated with the message handler.
 * @param handler message handler object.
 * @return pointer to child object.
 */
MSGHUB_API
void *msghub_handler_get_child(struct msghub_handler *handler);

/**
 * Handle a message by calling the specific operation of the message handler.
 * @param handler message handler object.
 * @param msg message received.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_handler_handle(struct msghub_handler *handler,
	const struct msghub_msg *msg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !MSGHUB_H */
