/*
 * Copyright (c) 2019 Parrot Drones SAS
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
 * @file vacq_events.h
 * @copyright Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef _VACQ_EVENTS_H_
#define _VACQ_EVENTS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Event type.
 *
 * Device can generate some events to notify application about new frame or
 * control value changes.
 *
 * An event can have one of the standard types or a custom type which must be
 * associated with an unique ID.
 *
 * When the #VACQ_EVENT_TYPE_CUSTOM type is used, the vacq_event_sub.id must be
 * set with the corresponding custom event to catch.
 *
 * The #VACQ_EVENT_TYPE_ALL type can be used to unsubscribe all events in once.
 */
enum vacq_event_type {
	/**
	 * All events.
	 * Only valid when calling vacq_device_unsubscribe_event() to
	 * unsubscribe all events in once.
	 */
	VACQ_EVENT_TYPE_ALL = 0,

	/**
	 * Start Of Frame event.
	 * This event is triggered when device start to acquire / process a new
	 * frame.
	 * The vacq_event.frame is set accordingly.
	 */
	VACQ_EVENT_TYPE_SOF,
	/**
	 * Middle Of Frame event.
	 * This event is triggered when device has acquired / processed half of
	 * the frame.
	 * The vacq_event.frame is set accordingly.
	 */
	VACQ_EVENT_TYPE_MOF,
	/**
	 * End Of Frame event.
	 * This event is triggered when device finish to acquire / process a
	 * frame.
	 * The vacq_event.frame is set accordingly.
	 */
	VACQ_EVENT_TYPE_EOF,

	/**
	 * Control event.
	 * This event is triggered when a control value is changed.
	 * To select which control to monitor, the vacq_event_sub.ctrl_class and
	 * vacq_event_sub.id must be set.
	 * The vacq_event.control is set accordingly.
	 */
	VACQ_EVENT_TYPE_CTRL,

	/**
	 * Sync event.
	 * This event is triggered when device has reached a synchronized state
	 * internally. It can be used to synchronize the device with some
	 * external operations like ISP settings update.
	 */
	VACQ_EVENT_TYPE_SYNC,

	/**
	 * Custom event.
	 * This event type is used to specify a custom event which is device
	 * implementation dependant. The vacq_event_sub.id and vacq_event.id is
	 * used to differentiate multiple custom events.
	 */
	VACQ_EVENT_TYPE_CUSTOM,

	VACQ_EVENT_TYPE_COUNT
};

/**
 * Device / pad  event descriptor.
 *
 * This structure describes an event, by presenting its type and ID and name for
 * custom events.
 */
struct vacq_event_desc {
	/** Event type. */
	enum vacq_event_type type;
	/**
	 * Custom event ID.
	 * This field is set with the ID of the current custom event.
	 */
	unsigned int id;
	/**
	 * Custom event name.
	 * This field should be set to provide some clues on event when type is
	 * #VACQ_EVENT_TYPE_CUSTOM.
	 */
	const char *name;
};

/**
 * Event subscription flags.
 *
 * When application subscribe to a new event, some flags can be set to specify
 * when event should be raised.
 */
enum vacq_event_sub_flags {
	/** No flags. */
	VACQ_EVENT_SUB_FLAGS_NONE = 0,
};

/**
 * Event subscription descriptor.
 *
 * This structure is used during call of vacq_device_subscribe_event() and
 * vacq_device_unsubscribe_event() to specify which kind of event should be
 * monitored by the application. Some additional fields as #ctrl_class and #id
 * can be used to provide more details on the event to catch.
 *
 * For more details on event type available, please refer to #vacq_event_type.
 */
struct vacq_event_sub {
	/** Event type to catch. */
	enum vacq_event_type type;
	/**
	 * Control class to catch.
	 * This field is used only when the event type is #VACQ_EVENT_TYPE_CTRL.
	 */
	enum vacq_control_class ctrl_class;
	/**
	 * Event ID to catch.
	 * This field is the control ID when event type is #VACQ_EVENT_TYPE_CTRL
	 * and it is the custom event ID when event type is
	 * #VACQ_EVENT_TYPE_CUSTOM.
	 */
	unsigned int id;
	/** Event subscription flags to use. */
	enum vacq_event_sub_flags flags;
};

/**
 * Frame event data.
 *
 * This structure contains data about a #VACQ_EVENT_TYPE_SOF,
 * #VACQ_EVENT_TYPE_MOF or #VACQ_EVENT_TYPE_EOF event.
 */
struct vacq_event_frame {
	/**
	 * Sequence number of the current frame.
	 * This sequence number is connected to the sequence number of the
	 * #vacq_buffer structure and it can be used to follow a frame from its
	 * start of capture / processing until the vacq_device_get_frame() call.
	 */
	unsigned int sequence;
};

/**
 * Control event data.
 *
 * This structure contains data about a #VACQ_EVENT_TYPE_CTRL.
 */
struct vacq_event_control {
	/** Control class of the control value which has changed. */
	enum vacq_control_class ctrl_class;
	/** Control ID of the control value which has changed. */
	unsigned int id;
};

/**
 * Event descriptor.
 *
 * This structure contains all data about an event which has been triggered.
 * Each event has a time stamp set in #ts and it should correspond to the moment
 * at which the event occurred.
 *
 * The remaining event counts to dequeue with vacq_device_get_event() is set in
 * the field #pending. The function vacq_device_get_event() should be called
 * until the #pending value is zero.
 */
struct vacq_event {
	/** Type of the event. */
	enum vacq_event_type type;
	/**
	 * ID of the current event.
	 * This field is valid only for #VACQ_EVENT_TYPE_CTRL and
	 * #VACQ_EVENT_TYPE_CUSTOM events.
	 */
	unsigned int id;
	/**
	 * Remaining events in queue.
	 * The function vacq_device_get_event() should be called until this
	 * value is equal to zero.
	 */
	unsigned int pending;
	/**
	 * Sequence number of the event.
	 * This value is incremented at each event generation. If the internal
	 * event queue is full, the next events will increment this sequence
	 * number but event will be dropped. Then, it can be used to detect an
	 * event drop.
	 */
	unsigned int sequence;
	/**
	 * Time stamp of the event.
	 * This time stamp is the exact date at which the events has occurred.
	 */
	struct timespec ts;
	union {
		/**
		 * Frame event data.
		 * This field is set when #type is #VACQ_EVENT_TYPE_SOF,
		 * #VACQ_EVENT_TYPE_MOF or #VACQ_EVENT_TYPE_EOF.
		 */
		struct vacq_event_frame frame;
		/**
		 * Control event data.
		 * This field is set when #type is #VACQ_EVENT_TYPE_CTRL.
		 */
		struct vacq_event_control control;
		/**
		 * Custom event data.
		 * This field can be set when #type is #VACQ_EVENT_TYPE_CUSTOM.
		 */
		unsigned char data[64];
	};
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VACQ_EVENTS_H_ */
