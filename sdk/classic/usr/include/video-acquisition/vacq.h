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
 * @file vacq.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VACQ_H_
#define _VACQ_H_

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#include <video-defs/vdefs.h>

#include <video-acquisition/vacq_controls.h>
#include <video-acquisition/vacq_events.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* To be used for all public API */
#ifdef VACQ_API_EXPORTS
#	ifdef _WIN32
#		define VACQ_API __declspec(dllexport)
#	else /* !_WIN32 */
#		define VACQ_API __attribute__((visibility("default")))
#	endif /* !_WIN32 */
#else /* !VACQ_API_EXPORTS */
/** API export. */
#	define VACQ_API
#endif /* !VACQ_API_EXPORTS */

/**
 * Data types
 */

/* Opaque structures */
struct vacq_media;
struct vacq_topology;
struct vacq_device;

/**
 * Device pad flags.
 *
 * A pad has one or more flags to specify its type and its capabilities.
 */
enum vacq_pad_flags {
	/**
	 * No flags.
	 * This value is prohibited since it doesn't define a pad as a source or
	 * a sink.
	 */
	VACQ_PAD_FLAGS_NONE = 0,
	/**
	 * Pad is a sink.
	 * Data enter the device through the pad.
	 * The pad cannot have the flag #VACQ_PAD_FLAGS_SOURCE also set!
	 */
	VACQ_PAD_FLAGS_SINK = (1 << 0),
	/**
	 * Pad is a source.
	 * Data exit the device through the pad.
	 * The pad cannot have the flag #VACQ_PAD_FLAGS_SINK also set!
	 */
	VACQ_PAD_FLAGS_SOURCE = (1 << 1),
	/**
	 * Pad must be connected.
	 * The device won't start any activities until the pad is connected to
	 * another pad through one or more link(s) described with
	 * vacq_link_desc.
	 */
	VACQ_PAD_FLAGS_MUST_CONNECT = (1 << 2),
	/**
	 * Pad has a memory interface.
	 * The pad can read (if #VACQ_PAD_FLAGS_SINK is set) or write (if
	 * #VACQ_PAD_FLAGS_SOURCE is set) to the memory (RAM).
	 *
	 * If the pad doesn't have this flag set, the call to following
	 * functions will fail:
	 *  - vacq_device_stream_on() / vacq_device_stream_off(),
	 *  - vacq_device_get_fd() / vacq_device_release_fd(),
	 *  - vacq_device_dequeue_frame() / vacq_device_queue_frame().
	 */
	VACQ_PAD_FLAGS_MEMORY_INTERFACE = (1 << 3),
};

/**
 * Media link flags.
 *
 * A link can have one or more flags to specify its state and capabilities.
 * If no flags are set for a link, it means it is disabled.
 */
enum vacq_link_flags {
	/** No flags: link is disabled. */
	VACQ_LINK_FLAGS_NONE = 0,
	/** Link is enabled. */
	VACQ_LINK_FLAGS_ENABLED = (1 << 0),
	/**
	 * Link is immutable.
	 * The link state cannot be changed and any attempt to change its state
	 * with vacq_media_setup_link() will results with an error.
	 */
	VACQ_LINK_FLAGS_IMMUTABLE = (1 << 1),
	/**
	 * Link is dynamic.
	 * The link state can be changed dynamically at runtime. If this flag is
	 * not set, any call to vacq_media_setup_link() will results with an
	 * error if the pad is started.
	 */
	VACQ_LINK_FLAGS_DYNAMIC = (1 << 2),
};

/**
 * Media descriptor.
 *
 * This structure provides details on a media as its name or its type.
 */
struct vacq_media_desc {
	/** Media ID. */
	unsigned int id;
	/**
	 * Name of the media.
	 * Each media instance of a same type must have different names.
	 */
	char *name;
	/**
	 * Type of the media.
	 * A media type is a unique string. The corresponding implementation is
	 * loaded at runtime from a video-acquisition plugin.
	 */
	char *type;
};

/**
 * Device pad descriptor.
 *
 * This structure is used to provide some details on a device pad.
 * The flags contains the state and capabilities of the pad.
 */
struct vacq_pad_desc {
	/** Pad ID. */
	unsigned int id;
	/** Pad flags (see vacq_pad_flags for more details). */
	enum vacq_pad_flags flags;
};

/**
 * Device descriptor.
 *
 * This structure is used to provide some details on a device, such as its name
 * and number of pads.
 */
struct vacq_device_desc {
	/** Device ID. */
	unsigned int id;
	/** Device name. */
	char *name;
	/** Number of pads. */
	unsigned int pad_count;
	/** List of pads. */
	struct vacq_pad_desc *pad_list;
};

/**
 * Media link descriptor.
 *
 * This structure is used to provide some details on a media link which is
 * basically a link between two device pads (one source pad and one sink pad).
 * It contains the sink and source device and their respective sink and source
 * pad.
 *
 * The flags contains the state and capabilities of the link.
 */
struct vacq_link_desc {
	/** Link ID. */
	unsigned int id;
	/** Sink device ID. */
	unsigned int sink_dev;
	/** Sink pad ID of the sink device. */
	unsigned int sink_pad;
	/** Source device ID. */
	unsigned int source_dev;
	/** Source pad ID of the source device. */
	unsigned int source_pad;
	/** Link flags (see vacq_link_flags for more details). */
	enum vacq_link_flags flags;
};

/**
 * Propagation flags.
 *
 * This enumerator is used to select options for format propagation in a media
 * topology through a call to vacq_media_propagate().
 *
 * The #VACQ_PROPAGATE_FLAGS_DOWNSTREAM and #VACQ_PROPAGATE_FLAGS_UPSTREAM flags
 * cannot be set in once.
 */
enum vacq_propagate_flags {
	/**
	 * No flags: do not propagate format.
	 * Only the current device pad formats are updated.
	 */
	VACQ_PROPAGATE_FLAGS_NONE = 0,

	/** Propagate format from device to first source device. */
	VACQ_PROPAGATE_FLAGS_DOWNSTREAM = (1 << 0),
	/** Propagate format from device to last sink device. */
	VACQ_PROPAGATE_FLAGS_UPSTREAM = (1 << 1),

	/** Update resolution. */
	VACQ_PROPAGATE_FLAGS_SET_RESOLUTION = (1 << 2),
	/** Update pixel format. */
	VACQ_PROPAGATE_FLAGS_SET_PIX_FORMAT = (1 << 3),
	/** Update frame rate. */
	VACQ_PROPAGATE_FLAGS_SET_FPS = (1 << 4),
};

/** Video / image frame pixel format. */
enum vacq_pix_format {
	/**
	 * Unknown format.
	 * This pixel format is unknown and it should be not used.
	 */
	VACQ_PIX_FORMAT_UNKNOWN = 0,

	/** RAW pixel of 8-bits. */
	VACQ_PIX_FORMAT_RAW8,
	/**
	 * RAW pixel of 10-bits.
	 *
	 * Pixel data is aligned on 16-bits.
	 *
	 * The actual size in bytes of a line is (pixel_count * 2).
	 */
	VACQ_PIX_FORMAT_RAW10,
	/**
	 * RAW pixel of 10-bits.
	 *
	 * Pixel data is packet on 10-bits.
	 *
	 * The actual size in bytes of a line is (pixel_count * 10 / 8).
	 */
	VACQ_PIX_FORMAT_RAW10_PACKED,
	/**
	 * RAW pixel of 12-bits.
	 *
	 * Pixel data is aligned on 16-bits.
	 *
	 * The actual size in bytes of a line is (pixel_count * 2).
	 */
	VACQ_PIX_FORMAT_RAW12,
	/**
	 * RAW pixel of 12-bits.
	 *
	 * Pixel data is packet on 12-bits.
	 *
	 * The actual size in bytes of a line is (pixel_count * 12 / 8).
	 */
	VACQ_PIX_FORMAT_RAW12_PACKED,
	/**
	 * RAW pixel of 14-bits.
	 *
	 * Pixel data is aligned on 16-bits.
	 *
	 * The actual size in bytes of a line is (pixel_count * 2).
	 */
	VACQ_PIX_FORMAT_RAW14,
	/**
	 * RAW pixel of 14-bits.
	 *
	 * Pixel data is packet on 14-bits.
	 *
	 * The actual size in bytes of a line is (pixel_count * 14 / 8).
	 */
	VACQ_PIX_FORMAT_RAW14_PACKED,
	/** RAW pixel of 16-bits. */
	VACQ_PIX_FORMAT_RAW16,
	/** RAW pixel of 32-bits. */
	VACQ_PIX_FORMAT_RAW32,

	/** Bayer RGGB pixel of 8-bits. */
	VACQ_PIX_FORMAT_BAYER_RGGB,
	/** Bayer GRBG pixel of 8-bits. */
	VACQ_PIX_FORMAT_BAYER_GRBG,
	/** Bayer BGGR pixel of 8-bits. */
	VACQ_PIX_FORMAT_BAYER_BGGR,
	/** Bayer GBRG pixel of 8-bits. */
	VACQ_PIX_FORMAT_BAYER_GBRG,

	/**
	 * Bayer RGGB pixel of 10-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW10)
	 */
	VACQ_PIX_FORMAT_BAYER_RGGB_10B,
	/**
	 * Bayer GRBG pixel of 10-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW10)
	 */
	VACQ_PIX_FORMAT_BAYER_GRBG_10B,
	/**
	 * Bayer BGGR pixel of 10-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW10)
	 */
	VACQ_PIX_FORMAT_BAYER_BGGR_10B,
	/**
	 * Bayer GBRG pixel of 10-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW10)
	 */
	VACQ_PIX_FORMAT_BAYER_GBRG_10B,
	/**
	 * Bayer RGGB pixel of 10-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW10_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_RGGB_10B_PACKED,
	/**
	 * Bayer GRBG pixel of 10-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW10_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_GRBG_10B_PACKED,
	/**
	 * Bayer BGGR pixel of 10-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW10_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_BGGR_10B_PACKED,
	/**
	 * Bayer GBRG pixel of 10-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW10_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_GBRG_10B_PACKED,

	/**
	 * Bayer RGGB pixel of 12-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW12)
	 */
	VACQ_PIX_FORMAT_BAYER_RGGB_12B,
	/**
	 * Bayer GRBG pixel of 12-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW12)
	 */
	VACQ_PIX_FORMAT_BAYER_GRBG_12B,
	/**
	 * Bayer BGGR pixel of 12-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW12)
	 */
	VACQ_PIX_FORMAT_BAYER_BGGR_12B,
	/**
	 * Bayer GBRG pixel of 12-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW12)
	 */
	VACQ_PIX_FORMAT_BAYER_GBRG_12B,
	/**
	 * Bayer RGGB pixel of 12-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW12_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_RGGB_12B_PACKED,
	/**
	 * Bayer GRBG pixel of 12-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW12_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_GRBG_12B_PACKED,
	/**
	 * Bayer BGGR pixel of 12-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW12_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_BGGR_12B_PACKED,
	/**
	 * Bayer GBRG pixel of 12-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW12_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_GBRG_12B_PACKED,

	/**
	 * Bayer RGGB pixel of 14-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW14)
	 */
	VACQ_PIX_FORMAT_BAYER_RGGB_14B,
	/**
	 * Bayer GRBG pixel of 14-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW14)
	 */
	VACQ_PIX_FORMAT_BAYER_GRBG_14B,
	/**
	 * Bayer BGGR pixel of 14-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW14)
	 */
	VACQ_PIX_FORMAT_BAYER_BGGR_14B,
	/**
	 * Bayer GBRG pixel of 14-bits.
	 * Same size and alignment as #VACQ_PIX_FORMAT_RAW14)
	 */
	VACQ_PIX_FORMAT_BAYER_GBRG_14B,
	/**
	 * Bayer RGGB pixel of 14-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW14_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_RGGB_14B_PACKED,
	/**
	 * Bayer GRBG pixel of 14-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW14_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_GRBG_14B_PACKED,
	/**
	 * Bayer BGGR pixel of 14-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW14_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_BGGR_14B_PACKED,
	/**
	 * Bayer GBRG pixel of 14-bits.
	 * Same size and packing as #VACQ_PIX_FORMAT_RAW14_PACKED)
	 */
	VACQ_PIX_FORMAT_BAYER_GBRG_14B_PACKED,

	/** Bayer RGGB pixel of 16-bits. */
	VACQ_PIX_FORMAT_BAYER_RGGB_16B,
	/** Bayer GRBG pixel of 16-bits. */
	VACQ_PIX_FORMAT_BAYER_GRBG_16B,
	/** Bayer BGGR pixel of 16-bits. */
	VACQ_PIX_FORMAT_BAYER_BGGR_16B,
	/** Bayer GBRG pixel of 16-bits. */
	VACQ_PIX_FORMAT_BAYER_GBRG_16B,

	/** Grey pixel (as RAW8 or Y single plane) */
	VACQ_PIX_FORMAT_GREY,

	/** Interleaved YUYV 4:2:2. */
	VACQ_PIX_FORMAT_YUYV,
	/** Interleaved YYUV 4:2:2. */
	VACQ_PIX_FORMAT_YYUV,
	/** Interleaved YVYU 4:2:2. */
	VACQ_PIX_FORMAT_YVYU,
	/** Interleaved UYVY 4:2:2. */
	VACQ_PIX_FORMAT_UYVY,
	/** Interleaved VYUY 4:2:2. */
	VACQ_PIX_FORMAT_VYUY,

	/** Semi-planar Y-UV 4:2:0 */
	VACQ_PIX_FORMAT_NV12,
	/** Semi-planar Y-VU 4:2:0 */
	VACQ_PIX_FORMAT_NV21,
	/** Semi-planar Y-UV 4:2:2 */
	VACQ_PIX_FORMAT_NV16,
	/** Semi-planar Y-VU 4:2:2 */
	VACQ_PIX_FORMAT_NV61,

	/** Semi-planar Y-UV 4:2:0 10-bit */
	VACQ_PIX_FORMAT_NV12_10B,
	/** Semi-planar Y-VU 4:2:0 10-bit */
	VACQ_PIX_FORMAT_NV21_10B,
	/** Semi-planar Y-UV 4:2:2 10-bit */
	VACQ_PIX_FORMAT_NV16_10B,
	/** Semi-planar Y-VU 4:2:2 10-bit */
	VACQ_PIX_FORMAT_NV61_10B,

	/** Semi-planar Y-UV 4:2:0 10-bit packed */
	VACQ_PIX_FORMAT_NV12_10B_PACKED,
	/** Semi-planar Y-VU 4:2:0 10-bit packed */
	VACQ_PIX_FORMAT_NV21_10B_PACKED,
	/** Semi-planar Y-UV 4:2:2 10-bit packed */
	VACQ_PIX_FORMAT_NV16_10B_PACKED,
	/** Semi-planar Y-VU 4:2:2 10-bit packed */
	VACQ_PIX_FORMAT_NV61_10B_PACKED,

	/** Multi-planar Y-U-V 4:2:0 */
	VACQ_PIX_FORMAT_YUV420,
	/** Multi-planar Y-V-U 4:2:0 */
	VACQ_PIX_FORMAT_YVU420,
	/** Multi-planar Y-U-V 4:2:2 */
	VACQ_PIX_FORMAT_YUV422,
	/** Multi-planar Y-V-U 4:2:2 */
	VACQ_PIX_FORMAT_YVU422,

	/** RGB packed into 24 bits/pix (8 bits/channel) */
	VACQ_PIX_FORMAT_RGB24,
	/** BGR packed into 24 bits/pix (8 bits/channel) */
	VACQ_PIX_FORMAT_BGR24,
	/** RGBA packed into 32 bits/pix (8 bits/channel) */
	VACQ_PIX_FORMAT_RGBA32,
	/** BGRA packed into 32 bits/pix (8 bits/channel) */
	VACQ_PIX_FORMAT_BGRA32,

	VACQ_PIX_FORMAT_COUNT
};

/** Video / image field configuration. */
enum vacq_field {
	/**
	 * Let device to select field base.
	 *
	 * This field is only relevant for vacq_device_set_format() calls:
	 * device will select best field configuration and the returned value by
	 * the function is the selected configuration.
	 */
	VACQ_FIELD_ANY = 0,
	/** Frame based: image is progressive. */
	VACQ_FIELD_NONE,
	/**
	 * Odd field.
	 *
	 * When set with vacq_device_set_format(), the device will only capture
	 * the odd field.
	 *
	 * In struct vacq_buffer, it means that only the odd field is contained
	 * in the buffer.
	 */
	VACQ_FIELD_TOP,
	/**
	 * Even field.
	 *
	 * When set with vacq_device_set_format(), the device will only capture
	 * the even field.
	 *
	 * In struct vacq_buffer, it means that only the even field is contained
	 * in the buffer.
	 */
	VACQ_FIELD_BOTTOM,
	/**
	 * Interleaved line by line.
	 *
	 * When set with vacq_device_set_format(), the device will capture both
	 * fields.
	 *
	 * In struct vacq_buffer, it means that both fields are contained in the
	 * buffer, interleaved line by line.
	 */
	VACQ_FIELD_INTERLACED,
	/**
	 * Odd then even fields.
	 *
	 * When set with vacq_device_set_format(), the device will capture both
	 * fields and stored as odd field first and then even field in memory.
	 *
	 * In struct vacq_buffer, it means that both fields are contained in the
	 * buffer, first odd field followed immediately by even field in memory.
	 */
	VACQ_FIELD_SEQ_TB,
	/**
	 * Even then odd fields.
	 *
	 * When set with vacq_device_set_format(), the device will capture both
	 * fields and stored as even field first and then odd field in memory.
	 *
	 * In struct vacq_buffer, it means that both fields are contained in the
	 * buffer, first even field followed immediately by odd field in memory.
	 */
	VACQ_FIELD_SEQ_BT,
	/**
	 * Alternate fields.
	 *
	 * When set with vacq_device_set_format(), the device will capture both
	 * fields and stored alternatively in frame buffers.
	 *
	 * In struct vacq_buffer, it means that both fields are contained in two
	 * different buffers, alternatively.
	 */
	VACQ_FIELD_ALTERNATE,
	/**
	 * Interleaved line by line, odd first.
	 *
	 * Please see #VACQ_FIELD_INTERLACED.
	 */
	VACQ_FIELD_INTERLACED_TB,
	/**
	 * Interleaved line by line, even first.
	 *
	 * Please see #VACQ_FIELD_INTERLACED.
	 */
	VACQ_FIELD_INTERLACED_BT,

	VACQ_FIELD_COUNT
};

/**
 * Video / image frame resolution.
 */
struct vacq_resolution {
	/** Width of the frame. */
	unsigned int width;
	/** Height of the frame. */
	unsigned int height;
};

/**
 * Video / image frame format.
 *
 * A video / image frame format is composed of a pixel format, the width and the
 * height of the frame.
 */
struct vacq_format {
	/** Video / image pixel format. */
	enum vacq_pix_format pix_format;
	/** Width of the frame. */
	unsigned int width;
	/** Height of the frame. */
	unsigned int height;
	/** Field order. */
	enum vacq_field field;
	/** YUV full-range flag. */
	bool full_range;
	/** Dynamic range. */
	enum vdef_dynamic_range dynamic_range;
	/** Tone mapping. */
	enum vdef_tone_mapping tone_mapping;
	/**
	 * Stride (bytes per line) of the frame.
	 * If the user set this value to zero, the device will automatically set
	 * the needed stride.
	 */
	unsigned int stride;
	/**
	 * Scanline (number of lines) of each planes.
	 * If the user set this value to zero, the device will automatically set
	 * the needed scanline to the height.
	 */
	unsigned int scanline;
	/**
	 * Alignment of the frame.
	 * This value can be set to specify the memory buffer alignment
	 * constraints. If the value is set to zero, the device will
	 * automatically set the needed alignment.
	 */
	unsigned int align;
	/** Color primaries. */
	enum vdef_color_primaries color_primaries;
	/** Transfer functions. */
	enum vdef_transfer_function transfer_function;
};

/**
 * Video frame rate / fps (frame per second).
 *
 * This value describe the time between two consecutive frame.
 *
 * The actual frame rate is calculated as:
 * @code
 * float fps = vacq_fps.num * 1.0 / vacq_fps.den;
 * @endcode
 */
struct vacq_fps {
	/** Numerator of the frame rate.*/
	unsigned int num;
	/** denominator of the frame rate.*/
	unsigned int den;
};

/**
 * Video / image rectangle.
 *
 * This structure can be used to describe a crop or a region of interest (ROI).
 */
struct vacq_rect {
	/** Horizontal offset of the top-left corner of the rectangle. */
	int left;
	/** Vertical offset of the top-left corner of the rectangle. */
	int top;
	/** Width of the rectangle. */
	unsigned int width;
	/** Height of the rectangle. */
	unsigned int height;
};

/**
 * Video / image selection target.
 *
 * A selection target is used to select which cropping or composing rectangle
 * will be accessed.
 *
 * The selection rectangles are split in two main categories:
 *  - a crop rectangle : it will be used to select a region of a source image,
 *  - a compose rectangle: it will be used to select a region of a destination
 *                         image or video buffer.
 *
 * This API follows the V4L2's selection API and more details, explanation and
 * schematics can be found in Selection API documentation section of Linux
 * kernel and Linux media subsystem documentation:
 * https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/selection-api.html
 */
enum vacq_sel_target {
	/**
	 * Crop rectangle.
	 *
	 * It must fit inside the crop rectangle defined by
	 * #VACQ_SEL_TARGET_CROP_BOUNDS.
	 *
	 * For a camera sensor, it can be used to set the Digital / ISP crop.
	 */
	VACQ_SEL_TARGET_CROP = 0,
	/**
	 * Default crop rectangle.
	 * It should be the value applied by default, at first load. It follows
	 * same restrictions as #VACQ_SEL_TARGET_CROP.
	 */
	VACQ_SEL_TARGET_CROP_DEFAULT,
	/**
	 * Bounds of the crop rectangle.
	 *
	 * A valid crop rectangle defined with #VACQ_SEL_TARGET_CROP must fit
	 * inside this rectangle.
	 *
	 * For a camera sensor, it can be used to set the Analog crop.
	 */
	VACQ_SEL_TARGET_CROP_BOUNDS,
	/**
	 * The native size of the device.
	 *
	 * A valid crop rectangle defined with #VACQ_SEL_TARGET_CROP_BOUNDS must
	 * fit inside this rectangle.
	 *
	 * For a camera sensor, it can be used to provide pixel array size.
	 */
	VACQ_SEL_TARGET_NATIVE_SIZE,

	/**
	 * Compose rectangle.
	 *
	 * It must fit inside the compose rectangle defined by
	 * #VACQ_SEL_TARGET_COMPOSE_BOUNDS.
	 *
	 * For a camera sensor, it can be used to set output of an internal
	 * scaler / ISP.
	 */
	VACQ_SEL_TARGET_COMPOSE,
	/**
	 * Default compose rectangle.
	 * It should be the value applied by default, at first load. It follows
	 * same restrictions as #VACQ_SEL_TARGET_COMPOSE.
	 */
	VACQ_SEL_TARGET_COMPOSE_DEFAULT,
	/**
	 * Bounds of the compose rectangle.
	 *
	 * A valid compose rectangle defined with #VACQ_SEL_TARGET_COMPOSE must
	 * fit inside this rectangle.
	 *
	 * The vacq_rect.left and vacq_rect.top should be set to 0 and the
	 * vacq_rect.width and vacq_rect.height should be set to the resolution
	 * defined on the device pad with vacq_device_set_format().
	 */
	VACQ_SEL_TARGET_COMPOSE_BOUNDS,
	/**
	 * Padding pixels area.
	 * It is the active area and all padding pixels that are inserted or
	 * modified by device.
	 */
	VACQ_SEL_TARGET_COMPOSE_PADDED,

	VACQ_SEL_TARGET_COUNT
};

/**
 * Video / image selection flags for application.
 *
 * These flags are used to specify some restrictions on the adjustments done by
 * the device, of the rectangle during a call to vacq_device_set_selection().
 */
enum vacq_sel_flags {
	/** The device adjust rectangle freely. */
	VACQ_SEL_FLAGS_NONE = 0,
	/** The device is not allowed to shrink the rectangle. */
	VACQ_SEL_FLAGS_GE = (1 << 0),
	/** The device is not allowed to enlarge the rectangle. */
	VACQ_SEL_FLAGS_LE = (1 << 1),
	/**
	 * The device must use the rectangle.
	 *
	 * This flag is equal to VACQ_SEL_FLAGS_GE | VACQ_SEL_FLAGS_LE.
	 *
	 * If the rectangle cannot be applied, the function involved will return
	 * an error.
	 */
	VACQ_SEL_FLAGS_KEEP = VACQ_SEL_FLAGS_GE | VACQ_SEL_FLAGS_LE,

	/**
	 * Do not apply the rectangle.
	 * When this flag is set during a call to vacq_device_set_selection(),
	 * the rectangle won't be applied to the device pad but the components
	 * of the rectangle will be arranged in respect with the other flags of
	 * the selection request.
	 */
	VACQ_SEL_FLAGS_TRY = (1 << 2),
};

/**
 * Video / image selection rectangle of a device pad.
 *
 * This structure describes the current selection rectangle applied or to apply
 * on a device pad (if supported). This API can be used to set some crops and
 * target rectangle to perform some scaling or composition of images internally
 * in the device.
 *
 * It can be used for a camera sensor device to control analog crop, an optional
 * digital / ISP crop and an optional scaler.
 *
 * It can also be used to control all internal processing of an image processor
 * device: crop at sink pad(s), internal composition and scaling, crop at source
 * pad(s).
 *
 * The #target field is used to select which rectangle to interact with. For
 * more details, please see #vacq_sel_target.
 *
 * By default, when a new rectangle is set with vacq_device_set_selection(), the
 * device will adapt the rectangle to fit its internal restrictions (like
 * hardware limitations). The #flags field can be used to add some restriction
 * on the adjustments the device will do on the rectangle. Please see
 * #vacq_sel_flags for more details.
 */
struct vacq_selection {
	/**
	 * Selection target.
	 * This field can be used to select which cropping / composing rectangle
	 * to set. See #vacq_sel_target for more details.
	 */
	enum vacq_sel_target target;
	/**
	 * Selection flags.
	 * Set the behaviour and adjustments to perform on rectangle. See
	 * #vacq_sel_flags for more details.
	 */
	enum vacq_sel_flags flags;
	/**
	 * Selection rectangle.
	 * See #vacq_sel_target targets for restriction on rectangle values.
	 */
	struct vacq_rect rect;
};

/**
 * Pad depth flags.
 *
 * These flags can be set to specify some specific actions when setting the
 * depth of a device pad. They are passed during a call to
 * vacq_device_set_depth().
 */
enum vacq_depth_flags {
	/** No specific action. */
	VACQ_DEPTH_FLAGS_NONE = 0,

	/**
	 * Don't allocate buffers on the device pad.
	 * When set, the device won't allocate any buffers: the user must queue
	 * and dequeue buffers from another device or buffer pool.
	 * If not set, the vacq_device_queue_frame() will refuse external
	 * buffers (not allocated by the device).
	 */
	VACQ_DEPTH_FLAGS_NO_ALLOCATE = (1 << 0),

	/**
	 * Map all buffers.
	 * When set, all allocated buffers will be mapped in user-space and the
	 * vacq_buffer_plane.data will be set accordingly with the virtual
	 * address of each frame planes at every call to vacq_dequeue_frame().
	 * This flag should be used if application will access all frame data.
	 * If only a few bytes are accessed for each frame, please consider
	 * usage of the vacq_buffer_map() and vacq_buffer_unmap() functions.
	 * Finally, if the application doesn't access frame data, (frame is got
	 * from one device and send to another device), this flag should be not
	 * set.
	 *
	 * This flag is exclusive with #VACQ_DEPTH_FLAGS_NO_ALLOCATE.
	 */
	VACQ_DEPTH_FLAGS_MAP = (1 << 1),
	/**
	 * Map all buffers as cached.
	 * If set with #VACQ_DEPTH_FLAGS_MAP, the buffers will be mapped with
	 * the CPU cache enabled.
	 */
	VACQ_DEPTH_FLAGS_MAP_CACHED = (1 << 2),

	/** Mark buffers with #VACQ_BUFFER_FLAGS_NO_CACHE_INVALIDATE. */
	VACQ_DEPTH_FLAGS_NO_CACHE_INVALIDATE = (1 << 3),
	/** Mark buffers with #VACQ_BUFFER_FLAGS_NO_CACHE_CLEAN. */
	VACQ_DEPTH_FLAGS_NO_CACHE_CLEAN = (1 << 4),
};

/**
 * Video / image buffer flags.
 */
enum vacq_buffer_flags {
	/** The buffer has no flags set */
	VACQ_BUFFER_FLAGS_NONE = 0,

	/**
	 * Buffer memory is not mapped to user-space.
	 * Some buffer memory cannot be mapped to user-space (e.g. DMA buffer
	 * memory). In such case, this flag is set to specify the application
	 * that memory won't be accessible for read and / or write. If this flag
	 * is not set, the frame is considered readable / writable by CPU.
	 */
	VACQ_BUFFER_FLAGS_NOT_MAPPED = (1 << 0),

	/**
	 * The buffer has encountered an error.
	 * When this flag is set, the buffer memory data might be corrupted and
	 * should not be read by the application.
	 */
	VACQ_BUFFER_FLAGS_ERROR = (1 << 1),

	/**
	 * Buffer memory data should not be invalidated.
	 * When a frame is returned to the device with this flag set, the next
	 * generated buffer memory should not be invalidated in the CPU cache.
	 * It is only applicable for memory written by DMA-capable devices and
	 * when buffer memory is mapped as cached.
	 */
	VACQ_BUFFER_FLAGS_NO_CACHE_INVALIDATE = (1 << 2),

	/**
	 * Buffer memory data should not be flushed and cleaned.
	 * When a buffer is sent to the device with this flag set, the device
	 * should not flush and clean the CPU cache for the buffer memory. It is
	 * only applicable for memory read by DMA-capable devices and when the
	 * buffer is mapped as cached and written by CPU.
	 */
	VACQ_BUFFER_FLAGS_NO_CACHE_CLEAN = (1 << 3),
};

/**
 * Video / image frame plane.
 *
 * This structure describes a video / image frame plane. A plane can be one or
 * more pixels types grouped.
 *
 * For example, for #VACQ_PIX_FORMAT_NV12, you will have 2 planes:
 *  - a Y plane,
 *  - a UV interleaved plane.
 */
struct vacq_buffer_plane {
	/**
	 * Physical address of the plane in RAM.
	 * Use of this address is not recommended since it is not mapped by CPU
	 * by default and it is provided only for advanced usage.
	 */
	uintptr_t phys_addr;
	/** Virtual address of the plane.
	 *
	 * This field is a pointer to the plane data and it is set only if the
	 * flag #VACQ_DEPTH_FLAGS_MAP has been set during last
	 * vacq_device_set_dept() call. In other case, its value will always be
	 * equal to NULL.
	 *
	 * A call to vacq_buffer_map() will not set this field.
	 */
	void *data;
	/** Size of the plane in bytes. */
	size_t size;
	/**
	 * Stride of the plane in bytes.
	 * This value can be used to calculate height of the plane from the size
	 * and must be used to access next lines in the memory: to access the
	 * second line of pixels in the plane, you must use the stride value
	 * instead of the width value as offset from starting plane address.
	 */
	unsigned int stride;
	/**
	 * Reserved data pointer.
	 * This pointer is only intended for plugin developer. It can be used to
	 * attach a data to the plane buffer for internal use in the device
	 * implementation.
	 */
	void *reserved;
};

/**
 * Maximum video / image frame plane count.
 *
 * A video frame came have up to 4 pixel types, so 4 planes:
 *  - for bayer: one red, two green and one blue,
 *  - for RGB: one red, one green, one blue and an alpha,
 *  - for YUV: one Y, one U and one V.
 */
#define VACQ_BUFFER_PLANE_COUNT 4

/**
 * Video / image frame buffer.
 *
 * This structure holds all data about a video / image frame got after a call to
 * vacq_device_dequeue_frame() and before a call to vacq_device_queue_frame().
 *
 * It basically contains:
 *  - a sequence number to identify which frame has been got,
 *  - a time stamp to know when frame has been captured and at which moment, it
 *    should be displayed (or used),
 *  - a pixel format to identify which kind of frame it is,
 *  - one or more plane with data address(es) to access the frame data.
 *
 * This structure doesn't provide a pointer to the data, which means the frame
 * data cannot be accessed directly. A call to vacq_buffer_map() must be done to
 * get a usable pointer.
 *
 * A vacq_buffer must be initialized with a call to the vacq_buffer_init() in
 * order to set the map and unmap functions and to provide the function used to
 * free internal data. If the buffer is retrieved through a call to
 * vacq_device_dequeue_frame(), it is not necessary to call the initialization
 * function since the device has done it.
 */
struct vacq_buffer {
	/**
	 * Frame sequence number.
	 * This value is incremented by 1 at each new frame. It can be used to
	 * detect if a frame has been lost, or synchronize with another pad or
	 * device.
	 */
	unsigned int sequence;
	/** Format of the frame. */
	struct vacq_format format;
	/**
	 * Time stamp of the frame.
	 * This time stamp can be used to calculate actual frame rate. It should
	 * be based on an hardware clock or high priority software thread.
	 *
	 * However, the accuracy of this value is not guaranteed since it is
	 * dependent of the device implementation. Please refer to the specific
	 * media / device documentation of the used plugin.
	 */
	struct timespec ts;
	/**
	 * Presentation time stamp of the frame.
	 * This time stamp can be used to synchronize with some devices like a
	 * video output device. It should be a more perfect time stamp,
	 * following the requested frame rate.
	 */
	struct timespec pts;

	/** Number of planes in the frame. */
	unsigned int plane_count;
	/** Plane list of the frame. */
	struct vacq_buffer_plane plane_list[VACQ_BUFFER_PLANE_COUNT];

	/**
	 * User data pointer.
	 * This pointer can be set by the application, when the frame is send to
	 * a device. The value will be kept by the device and set within the
	 * frame generated by the device. It is useful to follow a frame from
	 * the device input to the device output.
	 */
	void *user_data;

	/**
	 * Reserved data pointer.
	 * This pointer is only intended for plugin developer. It can be used to
	 * attach a data to the buffer for internal use in the device
	 * implementation.
	 */
	void *reserved;

	/**
	 * Buffer flags.
	 * This value is a bit-field composed of values from
	 * enum vacq_buffer_flags. See its documentation for more details.
	 */
	uint32_t flags;

	/** @private */
	unsigned char priv[24];
};

/**
 * Video / image frame buffer map flags.
 *
 * When a vacq_buffer is mapped with vacq_buffer_map(), some flags can be
 * set to perform some different operations on memory mapped.
 *
 * The most important is the cache usage: if the flag #VACQ_MAP_FLAGS_CACHED is
 * set, the CPU cache will be used and better performances will be reached for a
 * multiple operation on same pixels of the video frame.
 */
enum vacq_map_flags {
	/** No flags: video frame is mapped as non-cached. */
	VACQ_MAP_FLAGS_NONE = 0,
	/**
	 * Video frame is mapped as cached.
	 * This flag should be set if multiple read and/or write operations are
	 * done on same pixels of the video frame.
	 */
	VACQ_MAP_FLAGS_CACHED = (1 << 0),
};

/**
 * Global API
 */

/**
 * Initialize video-acquisition library context.
 *
 * This function must be called before any call to other functions of the
 * library.
 *
 * During its call, the global context is initialized, then the configuration
 * file is parsed and medias are populated. The required plugins are loaded
 * and initialized, according to the media types.
 *
 * This function can be called multiple times.
 *
 * @return 0 if the initialization succeed, -1 otherwise.
 */
VACQ_API int vacq_init(void);

/**
 * Free video-acquisition library context and resources.
 *
 * This function must be called after all other pending calls to
 * video-acquisition library have finished and any further call is prohibited.
 * This function should be called at program exit.
 *
 * During its call, all plugins are exited and unloaded, and the global context
 * is freed.
 *
 * This function can be called multiple times, however, only the first call
 * releases everything and next calls will do nothing.
 *
 * @return 0 if the resources and context have been released, -1 otherwise.
 */
VACQ_API int vacq_exit(void);

/**
 * Media API
 */

/**
 * Get available media count.
 *
 * This function should be used first to know how many media are available for
 * current library instance.
 *
 * @return the number of available medias.
 */
VACQ_API unsigned int vacq_media_get_count(void);

/**
 * Open a media.
 *
 * This function opens a media from its ID. The range of media ID is from 0 to
 * the value returned by vacq_media_get_count() minus 1. So, for a media count
 * of N, media ID range is from 0 to (N - 1).
 *
 * @param[in] media_id is the ID of the media
 * @return a vacq_media if the media has been opened successfully or NULL.
 */
VACQ_API struct vacq_media *vacq_media_open(unsigned int media_id);

/**
 * Close a media.
 *
 * This function closes a media opened with vacq_media_open().
 *
 * @param[in] media is a valid vacq_media to close
 * @return 0 if the media has been closed successfully, -1 otherwise.
 */
VACQ_API int vacq_media_close(struct vacq_media *media);

/**
 * Get media ID.
 *
 * @param[in] media is a valid vacq_media
 * @return the ID of the current media.
 */
VACQ_API unsigned int vacq_media_get_id(struct vacq_media *media);

/**
 * Get media descriptor.
 *
 * @param[in] media is a valid vacq_media
 * @return the media descriptor of the media instance.
 */
VACQ_API const struct vacq_media_desc *
vacq_media_get_desc(struct vacq_media *media);

/**
 * Get current media topology.
 *
 * This function is used to get the current device topology of the media. The
 * topology can change from one call to another one.
 *
 * @param[in] media is a valid vacq_media
 * @return a new instance of a topology, or NULL. After usage, the topology
 * should be freed with vacq_topology_unref().
 */
VACQ_API struct vacq_topology *
vacq_media_get_topology(struct vacq_media *media);

/**
 * Setup a media link.
 *
 * This function can be used to change a link state of one of the media links.
 *
 * The link must be filled with a valid source device ID, source pad ID,
 * sink device ID, sink pad ID and valid flags. The function
 * vacq_topology_parse_link() can be used to fill a vacq_link_desc (IDs only)
 * from a string (see function documentation for more details).
 *
 * Currently, only the #VACQ_LINK_FLAGS_ENABLED flag modification is supported:
 * other flags cannot be modified.
 *
 * @param[in] media is a valid vacq_media
 * @param[in] link is a link descriptor defining the link to modify and new
 *                 flags state
 * @return 0 if the link state has been changed, -1 otherwise.
 */
VACQ_API int vacq_media_setup_link(struct vacq_media *media,
				   const struct vacq_link_desc *link);

/**
 * Setup a media link by name.
 *
 * This function can be used to change a link state of one of the media links.
 * It does the same than vacq_media_setup_link() but user provides the device
 * names instead of the device IDs.
 *
 * Currently, only the #VACQ_LINK_FLAGS_ENABLED flag modification is supported:
 * other flags cannot be modified.
 *
 * @param[in] media is a valid vacq_media
 * @param[in] source_device is the source device name
 * @param[in] source_pad is the source pad ID
 * @param[in] sink_device is the sink device name
 * @param[in] sink_pad is the sink pad ID
 * @param[in] flags is the new flags state to apply
 * @return 0 if the link state has been changed, -1 otherwise.
 */
VACQ_API int vacq_media_setup_link_by_name(struct vacq_media *media,
					   const char *source_device,
					   unsigned int source_pad,
					   const char *sink_device,
					   unsigned int sink_pad,
					   enum vacq_link_flags flags);

/**
 * Unlink one or more device(s).
 *
 * This function disables all links to/from pads of one or more device(s).
 *
 * To specify which pads to disconnect on each device, the flags argument can
 * be set with a list of pad flags with #VACQ_PAD_FLAGS_SINK and/or
 * #VACQ_PAD_FLAGS_SOURCE set respectively for each device defined in the list
 * argument.
 *
 * @param[in] media is a valid vacq_media
 * @param[in] list is a list of ID of the device(s) to unlink
 * @param[in] flags is a list of pad flags to set which pad to disconnect. All
 *                  pads are disconnected if NULL
 * @param[in] count is the number of device IDs in the list
 * @return 0 if all devices have been unlinked, -1 otherwise.
 */
VACQ_API int vacq_media_unlink_device_list(struct vacq_media *media,
					   unsigned int *list,
					   enum vacq_pad_flags *flags,
					   unsigned int count);

/**
 * Propagate a format / fps along connected devices.
 *
 * This functions propagate a format / fps through a media topology: the format
 * and/or fps set in parameters are propagated from the selected device to the
 * first source device if #VACQ_PROPAGATE_FLAGS_DOWNSTREAM is set or to the last
 * sink device if #VACQ_PROPAGATE_FLAGS_UPSTREAM is selected (both propagation
 * direction cannot be selected in once).
 *
 * The function apply first the format / fps on the sink pad and then on the
 * source pad, except for device without a (connected) sink pad.
 *
 * If a device is connected to multiple sink devices or multiple source devices,
 * the propagation is stopped on the current device respectively when downstream
 * propagation or upstream propagation is selected.
 *
 * If the pad ID is set to VACQ_PAD_NONE, the function will find the unique
 * link starting from the sink or source pad according to the propagation flags,
 * otherwise, it starts from the pad ID provided.
 *
 * @param[in] media is a valid vacq_media
 * @param[in] device_id is the ID of the device from which propagation starts
 * @param[in] pad_id is the ID of the pad from which propagation starts or
 *                      VACQ_PAD_NONE
 * @param[in] format is the format to apply, or NULL
 * @param[in] fps is the frame rate to apply, or NULL
 * @param[in] flags is the propagation options
 * @return 0 if all format / fps device pads have been updated, or the last ID
 *         device updated, or -1 if an error occurred.
 */
VACQ_API int vacq_media_propagate(struct vacq_media *media,
				  unsigned int device_id,
				  int pad_id,
				  const struct vacq_format *format,
				  const struct vacq_fps *fps,
				  enum vacq_propagate_flags flags);

/**
 * Get a device ID from a device name.
 *
 * The device ID used to open a device with vacq_device_open() can be retrieved
 * from the media it belongs by a name.
 *
 * @param[in] media is a valid vacq_media
 * @param[in] name is the device name to use
 * @return the device ID corresponding to the name provided, -1 otherwise.
 */
VACQ_API int vacq_media_get_device_id_by_name(struct vacq_media *media,
					      const char *name);

/**
 * Create a new buffer pool.
 *
 * This function can be used to create a buffer pool from a media and then use
 * the buffers within some devices of the media.
 *
 * @param[in] media is a valid vacq_media
 * @param[in] format is the format to allocate buffers
 * @param[in] count is the number of buffers to allocate in pool
 * @return the created pool or NULL. To free the pool, a call to
 *         vacq_buffer_pool_free() should be done.
 */
VACQ_API struct vacq_buffer_pool *
vacq_media_new_buffer_pool(struct vacq_media *media,
			   const struct vacq_format *format,
			   unsigned int count);

/**
 * Call an extended media function.
 *
 * A media can be extended with some specific functions which are not provided
 * by default video-acquisition API, through this call.
 *
 * The extended functions are specific to a media implementation.
 *
 * @param[in] media is a valid vacq_media
 * @param[in] func is the name of the extended function defined for the media
 * @param[in,out] data is a pointer to the specific data to pass
 * @return 0 if the call succeeded, -1 otherwise.
 */
VACQ_API int
vacq_media_ext_func(struct vacq_media *media, const char *func, void *data);

/**
 * Topology API
 */

/**
 * Create a new topology.
 *
 * This function should only be used for plugin development.
 *
 * @param[in] device_list is the device list in the topology
 * @param[in] device_count is the number of devices in the list
 * @param[in] link_list is the link list in the topology
 * @param[in] link_count is the number of links in the list
 * @return the created topology or NULL. To free the topology, a call must be
 *         done to vacq_topology_unref().
 */
VACQ_API struct vacq_topology *
vacq_topology_new(struct vacq_device_desc *device_list,
		  unsigned int device_count,
		  struct vacq_link_desc *link_list,
		  unsigned int link_count);

/**
 * Get a topology reference.
 *
 * A call to this function guarantees that the returned reference will be valid
 * until call to vacq_topology_unref().
 *
 * This function increments an internal reference count by 1.
 *
 * @param[in] topology is a valid vacq_topology
 * @return a new reference to the topology or NULL. After usage, the topology
 * should be freed with vacq_topology_unref().
 */
VACQ_API struct vacq_topology *
vacq_topology_ref(struct vacq_topology *topology);

/**
 * Free a topology reference.
 *
 * This function must be called after a local usage of a topology for which a
 * reference has been generated with vacq_topology_ref() or vacq_topology_new()
 * or vacq_media_get_topology().
 *
 * @param[in] topology is a valid vacq_topology
 */
VACQ_API void vacq_topology_unref(struct vacq_topology *topology);

/**
 * Get the device list of the topology.
 *
 * This function returns the device list handled by the topology and set count
 * with the number of device in the returned list.
 *
 * @param[in] topology is a valid vacq_topology
 * @param[out] count is a pointer to an integer with the device count
 * @return the device list or NULL. The count is set with the number of device
 *         in the returned list.
 */
VACQ_API const struct vacq_device_desc *
vacq_topology_get_device_list(struct vacq_topology *topology,
			      unsigned int *count);

/**
 * Get the link list of the topology.
 *
 * This function returns the link list handled by the topology and set count
 * with the number of link in the returned list.
 *
 * @param[in] topology is a valid vacq_topology
 * @param[out] count is a pointer to an integer with the link count
 * @return the link list or NULL. The count is set with the number of link in
 *         the returned list.
 */
VACQ_API const struct vacq_link_desc *
vacq_topology_get_link_list(struct vacq_topology *topology,
			    unsigned int *count);

/**
 * Find a link from a topology.
 *
 * This function will find from a topology a link from source and sink device
 * names and their respective pads. If the link is found, the link descriptor
 * will be filled accordingly.
 *
 * @param[in] topology is a valid vacq_topology
 * @param[in] source_device is the source device name
 * @param[in] source_pad is the source pad ID
 * @param[in] sink_device is the sink device name
 * @param[in] sink_pad is the sink pad ID
 * @param[out] link_desc is the link descriptor to fill
 * @return 0 if the link has been found successfully, -1 otherwise.
 */
VACQ_API int vacq_topology_find_link(struct vacq_topology *topology,
				     const char *source_device,
				     unsigned int source_pad,
				     const char *sink_device,
				     unsigned int sink_pad,
				     struct vacq_link_desc *link_desc);

/**
 * Parse a link from a string.
 *
 * A string describing a link according to the following format can be parsed
 * with this function:
 * @code
 * SOURCE_DEVICE_NAME:SOURCE_PAD_ID -> SINK_DEVICE_NAME:SINK_PAD_ID
 * @endcode
 *
 * The components are:
 *  - SOURCE_DEVICE_NAME is the source device name,
 *  - SOURCE_PAD_ID is the source pad ID of the source device,
 *  - SINK_DEVICE_NAME is the sink device name,
 *  - SINK_PAD_ID is the sink pad ID of the sink device.
 *
 * The ':' are used to separate device name and the pad ID, and the '->' is used
 * to separate the source and sink.
 *
 * @param[in] topology is a valid vacq_topology
 * @param[in] link_name is the string to parse (see function description for
 *                      format)
 * @param[out] link_desc is the link descriptor to fill
 * @return 0 if the string has been parsed successfully, -1 otherwise.
 */
VACQ_API int vacq_topology_parse_link(struct vacq_topology *topology,
				      const char *link_name,
				      struct vacq_link_desc *link_desc);

/**
 * Buffer pool API
 */

/**
 * Get free buffer count from a buffer pool.
 *
 * @param[in] pool is a valid buffer pool
 * @return the number of free buffers.
 */
VACQ_API unsigned int
vacq_buffer_pool_get_free_count(struct vacq_buffer_pool *pool);

/**
 * Get total count of buffer handled by a buffer pool.
 *
 * @param[in] pool is a valid buffer pool
 * @return the number of buffers handled by the pool.
 */
VACQ_API unsigned int vacq_buffer_pool_get_count(struct vacq_buffer_pool *pool);

/**
 * Get a buffer from buffer pool.
 *
 * This function provides a new free buffer from the pool. If all buffers have
 * been retrieved from pool, the function will return NULL.
 * To check number of free available buffers in pool, the user can call
 * vacq_buffer_pool_get_free_count(). In addition, to know the total number of
 *  buffers handled by the pool, the user can call vacq_buffer_pool_get_count().
 *
 * @param[in] pool is a valid buffer pool
 * @return a free buffer or NULL if the pool is empty.
 */
VACQ_API struct vacq_buffer *
vacq_buffer_pool_get(struct vacq_buffer_pool *pool);

/**
 * Free a buffer pool.
 *
 * First-of-all, all buffers got from pool with vacq_buffer_pool_get() must be
 * released with vacq_buffer_unref() before calling this function. If some
 * buffers are still not released, the function will return in error.
 *
 * @param[in] pool is a valid buffer pool
 * @return 0 if the buffer pool has been freed, -1 otherwise.
 */
VACQ_API int vacq_buffer_pool_free(struct vacq_buffer_pool *pool);

/**
 * Device API
 */

/**
 * Macro to select device.
 * Use this macro as device pad ID to select the device itself instead of one of
 * its pad(s).
 */
#define VACQ_PAD_NONE -1

/**
 * Open a device.
 *
 * This function opens a device from a media with their respective IDs. The
 * device ID is get from the media by calling vacq_media_get_topology() or
 * vacq_media_get_device_id_by_name(). The range ID should be from 0 to the
 * count of device in the media minus 1. To get the device count, you can use
 * vacq_topology_get_device_list().
 *
 * @param[in] media_id is the ID of the media
 * @param[in] device_id is the ID of the device to open
 * @return a vacq_device if the device has been opened successfully or NULL.
 */
VACQ_API struct vacq_device *vacq_device_open(unsigned int media_id,
					      unsigned int device_id);

/**
 * Close a device.
 *
 * This function closes a device opened with vacq_device_open().
 *
 * @param[in] device is a valid vacq_device to close
 * @return 0 if the device has been closed successfully, -1 otherwise.
 */
VACQ_API int vacq_device_close(struct vacq_device *device);

/**
 * Get device ID.
 *
 * @param[in] device is a valid vacq_device
 * @return the ID of the current device.
 */
VACQ_API unsigned int vacq_device_get_id(struct vacq_device *device);

/**
 * Get media ID that device belongs to.
 *
 * @param[in] device is a valid vacq_device
 * @return the ID of the media that device belongs to.
 */
VACQ_API unsigned int vacq_device_get_media_id(struct vacq_device *device);

/**
 * Get device descriptor.
 *
 * This function should be used to retrieve the device name and the list of its
 * available pads.
 *
 * @param[in] device is a valid vacq_device
 * @return the device descriptor of the device instance.
 */
VACQ_API const struct vacq_device_desc *
vacq_device_get_desc(struct vacq_device *device);

/**
 * Get control list of a device / device pad
 *
 * This function provides the control list available for the device or the
 * device pad.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[out] desc is a pointer to the returned list
 * @param[out] count is a pointer to the control count
 * @return 0 if the list has been generated successfully, -1 otherwise.
 */
VACQ_API int vacq_device_list_control(struct vacq_device *device,
				      int pad_id,
				      const struct vacq_control_desc **desc,
				      unsigned int *count);

/**
 * Get device / device pad control value(s).
 *
 * This function can be used to get the value for one or more device or device
 * pad control(s).
 *
 * The control list must be filled with a valid control class and ID, and a size
 * if the control holds an array. The function will set one of the value fields
 * of the control structure with the actual control value.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[in,out] control is the control array to get
 * @param[in] count is the count of controls to get
 * @return 0 if the control(s) have been got, -1 otherwise.
 */
VACQ_API int vacq_device_get_control(struct vacq_device *device,
				     int pad_id,
				     struct vacq_control *control,
				     unsigned int count);

/**
 * Set device / device pad control value(s).
 *
 * This function can be used to set a value for one or more device or device pad
 * control(s).
 *
 * The control list must be filled with a valid control class and ID, the value
 * to set in the appropriate field, and a size if the control holds an array.
 * The function will update the control structure value with the actual set
 * value.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[in,out] control is the control array to set
 * @param[in] count is the count of controls to set
 * @return 0 if the control(s) have been set, -1 otherwise.
 */
VACQ_API int vacq_device_set_control(struct vacq_device *device,
				     int pad_id,
				     struct vacq_control *control,
				     unsigned int count);

/**
 * Get current format applied on pad.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[out] format is set with the current frame format
 * @return 0 if the device pad format has been got successfully, -1 otherwise.
 */
VACQ_API int vacq_device_get_format(struct vacq_device *device,
				    unsigned int pad_id,
				    struct vacq_format *format);

/**
 * Set a new format on pad.
 *
 * This function can be used to modify input / output format of a sink / source
 * pad.
 *
 * A modification on the format resolution can have some effects on the
 * selection rectangle of the pad.
 *
 * If the stream of the pad is started, it will returns with an error.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in] format is the frame format to set
 * @return 0 if the device pad format has been set successfully, -1 otherwise.
 *         On error, the errno is set appropriately.
 * @exception EBUSY when pad depth is set or stream pad is on.
 */
VACQ_API int vacq_device_set_format(struct vacq_device *device,
				    unsigned int pad_id,
				    const struct vacq_format *format);

/**
 * Get current selection rectangle(s) on pad.
 *
 * This function will get one or more selection rectangle(s) on the current pad.
 * The vacq_selection.target is used to specify which rectangle should be
 * retrieved.
 *
 * For more details on pad selection, please see #vacq_selection and
 * #vacq_sel_target documentation.
 *
 * The vacq_selection.flags is ignored during this call.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in,out] sel is the selection rectangle array to get
 * @param[in] count is the count of selection rectangle to get
 * @return 0 if the device pad selection has been got successfully, -1
 *         otherwise.
 */
VACQ_API int vacq_device_get_selection(struct vacq_device *device,
				       unsigned int pad_id,
				       struct vacq_selection *sel,
				       unsigned int count);

/**
 * Set new selection rectangle(s) on pad.
 *
 * This function will set one or more selection rectangle(s) on the current pad.
 * The vacq_selection.target is used to specify which rectangle should be
 * modified.
 * It is recommended to start with sink pad and finish with source pads.
 *
 * If the vacq_selection.flags is not set to #VACQ_SEL_FLAGS_KEEP, the rectangle
 * values will be changed accordingly to the flags set.
 *
 * For more details on pad selection, please see #vacq_selection and
 * #vacq_sel_target documentation.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in,out] sel is the selection rectangle array to set
 * @param[in] count is the count of selection rectangle to set
 * @return 0 if the device pad selection has been set successfully, -1
 *         otherwise.
 */
VACQ_API int vacq_device_set_selection(struct vacq_device *device,
				       unsigned int pad_id,
				       struct vacq_selection *sel,
				       unsigned int count);

/**
 * Try selection rectangle(s) on pad.
 *
 * This function do the same as vacq_device_set_selection() without applying the
 * rectangle(s). It actually set the #VACQ_SEL_FLAGS_TRY flag on the
 * selection(s) passed to the function. It can be used to test a set of
 * rectangle(s) and get the arranged values.
 * For more details, please refer to vacq_device_set_selection() documentation.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in,out] sel is the selection rectangle array to try
 * @param[in] count is the count of selection rectangle to try
 * @return 0 if the device pad selection has been tried successfully, -1
 *         otherwise.
 */
VACQ_API int vacq_device_try_selection(struct vacq_device *device,
				       unsigned int pad_id,
				       struct vacq_selection *sel,
				       unsigned int count);

/**
 * Get current frame rate applied on pad.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[out] fps is set with the current frame rate
 * @return 0 if the device pad frame rate has been got successfully, -1
 *         otherwise.
 */
VACQ_API int vacq_device_get_fps(struct vacq_device *device,
				 unsigned int pad_id,
				 struct vacq_fps *fps);

/**
 * Set a new frame rate on pad.
 *
 * This function can be used to modify input / output frame rate of a sink /
 * source pad.
 *
 * If the stream of the pad is started, it could returns with an error. The
 * behavior of this function is device implementation dependent. Please refer to
 * the specific device documentation.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in] fps is the frame rate to set
 * @return 0 if the device pad frame rate has been set successfully, -1
 *         otherwise.
 */
VACQ_API int vacq_device_set_fps(struct vacq_device *device,
				 unsigned int pad_id,
				 const struct vacq_fps *fps);

/**
 * Get current FIFO depth used for pad.
 *
 * This function returns the number of buffer allocated for the device pad to
 * store frame data in memory.
 *
 * This function is only applicable on pad which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * For devices which doesn't provide depth control, this value will be fixed to
 * a constant value or zero.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[out] count is set with the internal queue depth
 * @param[out] flags is the flags currently applied
 * @return 0 if the device pad FIFO buffer depth has been got successfully, -1
 *         otherwise.
 */
VACQ_API int vacq_device_get_depth(struct vacq_device *device,
				   unsigned int pad_id,
				   unsigned int *count,
				   enum vacq_depth_flags *flags);

/**
 * Set FIFO depth used for pad.
 *
 * This function set the internal queue depth to 'count'.
 * By default, 'count' buffers will be allocated and used by the device. If the
 * flag #VACQ_DEPTH_FLAGS_NO_ALLOCATE is set, no buffers will be allocated and
 * the device will wait for external buffers through the
 * vacq_device_queue_frame().
 *
 * This function is only applicable on pad which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * It can be called only when stream of the pad is off. If it is on, it will
 * returns an error.
 *
 * For devices which doesn't provide depth control, this function will returns
 * an error.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in] count is the number of internal queue depth
 * @param[in] flags is a bit-field of flags to specify actions
 * @return 0 if the device pad FIFO buffer depth has been set successfully, -1
 *         otherwise.
 */
VACQ_API int vacq_device_set_depth(struct vacq_device *device,
				   unsigned int pad_id,
				   unsigned int count,
				   enum vacq_depth_flags flags);

/**
 * Start a stream capture / processing.
 *
 * When the required format, frame rate and FIFO depth are set for the pad, the
 * stream capture / processing can be started with this function. This call is
 * mandatory to get frames with vacq_device_dequeue_frame() and send frames with
 * vacq_device_queue_frame().
 *
 * When capture is finished, the stream of the pad should be switched off with
 * vacq_device_stream_off().
 *
 * This function is only applicable on pad which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @return 0 if the device pad has been switched on successfully, -1 otherwise.
 */
VACQ_API int vacq_device_stream_on(struct vacq_device *device,
				   unsigned int pad_id);

/**
 * Stop a stream capture / processing.
 *
 * This function must be called when frame capture / processing is finished.
 * Before calling it, a call to vacq_device_stream_on() should succeeded.
 *
 * This function is only applicable on pad which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @return 0 if the device pad has been switched off successfully, -1 otherwise.
 */
VACQ_API int vacq_device_stream_off(struct vacq_device *device,
				    unsigned int pad_id);

/**
 * Get a file descriptor to poll.
 *
 * If the application wants to use the poll() function to waits on multiple
 * pads, this function can be called to get a usable file descriptor with
 * poll().
 *
 * An example of usage:
 * @code
 * struct pollfd ufds;
 * int fd;
 *
 * fd = vacq_device_get_fd(dev, pad_id);
 * [...]
 * ufds.events = POLLIN;
 * ufds.fd = fd;
 * [...]
 * poll(&ufds, 1, 100);
 * if (ufds.revents & POLLIN)
 *         vacq_device_dequeue_frame(dev, pad_id, &buf, &timeout);
 * [...]
 * vacq_device_release_fd(dev, pad_id, fd);
 * @endcode
 *
 * when poll() is used, the call to vacq_device_dequeue_frame() should be done
 * with a timeout equal to zero.
 *
 * After usage, the file descriptor must be released with
 * vacq_device_release_fd().
 *
 * This function is only applicable on pad which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * If file descriptor cannot be provided by device implementation, this function
 * will returns an error and poll() will be unavailable.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @return the file descriptor, -1 otherwise.
 */
VACQ_API int vacq_device_get_fd(struct vacq_device *device,
				unsigned int pad_id);

/**
 * Release a file descriptor.
 *
 * This function must be called to release a file descriptor obtained with
 * vacq_device_get_fd().
 *
 * This function is only applicable on pad which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in] fd is the file descriptor to release
 * @return 0 if the file descriptor has been released successfully, -1
 *         otherwise.
 */
VACQ_API int
vacq_device_release_fd(struct vacq_device *device, unsigned int pad_id, int fd);

/**
 * Queue a frame on a pad.
 *
 * This function is used to release a frame to a device source pad or to provide
 * next frame to process by the device to a sink pad. Before, the stream should
 * be started with vacq_device_stream_on().
 *
 * For sink pad: the buffer is queued in internal input list of the device and
 * is processed later. If the vacq_buffer.user_data field is set, the device is
 * responsible to provide the same data on source pads. When the device has
 * finished to use the buffer, it is queued in free list buffer and it can be
 * retrieved with the vacq_device_dequeue_frame().
 *
 * For source pad: the buffer is queued in internal free list of the device and
 * it will be used for next incoming frames.
 *
 * The function has a non-blocking / blocking with timeout mechanism which is
 * controlled with the value of timeout:
 *  - if timeout < 0: the function is blocking and waits indefinitely,
 *  - if timeout = 0: the function is non-blocking and returns immediately,
 *  - if timeout > 0: the function is blocking and waits at most the timeout
 *    value and returns,
 *
 * If the timeout parameter is set to NULL, it will be interpreted as a timeout
 * of 0s which means the function will returns immediately.
 *
 * This function is only applicable on pads which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in] buffer is the frame to queue in device
 * @param[in] timeout is the time before function will return (< 0 for infinite)
 * @return 0 if a frame has been returned successfully, -1 otherwise.
 */
VACQ_API int vacq_device_queue_frame(struct vacq_device *device,
				     unsigned int pad_id,
				     struct vacq_buffer *buffer,
				     const struct timespec *timeout);

/**
 * Dequeue a frame from a pad.
 *
 * This function is used to get the next frame from a device source pad or
 * retrieve a free frame buffer from a sink pad. Before, the stream should be
 * started with vacq_device_stream_on().
 *
 * For sink pad: the returned buffer is only initialized and is ready to receive
 * data which will be used by device after a vacq_device_queue_frame() call.
 * This function will return a new buffer until free buffer list is empty. When
 * frame is ready for processing, the vacq_device_queue_frame() can be called.
 * In case the frame is not queued to device pad, a call to vacq_buffer_unref()
 * should be done to release the frame.
 *
 * For source pad: the returned buffer is filled with next awaiting frame (if
 * application took more than one period to process previous frame, the pad can
 * have multiple awaiting frames). After usage, the frame must be released with
 * vacq_device_queue_frame() or vacq_buffer_unref(). If it is not done, the
 * device can miss some frame buffers to store next frames and then loose some
 * frames. A such behavior can be monitored thanks to the vacq_buffer.sequence
 * field (for more details, please read vacq_buffer details).
 *
 * The function has a non-blocking / blocking with timeout mechanism which is
 * controlled with the value of timeout:
 *  - if timeout < 0: the function is blocking and waits indefinitely,
 *  - if timeout = 0: the function is non-blocking and returns immediately,
 *  - if timeout > 0: the function is blocking and waits at most the timeout
 *    value and returns,
 *
 * If the timeout parameter is set to NULL, it will be interpreted as a timeout
 * of 0s which means the function will returns immediately.
 *
 * This function is only applicable on pad which have the flag
 * #VACQ_PAD_FLAGS_MEMORY_INTERFACE set.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device
 * @param[in] timeout is the time before function will return (< 0 for infinite)
 * @return a video-acquisition buffer initialized (for sink) or filled (for
 *         source, NULL otherwise. On error, the errno is set appropriately.
 *         when buffer is not used anymore, it must be released with
 *         vacq_buffer_unref() or vacq_device_queue_frame().
 * @exception EAGAIN when no buffer was in the outgoing queue
 *            EINTR when a signal occurred
 *            ETIMEDOUT when timeout event occurred
 */
VACQ_API struct vacq_buffer *
vacq_device_dequeue_frame(struct vacq_device *device,
			  unsigned int pad_id,
			  const struct timespec *timeout);

/**
 * List available events of a device / device pad.
 *
 * This function provides the event list available for the device or the device
 * pad.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[out] desc is a pointer to the returned list
 * @param[out] count is a pointer to the event list count
 * @return 0 if the list has been generated successfully, -1 otherwise.
 */
VACQ_API int vacq_device_list_event(struct vacq_device *device,
				    int pad_id,
				    const struct vacq_event_desc **desc,
				    unsigned int *count);

/**
 * Subscribe to a device / device pad event.
 *
 * Application can monitor some specific events on a device or one of its pads,
 * like a control changes or a start / end of frame processing. To monitor such
 * events, the application must call this function first, to subscribe on one
 * event.
 *
 * When subscribed, to get an event, the function vacq_device_get_event() can be
 * used to get generated events.
 *
 * When an event is subscribed, it is local to the device instance which means
 * the event queue will be different from each device instances. The queue will
 * be destroyed a device close.
 *
 * If the event is not available for the device or device pad, an error is
 * returned.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[in] sub is the description of the event to subscribe
 * @returns 0 if the subscription has been done, -1 otherwise.
 */
VACQ_API int vacq_device_subscribe_event(struct vacq_device *device,
					 int pad_id,
					 const struct vacq_event_sub *sub);

/**
 * Unsubscribe to a device / device pad event.
 *
 * This function can be used to unsubscribe a subscribed event with
 * vacq_device_subscribe_event(). All events should be unsubscribed before
 * closing the device instance.
 *
 * If the vacq_event_sub.type is #VACQ_EVENT_TYPE_ALL, all events will be
 * unsubscribed in once.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[in] sub is the description of the event to unsubscribe
 * @returns 0 if the subscription has been removed, -1 otherwise.
 */
VACQ_API int vacq_device_unsubscribe_event(struct vacq_device *device,
					   int pad_id,
					   const struct vacq_event_sub *sub);

/**
 * Get an event file descriptor to poll.
 *
 * To wait for next event on a device, the poll() function must be used since
 * vacq_device_get_event() is a non-blocking call and will returns immediately
 * if a new event occurred or not.
 *
 * An example of usage can be found in description of vacq_device_get_fd().
 *
 * After usage, the file descriptor must be released with
 * vacq_device_release_event_fd().
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @return the file descriptor, -1 otherwise.
 */
VACQ_API int vacq_device_get_event_fd(struct vacq_device *device, int pad_id);

/**
 * Release an event file descriptor.
 *
 * This function must be called to release the file descriptor obtained with
 * vacq_device_get_event_fd().
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[in] fd is the file descriptor to release
 * @return 0 if the file descriptor has been released successfully, -1
 *         otherwise.
 */
VACQ_API int
vacq_device_release_event_fd(struct vacq_device *device, int pad_id, int fd);

/**
 * Get next event in queue.
 *
 * This function is used to dequeue the next subscribed event on a device or one
 * of its pads. Only subscribed events with vacq_device_subscribe_event() can be
 * dequeued with this function.
 *
 * This function is non-blocking and doesn't have any timeout feature!: to wait
 * for next events, a file descriptor can be retrieved with
 * vacq_device_get_event_fd() and then used with select() or poll().
 *
 * The vacq_event.pending field contains how many events are still remaining in
 * internal queue: this function should be called until this value is equal to
 * zero.
 *
 * The internal event queue can have a variable or fixed size: to detect an
 * event drop when queue is full, the vacq_event.sequence value can be used.
 *
 * @param[in] device is a valid vacq_device
 * @param[in] pad_id is the pad ID of the device, or #VACQ_PAD_NONE for device
 * @param[out] event is the next event dequeued
 * @returns 0 if an event has been dequeued, -1 otherwise.
 */
VACQ_API int vacq_device_get_event(struct vacq_device *device,
				   int pad_id,
				   struct vacq_event *event);

/**
 * Buffer API
 */

/**
 * Macro to select all planes on video acquisition buffer.
 *
 * Use this macro as buffer plane to select all planes during vacq_buffer_map()
 * or vacq_buffer_export_dma_buf() calls. It will select the first plane in
 * memory as starting point for operations.
 */
#define VACQ_BUFFER_ALL_PLANES (UINT_MAX)

/**
 * Video / image frame buffer callbacks.
 *
 * This structure contains all callbacks used by a video acquisition buffer to
 * handle basic operations such as map / unmap or DMA buffer export.
 *
 * This structure is passed during vacq_buffer_init() call.
 */
struct vacq_buffer_cb {
	/**
	 * Video / image frame buffer mapping callback.
	 *
	 * This function is called when a call to vacq_buffer_map() is done. For
	 * more details, please see function documentation.
	 *
	 * @param[in] buffer is the video frame buffer to map
	 * @param[in] plane is the plane to map
	 * @param[in] offset is the offset in bytes in the plane from which to
	 *                   start
	 * @param[in] length is the length in bytes in the plane to map
	 * @param[in] flags is the flags to use for mapping
	 * @param[in] user_data is the user data provided in vacq_buffer_init()
	 * @return the virtual address of the plane mapped or MAP_FAILED.
	 */
	void *(*map_cb)(struct vacq_buffer *buffer,
			unsigned int plane,
			off_t offset,
			size_t length,
			enum vacq_map_flags flags,
			void *user_data);

	/**
	 * Video / image frame buffer un-mapping callback.
	 *
	 * This function is called when a call to vacq_buffer_unmap() is done.
	 * For more details, please see function documentation.
	 *
	 * @param[in] buffer is the video frame buffer to unmap
	 * @param[in] addr is the address of mapped memory returned by
	 *                 vacq_buffer_map()
	 * @param[in] length is the length of mapped memory
	 * @param[in] user_data is the user data provided in vacq_buffer_init()
	 * @return 0 if the memory has been unmapped successfully, -1 otherwise.
	 */
	int (*unmap_cb)(struct vacq_buffer *buffer,
			void *addr,
			size_t length,
			void *user_data);

	/**
	 * Video / image frame buffer Invalidation callback.
	 *
	 * This function is called when a call to vacq_buffer_invalidate() is
	 * done. For more details, please see function documentation.
	 *
	 * @param[in] buffer is the video frame buffer to invalidate
	 * @param[in] addr is the address of mapped memory returned by
	 *                 vacq_buffer_map()
	 * @param[in] length is the length of mapped memory
	 * @param[in] user_data is the user data provided in vacq_buffer_init()
	 * @return 0 if the memory has been invalidated successfully, -1
	 *         otherwise.
	 */
	int (*invalidate_cb)(struct vacq_buffer *buffer,
			     void *addr,
			     size_t length,
			     void *user_data);

	/**
	 * Video / image frame flushing callback.
	 *
	 * This function is called when a call to vacq_buffer_flush() is
	 * done. For more details, please see function documentation.
	 *
	 * @param[in] buffer is the video frame buffer to flush
	 * @param[in] addr is the address of mapped memory returned by
	 *                 vacq_buffer_map()
	 * @param[in] length is the length of mapped memory
	 * @param[in] user_data is the user data provided in vacq_buffer_init()
	 * @return 0 if the memory has been flushed successfully, -1 otherwise.
	 */
	int (*flush_cb)(struct vacq_buffer *buffer,
			void *addr,
			size_t length,
			void *user_data);

	/**
	 * Video / image frame buffer get DMA buffer callback.
	 *
	 * This function is called when a call to vacq_buffer_get_dma_buf()
	 * is done. For more details, please see function details.
	 *
	 * @param[in] buffer is the video frame buffer to get
	 * @param[in] plane is the plane to get
	 * @param[out] offset is for the plane offset in the DMA buffer memory
	 * @param[in] user_data is the user data provided in vacq_buffer_init()
	 * @return the file descriptor to handle the DMA buffer, -1 otherwise.
	 */
	int (*get_dma_buf_cb)(struct vacq_buffer *buffer,
			      unsigned int plane,
			      unsigned int *offset,
			      void *user_data);

	/**
	 * Video / image frame buffer free callback.
	 *
	 * This function is called when a call to vacq_buffer_unref() is done
	 * and the internal reference counter reaches 0. For more details,
	 * please see function documentation.
	 *
	 * @param[in] buffer is the video frame buffer to free
	 * @param[in] user_data is the user data provided in vacq_buffer_init()
	 * @return 0 if the frame data has been freed successfully, -1
	 *         otherwise.
	 */
	int (*free_cb)(struct vacq_buffer *buffer, void *user_data);
};

/**
 * Video / image frame buffer initialization.
 *
 * This function can be called to initialize a buffer. Its call is mandatory
 * when buffer is not retrieved through a call to vacq_device_dequeue_frame().
 *
 * For device developers, this function must be called to initialize the buffer
 * before returning in the implementation of the vacq_device_dequeue_frame().
 *
 * @param[in] buffer is the buffer to initialize
 * @param[in] cbs is the structure containing all callbacks to use
 * @param[in] user_data is the user data passed to functions
 * @return 0 the buffer has been initialize, -1 otherwise.
 */
VACQ_API int vacq_buffer_init(struct vacq_buffer *buffer,
			      const struct vacq_buffer_cb *cbs,
			      void *user_data);

/**
 * Increment reference counter of a buffer.
 *
 * This function increments the internal reference counter of a buffer. It is
 * very useful to share a buffer between multiple devices or user code and avoid
 * the buffer is released before all users have finished to use it.  When the
 * reference of the buffer  obtained with this function is not useful anymore,
 * the vacq_buffer_unref() must be called to decrement the reference counter and
 * free this reference.
 *
 * @param[in] buffer is the buffer to ref
 * @return the buffer to instance or NULL if an error occurred.
 */
VACQ_API struct vacq_buffer *vacq_buffer_ref(struct vacq_buffer *buffer);

/**
 * Decrement reference counter of a buffer.
 *
 * This function decrements the internal reference counter of a buffer. It must
 * be called when the buffer reference obtained with vacq_buffer_ref() is not
 * used anymore.
 *
 * If one of planes has been mapped with vacq_buffer_map(), it should be
 * unmapped with vacq_buffer_unmap() before calling this function to avoid
 * memory inconsistency.
 *
 * @param[in] buffer is the buffer to unref
 * @return 0 if reference counter has been decremented, -1 otherwise.
 */
VACQ_API int vacq_buffer_unref(struct vacq_buffer *buffer);

/**
 * Map a buffer memory.
 *
 * In order to access data of a frame buffer handled by vacq_buffer, the
 * memory must be mapped before with this function.
 *
 * Map is performed plane by plane, so the application must specify which plane
 * to map, the starting point in the plane (offset) and the length to map. In
 * some case, only few bytes of the whole memory are necessary, so the offset
 * and length parameters can be very useful.
 *
 * The flags can be used to specify if the memory should be mapped with CPU
 * cache or not: if only a small portion is accessed once, the non-cached
 * option should be used. If the whole frame data is accessed multiple times, it
 * should mapped with cache in order to reduce RAM bandwidth usage.
 * Finally, if the frame buffer is only copied to another buffer, the non-cached
 * option is recommended.
 *
 * After usage, the mapped memory must be released with vacq_buffer_unmap() with
 * the same parameters and the returned pointer by this function, as the
 * address.
 *
 * @param[in] buffer is the video frame buffer to map
 * @param[in] plane is the plane to map or VACQ_BUFFER_ALL_PLANES
 * @param[in] offset is the offset in bytes in the plane from which to start
 * @param[in] length is the length in bytes in the plane to map
 * @param[in] flags is the flags to use for mapping
 * @return the virtual address of the plane mapped or MAP_FAILED. After usage,
 *         the memory must be unmapped with vacq_buffer_unmap().
 */
VACQ_API void *vacq_buffer_map(struct vacq_buffer *buffer,
			       unsigned int plane,
			       off_t offset,
			       size_t length,
			       enum vacq_map_flags flags);

/**
 * Unmap a buffer memory.
 *
 * This function must be used to unmap a mapped frame buffer memory with
 * vacq_buffer_map(). The address to provide is the returned address by the
 * vacq_buffer_map() and the length must be the same value used to map the
 * memory.
 *
 * @param[in] buffer is the video frame buffer to unmap
 * @param[in] addr is the address of mapped memory returned by vacq_buffer_map()
 * @param[in] length is the length of mapped memory
 * @return 0 if the memory has been unmapped successfully, -1 otherwise.
 */
VACQ_API
int vacq_buffer_unmap(struct vacq_buffer *buffer, void *addr, size_t length);

/**
 * Invalidate a buffer data in cache.
 *
 * This function can be used on a buffer which has been mapped with the flag
 * #VACQ_MAP_FLAGS_CACHED set, to invalidate the data which could remain in the
 * CPU cache.
 * It should be called after a call to vacq_device_dequeue_frame() on a source
 * pad of a device for which data is not written by the CPU, like DMA transfer).
 * It ensures that data is up-to-date in CPU cache.
 *
 * @param[in] buffer is the video frame buffer
 * @param[in] addr is the address of mapped memory returned by vacq_buffer_map()
 * @param[in] length is the length of mapped memory
 */
VACQ_API int
vacq_buffer_invalidate(struct vacq_buffer *buffer, void *addr, size_t length);

/**
 * Flush a buffer data from cache.
 *
 * This function can be used on a buffer which has been mapped with the flag
 * #VACQ_MAP_FLAGS_CACHED set, to flush the data which could remain in the
 * CPU cache to the main RAM memory.
 * It should be called after a call to vacq_device_queue_frame() on a sink pad
 * of a device for which data is not read by the CPU, like DMA transfer).
 * It ensures that data is up-to-date in RAM.
 *
 * @param[in] buffer is the video frame buffer
 * @param[in] addr is the address of mapped memory returned by vacq_buffer_map()
 * @param[in] length is the length of mapped memory
 */
VACQ_API
int vacq_buffer_flush(struct vacq_buffer *buffer, void *addr, size_t length);

/**
 * Get DMA buffer from a buffer memory.
 *
 * This function can be used to get the DMA buffer memory attached to a video /
 * image which can be handled by a file descriptor.
 *
 * The returned file descriptor is valid until the video frame exists. The user
 * should not call close() since the video buffer under-layer will do it at
 * buffer release. To keep an independent reference, the dup() function should
 * be used.
 *
 * It will returns in error if the memory of the buffer is allocated from the
 * user-space.
 *
 * @param[in] buffer is the video frame buffer to get
 * @param[in] plane is the plane to get or VACQ_BUFFER_ALL_PLANES
 * @param[out] offset is for the plane offset in the DMA buffer memory
 * @return the file descriptor to handle the DMA buffer, -1 otherwise.
 */
VACQ_API int vacq_buffer_get_dma_buf(struct vacq_buffer *buffer,
				     unsigned int plane,
				     unsigned int *offset);

/**
 * Utility API
 */

/**
 * Convert a pad flag to a string.
 *
 * @param[in] flag is the pad flag to convert
 * @return the string corresponding to the pad flag or NULL.
 */
VACQ_API const char *vacq_pad_flag_to_string(enum vacq_pad_flags flag);

/**
 * Convert a string to a pad flag.
 *
 * @param[in] str is the string to convert
 * @return the corresponding pad flag or #VACQ_PAD_FLAGS_NONE.
 */
VACQ_API enum vacq_pad_flags vacq_pad_flag_from_string(const char *str);

/**
 * Convert a pad flag bit-field to a string.
 *
 * @param[in] flags is the pad flag bit-field to convert
 * @return the string corresponding to the pad flag bit-field or NULL.
 */
VACQ_API char *vacq_pad_flags_to_string(enum vacq_pad_flags flags);

/**
 * Convert a string to a pad flag bit-field.
 *
 * @param[in] str is string to convert
 * @return the pad flag bit-field corresponding or #VACQ_PAD_FLAGS_NONE.
 */
VACQ_API enum vacq_pad_flags vacq_pad_flags_from_string(const char *str);

/**
 * Convert a link flag to a string.
 *
 * @param[in] flag is the link flag to convert
 * @return the string corresponding to the link flag or NULL.
 */
VACQ_API const char *vacq_link_flag_to_string(enum vacq_link_flags flag);

/**
 * Convert a string to a link flag.
 *
 * @param[in] str is the string to convert
 * @return the corresponding link flag or #VACQ_LINK_FLAGS_NONE.
 */
VACQ_API enum vacq_link_flags vacq_link_flag_from_string(const char *str);

/**
 * Convert a link flag bit-field to a string.
 *
 * @param[in] flags is the link flag bit-field to convert
 * @return the string corresponding to the link flag bit-field or NULL.
 */
VACQ_API char *vacq_link_flags_to_string(enum vacq_link_flags flags);

/**
 * Convert a string to a link flag bit-field.
 *
 * @param[in] str is string to convert
 * @return the link flag bit-field corresponding or #VACQ_LINK_FLAGS_NONE.
 */
VACQ_API enum vacq_link_flags vacq_link_flags_from_string(const char *str);

/**
 * Convert a pixel format to a string.
 *
 * @param[in] pix_format is the pixel format to convert
 * @return the string corresponding to the pixel format or NULL.
 */
VACQ_API const char *vacq_pix_format_to_string(enum vacq_pix_format pix_format);

/**
 * Convert a string to a pixel format.
 *
 * @param[in] str is the string to convert
 * @return the corresponding pixel format or #VACQ_PIX_FORMAT_UNKNOWN.
 */
VACQ_API enum vacq_pix_format vacq_pix_format_from_string(const char *str);

/**
 * Convert a control class to a string.
 *
 * @param[in] ctrl_class is the control class to convert
 * @return the string corresponding to the control class or NULL.
 */
VACQ_API const char *
vacq_control_class_to_string(enum vacq_control_class ctrl_class);

/**
 * Convert a string to a control class.
 *
 * @param[in] str is the string to convert
 * @return the corresponding control class or #VACQ_CONTROL_CLASS_UNKNOWN.
 */
VACQ_API enum vacq_control_class
vacq_control_class_from_string(const char *str);

/**
 * Convert a control ID to a string.
 *
 * @param[in] ctrl_class is the control class
 * @param[in] id is the control ID to convert
 * @return the string corresponding to the control ID or NULL.
 */
VACQ_API const char *vacq_control_to_string(enum vacq_control_class ctrl_class,
					    unsigned int id);

/**
 * Convert a string to a control ID.
 *
 * @param[in] ctrl_class is the control class
 * @param[in] str is the string to convert
 * @return the corresponding control ID or 0 for UNKNOWN.
 */
VACQ_API unsigned int
vacq_control_from_string(enum vacq_control_class ctrl_class, const char *str);

/**
 * Convert a class + ID strings to a control class + ID.
 *
 * This function converts two strings containing respectively a class and a
 * control ID value/name to a control class and an integer representing the
 * control ID.
 *
 * First, the function tries to parse the strings as an integer. If it fails, it
 * tries to parse the string as a class or control name by comparing with
 * standard control names or the provided control list for custom controls.
 *
 * @param[in] class_str is the control class string to convert
 * @param[in] id_str is the control ID string to convert
 * @param[in] list is the control list to use
 * @param[in] list_count it the count of controls in the list
 * @param[out] ctrl_class is a pointer to set control class
 * @param[out] id is a pointer to set control ID
 * @return 0 if the strings have been converted successfully, -1 otherwise.
 */
VACQ_API int vacq_control_from_strings(const char *class_str,
				       const char *id_str,
				       const struct vacq_control_desc *list,
				       unsigned int list_count,
				       enum vacq_control_class *ctrl_class,
				       unsigned int *id);

/**
 * Convert a control type to a string.
 *
 * @param[in] type is the control type to convert
 * @return the string corresponding to the control type or NULL.
 */
VACQ_API const char *vacq_control_type_to_string(enum vacq_control_type type);

/**
 * Convert a string to a control type.
 *
 * @param[in] str is the string to convert
 * @return the corresponding control type or #VACQ_CONTROL_TYPE_UNKNOWN.
 */
VACQ_API enum vacq_control_type vacq_control_type_from_string(const char *str);

/**
 * Convert a control flag to a string.
 *
 * @param[in] flag is the control flag to convert
 * @return the string corresponding to the control flag or NULL.
 */
VACQ_API const char *vacq_control_flag_to_string(enum vacq_control_flags flag);

/**
 * Convert a string to a control flag.
 *
 * @param[in] str is the string to convert
 * @return the corresponding control flag or #VACQ_CONTROL_FLAGS_NONE.
 */
VACQ_API enum vacq_control_flags vacq_control_flag_from_string(const char *str);

/**
 * Convert a control flag bit-field to a string.
 *
 * @param[in] flags is the control flag bit-field to convert
 * @return the string corresponding to the control flag bit-field or NULL.
 */
VACQ_API char *vacq_control_flags_to_string(enum vacq_control_flags flags);

/**
 * Convert a string to a control flag bit-field.
 *
 * @param[in] str is string to convert
 * @return the control flag bit-field corresponding or #VACQ_CONTROL_FLAGS_NONE.
 */
VACQ_API enum vacq_control_flags
vacq_control_flags_from_string(const char *str);

/**
 * Check a control value according to a control descriptor.
 *
 * @param[in] desc is the control descriptor for check
 * @param[in] ctrl is the control to check
 * @return 0 if the control value is valid, -1 otherwise.
 */
VACQ_API int vacq_check_control_value(const struct vacq_control_desc *desc,
				      const struct vacq_control *ctrl);

/**
 * Check a control array is valid according to a control descriptor list.
 *
 * @param[in] desc is the control descriptor array
 * @param[in] desc_count is the count of control descriptor in list
 * @param[in] ctrl is a control array to valid
 * @param[in] ctrl_count is the count of controls in the array
 * @param[in] check_value is set to true if value should be checked
 * @return 0 is control array is valid, -1 otherwise.
 */
VACQ_API int vacq_check_controls(const struct vacq_control_desc *desc,
				 unsigned int desc_count,
				 const struct vacq_control *ctrl,
				 unsigned int ctrl_count,
				 bool check_value);

/**
 * Find a control descriptor from a control.
 *
 * @param[in] desc is the control descriptor list in which to search
 * @param[in] desc_count is the count of control descriptor in list
 * @param[in] ctrl is the control to use
 * @return a reference to one of the control descriptors if found or NULL.
 */
VACQ_API const struct vacq_control_desc *
vacq_find_control_desc(const struct vacq_control_desc *desc,
		       unsigned int desc_count,
		       const struct vacq_control *ctrl);

/**
 * Convert an event type to a string.
 *
 * @param[in] type is the event type to convert
 * @return the string corresponding to the event type or NULL.
 */
VACQ_API const char *vacq_event_type_to_string(enum vacq_event_type type);

/**
 * Convert a string to an event type.
 *
 * @param[in] str is the string to convert
 * @return the corresponding event type or #VACQ_EVENT_TYPE_CUSTOM.
 */
VACQ_API enum vacq_event_type vacq_event_type_from_string(const char *str);

/**
 * Calculate stride of buffer plane according to format.
 *
 * This function calculates the stride (number of bytes used by one frame line)
 * from the pixel format.
 *
 * @param[in] pix_format is the pixel format of the frame
 * @param[in] width is the width of the frame
 * @param[in] align is the alignment to respect for stride (0: no alignment)
 * @return 0 if sizes have been set, -1 otherwise.
 */
VACQ_API unsigned int vacq_calc_stride(enum vacq_pix_format pix_format,
				       unsigned int width,
				       unsigned int align);

/**
 * Calculate size of buffer planes according to format.
 *
 * The format must be specified first in the buffer to calculate the planes
 * size. If the stride is not specified, the width is used by default.
 *
 * @param[in,out] buffer is the buffer to set with plane sizes
 * @return 0 if sizes have been set, -1 otherwise.
 */
VACQ_API int vacq_calc_planes_size(struct vacq_buffer *buffer);

/**
 * Calculate size of a sequential memory buffer according to format.
 *
 * This function calculates the space occupied by a frame in memory when planes
 * are consecutive. If the planes are separated and located in different area of
 * the memory, this function should be not used.
 *
 * @param[in] pix_format is the pixel format of the frame
 * @param[in] width is the width of the frame
 * @param[in] height is the height of the frame
 * @param[in] stride is the length of one line (most of time equal to width, 0
 *                   for default stride)
 * @param[in] stride_align is the alignment to respect for stride (0: disabled)
 * @param[in] align is the value used to align the buffer size to (0: disabled)
 * @return the size of the frame in memory, 0 otherwise.
 */
VACQ_API size_t vacq_calc_buffer_size(enum vacq_pix_format pix_format,
				      unsigned int width,
				      unsigned int height,
				      unsigned int stride,
				      unsigned int stride_align,
				      unsigned int align);
/**
 * Copy a device descriptor content.
 *
 * All strings and the pad list are copied.
 *
 * @param[out] dest the destination device descriptor
 * @param[in] src the source device descriptor
 */
VACQ_API void vacq_device_desc_copy(struct vacq_device_desc *dest,
				    const struct vacq_device_desc *src);

/**
 * Clear a device descriptor content.
 *
 * All strings and the pad list are freed and set to 0.
 *
 * @param[in,out] desc the device descriptor to clear
 */
VACQ_API void vacq_device_desc_clear(struct vacq_device_desc *desc);

/**
 * Copy a link descriptor content.
 *
 * All strings, IDs and flags are copied.
 *
 * @param[out] dest the destination link descriptor
 * @param[in] src the source link descriptor
 */
VACQ_API void vacq_link_desc_copy(struct vacq_link_desc *dest,
				  const struct vacq_link_desc *src);

/**
 * Clear a link descriptor content.
 *
 * All strings are freed and set to 0.
 *
 * @param[in,out] desc the link descriptor to clear
 */
VACQ_API void vacq_link_desc_clear(struct vacq_link_desc *desc);

/**
 * Compare resolution.
 *
 * This function compares two resolutions r1 and r2.
 *
 * @param[in] r1 is the first resolution to compare
 * @param[in] r2 is the second resolution to compare
 * @return true if the both resolutions are identical, false otherwise.
 */
VACQ_API bool vacq_resolution_cmp(const struct vacq_resolution *r1,
				  const struct vacq_resolution *r2);

/**
 * Compare frame rate.
 *
 * This function compares two frame rate f1 and f2. It returns an integer less
 * than, equal to, or grater than zero if f1 is found, respectively, to be less
 * than, to match, or be greater than f2.
 *
 * @param[in] f1 is the first frame rate to compare
 * @param[in] f2 is the second frame rate to compare
 * @return an integer less than, equal to, or grater than zero if f1 is found,
 *         respectively, to be less than, to match, or be greater than f2.
 */
VACQ_API int vacq_fps_cmp(const struct vacq_fps *f1, const struct vacq_fps *f2);

/**
 * Check a rectangle is valid and inside another rectangle.
 *
 * This function checks that a rectangle fits inside another rectangle and it
 * has valid dimensions (vacq_rect.width and vacq_rect.height != 0).
 *
 * If the bounds rectangle is not provided, only the dimensions different from
 * zero will be checked. Then it can be used a non-null check function.
 *
 * @param[in] rect is the rectangle to check
 * @param[in] bounds is the bounding rectangle, can be NULL
 * @returns 1 if the rectangle fit inside bounding rectangle, 0 if the rectangle
 *          doesn't fit the bounding rectangle, -1 if the rectangle is invalid.
 */
VACQ_API int vacq_rect_check(const struct vacq_rect *rect,
			     const struct vacq_rect *bounds);

/**
 * Check a rectangle is aligned.
 *
 * This function checks that all values of a rectangle are aligned. It is very
 * useful to check hardware limitations.
 *
 * @param[in] rect is the rectangle to check
 * @param[in] align is a rectangle with restriction
 * @returns 1 if the rectangle is aligned, 0 if the rectangle is not aligned, -1
 *          otherwise.
 */
VACQ_API int vacq_rect_is_aligned(const struct vacq_rect *rect,
				  const struct vacq_rect *align);

/**
 * Align values of a rectangle.

 * @param[in,out] rect is the rectangle to align
 * @param[in] align is a rectangle with restriction to apply
 * @param[in] align_lower is a boolean to select if the left and top values are
 *                        aligned on lower or upper value
 * @param[in] enlarge is a boolean to select if window should be enlarged
 *                    accordingly with the left and top alignment
 */
VACQ_API void vacq_rect_align(struct vacq_rect *rect,
			      const struct vacq_rect *align,
			      bool align_lower,
			      bool enlarge);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VACQ_H_ */
