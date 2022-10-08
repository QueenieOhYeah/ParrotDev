/*
 * Copyright (c) 2019 Parrot Drones SAS
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Parrot Drones SAS Company nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE PARROT DRONES SAS COMPANY BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file vipc_backend.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VIPC_BACKEND_H_
#define _VIPC_BACKEND_H_

#include <video-ipc/vipc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Message ID base for private back-end messages
 *
 * A back-end can send / receive some private messages in addition to the
 * internal messages handled by the video IPC library, to extended their
 * features. This macro defines the base ID for such private messages: the
 * back-end must generates pomp messages with a message ID greater or equal to
 * this value.
 */
#define VIPC_BE_PRIV_MSGID_BASE 100

/**
 * Video IPC back-end callbacks.
 *
 * This structure defines all the back-end callbacks which will be used by video
 * IPC server and client instances.
 */
struct vipc_be_cb {
	/* Server callbacks */

	/**
	 * Generate method and method parameters
	 *
	 * This function is called just before the status is sent. It generates
	 * the method string to identify the back-end and the method parameters
	 * to use in back-end client context.
	 *
	 * Both strings are malloc'd, caller is responsible for freeing them.
	 *
	 * It is called only by server side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[out] method the string identifying the back-end
	 * @param[out] method_params an optional string to pass parameters to
	 *             back-end client instance(s)
	 * @return 0 in case of success, -errno for failure
	 */
	int (*server_gen_method_params)(struct vipc_be_ctx *ctx,
					char **method,
					char **method_params);

	/**
	 * Client state (started / stopped) has changed
	 *
	 * This function is called when a client has requested a start or a
	 * stop.
	 *
	 * A private message can be sent to client(s) by setting the msg
	 * parameter with a message ID greater or equal to
	 * #VIPC_BE_PRIV_MSGID_BASE. It will be send before first frame.
	 *
	 * It is called only by server side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in] start true when start is requested, false when stop is
	 *            requested
	 * @param[out] msg the private message to send (optional)
	 */
	void (*server_new_client_state)(struct vipc_be_ctx *ctx,
					bool start,
					struct pomp_msg **msg);

	/**
	 * Store a video buffer reference in the back-end
	 *
	 * This function is called during vipcs_send_frame(), to store
	 * internally to the back-end, the vipc_frame and its native buffer.
	 *
	 * If some resources are allocated or reserved during the call, the
	 * vipc_be_cb.server_release_buffer function should be implemented to
	 * release and free all resources.
	 *
	 * A private message can be sent to client(s) by setting the msg
	 * parameter with a message ID greater or equal to
	 * #VIPC_BE_PRIV_MSGID_BASE. It will be send just before the frame and
	 * it can be received by client by implementing the
	 * vipc_be_cb.client_handle_priv_msg callback.
	 *
	 * It is called only by server side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in] native_frame the native frame to be stored
	 * @param[in,out] frame the video IPC frame,(it will be updated to
	 *                reflect the storage
	 * @param[out] msg a private message to send before frame (optional)
	 * @return 0 in case of success, -errno for failure
	 */
	int (*server_store_buffer)(struct vipc_be_ctx *ctx,
				   void *native_frame,
				   struct vipc_frame *vipc_frame,
				   struct pomp_msg **msg);
	/**
	 * Release a video buffer reference from the back-end
	 *
	 * This function is called by server instance when a vipc_frame has bee,
	 * released by all the clients.
	 *
	 * If the vipc_be_cb.server_store_buffer callback has allocated /
	 * reserved some resources, this function should release and free them.
	 *
	 * It is called only by server side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in] native_frame the native frame to be released
	 * @param[in] frame the video IPC frame to release
	 * @return 0 in case of success, -errno for failure
	 */
	int (*server_release_buffer)(struct vipc_be_ctx *ctx,
				     void *native_frame,
				     struct vipc_frame *vipc_frame);

	/**
	 * Connect a client
	 *
	 * This function is called after a client connected to the server
	 * instance.
	 *
	 * It is called only by server side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in] conn libpomp connection from the protocol link
	 */
	void (*server_connect_client)(struct vipc_be_ctx *ctx,
				      struct pomp_conn *conn);

	/**
	 * Disconnect a client
	 *
	 * This function is called when a client has disconnected from server
	 * instance.
	 *
	 * It is called only by server side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in] conn libpomp connection from the protocol link
	 */
	void (*server_disconnect_client)(struct vipc_be_ctx *ctx,
					 struct pomp_conn *conn);

	/* Client callbacks */

	/**
	 * Create a back-end client context
	 *
	 * This function is called when a new status is received on client side.
	 * It provides the method and method_params received in the vipc_status
	 * message.
	 *
	 * If some resources are allocated / reserved during this call, the
	 * vipc_be_cb.client_destroy function should be implemented to release
	 * and free these resources.
	 *
	 * If a new status is received, the vipc_be_cb.client_destroy will be
	 * called before this function.
	 *
	 * It is called only by client side.
	 *
	 * @param[in] loop the pomp loop where the back-end will be registered
	 * @param[in] parent a pointer to the parent video IPC client
	 * @param[in] max_frames the maximum number of frames the client will
	 *            handle concurrently
	 * @param[in] conn libpomp connection from the protocol link
	 * @param[in] status the video IPC status received from the server
	 * @return a valid back-end context or NULL
	 */
	struct vipc_be_ctx *(*client_init)(struct pomp_loop *loop,
					   struct vipcc_ctx *parent,
					   uint32_t max_frames,
					   struct pomp_conn *conn,
					   const struct vipc_status *status);

	/**
	 * Get a native buffer
	 *
	 * This function is called to retrieve the native buffer (stored
	 * internally with vipc_be_cb.server_store_buffer on server side) when a
	 * new frame is received on client side.
	 *
	 * Any method can be used by the back-end to share the native buffer
	 * between the server and client(s) applications, like shared memory,
	 * private messages, additional socket, ...
	 *
	 * If some resources are allocated or reserved during the call, the
	 * vipc_be_cb.client_free_native function should be implemented to
	 * release all resources.
	 *
	 * It is called only by client side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in,out] frame the video IPC frame received from the server
	 * @param[out] native_frame the native frame to be allocated and cast
	 *             by the back-end, can be NULL
	 * @param[in] map true when the video IPC frame should be mapped in
	 *            user-space
	 * @return 0 if the native_frame is available, -EAGAIN if the frame is
	 *         not available yet and -errno for any other errors
	 */
	int (*client_get_native)(struct vipc_be_ctx *ctx,
				 struct vipc_frame *frame,
				 void **native_frame,
				 bool map);

	/**
	 * Free a native buffer
	 *
	 * This function is called by client instance when a vipc_frame has been
	 * released with vipcc_release().
	 *
	 * If the vipc_be_cb.client_get_native callback has allocated / reserved
	 * some resources, this function should free them.
	 *
	 * It is called only by client side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in] frame the video IPC frame received from the server
	 * @return 0 if in case of success, -errno otherwise
	 */
	int (*client_free_native)(struct vipc_be_ctx *ctx,
				  struct vipc_frame *frame);

	/**
	 * Receive a private message
	 *
	 * This function can be implemented to receive and handle a private
	 * message from a server instance. It is useful if the back-end sever
	 * instance need to send additional informations or data to client(s).
	 *
	 * It is called only by client side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 * @param[in] msg the pomp message to read
	 * @return 0 if in case of success, -errno otherwise
	 */
	int (*client_handle_priv_msg)(struct vipc_be_ctx *ctx,
				      const struct pomp_msg *msg);

	/**
	 * Destroy a back-end client context
	 *
	 * This function is called when a client instance is destroyed or when
	 * a new status is received on client side.
	 *
	 * If some resources have been allocated / reserved during
	 * vipc_be_cb.client_init call, this function should be implemented to
	 * free these resources.
	 *
	 * It is called only by client side.
	 *
	 * @param[in] ctx the video IPC back-end context
	 */
	void (*client_destroy)(struct vipc_be_ctx *ctx);
};

/**
 * Call the vipcc_cb.frame_cb() of a client.
 *
 * This can be called to acknowledge frame reception from back-ends when
 * vipc_be_cb.client_get_native() returned -EAGAIN because the frame was not
 * available yet.
 *
 * @param[in] ctx the video IPC client context (the parent parameter of
 *            vipc_be_cb.client_init())
 * @param[in] native_frame the native frame or NULL
 * @param[in] frame the video IPC frame
 */
VIPC_API void vipcc_call_frame_cb(struct vipcc_ctx *ctx,
				  void *native_frame,
				  struct vipc_frame *frame);

/**
 * Get the setup data from a vipc client context.
 *
 * @param[in] ctx the video IPC client context (the parent parameter of
 *            vipc_be_cb.client_init())
 * @param[out] size the setup data size in bytes
 *
 * @return the setup data or NULL if no setup data are available
 */
VIPC_API const void *vipcc_get_setup_data(struct vipcc_ctx *ctx, size_t *size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VIPC_BACKEND_H_ */
