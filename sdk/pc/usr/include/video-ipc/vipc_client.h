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
 * @file vipc_client.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VIPC_CLIENT_H_
#define _VIPC_CLIENT_H_

#include <video-ipc/vipc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Video IPC client callbacks.
 *
 * This structure defines all the client callbacks which will be called by the
 * client instance when events happen (new status, configure response, new
 * frame, end of stream, ...).
 *
 * The callbacks are not mandatory.
 */
struct vipcc_cb {
	/**
	 * New status received.
	 *
	 * This function is called when a new status is received from the
	 * server: while no status is received, the vipcc_start() call will
	 * fail.
	 *
	 * @param[in] ctx the client context
	 * @param[in] status the actual status
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*status_cb)(struct vipcc_ctx *ctx,
			  const struct vipc_status *status,
			  void *userdata);

	/**
	 * Configure response.
	 *
	 * This function is called when the server has processed a configure
	 * request from the current client instance.
	 *
	 * The values found on the config structure are the actual values
	 * applied by the server: they can be slightly different from the
	 * requested values.
	 * If the request has failed, the flag #VIPC_CONFIGURE_FLAG_ERROR will
	 * be set:
	 *  - If the flag #VIPC_CONFIGURE_FLAG_NOT_SUPPORTED is also set, it
	 *    means that one of the operations is not supported. The
	 *    unsupported operations will be notified by flags field: the
	 *    respective flags of the unsupported operations will be set,
	 *  - Otherwise, it means that one of the operation values is invalid.
	 *
	 * @param[in] ctx the client context
	 * @param[in] config the actual configuration
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*configure_cb)(struct vipcc_ctx *ctx,
			     const struct vipc_configure *config,
			     void *userdata);

	/**
	 * New frame received.
	 *
	 * This function is called when a new frame is received from the server
	 * side.
	 *
	 * If the map has been set to true during vipcc_new() call, the
	 * addresses of video frame planes is set and can be used to read the
	 * data frame.
	 *
	 * The be_frame argument will contain the back-end frame or NULL if not
	 * applicable.
	 *
	 * When the frame is no longer used by the application, it must be
	 * released with a call to vipcc_release(). If the release is not done,
	 * the frame will be locked and won't be usable by the server to handle
	 * next frames.
	 *
	 * @param[in] ctx the client context
	 * @param[in] frame the video IPC frame
	 * @param[in] be_frame the underlying back-end frame
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*frame_cb)(struct vipcc_ctx *ctx,
			 const struct vipc_frame *frame,
			 void *be_frame,
			 void *userdata);

	/**
	 * Connection to server status.
	 *
	 * This function is called when the client instance is connected or
	 * disconnected from the server: it is useful to monitor when a server
	 * is online or not.
	 *
	 * @param[in] ctx the client context
	 * @param[in] connected true when connected, false when disconnected
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*connection_status_cb)(struct vipcc_ctx *ctx,
				     bool connected,
				     void *userdata);

	/**
	 * End of stream.
	 *
	 * This function is called when the stream is finished: no more frame
	 * will be received. In such case, the client instance is automatically
	 * stopped and the call to vipcc_stop() can be avoided.
	 *
	 * @param[in] ctx the client context
	 * @param[in] reason the reason why video IPC stream is stopping
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*eos_cb)(struct vipcc_ctx *ctx,
		       enum vipc_eos_reason reason,
		       void *userdata);
};

/**
 * Create a VIDEO IPC Client context
 *
 * Backend will be created through a backend callback when the status is
 * received. Frame after received after max_frames will be immediately released.
 *
 * @param[in] loop The pomp loop where the server will be registered
 * @param[in] cbs Array of callbacks, @see vipcc_cb
 * @param[in] be_cbs Callbacks for the backend
 * @param[in] pomp_addr remote address to connect to (in pomp_addr_parse format)
 * @param[in] userdata passed as an extra argument to the callbacks
 * @param[in] max_frames max frames that can be held at a given time
 * @param[in] map wether to map the frame in the address space of the client
 *
 * @return a valid context or NULL
 */
VIPC_API struct vipcc_ctx *vipcc_new(struct pomp_loop *loop,
				     const struct vipcc_cb *cbs,
				     const struct vipc_be_cb *be_cbs,
				     const char *pomp_addr,
				     void *userdata,
				     size_t max_frames,
				     bool map);

/**
 * Create a VIDEO IPC Client context (version 2)
 *
 * Backend will be created through a backend callback when the status is
 * received. Frame after received after max_frames will be immediately released.
 *
 * @param[in] loop The pomp loop where the server will be registered
 * @param[in] cbs Array of callbacks, @see vipcc_cb
 * @param[in] be_cbs Callbacks for the backend
 * @param[in] pomp_addr remote address to connect to (in pomp_addr_parse format)
 * @param[in] friendly_name optional friendly name for logging
 *                          (if NULL the pomp_addr is used)
 * @param[in] userdata passed as an extra argument to the callbacks
 * @param[in] max_frames max frames that can be held at a given time
 * @param[in] map wether to map the frame in the address space of the client
 *
 * @return a valid context or NULL
 */
VIPC_API struct vipcc_ctx *vipcc_new2(struct pomp_loop *loop,
				      const struct vipcc_cb *cbs,
				      const struct vipc_be_cb *be_cbs,
				      const char *pomp_addr,
				      const char *friendly_name,
				      void *userdata,
				      size_t max_frames,
				      bool map);

/**
 * Destroy a VIDEO IPC Client context
 *
 * Release all frames and disconnect from the server.
 * @warning this function must not be called from any of
 * the VIPC client callbacks.
 *
 * @param[in] ctx video ipc ctx
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcc_destroy(struct vipcc_ctx *ctx);

/**
 * Setup a VIDEO IPC Client
 *
 * This function can be used to provide some additional data to the vipc client
 * backend.
 * If the data or the size are incorrect, -EINVAL will be returned. A copy is
 * internally made by this function, thus the original data pointer can be
 * released after the call.
 * The vipc client should not be started while calling this function, otherwise
 * a -EAGAIN will be returned.
 *
 * To get the data format expected, please refer to the backend documentation
 * and its C header file.
 *
 * @param[in] ctx video ipc ctx
 * @param[in] data setup data to forward to backend
 * @param[in] size setup data size in bytes
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcc_setup(struct vipcc_ctx *ctx, const void *data, size_t size);

/**
 * Send start to the server
 *
 * The server will send frames after receiving this message.
 * It can only be send if the status has been received.
 *
 * @param[in] ctx video ipc ctx
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcc_start(struct vipcc_ctx *ctx);

/**
 * Send stop to the server
 *
 * The server will send frames after receiving this message.
 * It can only be send if the status has been received.
 *
 * @param[in] ctx video ipc ctx
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcc_stop(struct vipcc_ctx *ctx);

/**
 * Release a frame
 *
 * Send a release message to the server.
 * All resources associated with the frame in the client will be freed as well.
 *
 * @param[in] ctx video ipc ctx
 * @param[in] frame to release.
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcc_release(struct vipcc_ctx *ctx,
			   const struct vipc_frame *frame);

/**
 * Release a frame, thread safe (can be called outside of the pomp loop)
 *
 * Send a release message to the server.
 * All resources associated with the frame in the client will be freed as well.
 * This will be done asynchronously, not all errors will be propagated back
 *
 * @param[in] ctx video ipc ctx
 * @param[in] frame to release.
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcc_release_safe(const struct vipc_frame *frame);

/**
 * Send a new config to the server
 *
 * @param[in] ctx video ipc context
 * @param[in] config new config
 */
VIPC_API int vipcc_configure(struct vipcc_ctx *ctx,
			     const struct vipc_configure *config);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VIPC_H_ */
