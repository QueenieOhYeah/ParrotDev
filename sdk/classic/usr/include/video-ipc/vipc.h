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
 * @file vipc.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VIPC_H_
#define _VIPC_H_

#include <stdbool.h>
#include <stdint.h>

#include <libpomp.h>

#include <video-acquisition/vacq.h>
#include <video-defs/vdefs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* To be used for all public API */
#ifdef VIPC_API_EXPORTS
#	ifdef _WIN32
#		define VIPC_API __declspec(dllexport)
#	else /* !_WIN32 */
#		define VIPC_API __attribute__((visibility("default")))
#	endif /* !_WIN32 */
#else /* !VIPC_API_EXPORTS */
#	define VIPC_API
#endif /* !VIPC_API_EXPORTS */

/**
 * IPC library for video frames
 *
 * As usual all functions needs to be called from the pomp loop thread
 *
 */

/** Maximum number of planes */
#define VIPC_PLANE_COUNT 3
#if (VACQ_BUFFER_PLANE_COUNT < VIPC_PLANE_COUNT)
#	error "issue with VACQ_BUFFER_PLANE_COUNT"
#endif

/**
 * Frame dimension.
 */
struct vipc_dim {
	/** Width of the frame. */
	uint32_t width;
	/** Height of the frame. */
	uint32_t height;
};

/**
 * Frame crop rectangle.
 *
 * The crop rectangle is composed of float which must be set in the range of
 * 0.0 to 1.0: the values are relative.
 */
struct vipc_crop {
	/** Horizontal offset of the top-left corner of the crop rectangle. */
	float left;
	/** Vertical offset of the top-left corner of the crop rectangle. */
	float top;
	/** Width of the crop rectangle. */
	float width;
	/** Height of the crop rectangle. */
	float height;
};

/**
 * Status, sent at connection or whenever the configuration changes.
 *
 * width, height, display aspect ratio is the "original" format of the server:
 *	* this is what will be sent by default (without vipc_configure being
 *	  called)
 *	* frame cannot be configured bigger than this original format
 */
struct vipc_status {
	/** underlying backend */
	char *method;
	/** underlying backend parameters, used for backend initialisation */
	char *method_params;
	/** frame format */
	enum vacq_pix_format format;
	/** YUV full-range flag */
	bool full_range;
	/** Color primaries */
	enum vdef_color_primaries color_primaries;
	/** Transfer function */
	enum vdef_transfer_function transfer_function;
	/** Dynamic range */
	enum vdef_dynamic_range dynamic_range;
	/** Tone mapping */
	enum vdef_tone_mapping tone_mapping;
	/** frame width */
	uint32_t width;
	/** frame height */
	uint32_t height;
	/** display aspect ratio */
	float dar;
	/** number of planes [1, #VIPC_PLANE_COUNT] */
	unsigned int num_planes;
	/** planes */
	struct {
		/** stride (size in bytes of a row) for the plane */
		uint32_t stride;
		/** size in byte of the plane */
		size_t size;
	} planes[VIPC_PLANE_COUNT];
	/** framerate numerator */
	uint32_t framerate_num;
	/** framerate denominator */
	uint32_t framerate_den;
};

/**
 * Frame meta data presence flag.
 *
 * When a bit is set, the associated meta data value is set in the
 * vipc_frame_meta structure.
 */
enum vipc_meta_flag {
	/** No meta data are set. */
	VIPC_META_FLAG_NONE = 0,
	/** Exposure time is set in vipc_frame_meta.exposure_time_ns. */
	VIPC_META_FLAG_EXPOSURE_TIME = (1 << 0),
	/** A snapshot has been taken (no field is set in vipc_frame_meta) */
	VIPC_META_FLAG_SNAPSHOT = (1 << 1),
	/** YUV full-range is used (no field is set in vipc_frame_meta) */
	VIPC_META_FLAG_FULL_RANGE = (1 << 2),
};

/**
 * Frame meta data.
 *
 * This structure fields are intended to store some addition meta data within a
 * frame. The fields are optional and if no meta data are linked to the frame,
 * the flags value must be 0.
 */
struct vipc_frame_meta {
	/**
	 * Meta data presence.
	 * This is a bit-field composed by the enum vipc_meta_flag values. For
	 * more details, please read its documentation.
	 * When a bit is set, the associated meta data value is set below.
	 */
	uint64_t flags;

	/** Exposure time in ns (set #VIPC_META_FLAG_EXPOSURE_TIME). */
	uint64_t exposure_time_ns;
};

/**
 * frame
 */
struct vipc_frame {
	/** private context */
	void *context;
	/** frame index, used by the backend */
	uint32_t index;
	/** frame format */
	enum vacq_pix_format format;
	/** start of frame timestamp, ns */
	uint64_t ts_sof_ns;
	/** end of frame timestamp, ns */
	uint64_t ts_eof_ns;
	/** frame width */
	uint32_t width;
	/** frame height */
	uint32_t height;
	/** display aspect ratio */
	float dar;
	/** number of planes [1, #VIPC_PLANE_COUNT] */
	unsigned int num_planes;
	/** planes */
	struct {
		/** stride (size in bytes of a row) for the plane */
		uint32_t stride;
		/** size in byte of the plane */
		size_t size;
		/** virtual address if the plane is mapped */
		uintptr_t virt_addr;
	} planes[VIPC_PLANE_COUNT];
	/** Effective crop applied on frame. */
	struct vipc_crop crop;
	/** Additional meta data. */
	struct vipc_frame_meta meta;

	/** debug: vipc client output timestamp, ns */
	uint64_t ts_out_ns;

	/** private data (used by backend implementation) */
	void *priv;
};

/**
 * Configure flag.
 *
 * This enum is intended to set one or more configuration operation within the
 * vipc_configure structure. The field vipc_configure.flags must be set with one
 * or more if the flags and the associated field must be set accordingly.
 */
enum vipc_configure_flag {
	/** No configuration operation. */
	VIPC_CONFIGURE_FLAG_NONE = 0,

	/* Response flags */

	/**
	 * The configuration request has failed.
	 * If one of the operations is not supported, the flag
	 * #VIPC_CONFIGURE_FLAG_NOT_SUPPORTED is be set additionally. Otherwise,
	 * it means that one of the values related to operations requested is
	 * invalid.
	 */
	VIPC_CONFIGURE_FLAG_ERROR = (1 << 0),
	/**
	 * One of the operations is not supported.
	 * The not supported operations should be set as well in the
	 * vipc_configure.flags field to specify which operations are not
	 * supported.
	 */
	VIPC_CONFIGURE_FLAG_NOT_SUPPORTED = (1 << 1),

	/* Operations */

	/** Reset all frame settings to default. */
	VIPC_CONFIGURE_FLAG_RESET = (1 << 2),
	/**
	 * Change the frame resolution.
	 * The resolution of the frame which will be sent by the video IPC
	 * server.
	 */
	VIPC_CONFIGURE_FLAG_RESOLUTION = (1 << 3),
	/**
	 * Change the crop rectangle in the original frame.
	 * The crop is applied on the original video frame: the frame resolution
	 * set with #VIPC_CONFIGURE_FLAG_RESOLUTION will be a down/up-scale from
	 *  the resolution set by the crop rectangle.
	 */
	VIPC_CONFIGURE_FLAG_CROP = (1 << 4),
};
#define VIPC_CONFIGURE_FLAG_ALL_OPS                                            \
	(VIPC_CONFIGURE_FLAG_RESET | VIPC_CONFIGURE_FLAG_RESOLUTION |          \
	 VIPC_CONFIGURE_FLAG_CROP)

/**
 * Configure frame resolution / crop.
 *
 * This structure is used to do dynamic configuration on a video IPC server,
 * even if it is started.
 * For operations currently supported, please refer to vipc_configure_flag
 * enumerator.
 */
struct vipc_configure {
	/**
	 * Configuration flags.
	 * This is a bit-field composed by the enum vipc_configure_flag values.
	 * For more details, please read its documentation.
	 */
	uint8_t flags;

	/**
	 * Frame resolution to output.
	 * This field must be set when flag #VIPC_CONFIGURE_FLAG_RESOLUTION is
	 * set.
	 */
	struct vipc_dim resolution;

	/**
	 * Crop in original image.
	 * This crop is effective only when the flag #VIPC_CONFIGURE_FLAG_CROP
	 * is set in flags.
	 */
	struct vipc_crop crop;
};

/**
 * End Of Stream reason.
 *
 * This enum is used to know the reason why a video IPC stream is stopping.
 */
enum vipc_eos_reason {
	/**
	 * No reason.
	 * When the video IPC stream is stopped for a long period or the program
	 * is exited and the video source is not anymore active, this reason
	 * should be used.
	 */
	VIPC_EOS_REASON_NONE = 0,
	/**
	 * Restart of video IPC stream.
	 * This reason can be used to specify the source of the video IPC stream
	 * is restarting or changing its configuration.
	 * It means that the stream is temporarily stopped but will restart as
	 * soon as possible.
	 */
	VIPC_EOS_REASON_RESTART,
	/**
	 * Configuration change has stopped the video IPC stream.
	 * This reason can be used to indicate that a configuration change has
	 * stopped the video IPC stream but does not mean that the stream
	 * will restart.
	 */
	VIPC_EOS_REASON_CONFIGURATION,
};

/** Video IPC back-end context. */
struct vipc_be_ctx;

/** Video IPC back-end callbacks. */
struct vipc_be_cb;

/** Video IPC client context. */
struct vipcc_ctx;

/* helper functions */

/**
 * Fill out a vipc frame from a vacq_buffer
 *
 * @param[in] buffer
 * @param[out] frame
 *
 * @return 0 in case of success, -errno for failure
 */
VIPC_API int vipc_frame_from_vacq_buffer(const struct vacq_buffer *const buffer,
					 struct vipc_frame *frame);

/**
 * Convert an EOS reason to string.
 *
 * @param[in] reason the reason to convert
 * @return the string corresponding to the reason
 */
VIPC_API const char *vipc_eos_reason_to_str(enum vipc_eos_reason reason);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VIPC_H_ */
