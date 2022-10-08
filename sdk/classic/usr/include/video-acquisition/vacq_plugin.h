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
 * @file vacq_plugin.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VACQ_PLUGIN_H_
#define _VACQ_PLUGIN_H_

#include <libconfig.h>

#include <video-acquisition/vacq.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** String helper. */
#define xstr(s) str(s)
/** String helper. */
#define str(s) #s

/**
 * Video-acquisition plugin path.
 * This macro defines where plugins are stored and from where they should be
 * loaded.
 */
#define VACQ_PLUGIN_PATH "/usr/lib/"

/**
 * Current plugin version.
 * The macro value is incremented each times the API and/or plugin structures
 * are updated.
 */
#define VACQ_PLUGIN_VERSION 0xB

/**
 * Plugin file prefix.
 * This macro defines the prefix for plugin file name.
 */
#define VACQ_PLUGIN_NAME_TEMPLATE "libvacqplugin_"

/**
 * Symbol name to use for vacq_plugin definition.
 * This symbol name must be used to define the plugin through the vacq_plugin
 * structure in order to be loaded by main instance of the video-acquisition
 * library.
 * It should be written like:
 * @code
 * const struct vacq_plugin VACQ_PLUGIN_INFO_SYM = {
 * };
 * @endcode
 */
#define VACQ_PLUGIN_INFO_SYM VACQ_PLUGIN
/**
 * String version of the symbol name.
 * This macro defines the string version of the plugin symbol name defined by
 * #VACQ_PLUGIN_INFO_SYM.
 */
#define VACQ_PLUGIN_INFO_SYM_STR xstr(VACQ_PLUGIN_INFO_SYM)

/**
 * Device operations.
 *
 * This structure provides all function specific implementation of a device. All
 * vacq_device functions will call one of the functions defined in this
 * structure.
 *
 * When a device is opened with vacq_device_open(), a call to the specific
 * vacq_media_ops.get_device_ops() of the media is done to retrieve a
 * vacq_device_ops which contains all the functions to call for this device.
 * Then, the vacq_device_ops.init() implementation is called to initialize
 * internal context and allocate resources. This callback can set a user pointer
 * which will be passed to any subsequent calls.
 */
struct vacq_device_ops {
	/**
	 * Initialize device instance.
	 *
	 * This function is called when a new device instance is created during
	 * vacq_device_open() call.
	 *
	 * The device descriptor should be filled accurately during call and
	 * after it returns, the descriptor should not be modified anymore: the
	 * descriptor is managed by the vacq_device itself and ownership of all
	 * fields (like strings) is taken, so no need to free strings in device
	 * implementation.
	 *
	 * The operation data are the user pointer attached to the
	 * vacq_device_ops while getting these operations. It is the optional
	 * pointer set by vacq_media_ops.get_device_ops() during its call. This
	 * pointer is media specific implementation.
	 *
	 * The user field can be used to set a pointer which will be passed to
	 * next calls to the other functions of the same vacq_device instance.
	 * It is useful to manage an internal allocated context. The allocated
	 * memory and resources should be released and/or freed during
	 * vacq_device_ops.exit() call.
	 *
	 * The descriptor and user are valid during call to this function.
	 *
	 * @param[in] media_id is the media ID
	 * @param[in] device_id is the device ID to initialize
	 * @param[in,out] desc is the device descriptor to fill (ownership is
	 *                     taken by caller after it returns)
	 * @param[in] ops_data is the user pointer attached to the
	 *                     vacq_device_ops used to get these operations
	 * @param[out] user is a pointer which can be set to pass a pointer to
	 *                  subsequent calls to these operations
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*init)(unsigned int media_id,
		    unsigned int device_id,
		    struct vacq_device_desc *desc,
		    void *ops_data,
		    void **user);

	/**
	 * Release device instance.
	 *
	 * This function is called when the device instance is closed with
	 * vacq_device_close().
	 *
	 * If the user pointer has been defined during vacq_device_ops.init(),
	 * all resources must be released (and freed if necessary) here.
	 *
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*exit)(void *user);

	/**
	 * Get control list of a device callback.
	 *
	 * This function is called by vacq_device_list_control(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and pointers are checked before call.
	 *
	 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE
	 * @param[out] desc is a pointer to the returned list
	 * @param[out] count is a pointer to the control count
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*list_control)(int pad_id,
			    const struct vacq_control_desc **desc,
			    unsigned int *count,
			    void *user);
	/**
	 * Get device control value(s) callback.
	 *
	 * This function is called by vacq_device_get_control(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and control pointer are checked before call.
	 *
	 * The control values are not verified by the caller: implementation
	 * should check the values with vacq_check_controls(),
	 * vacq_check_control_value() or a custom function.
	 *
	 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE
	 * @param[in,out] control is the control array to get
	 * @param[in] count is the count of controls to get
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_control)(int pad_id,
			   struct vacq_control *control,
			   unsigned int count,
			   void *user);
	/**
	 * Set device control value(s) callback.
	 *
	 * This function is called by vacq_device_set_control(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and control pointer are checked before call.
	 *
	 * The control values are not verified by the caller: implementation
	 * should check the values with vacq_check_controls(),
	 * vacq_check_control_value() or a custom function.
	 *
	 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE
	 * @param[in,out] control is the control array to set
	 * @param[in] count is the count of controls to set
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*set_control)(int pad_id,
			   struct vacq_control *control,
			   unsigned int count,
			   void *user);

	/**
	 * Get device pad format callback.
	 *
	 * This function is called by vacq_device_get_format(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and format pointer are checked before call.
	 *
	 * This function is mandatory and must be implemented.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[out] format is set with the current frame format
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_format)(unsigned int pad_id,
			  struct vacq_format *format,
			  void *user);
	/**
	 * Set device pad format callback.
	 *
	 * This function is called by vacq_device_set_format(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and format pointer are checked before call.
	 * The format is not checked by caller and should be verified by device
	 * implementation.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] format is the frame format to set
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*set_format)(unsigned int pad_id,
			  const struct vacq_format *format,
			  void *user);

	/**
	 * Get device pad selection rectangle(s) callback.
	 *
	 * This function is called by vacq_device_get_selection(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and selection pointer are checked before call.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in,out] sel is the selection rectangle array to get
	 * @param[in] count is the count of selection rectangle to get
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_selection)(unsigned int pad_id,
			     struct vacq_selection *sel,
			     unsigned int count,
			     void *user);
	/**
	 * Set device pad selection rectangle(s) callback.
	 *
	 * This function is called by vacq_device_set_selection(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and selection pointer are checked before call.
	 * The selection rectangle values are not checked by caller and should
	 * be verified by device implementation.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in,out] sel is the selection rectangle array to set
	 * @param[in] count is the count of selection rectangle to set
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*set_selection)(unsigned int pad_id,
			     struct vacq_selection *sel,
			     unsigned int count,
			     void *user);

	/**
	 * Get device pad frame rate callback.
	 *
	 * This function is called by vacq_device_get_fps(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and frame rate pointer are checked before
	 * call.
	 *
	 * This function is mandatory and must be implemented.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[out] fps is set with the current frame rate
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_fps)(unsigned int pad_id, struct vacq_fps *fps, void *user);
	/**
	 * Set device pad frame rate callback.
	 *
	 * This function is called by vacq_device_set_fps(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and frame rate pointer are checked before
	 * call. The frame rate is not checked by caller and should be verified
	 * by device implementation.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] fps is the frame rate to set
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*set_fps)(unsigned int pad_id,
		       const struct vacq_fps *fps,
		       void *user);

	/**
	 * Get FIFO depth of device pad callback.
	 *
	 * This function is called by vacq_device_get_depth(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and pointers are checked before call. The pad
	 * capabilities are also checked and this function is called only if pad
	 * is compatible.
	 *
	 * This function is mandatory and must be implemented. If the control is
	 * not available or not supported, the count value can be fixed to a
	 * constant or to zero.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[out] count is set with the internal queue depth
	 * @param[out] flags is the flags currently applied
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_depth)(unsigned int pad_id,
			 unsigned int *count,
			 enum vacq_depth_flags *flags,
			 void *user);
	/**
	 * Set FIFO depth of device pad callback.
	 *
	 * This function is called by vacq_device_set_depth(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID is checked before call. The pad capabilities
	 * are also checked and this function is called only if pad is
	 * compatible.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] count is the number of buffer to allocate
	 * @param[in] count is the number of internal queue depth
	 * @param[in] flags is a bit-field of flags to specify actions
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*set_depth)(unsigned int pad_id,
			 unsigned int count,
			 enum vacq_depth_flags flags,
			 void *user);

	/**
	 * Start a stream capture / processing callback.
	 *
	 * This function is called by vacq_device_stream_on(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID is checked before call. The pad capabilities
	 * are also checked and this function is called only if the pad has the
	 * flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * This function is mandatory and must be implemented if one or more
	 * pads have the flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*stream_on)(unsigned int pad_id, void *user);
	/**
	 * Stop a stream capture / processing callback.
	 *
	 * This function is called by vacq_device_stream_off(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID is checked before call. The pad capabilities
	 * are also checked and this function is called only if the pad has the
	 * flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * This function is mandatory and must be implemented if one or more
	 * pads have the flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*stream_off)(unsigned int pad_id, void *user);

	/**
	 * Get a file descriptor callback.
	 *
	 * This function is called by vacq_device_get_fd(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID is checked before call. The pad capabilities
	 * are also checked and this function is called only if pad is
	 * compatible.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_fd)(unsigned int pad_id, void *user);
	/**
	 * Release a file descriptor callback.
	 *
	 * This function is called by vacq_device_release_fd(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and file descriptor are checked before call.
	 * The pad capabilities are also checked and this function is called
	 * only if pad is compatible.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] fd is the file descriptor to release
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*release_fd)(unsigned int pad_id, int fd, void *user);

	/**
	 * Queue a frame on a pad callback.
	 *
	 * This function is called by vacq_device_queue_frame(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and pointers are checked before call. The pad
	 * capabilities are also checked and this function is called only if the
	 * pad has the flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * If the timeout parameter was set to NULL during call to
	 * vacq_device_queue_frame(), a timeout of 0 will be passed to this
	 * function, which means the timeout parameter will be never NULL.
	 *
	 * This function is mandatory and must be implemented if one or more
	 * pads have the flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] buffer is the frame to queue in device
	 * @param[in] timeout is the time before function will return
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*queue_frame)(unsigned int pad_id,
			   struct vacq_buffer *buffer,
			   const struct timespec *timeout,
			   void *user);
	/**
	 * Dequeue a frame from a pad callback.
	 *
	 * This function is called by vacq_device_dequeue_frame(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and pointers are checked before call. The pad
	 * capabilities are also checked and this function is called only if the
	 * pad has the flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * If the timeout parameter was set to NULL during call to
	 * vacq_device_dequeue_frame(), a timeout of 0 will be passed to this
	 * function, which means the timeout parameter will be never NULL.
	 *
	 * This function is mandatory and must be implemented if one or more
	 * pads have the flag #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
	 *
	 * @param[in] pad_id is the pad ID of the device
	 * @param[in] timeout is the time before function will return
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return the video-acquisition frame, NULL otherwise.
	 */
	struct vacq_buffer *(*dequeue_frame)(unsigned int pad_id,
					     const struct timespec *timeout,
					     void *user);

	/**
	 * List available events of a device / device pad callback.
	 *
	 * This function is called by vacq_device_list_event(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and pointers are checked before call.
	 *
	 * @param[in] pad_id is the pad ID of the device or #VACQ_PAD_NONE
	 * @param[out] desc is a pointer to the returned list
	 * @param[out] count is a pointer to the event list count
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*list_event)(int pad_id,
			  const struct vacq_event_desc **desc,
			  unsigned int *count,
			  void *user);
	/**
	 * Subscribe to a device / device pad event callback.
	 *
	 * This function is called by vacq_device_subscribe_event(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and event subscriber pointer are checked
	 * before call. Check of event availability must be done in device
	 * implementation and if event is already subscribed for current device
	 * instance, an error should be returned.
	 *
	 * @param[in] pad_id is the pad ID of the device or #VACQ_PAD_NONE
	 * @param[in] sub is the description of the event to subscribe
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*subscribe_event)(int pad_id,
			       const struct vacq_event_sub *sub,
			       void *user);
	/**
	 * Unsubscribe from a device / device pad event callback.
	 *
	 * This function is called by vacq_device_unsubscribe_event(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and event subscriber pointer are checked
	 * before call.
	 *
	 * @param[in] pad_id is the pad ID of the device or #VACQ_PAD_NONE
	 * @param[in] sub is the description of the event to unsubscribe
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*unsubscribe_event)(int pad_id,
				 const struct vacq_event_sub *sub,
				 void *user);

	/**
	 * Get an event file descriptor callback.
	 *
	 * This function is called by vacq_device_get_event_fd(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID is checked before call.
	 *
	 * @param[in] pad_id is the pad ID of the device or #VACQ_PAD_NONE
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_event_fd)(int pad_id, void *user);
	/**
	 * Release an event file descriptor callback.
	 *
	 * This function is called by vacq_device_release_event_fd(). For more
	 * details on implementation, please see function documentation.
	 *
	 * The validity of pad ID and file descriptor are checked before call.
	 *
	 * @param[in] pad_id is the pad ID of the device or #VACQ_PAD_NONE
	 * @param[in] fd is the file descriptor to release
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*release_event_fd)(int pad_id, int fd, void *user);

	/**
	 * Get next event callback.
	 *
	 * This function is called by vacq_device_get_event(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of pad ID and event pointer are checked before call.
	 *
	 * @param[in] pad_id is the pad ID of the device or #VACQ_PAD_NONE
	 * @param[out] event is the next event dequeued
	 * @param[in] user is the pointer set by vacq_device_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_event)(int pad_id, struct vacq_event *event, void *user);
};

/**
 * Buffer pool operations.
 */
struct vacq_buffer_pool_ops {
	/**
	 * Get available free buffer count callback.
	 *
	 * This function provides the number of available free buffer in the
	 * pool.
	 *
	 * @param[in] user is the user pointer provided at pool creation
	 * @return the number of available free buffer.
	 */
	unsigned int (*get_free_count)(void *user);

	/**
	 * Get a free buffer callback.
	 *
	 * This function is called by vacq_buffer_pool_get() and it should
	 * return a free buffer or NULL if the pool is empty.
	 *
	 * @param[in] user is the user pointer provided at pool creation
	 * @return a free buffer or NULL.
	 */
	struct vacq_buffer *(*get)(void *user);

	/**
	 * Destroy pool callback.
	 *
	 * This function is called when buffer pool is destroyed with
	 * vacq_buffer_pool_free().
	 *
	 * @param[in] user is the user pointer provided at pool creation
	 * @return 0 if the pool has been destroyed, -1 otherwise.
	 */
	int (*destroy)(void *user);
};

/**
 * Media operations.
 *
 * This structure is the main entry point to implement a new type of media. It
 * is attached to a vacq_plugin and must be defined.
 *
 * It is loaded from the plugin at video-acquisition library initialization done
 * during vacq_init() call. The video-acquisition configuration file is parsed
 * to get the media list and initialize each instance.
 *
 * The library parser read the libconfig list member named 'media_list' from
 * configuration file root and for each item of the list, the group member
 * holding details on the media are parsed.
 *
 * Each media must define a type set in string member named 'type'. When a new
 * type is found, the corresponding plugin is loaded and the its
 * vacq_media_ops.init() implementation is called to initialize the new media.
 *
 * An example of configuration is:
 * @code
 * media_list: (
 *   {
 *     name = "Media foo";
 *     type = "foo";
 *     [...]
 *     );
 *   }
 * );
 * @endcode
 *
 * The following operations are mandatory:
 *  - vacq_media_ops.init(),
 *  - vacq_media_ops.get_topology(),
 *  - vacq_media_ops.get_device_ops().
 *
 * For more details, please read documentation of each operations.
 */
struct vacq_media_ops {
	/**
	 * Initialize media.
	 *
	 * At library initialization, the video-acquisition configuration file
	 * is parsed and one or more media are added to the global media list
	 * handled by the library. For each media, a type is specified and a
	 * plugin containing the media implementation is loaded. Then, the
	 * vacq_media_ops.init() function is called to initialize the media
	 * instance.
	 *
	 * For each instance, a unique ID is passed, with the corresponding
	 * member configuration read from the file. This configuration can be
	 * parsed by the init() implementation if necessary. The configuration
	 * member format are free but it is recommended to prefix all member
	 * names with the media type to avoid any conflicts in future version.
	 *
	 * The media descriptor is initialized by caller with only the type
	 * string. The other fields should be set by this functions. The
	 * ownership of descriptor fields is taken caller after the function
	 * returns, which means strings will automatically freed by the
	 * library and should not be a static string.
	 *
	 * The user field can be used to set a pointer which will be passed to
	 * next calls to the other functions of the same vacq_media instance.
	 * It is useful to manage an internal allocated context. The allocated
	 * memory and resources should be released and/or freed during
	 * vacq_media_ops.exit() call.
	 *
	 * All pointers are valid during call to this function.
	 *
	 * @param[in] id is the media ID (index of media in configuration file)
	 * @param[in] cfg is the libconfig configuration member corresponding to
	 *                this media instance
	 * @param[in,out] desc is the media descriptor to fill
	 * @param[out] user is a pointer which can be set to pass a pointer to
	 *                  subsequent calls to these operations
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*init)(unsigned int id,
		    config_setting_t *cfg,
		    struct vacq_media_desc *desc,
		    void **user);

	/**
	 * Parse a device configuration.
	 *
	 * After initializing a new media with vacq_media_ops.init(), the
	 * library continues to parse the media configuration loaded from
	 * video-acquisition configuration file.
	 *
	 * In this configuration, the user can list some devices by defining a
	 * list member with the name 'device_list'. Each element in list are
	 * groups and correspond to one device.
	 *
	 * The device ID can be specified with the integer member named 'id' and
	 * the device name can be specified with the string member named 'name'.
	 * If fields can be avoided: the ID will be the index of the element in
	 * the list and the name will be NULL.
	 *
	 * Additionally a pad list can be defined by adding a list member named
	 * 'pad_list' which contains groups as item for each pads. A pad can
	 * define the flags to apply with an array member named 'flags' which
	 * contains strings for each flag to set. The flag string is parsed with
	 * vacq_pad_flag_from_string().
	 * If the flags are not defined, the #VACQ_PAD_FLAGS_NONE is used.
	 *
	 * The configuration can reflects all or a part of devices and device
	 * pads: if no specific configuration is needed for a device or a pad,
	 * it can be avoided thanks to the integer member 'id'.
	 *
	 * An example of configuration is:
	 * @code
	 * media_list: (
	 *   {
	 *     name = "Media foo";
	 *     type = "foo";
	 *     [...]
	 *     device_list: (
	 *       {
	 *         id = 15
	 *         name = "device_0";
	 *         [...]
	 *         pad_list: (
	 *           {
	 *             flags = [ "source" ];
	 *             [...]
	 *           }
	 *         );
	 *       }
	 *     );
	 *   }
	 * );
	 * @endcode
	 *
	 * The library will fill a vacq_device_desc with all data enumerated
	 * above and will call the vacq_media_ops.parse_device() function to
	 * provide pre-parseddata and the device libconfig member configuration
	 * for further parsing.
	 *
	 * The other configuration member format are free but it is recommended
	 * to prefix all member names with a prefix to avoid any conflicts in
	 * future version.
	 *
	 * This function can be useful to add settings to the devices of a
	 * media. It can be also used to add some devices which depends on the
	 * product or configuration, like cameras.
	 *
	 * All pointers are valid during call to this function.
	 *
	 * @param[in] device is a device descriptor pre-filled with standard
	 *                   values read from configuration
	 * @param[in] cfg is the libconfig configuration member corresponding to
	 *                a device of the media instance
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*parse_device)(const struct vacq_device_desc *device,
			    config_setting_t *cfg,
			    void *user);

	/**
	 * Parse a link configuration.

	 *
	 * After initializing a new media with vacq_media_ops.init(), and
	 * parsing the device list within a media (and calling
	 * vacq_media_ops.parse_device()), the library continues to parse the
	 * media configuration loaded from video-acquisition configuration file.
	 *
	 * In this configuration, the user can also list some links to setup at
	 * initialization by defining a list member with the name 'link_list'.
	 * Each element in list are groups and correspond to one link.
	 *
	 * A link must specify a name with the string member named 'name'. This
	 * name must follow the format described in vacq_topology_parse_link()
	 * documentation. From this string, the parser fill a link descriptor.
	 *
	 * The link flags to set are provided with another array member named
	 * 'flags' which contains strings members for each flag to set. The flag
	 * strings are converted with vacq_link_flag_from_string().
	 * If the flags are not defined, the #VACQ_LINK_FLAGS_NONE is used.
	 *
	 * The configuration can reflects all or a part of links: if no specific
	 * flags and/or configuration are needed for a link, it can be avoided.
	 *
	 * An example of configuration is:
	 * @code
	 * media_list: (
	 *   {
	 *     name = "Media foo";
	 *     type = "foo";
	 *     link_list: (
	 *       { name = "device_0:0->device_1:0"; flags = [ "enabled" ]; },
	 *       { name = "device_1:1->device_2:0"; flags = [ "enabled" ]; }
	 *     );
	 *   }
	 * );
	 * @endcode
	 *
	 * The library will fill a vacq_link_desc with all data enumerated
	 * above and will call the vacq_media_ops.parse_config() function to
	 * provide parsed data and the link libconfig member configuration for
	 * further parsing.
	 *
	 * The other configuration member format are free but it is recommended
	 * to prefix all member names with a prefix to avoid any conflicts in
	 * future version.
	 *
	 * This function is useful to setup links differently from a product to
	 * another one at initialization.
	 *
	 * All pointers are valid during call to this function.
	 *
	 * @param[in] link is a link descriptor filled with the standard values
	 *                 read from configuration
	 * @param[in] cfg is the libconfig configuration member corresponding to
	 *                a link of the media instance
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*parse_link)(const struct vacq_link_desc *link,
			  config_setting_t *cfg,
			  void *user);

	/**
	 * Get current media topology callback.
	 *
	 * This function is called by vacq_media_get_topology() and
	 * vacq_media_get_device_id_by_name(). For more details on
	 * implementation, please see functions documentation.
	 *
	 * The tpology pointer is valid during call.
	 *
	 * This function is mandatory since it provides the media topology.
	 *
	 * @param[out] topology is a pointer set with a reference to the current
	 *                      topology
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_topology)(struct vacq_topology **topology, void *user);

	/**
	 * Setup a media link callback.
	 *
	 * This function is called by vacq_media_setup_link(). For more details
	 * on implementation, please see function documentation.
	 *
	 * The validity of link pointer is checked before call.
	 *
	 * This function is not mandatory if all links are static.
	 *
	 * @param[in] link is a link descriptor defining the link to modify
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*setup_link)(const struct vacq_link_desc *link, void *user);

	/**
	 * Create a buffer pool callback.
	 *
	 * This function is called by vacq_media_new_buffer_pool(). For more
	 * details on implement, please see function documentation.
	 *
	 * The operations and its data must be specified in order to create the
	 * new buffer pool. For more details on operations, please read the
	 * associated documentation.
	 *
	 * This function is not mandatory.
	 *
	 * @param[in] format is the format to allocate buffers
	 * @param[in] count is the number of buffers to allocate in pool
	 * @param[out] ops is the operations to use
	 * @param[out] ops_data is the pointer to use with operations callbacks
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*create_pool)(const struct vacq_format *format,
			   unsigned int count,
			   const struct vacq_buffer_pool_ops **ops,
			   void **ops_data,
			   void *user);

	/**
	 * Get device operations structure.
	 *
	 * This function is called when a new vacq_device is opened: the
	 * vacq_device_ops of the device is requested through this function and
	 * the vacq_device_ops.init() is then called to initialize internal
	 * context and resources of the device instance.
	 *
	 * The device_ops_data can be set during call: this pointer will be
	 * passed to the subsequent call to vacq_device_ops.init(). It can be
	 * used to pass an internal context from the media to the device
	 * instance.
	 *
	 * All parameters are valid during call.
	 *
	 * This function is mandatory since it is used to initialize and open a
	 * device.
	 *
	 * @param[in] device_id is the device ID
	 * @param[out] device_ops is a pointer which is set with the
	 *                        vacq_device_ops to use for device interaction
	 * @param[out] device_ops_data is a pointer which can be set to attach
	 *                             a pointer to the returned vacq_device_ops
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*get_device_ops)(unsigned int device_id,
			      const struct vacq_device_ops **device_ops,
			      void **device_ops_data,
			      void *user);

	/**
	 * Call an extended media function callback.
	 *
	 * This function is called by vacq_media_ext_func(). For more details on
	 * implementation, please see function documentation.
	 *
	 * The validity of func pointer is checked before call. However, the
	 * func_data parameter must be checked in the implementation since
	 * caller doesn't know which kind of data is required by extended
	 * function.
	 *
	 * @param[in] func is the name of the extended function
	 * @param[in,out] func_data is a pointer to function data
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*ext_func)(const char *func, void *func_data, void *user);

	/**
	 * Release media context and resources.
	 *
	 * This function is called when the library is exited with vacq_exit().
	 *
	 * All dependent devices and media instances created respectively with
	 * vacq_device_open() and vacq_media_open() are guaranteed to be fully
	 * released.
	 *
	 * If the user pointer has been defined during vacq_media_ops.init(),
	 * all resources must be released (and freed if necessary) here.
	 *
	 * @param[in] user is the pointer set by vacq_media_ops.init()
	 * @return 0 if the call succeeded, -1 otherwise.
	 */
	int (*exit)(void *user);
};

/**
 * Plugin descriptor.
 * A plugin is an additional library loaded at runtime by main instance of the
 * video-acquisition library.
 * A plugin provides an implementation for a specific media type.
 * A plugin should be defined as:
 * @code
 * const struct vacq_plugin VACQ_PLUGIN_INFO_SYM = {
 *         .type = "test",
 *         .version = VACQ_PLUGIN_VERSION,
 *         .media_ops = {},
 * };
 * @endcode
 */
struct vacq_plugin {
	/**
	 * Media type provided by plugin.
	 * This string defines the type of media implementation provided by the
	 * plugin. A type must be unique string.
	 */
	const char *type;
	/**
	 * API version.
	 * Version on which the plugin has been built. This version is checked
	 * at load and if it is different from library version defined by
	 * #VACQ_PLUGIN_VERSION, the load is aborted.
	 */
	const uint32_t version;
	/**
	 * Media operation.
	 * It contains all operations implementation for the media type defined
	 * by #type.
	 * See vacq_media_ops for more details.
	 */
	const struct vacq_media_ops media_ops;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VACQ_PLUGIN_H_ */
