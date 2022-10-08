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
 * @file vacq_controls.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VACQ_CONTROLS_H_
#define _VACQ_CONTROLS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Device / pad control classes.
 *
 * Device and pad controls are grouped by classes to differentiate easily the
 * controls and their meanings. For custom controls (not defined in general API)
 * the #VACQ_CONTROL_CLASS_CUSTOM can be used.
 */
enum vacq_control_class {
	/** Unknown / undefined controls */
	VACQ_CONTROL_CLASS_UNKNOWN = 0,
	/** Processor / IP specific controls */
	VACQ_CONTROL_CLASS_PROC,
	/** Camera device specific controls */
	VACQ_CONTROL_CLASS_CAM,
	/** Image Signal Processor (ISP) specific controls */
	VACQ_CONTROL_CLASS_ISP,
	/** Image / Video processor specific controls */
	VACQ_CONTROL_CLASS_IMG,
	/** Debug specific controls */
	VACQ_CONTROL_CLASS_DBG,
	/**
	 * Custom controls.
	 * This class can be used to add custom controls for specific
	 * implementation.
	 */
	VACQ_CONTROL_CLASS_CUSTOM,

	VACQ_CONTROL_CLASS_COUNT
};

/**
 * Device / pad control types.
 *
 * Many types are available for device / pad controls in order to handle any
 * kind of value or data array.
 */
enum vacq_control_type {
	/**
	 * Unknown type.
	 *
	 * This type can be used for unknown data type as structure or undefined
	 * data.
	 *
	 * The vacq_control_desc.elem_size and vacq_control_desc.elem_count
	 * fields should be used.
	 *
	 * The vacq_control.value (or vacq_control.ptr if control flag
	 * #VACQ_CONTROL_FLAGS_HAS_PAYLOAD is set) and vacq_control.size are
	 * used to hold the data.
	 *
	 * No check are done on value while calling vacq_check_control_value()
	 * and vacq_check_controls().
	 */
	VACQ_CONTROL_TYPE_UNKNOWN = 0,

	/**
	 * Boolean type.
	 *
	 * This type can be used for boolean values (true / false).
	 *
	 * No additional vacq_control_desc field need to be set.
	 *
	 * The vacq_control.value is used to hold the boolean (0 for false and
	 * 1 for true).
	 */
	VACQ_CONTROL_TYPE_BOOLEAN,
	/**
	 * Integer type (32 bits).
	 *
	 * This type can be used for signed 32 bits integer or less.
	 *
	 * The vacq_control_desc.minimum and vacq_control_desc.maximum fields
	 * must be defined. The vacq_control_desc.step and
	 * vacq_control_desc.default_value are optional.
	 *
	 * The vacq_control.value is used to hold the integer.
	 */
	VACQ_CONTROL_TYPE_INTEGER,
	/**
	 * Long long integer type (64 bits).
	 *
	 * This type can be used for signed 64 bits long long integer or less.
	 *
	 * The vacq_control_desc.minimum and vacq_control_desc.maximum fields
	 * must be defined. The vacq_control_desc.step and
	 * vacq_control_desc.default_value are optional.
	 *
	 * The vacq_control.value64 is used to hold the long long integer.
	 */
	VACQ_CONTROL_TYPE_INTEGER_64,
	/**
	 * Bit-mask type (64 bits).
	 *
	 * This type can be used to handle bit-mask / bit-field values. It can
	 * handle up to 64 bits.
	 *
	 * The vacq_control_desc.minimum and vacq_control_desc.maximum fields
	 * must be defined. The vacq_control_desc.default_value is optional.
	 *
	 * The vacq_control.value64 is used to hold the bit-mask.
	 */
	VACQ_CONTROL_TYPE_BITMASK,
	/**
	 * String type.
	 *
	 * This type can be used to handle a string.
	 *
	 * No additional vacq_control_desc field need to be set.
	 *
	 * The vacq_control.string is used to hold the string.
	 */
	VACQ_CONTROL_TYPE_STRING,

	/**
	 * Unsigned 8 bits array.
	 *
	 * This type can be used to handle an array of 8 bits values.
	 *
	 * The vacq_control_desc.elem_size and vacq_control_desc.elem_count
	 * fields must be defined. If the array have multiple dimensions, the
	 * vacq_control_desc.dim_count and vacq_control_desc.dim_list can be
	 * used to specify respectively the number of dimensions and the size of
	 * each dimensions. The total of dimensions must be equal to the element
	 * count.
	 *
	 * The vacq_control.p_u8 is used to hold the array.
	 */
	VACQ_CONTROL_TYPE_U8,
	/**
	 * Unsigned 16 bits array.
	 *
	 * This type can be used to handle an array of 16 bits values.
	 *
	 * The vacq_control_desc.elem_size and vacq_control_desc.elem_count
	 * fields must be defined. If the array have multiple dimensions, the
	 * vacq_control_desc.dim_count and vacq_control_desc.dim_list can be
	 * used to specify respectively the number of dimensions and the size of
	 * each dimensions. The total of dimensions must be equal to the element
	 * count.
	 *
	 * The vacq_control.p_u16 is used to hold the array.
	 */
	VACQ_CONTROL_TYPE_U16,
	/**
	 * Unsigned 32 bits array.
	 *
	 * This type can be used to handle an array of 32 bits values.
	 *
	 * The vacq_control_desc.elem_size and vacq_control_desc.elem_count
	 * fields must be defined. If the array have multiple dimensions, the
	 * vacq_control_desc.dim_count and vacq_control_desc.dim_list can be
	 * used to specify respectively the number of dimensions and the size of
	 * each dimensions. The total of dimensions must be equal to the element
	 * count.
	 *
	 * The vacq_control.p_u32 is used to hold the array.
	 */
	VACQ_CONTROL_TYPE_U32,

	/**
	 * Button type.
	 *
	 * This type can be used to trigger an action.
	 *
	 * No additional vacq_control_desc field need to be set.
	 *
	 * No value is set in the vacq_control structure.
	 */
	VACQ_CONTROL_TYPE_BUTTON,
	/**
	 * Menu type.
	 *
	 * This type can be used to propose multiple value choice. It can be
	 * very useful to handle enumerator members.
	 *
	 * The vacq_control_desc.item_count and vacq_control_desc.item_list
	 * fields must be defined.
	 *
	 * The index of the item chosen from the menu is set in the
	 * vacq_control.value field.
	 */
	VACQ_CONTROL_TYPE_MENU,

	VACQ_CONTROL_TYPE_COUNT
};

/**
 * Device / pad control flags.
 *
 * Each control can have one or more flags to notify specific behavior like
 * read / write state, actions or internal state.
 */
enum vacq_control_flags {
	/**
	 * No flags.
	 *
	 * The value of the control can be read and/or write.
	 */
	VACQ_CONTROL_FLAGS_NONE = 0,
	/**
	 * Control is disabled.
	 *
	 * The control is permanently disabled and should be ignored. Any read
	 * and/or write will results in an error.
	 */
	VACQ_CONTROL_FLAGS_DISABLED = (1 << 0),
	/**
	 * Control is temporarily unchangeable.
	 *
	 * The value can be only read temporarily. Any write will results in an
	 * error.
	 */
	VACQ_CONTROL_FLAGS_GRABBED = (1 << 1),
	/**
	 * Control is read only.
	 *
	 * The value can be only read. Any write will results in an error.
	 */
	VACQ_CONTROL_FLAGS_READ_ONLY = (1 << 2),
	/**
	 * Control may affect other controls of the same class.
	 *
	 * A write on the value could imply some changes on other control of the
	 * same class. The application should read other controls.
	 */
	VACQ_CONTROL_FLAGS_UPDATE = (1 << 3),
	/**
	 * Control is not applicable in current configuration.
	 *
	 * The value should not be read and/or write for the current
	 * configuration. Any operation will not affect current configuration.
	 */
	VACQ_CONTROL_FLAGS_INACTIVE = (1 << 4),
	/**
	 * Control should be represented as a slider.
	 */
	VACQ_CONTROL_FLAGS_SLIDER = (1 << 5),
	/**
	 * Control is write only.
	 *
	 * The value can be only written. Any read will results in an error.
	 */
	VACQ_CONTROL_FLAGS_WRITE_ONLY = (1 << 6),
	/**
	 * Control is volatile.
	 *
	 * The value changes continuously.
	 *
	 * A write to the control is ignored unless
	 * #VACQ_CONTROL_FLAGS_EXECUTE_ON_WRITE flag is set.
	 */
	VACQ_CONTROL_FLAGS_VOLATILE = (1 << 7),
	/**
	 * Control uses pointer values.
	 *
	 * The value is accessed through one of the pointers values in the
	 * vacq_control structure. It should be set when control type is
	 * #VACQ_CONTROL_TYPE_U8, #VACQ_CONTROL_TYPE_U16, #VACQ_CONTROL_TYPE_U32
	 * or #VACQ_CONTROL_TYPE_UNKNOWN.
	 */
	VACQ_CONTROL_FLAGS_HAS_PAYLOAD = (1 << 8),
	/**
	 * Control value is propagated to driver.
	 *
	 * The value is propagated to under layers even if the value read
	 * remains constant. It can be useful for clearing some bits of a
	 * value.
	 *
	 * All controls of type #VACQ_CONTROL_TYPE_BUTTON must have this flag
	 * set.
	 */
	VACQ_CONTROL_FLAGS_EXECUTE_ON_WRITE = (1 << 9),
	/**
	 * Control may modify the buffer layout and/or pad format.
	 *
	 * A write could change the output format or buffer layout: a typical
	 * example would be the #VACQ_CONTROL_CLASS_IMG_ROTATE control.
	 *
	 * This kind of controls should use the #VACQ_CONTROL_FLAGS_GRABBED when
	 * stream is started.
	 */
	VACQ_CONTROL_FLAGS_MODIFY_LAYOUT = (1 << 10),
};

/**
 * Device / pad control menu item.
 *
 * This structure describe one item of a control defined as a menu with the type
 * #VACQ_CONTROL_TYPE_MENU.
 *
 * A menu item can have a integer and/or a string value. At least one of the two
 * values must be set.
 */
struct vacq_control_menu_item {
	/** Name of the item. */
	const char *name;
	/** Value of the item. */
	long long value;
	/** Private data (used for device implementation). */
	void *priv;
};

/**
 * Maximal dimension count for a control.
 *
 * A control of compound type can have one or more dimensions. This macro
 * defines the maximal dimension count.
 */
#define VACQ_CTRL_DIM_MAX_COUNT (4)

/**
 * Device / pad control descriptor.
 *
 * This structure describes a control, by presenting its class, ID and type.
 *
 * Some additional data are present in the structure to provide the range,
 * element size or element / item count, according to the defined type.
 */
struct vacq_control_desc {
	/** Control class (see vacq_control_class for more details). */
	enum vacq_control_class ctrl_class;
	/**
	 * Control ID.
	 * This field should have one of the controls defined by class, or a
	 * custom value depending on the device implementation for a control of
	 * type #VACQ_CONTROL_TYPE_UNKNOWN.
	 */
	unsigned int id;
	/** Control type (see vacq_control_type for more details). */
	enum vacq_control_type type;
	/** Name of the control (optional). */
	const char *name;

	/**
	 * Minimum value, inclusive.
	 * This field is used for integer / bit-mask / compound controls.
	 */
	long long minimum;
	/**
	 * Maximum value, inclusive.
	 * This field is used for integer / bit-mask / compound controls.
	 */
	long long maximum;
	/**
	 * Step value.
	 * This field provides the step size for a control (optional).
	 */
	unsigned long long step;
	/**
	 * Default value.
	 * This field provides the default value to be set if application wants
	 * to restore default configuration (optional).
	 */
	long long default_value;

	/**
	 * Element size.
	 * This field is used only when control value is an array: it is the
	 * element size in bytes (1 for #VACQ_CONTROL_TYPE_U8, 2 for
	 * #VACQ_CONTROL_TYPE_U16, 4 for #VACQ_CONTROL_TYPE_U32 and any for
	 * #VACQ_CONTROL_TYPE_UNKNOWN).
	 */
	size_t elem_size;
	/**
	 * Element count.
	 * This field is used only when control value is an array: it is the
	 * element count in the array. If #dim_count is set, this value must be
	 * equal to the sum of all dimensions sizes.
	 */
	unsigned int elem_count;

	/**
	 * Menu item count.
	 * This field is set when type is #VACQ_CONTROL_TYPE_MENU and it
	 * contains the number of items.
	 */
	unsigned int item_count;
	/**
	 * Menu item list.
	 * This field is set when type is #VACQ_CONTROL_TYPE_MENU and it
	 * provides the menu item list (see vacq_control_menu_item for more
	 * details).
	 */
	const struct vacq_control_menu_item *item_list;

	/**
	 * Dimension count.
	 * This field is optional and can be used when the control value is an
	 * array, to specify how much dimensions are available.
	 */
	unsigned int dim_count;
	/**
	 * Dimension list.
	 * This field must be set when #dim_count is defined and it must
	 * contains a list of the dimension sizes.
	 */
	unsigned int dim_list[VACQ_CTRL_DIM_MAX_COUNT];

	/** Control flags (see vacq_control_flags for more details). */
	enum vacq_control_flags flags;

	/** Private data (used for device implementation). */
	void *priv;
};

/**
 * Device / pad control.
 *
 * This structure is used to read / write a device or a pad control,
 * respectively with vacq_device_get_control() / vacq_device_set_control() or
 * vacq_device_get_pad_control() / vacq_device_set_pad_control().
 *
 * The control is identified with the #ctrl_class and #id fields.
 *
 * The union must be set only when a write is attempted, according to the
 * control type defined in the corresponding vacq_control_desc entry.
 */
struct vacq_control {
	/** Control class (see vacq_control_class for more details). */
	enum vacq_control_class ctrl_class;
	/** Control ID (one of the control IDs defined for the class). */
	unsigned int id;
	/**
	 * Size of the array.
	 * If the control has an array type, the size of the array pointed by
	 * #p_u8, #p_u16, #p_u32 or #ptr mst be provided with this field.
	 */
	size_t size;
	union {
		/**
		 * Boolean / integer / bit-mask / menu item value.
		 * This field should be used when control type is:
		 *  - #VACQ_CONTROL_TYPE_BOOLEAN,
		 *  - #VACQ_CONTROL_TYPE_INTEGER,
		 *  - #VACQ_CONTROL_TYPE_BITMASK,
		 *  - #VACQ_CONTROL_TYPE_MENU.
		 */
		int value;
		/**
		 * Integer 64-bits value.
		 * This field should be used when control type is
		 * #VACQ_CONTROL_TYPE_INTEGER_64.
		 */
		long long value64;
		/**
		 * String value.
		 * This field should be used when control type is
		 * #VACQ_CONTROL_TYPE_STRING.
		 */
		char *string;
		/**
		 * 8-bits array.
		 * This field should be used when control type is
		 * #VACQ_CONTROL_TYPE_U8.
		 */
		unsigned char *p_u8;
		/**
		 * 16-bits array.
		 * This field should be used when control type is
		 * #VACQ_CONTROL_TYPE_U16.
		 */
		unsigned short *p_u16;
		/**
		 * 32-bits array.
		 * This field should be used when control type is
		 * #VACQ_CONTROL_TYPE_U32.
		 */
		unsigned int *p_u32;
		/**
		 * Unknown value / array.
		 * This field should be used when control type is
		 * #VACQ_CONTROL_TYPE_UNKNOWN.
		 */
		void *ptr;
	};
};

/** Controls for Processor class (see #VACQ_CONTROL_CLASS_PROC). */
enum vacq_control_class_proc {
	VACQ_CONTROL_CLASS_PROC_UNKNOWN = 0,
	/** Processor / IP block frequency in Hz. */
	VACQ_CONTROL_CLASS_PROC_FREQUENCY,

	VACQ_CONTROL_CLASS_PROC_COUNT
};

/** Controls for camera class (see #VACQ_CONTROL_CLASS_CAM). */
enum vacq_control_class_cam {
	VACQ_CONTROL_CLASS_CAM_UNKNOWN = 0,

	/**
	 * Camera mode.
	 * Can be an integer or a menu to select a specific mode for the camera.
	 * It should be set to 0 by default.
	 */
	VACQ_CONTROL_CLASS_CAM_MODE,

	/**
	 * Trigger camera capture.
	 * This control is used to trigger one or multiple frame capture on the
	 * camera sensor. Depending on the camera sensor, this control should be
	 * a boolean or a button type.
	 */
	VACQ_CONTROL_CLASS_CAM_TRIGGER,

	/** Exposure (in line count). */
	VACQ_CONTROL_CLASS_CAM_EXPOSURE,
	/** Fine exposure (in pixel count). */
	VACQ_CONTROL_CLASS_CAM_FINE_EXPOSURE,
	/** Exposure time (in us). */
	VACQ_CONTROL_CLASS_CAM_EXPOSURE_TIME,

	/** Analogue gain. */
	VACQ_CONTROL_CLASS_CAM_ANALOG_GAIN,
	/** Digital gain. */
	VACQ_CONTROL_CLASS_CAM_DIGITAL_GAIN,
	/**
	 * Analogue and/or digital gain.
	 * When the value is a mix between the analogue and digital gain, it
	 * should be like: value = analog_gain * digital_gain, where analogue
	 * gain is increased to its maximal value, then the digital gain is
	 * increased.
	 */
	VACQ_CONTROL_CLASS_CAM_GAIN,

	/** Horizontal binning factor. */
	VACQ_CONTROL_CLASS_CAM_BINNING_FACTOR_H,
	/** Vertical binning factor. */
	VACQ_CONTROL_CLASS_CAM_BINNING_FACTOR_V,
	/**
	 * Binning method to use.
	 * This control should be a menu. Please consider usage of
	 * vacq_ctrl_binning_method and its associated macros to define menu
	 * items.
	 */
	VACQ_CONTROL_CLASS_CAM_BINNING_METHOD,

	/** Horizontal skipping / sub-sampling mode. */
	VACQ_CONTROL_CLASS_CAM_SKIPPING_H,
	/** Vertical skipping / sub-sampling mode. */
	VACQ_CONTROL_CLASS_CAM_SKIPPING_V,

	/** Number of pixels by line (including horizontal / line blanking) */
	VACQ_CONTROL_CLASS_CAM_LINE_LENGTH,
	/** Number of lines per frame (including vertical blanking) */
	VACQ_CONTROL_CLASS_CAM_FRAME_LENGTH,
	/** Read-out time (in ns) */
	VACQ_CONTROL_CLASS_CAM_READOUT_TIME,
	/** Active period time (in us) */
	VACQ_CONTROL_CLASS_CAM_ACTIVE_PERIOD_TIME,

	/**
	 * Statistics control.
	 * This control is a #VACQ_CONTROL_TYPE_BITMASK type and bit-fields are
	 * defined by #vacq_ctrl_stats_type.
	 * It is used to enable / disable (by setting / clearing the
	 * corresponding bit) the internal statistics generation of the camera
	 * device.
	 */
	VACQ_CONTROL_CLASS_CAM_STATS_ENABLE,
	/**
	 * Statistics output.
	 * This control uses the same bit-field as
	 * #VACQ_CONTROL_CLASS_CAM_STATS_ENABLE to control the output of the
	 * statistics data on the physical link between the camera device and
	 * the receiver device.
	 */
	VACQ_CONTROL_CLASS_CAM_STATS_OUTPUT,

	VACQ_CONTROL_CLASS_CAM_COUNT
};

/** Binning method. */
enum vacq_ctrl_binning_method {
	/** Binning is disabled. */
	VACQ_CTRL_BINNING_METHOD_DISABLED = 0,
	/** Use automatic method. */
	VACQ_CTRL_BINNING_METHOD_AUTO,
	/** Averaged binning (average of all pixels). */
	VACQ_CTRL_BINNING_METHOD_AVERAGED,
	/** Summed binning (sum of all pixels). */
	VACQ_CTRL_BINNING_METHOD_SUMMED,
	/** Weighting averaged (average with weight on each pixels). */
	VACQ_CTRL_BINNING_METHOD_WEIGHTING_AVERAGED,
};
/** String for #VACQ_CTRL_BINNING_METHOD_DISABLED. */
#define VACQ_CTRL_BINNING_METHOD_DISABLED_NAME "disabled"
/** String for #VACQ_CTRL_BINNING_METHOD_AUTO. */
#define VACQ_CTRL_BINNING_METHOD_AUTO_NAME "auto"
/** String for #VACQ_CTRL_BINNING_METHOD_AVERAGED. */
#define VACQ_CTRL_BINNING_METHOD_AVERAGED_NAME "averaged"
/** String for #VACQ_CTRL_BINNING_METHOD_SUMMED. */
#define VACQ_CTRL_BINNING_METHOD_SUMMED_NAME "summed"
/** String for #VACQ_CTRL_BINNING_METHOD_WEIGHTING_AVERAGED. */
#define VACQ_CTRL_BINNING_METHOD_WEIGHTING_AVERAGED_NAME "weighting averaged"

/** Statistics type. */
enum vacq_ctrl_stats_type {
	/** Statistics data for Auto-Exposure. */
	VACQ_CTRL_STATS_TYPE_AE = (1 << 0),
	/** Statistics data for Auto-White-Balance. */
	VACQ_CTRL_STATS_TYPE_AWB = (1 << 1),
	/** Statistics data for Anti-flickering. */
	VACQ_CTRL_STATS_TYPE_FLICKER = (1 << 2),
	/** Statistics data for Phase-Detection-Auto-Focus */
	VACQ_CTRL_STATS_TYPE_PDAF = (1 << 3),

	/** All statistics data. */
	VACQ_CTRL_STATS_TYPE_ALL = ((1 << 4) - 1)
};

/** Controls for ISP class (see #VACQ_CONTROL_CLASS_ISP). */
enum vacq_control_class_isp {
	VACQ_CONTROL_CLASS_ISP_UNKNOWN = 0,

	/**
	 * Auto-Exposure mode.
	 * This control should be a menu. Please consider the vacq_ctrl_ae_mode
	 * and its associated macros to define menu items.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_MODE,

	/** Auto-Exposure lock. */
	VACQ_CONTROL_CLASS_ISP_AE_LOCK,
	/**
	 * Auto-Exposure EV.
	 * This control can be used to set the exposure value: the gain and
	 * exposure time will be calculated according to the internal P-chart of
	 * the AE.
	 * This value can be modified only during AE lock.
	 * It should be the product of #VACQ_CONTROL_CLASS_CAM_GAIN and
	 * #VACQ_CONTROL_CLASS_CAM_EXPOSURE_TIME units.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_EV,
	/**
	 * Auto-Exposure EV bias
	 * This control can be used to add a bias on the targeted exposure value
	 * of the AE.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_EV_BIAS,
	/**
	 * Auto-Exposure maximal ISO sensitivity.
	 * This control can be used to set a maximal ISO sensitivity for the
	 * auto exposure mode. A value of 0 reset the maximal value to default
	 * one.
	 */
	VACQ_CONTROL_CLASS_ISP_MAX_ISO_SENSITIVITY,
	/**
	 * Anti-flickering mode.
	 * This control should be a menu. Please consider the
	 * vacq_ctrl_flicker_mode and its associated macros to define menu
	 * items.
	 */
	VACQ_CONTROL_CLASS_ISP_FLICKER_MODE,
	/** Digital gain applied by ISP. */
	VACQ_CONTROL_CLASS_ISP_GAIN,

	/**
	 * Auto-White-Balance mode.
	 * This control should be a menu. Please consider the vacq_ctrl_awb_mode
	 * and its associated macros to define menu items.
	 */
	VACQ_CONTROL_CLASS_ISP_AWB_MODE,
	/** Auto-White-Balance lock. */
	VACQ_CONTROL_CLASS_ISP_AWB_LOCK,
	/** White-Balance temperature. */
	VACQ_CONTROL_CLASS_ISP_WB_TEMPERATURE,
	/** Red balance (used for White balance). */
	VACQ_CONTROL_CLASS_ISP_RED_BALANCE,
	/** Blue balance (used for White balance). */
	VACQ_CONTROL_CLASS_ISP_BLUE_BALANCE,

	/** Auto-Focus lock. */
	VACQ_CONTROL_CLASS_ISP_AF_LOCK,

	/**
	 * Image statistics to be fed to ISP.
	 * This control should have an unknown type so that an undefined
	 * structure can be passed as an argument based on device
	 * implementation.
	 */
	VACQ_CONTROL_CLASS_ISP_STATISTICS,

	/**
	 * Auto-exposure weight table.
	 * This control should be 2-dimensions matrix of integer which contains
	 * the weight value to apply for each zone on the image.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_WEIGHT_TABLE,

	/**
	 * Average luminance value.
	 * This control should be a read-only integer which reflects the current
	 * average luminance of the image, measured by the ISP.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_LUMINANCE,

	/**
	 * Auto-exposure luminance error.
	 * This control should be a read-only integer which reflects the
	 * difference between the auto-exposure luminance target and the actual
	 * luminance measured from the input image.
	 * Closer the value is to zero, the closer the actual luminance is to
	 * the auto-exposure target.
	 * A negative value will express a higher luminance level in the image
	 * and a positive value will express a lower luminance level in the
	 * image, than the auto exposure target.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_LUMINANCE_ERROR,

	/**
	 * Auto-exposure target.
	 * This control can be used to set / get the current auto-exposure
	 * average luminance target.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_TARGET,

	/**
	 * IQ tuning file path
	 * This control is used to specify a file path to use for IQ tuning.
	 * The control must be a string type and any file format can be used
	 * (dependent from device implementation).
	 */
	VACQ_CONTROL_CLASS_ISP_IQ_FILE,

	/**
	 * IQ tuning scale factor
	 * This control reflects the current scale factor (or zoom)
	 * used for IQ tuning.
	 * The control should be an integer type.
	 */
	VACQ_CONTROL_CLASS_ISP_IQ_SCALE_FACTOR,

	/**
	 * ISP AE statistics crop.
	 * This control reflects the crop whithin the isp image for AE
	 * statistics generation. It can be used to set a Region Of Interest
	 * (ROI) for the AE algorithm.
	 * The control should be an array of integers representing rectangle
	 * coordinates in the following order: start X, start Y, width and
	 * height.
	 */
	VACQ_CONTROL_CLASS_ISP_AE_STATS_CROP,

	VACQ_CONTROL_CLASS_ISP_COUNT
};

/** Auto-exposure mode. */
enum vacq_ctrl_ae_mode {
	/** Automatic exposure time / gain */
	VACQ_CTRL_AE_MODE_AUTO = 0,
	/**
	 * Manual exposure time / gain.
	 * Values should be set with #VACQ_CONTROL_CLASS_CAM_EXPOSURE_TIME and
	 * #VACQ_CONTROL_CLASS_CAM_GAIN.
	 */
	VACQ_CTRL_AE_MODE_MANUAL,
	/**
	 * Manual exposure time / automatic gain.
	 * The exposure time should be set with
	 * #VACQ_CONTROL_CLASS_CAM_EXPOSURE_TIME.
	 */
	VACQ_CTRL_AE_MODE_SHUTTER_PRIORITY,
	/**
	 * Automatic exposure time / manual gain.
	 * The gain value should be set with #VACQ_CONTROL_CLASS_CAM_GAIN.
	 */
	VACQ_CTRL_AE_MODE_ISO_PRIORITY,
	/**
	 * Automatic exposure time / gain with preference on exposure time.
	 * The auto-exposure algorithm will increase the exposure time first and
	 * tries to keep a low gain.
	 */
	VACQ_CTRL_AE_MODE_AUTO_PREFER_SHUTTER,
	/**
	 * Automatic exposure time / gain with preference on gain.
	 * The auto-exposure algorithm will increase the gain first and tries to
	 * keep a low exposure time.
	 */
	VACQ_CTRL_AE_MODE_AUTO_PREFER_ISO,
};
/** String for #VACQ_CTRL_AE_MODE_AUTO. */
#define VACQ_CTRL_AE_MODE_AUTO_NAME "auto"
/** String for #VACQ_CTRL_AE_MODE_MANUAL. */
#define VACQ_CTRL_AE_MODE_MANUAL_NAME "manual"
/** String for #VACQ_CTRL_AE_MODE_SHUTTER_PRIORITY. */
#define VACQ_CTRL_AE_MODE_SHUTTER_PRIORITY_NAME "shutter_priority"
/** String for #VACQ_CTRL_AE_MODE_ISO_PRIORITY. */
#define VACQ_CTRL_AE_MODE_ISO_PRIORITY_NAME "iso_priority"
/** String for #VACQ_CTRL_AE_MODE_AUTO_PREFER_SHUTTER. */
#define VACQ_CTRL_AE_MODE_AUTO_PREFER_SHUTTER_NAME "auto_prefer_shutter"
/** String for #VACQ_CTRL_AE_MODE_AUTO_PREFER_ISO. */
#define VACQ_CTRL_AE_MODE_AUTO_PREFER_ISO_NAME "auto_prefer_iso"

/** Anti-flickering mode. */
enum vacq_ctrl_flicker_mode {
	/**
	 * Anti-flickering is disabled.
	 * Use #VACQ_CTRL_FLICKER_MODE_DISABLED_NAME for string.
	 */
	VACQ_CTRL_FLICKER_MODE_DISABLED = 0,
	/**
	 * Anti-flickering is set to 50 Hz.
	 * Use #VACQ_CTRL_FLICKER_MODE_50HZ_NAME for string.
	 */
	VACQ_CTRL_FLICKER_MODE_50HZ,
	/**
	 * Anti-flickering is set to 60 Hz.
	 * Use #VACQ_CTRL_FLICKER_MODE_60HZ_NAME for string.
	 */
	VACQ_CTRL_FLICKER_MODE_60HZ,
	/**
	 * Anti-flickering is set to auto.
	 * Use #VACQ_CTRL_FLICKER_MODE_AUTO_NAME for string.
	 */
	VACQ_CTRL_FLICKER_MODE_AUTO,

	VACQ_CTRL_FLICKER_MODE_COUNT
};
/** String for #VACQ_CTRL_FLICKER_MODE_DISABLED. */
#define VACQ_CTRL_FLICKER_MODE_DISABLED_NAME "disabled"
/** String for #VACQ_CTRL_FLICKER_MODE_50HZ_NAME. */
#define VACQ_CTRL_FLICKER_MODE_50HZ_NAME "50Hz"
/** String for #VACQ_CTRL_FLICKER_MODE_60HZ_NAME. */
#define VACQ_CTRL_FLICKER_MODE_60HZ_NAME "60Hz"
/** String for #VACQ_CTRL_FLICKER_MODE_AUTO_NAME. */
#define VACQ_CTRL_FLICKER_MODE_AUTO_NAME "auto"

/** Auto-white-balance mode. */
enum vacq_ctrl_awb_mode {
	/** Automatic white balande */
	VACQ_CTRL_AWB_MODE_AUTO = 0,
	/**
	 * Manual white balance.
	 * Temperature value should be set with
	 * #VACQ_CONTROL_CLASS_ISP_WB_TEMPERATURE control.
	 */
	VACQ_CTRL_AWB_MODE_MANUAL,
};
/** String for #VACQ_CTRL_AWB_MODE_AUTO. */
#define VACQ_CTRL_AWB_MODE_AUTO_NAME "auto"
/** String for #VACQ_CTRL_AWB_MODE_MANUAL. */
#define VACQ_CTRL_AWB_MODE_MANUAL_NAME "manual"

/** Controls for image class (see #VACQ_CONTROL_CLASS_IMG). */
enum vacq_control_class_img {
	VACQ_CONTROL_CLASS_IMG_UNKNOWN = 0,

	/** Do an horizontal flip. */
	VACQ_CONTROL_CLASS_IMG_HFLIP,
	/** Do a vertical flip. */
	VACQ_CONTROL_CLASS_IMG_VFLIP,
	/** Rotation angle. */
	VACQ_CONTROL_CLASS_IMG_ROTATE,

	/** Scale method.
	 * This control should be a menu. Please consider usage of
	 * vacq_ctrl_scale_method and its associated macros to define menu
	 * items.
	 */
	VACQ_CONTROL_CLASS_IMG_SCALE_METHOD,
	/** Scale factor.
	 * This control set the upsampling / downsampling factor for an internal
	 * scaler. If the value is > 1, an upscale is done, if the value is < 1,
	 * a downscale is done.
	 */
	VACQ_CONTROL_CLASS_IMG_SCALE_FACTOR,
	/** Scale factor unit / denominator.
	 * This control can be used to set the unit of the scale factor as:
	 * final factor = value of #VACQ_CONTROL_CLASS_IMG_SCALE_FACTOR / value
	 * of #VACQ_CONTROL_CLASS_IMG_SCALE_FACTOR_UNIT. It can be seen also as
	 * a denominator.
	 */
	VACQ_CONTROL_CLASS_IMG_SCALE_FACTOR_UNIT,

	/** Pixel clock in Hz */
	VACQ_CONTROL_CLASS_IMG_PIXEL_CLOCK,

	VACQ_CONTROL_CLASS_IMG_COUNT
};

/** Scale method. */
enum vacq_ctrl_scale_method {
	/** Scaler is disabled. */
	VACQ_CTRL_SCALE_METHOD_DISABLED = 0,
	/** Automatic method. */
	VACQ_CTRL_SCALE_METHOD_AUTO,
	/** Nearest-neighbor interpolation. */
	VACQ_CTRL_SCALE_METHOD_NEAREST,
	/** Bilinear interpolation. */
	VACQ_CTRL_SCALE_METHOD_BILINEAR,
	/** Bicubic interpolation. */
	VACQ_CTRL_SCALE_METHOD_BICUBIC,
	/** Lanczos resampling. */
	VACQ_CTRL_SCALE_METHOD_LANCZOS,
	/** Sinc resampling. */
	VACQ_CTRL_SCALE_METHOD_SINC,
	/** Spline interpolation. */
	VACQ_CTRL_SCALE_METHOD_SPLINE,
	/** Bayer interpolation. */
	VACQ_CTRL_SCALE_METHOD_BAYER,
	/** Bayer binning downsampling. */
	VACQ_CTRL_SCALE_METHOD_BAYER_BIN,
};
/** String for #VACQ_CTRL_SCALE_METHOD_DISABLED. */
#define VACQ_CTRL_SCALE_METHOD_DISABLED_NAME "disabled"
/** String for #VACQ_CTRL_SCALE_METHOD_AUTO. */
#define VACQ_CTRL_SCALE_METHOD_AUTO_NAME "auto"
/** String for #VACQ_CTRL_SCALE_METHOD_NEAREST. */
#define VACQ_CTRL_SCALE_METHOD_NEAREST_NAME "nearest-neighbor"
/** String for #VACQ_CTRL_SCALE_METHOD_BILINEAR. */
#define VACQ_CTRL_SCALE_METHOD_BILINEAR_NAME "bilinear"
/** String for #VACQ_CTRL_SCALE_METHOD_BICUBIC. */
#define VACQ_CTRL_SCALE_METHOD_BICUBIC_NAME "bicubic"
/** String for #VACQ_CTRL_SCALE_METHOD_LANCZOS. */
#define VACQ_CTRL_SCALE_METHOD_LANCZOS_NAME "lanczos"
/** String for #VACQ_CTRL_SCALE_METHOD_SINC. */
#define VACQ_CTRL_SCALE_METHOD_SINC_NAME "sinc"
/** String for #VACQ_CTRL_SCALE_METHOD_SPLINE. */
#define VACQ_CTRL_SCALE_METHOD_SPLINE_NAME "spline"
/** String for #VACQ_CTRL_SCALE_METHOD_BAYER. */
#define VACQ_CTRL_SCALE_METHOD_BAYER_NAME "bayer"
/** String for #VACQ_CTRL_SCALE_METHOD_BAYER_BIN. */
#define VACQ_CTRL_SCALE_METHOD_BAYER_BIN_NAME "bayer binning"

/** Controls for debug class (see #VACQ_CONTROL_CLASS_DBG). */
enum vacq_control_class_dbg {
	VACQ_CONTROL_CLASS_DBG_UNKNOWN = 0,

	/**
	 * Test pattern control.
	 * This control should be used to enable / disable test pattern
	 * generation. It should be a boolean.
	 */
	VACQ_CONTROL_CLASS_DBG_TEST_PATTERN,
	/**
	 * Test pattern mode.
	 * This control should be a menu.
	 */
	VACQ_CONTROL_CLASS_DBG_TEST_PATTERN_MODE,

	VACQ_CONTROL_CLASS_DBG_COUNT
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VACQ_CONTROLS_H_ */
