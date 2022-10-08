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
 * @file vipc_server.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VIPC_SERVER_H_
#define _VIPC_SERVER_H_

#include <video-ipc/vipc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Video IPC server context. */
struct vipcs_ctx;

/**
 * Video IPC frame release.
 *
 * This structure provides a video IPC frame to release and its associated user
 * data pointer. These values were passed together during a call to
 * vipcs_send_frame() call.
 *
 * This structure is used during the call of the server callback
 * vipcs_cb.frame_release_cb.
 */
struct vipc_release {
	/**
	 * Video IPC frame to release.
	 * This pointer is the frame provided at vipcs_send_frame() call.
	 */
	struct vipc_frame *frame;
	/**
	 * User data attached to the frame.
	 * This pointer is the user data pointer provided at vipcs_send_frame()
	 * call.
	 */
	void *userdata;
};

/**
 * Video IPC remote information.
 *
 * This structure provides information on currently connected video IPC clients.
 */
struct vipc_remote {
	/**
	 * The name of the process that owns the client.
	 */
	char *pname;
	/**
	 * True when remote is running.
	 */
	bool started;
};

#define VIPCS_CBS_FRAME_RELEASE (1 << 0)
#define VIPCS_CBS_RUNNING_REMOTES (1 << 1)
#define VIPCS_CBS_CONNECTED_REMOTES (1 << 2)
#define VIPCS_CBS_ALL_FRAMES_RELEASED (1 << 3)
#define VIPCS_CBS_CONFIG_SENT (1 << 4)

/**
 * Video IPC server callbacks.
 *
 * This structure defines all the server callbacks which will be called by the
 * server instance when events happen (new status, configure response, new
 * frame, end of stream, ...) or request are received from one of the clients.
 *
 * The callbacks are not mandatory.
 */
struct vipcs_cb {
	/**
	 * Release frame event.
	 *
	 * This function is called when a frame should be released. The function
	 * is called immediately when no clients have started the stream (after
	 * vipcs_send_frame() returns, in the pomp loop) or after all started
	 * remotes have released the frame.
	 *
	 * The same pointer passed to vipcs_send_frame() is in frame field of
	 * the vipc_release structure. The video IPC frame should be freed here.
	 *
	 * @param[in] ctx the server context
	 * @param[in] release the frame to release
	 * @param[in] userdata the user data passed at context creation
	 * @return 0 if the frame has been released, -1 otherwise.
	 */
	int (*frame_release_cb)(struct vipcs_ctx *ctx,
				struct vipc_release *release,
				void *userdata);

	/**
	 * Remote running event.
	 *
	 * This function is called every time a remote start or stop. The num
	 * argument reflects the number of remote which has started the stream
	 * at call time.
	 *
	 * @param[in] ctx the server context
	 * @param[in] num the number or running remotes
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*running_remotes_cb)(struct vipcs_ctx *ctx,
				   int num,
				   void *userdata);

	/**
	 * Remote connection event.
	 *
	 * This function is called every time a remote connects or disconnects.
	 * The num argument reflects the number of remote connected at call
	 * time.
	 *
	 * @param[in] ctx the server context
	 * @param[in] num the number of connected remotes
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*connected_remotes_cb)(struct vipcs_ctx *ctx,
				     int num,
				     void *userdata);

	/**
	 * Configuration request received.
	 *
	 * This function is called when a configuration request is received from
	 * a client.
	 * The values of the request can be modified by this function: they will
	 * be sent back automatically after the function returns.
	 * If one of the operations are not supported, the flags field should be
	 * set to #VIPC_CONFIGURE_FLAG_ERROR, #VIPC_CONFIGURE_FLAG_NOT_SUPPORTED
	 * and operations which are not supported, to notify the client that the
	 * request failed and the reason why. If one of the values are bad, the
	 * #VIPC_CONFIGURE_FLAG_ERROR flag should be set to notify the client
	 * that the values are invalid.
	 * If this callback is not defined, the flags field will be set with
	 * #VIPC_CONFIGURE_FLAG_ERROR and #VIPC_CONFIGURE_FLAG_NOT_SUPPORTED to
	 * notify that configuration is not supported. In addition, all
	 * operation flags will be set to notify that every operations are not
	 * supported.
	 *
	 * @param[in] ctx the server context
	 * @param[in,out] config the requested configuration
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*configure_cb)(struct vipcs_ctx *ctx,
			     struct vipc_configure *config,
			     void *userdata);

	/**
	 * All frames are released.
	 *
	 * This function is called when all frames have been released after a
	 * call to vipcs_send_eos(): it is very useful for waiting that all
	 * frames are released from all client before destroying a server
	 * isntance, or before changing status with different size / buffers.
	 *
	 * @param[in] ctx the server context
	 * @param[in] userdata the user data passed at context creation
	 */
	void (*all_frames_released_cb)(struct vipcs_ctx *ctx, void *userdata);
};

/**
 * Create a VIDEO IPC Server context
 *
 * @param[in] loop The pomp loop where the server will be registered
 * @param[in] cbs Array of callbacks, @see vipcs_cb
 * @param[in] be_ctx Context for the backend
 * @param[in] be_cbs Callbacks for the backend
 * @param[in] pomp_addr local address to listen on (in pomp_addr_parse format)
 * @param[in] max_frames max frames that can be send at a given time
 * @param[in] max_frames_per_client max frames a client can held unto
 * @param[in] userdata passed as an extra argument to the callbacks
 *
 * @return a valid context or NULL
 */
VIPC_API struct vipcs_ctx *vipcs_new(struct pomp_loop *loop,
				     const struct vipcs_cb *cbs,
				     struct vipc_be_ctx *be_ctx,
				     const struct vipc_be_cb *be_cbs,
				     const char *pomp_addr,
				     uint32_t max_frames,
				     uint32_t max_frames_per_client,
				     void *userdata);
/**
 * Destroy a VIDEO IPC Server context
 *
 * The clients will received an end of stream message, and all frames are
 * released
 *
 * @param[in] ctx video ipc ctx
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcs_destroy(struct vipcs_ctx *ctx);

/**
 * Set current status
 *
 * Status will be sent to connected clients.
 * It will also be stored to be sent if a client connects afterwards.
 *
 * Status will be "deep copied", so it can be freed by the caller.
 *
 * @param[in] ctx video ipc ctx
 * @param[in] status: status to be sent/stored
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcs_send_status(struct vipcs_ctx *ctx,
			       const struct vipc_status *status);

/**
 * Send a frame
 *
 * The same pointer will be passed to frame_release_cb, so they must not be
 * freed until then
 *
 * Even in case of errors, it is expected that the frame will be released
 * through the callback.
 *
 * @param[in] ctx video ipc ctx
 * @param[in] frame vipc frame (can be generated by vipc_frame_from_vacq_buffer)
 * @param[in] buffer native buffer description that will be stored by the
 * backend
 * @param[in] userdata will be passed at release
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcs_send_frame(struct vipcs_ctx *ctx,
			      struct vipc_frame *frame,
			      void *buffer,
			      void *userdata);

/**
 * Send EOS to connected clients
 *
 * It is still expected that clients will release the remaining frames they hold
 * Clients will need to wait for a new status and send a start to be able to
 * receive frames again.
 * This will also invalidate current status.
 *
 * @param[in] ctx video ipc ctx
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcs_send_eos(struct vipcs_ctx *ctx);

/**
 * Send EOS with reason to connected clients
 *
 * It is the same function as vipcs_send_eos() with an additional parameter to
 * specify the stop reason.
 *
 * @param[in] ctx video ipc ctx
 * @param[in] reason reason why video IPC stream is stopping
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcs_send_eos_reason(struct vipcs_ctx *ctx,
				   enum vipc_eos_reason reason);

/**
 * Update vipc server callbacks
 *
 * Update vipc server callbacks in accordance to the VIPCS_CBS_XXX flags.
 *
 * @param[in] ctx      video ipc ctx
 * @param[in] cbs      Array of callbacks, @see vipcs_cb
 * @param[in] flags    bitfield to indicate which callback to update
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int
vipcs_update_cbs(struct vipcs_ctx *ctx, const struct vipcs_cb *cbs, int flags);

/**
 * Get information on connected remotes
 *
 * Info will be "deep copied", so it can be freed by the caller with
 * vipcs_free_remotes.
 *
 * @param[in]  ctx video ipc ctx
 * @param[out] remotes list of connected remotes
 * @param[out] num number of connected remotes
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipcs_get_remotes(const struct vipcs_ctx *ctx,
			       struct vipc_remote **remotes,
			       int *num);

/**
 * Free a list of connected remotes
 *
 * Info will be "deep copied", so it can be freed by the caller.
 *
 * @param[in] remotes list of connected remotes
 * @param[in] num number of connected remotes
 */
VIPC_API void vipcs_free_remotes(struct vipc_remote *remotes, int num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VIPC_SERVER_H_ */
