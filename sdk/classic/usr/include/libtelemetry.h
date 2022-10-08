/**
 * Copyright (c) 2015 Parrot S.A.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Parrot Company nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE PARROT COMPANY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @file libtelemetry.h
 *
 */

#ifndef _LIBTELEMETRY_H_
#define _LIBTELEMETRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"  {
#endif /* __cplusplus */

/** Library major version. Updated for API changes */
#define TLM_VERSION_MAJOR      1

/** Library minor version. Updated for API addition or internal changes */
#define TLM_VERSION_MINOR      1

/** Type of variables */
enum tlm_var_type {
	TLM_TYPE_INVALID = -1,
	TLM_TYPE_BOOL = 0, /**< Boolean value 8-bit */
	TLM_TYPE_UINT8,    /**< 8-bit unsigned value */
	TLM_TYPE_INT8,     /**< 8-bit signed value */
	TLM_TYPE_UINT16,   /**< 16-bit unsigned value */
	TLM_TYPE_INT16,    /**< 16-bit signed value */
	TLM_TYPE_UINT32,   /**< 32-bit unsigned value */
	TLM_TYPE_INT32,    /**< 32-bit signed value */
	TLM_TYPE_UINT64,   /**< 64-bit unsigned value */
	TLM_TYPE_INT64,    /**< 64-bit signed value */
	TLM_TYPE_FLOAT32,  /**< 32-bit float value */
	TLM_TYPE_FLOAT64,  /**< 64-bit float (double) value */
	TLM_TYPE_STRING,   /**< Character string (fixed-size array of char) */
	TLM_TYPE_BINARY,   /**< Binary data (fixed-size array of u8) */
	TLM_TYPE_STRUCT,   /**< Complexe structure */
	/** Last entry corresponds to number of entries */
	TLM_TYPE_COUNT
};

/** Flags for variable registrations */
enum tlm_flag {
	TLM_FLAG_DEFAULT = 0,     /**< Deprecated */
	TLM_FLAG_INHERIT = 0,     /**< Deprecated */
	TLM_FLAG_NO_LOG = 1 << 2, /**< Deprecated */
	TLM_FLAG_POINTER = 1 << 3,/**< Variable is actually a pointer */
};

/** Query method */
enum tlm_method {
	TLM_LATEST,       /**< Get last sample (timestamp of query unused) */
	TLM_CLOSEST,      /**< Get closest sample to a given timestamp */
	TLM_FIRST_AFTER,  /**< Get closest sample AFTER given timestamp */
	TLM_FIRST_BEFORE, /**< Get closest sample BEFORE given timestamp */
	TLM_OLDEST,       /**< Get oldest sample (query timestamp unused) */

	TLM_STRICTLY_AFTER,  /**< Get closest sample STRICTLY AFTER ts */
	TLM_STRICTLY_BEFORE, /**< Get closest sample STRICTLY BEFORE ts */
};

/* Forward declarations */
struct timespec;
struct tlm_producer;
struct tlm_consumer;

/** Producer registration entry */
struct tlm_producer_reg_entry {
	void               *ptr;  /**< Pointer to data, shall be valid during
				       the lifetime of the producer */
	const char         *name; /**< Name of the variable
				       (excluding the section name) */
	enum tlm_var_type  type;  /**< Type of data produced */
	size_t             size;  /**< Size of a single data element */
	size_t             count; /**< Number of elements
				       (> 1 in the case of arrays) */
	uint32_t           flags; /**< Flags for registration */
};

/** Internal macro to fill a 'tlm_producer_reg_entry' structure */
#define _TLM_PRODUCER_REG_ENTRY_RAW(_ptr, _name, _type, _size, _count) \
	{ \
		.ptr = _ptr, \
		.name = _name, \
		.type = _type, \
		.size = _size, \
		.count = _count, \
		.flags = 0, \
	} \

/**
 * Macro to fill a 'tlm_producer_reg_entry' structure with a scalar.
 * _ptr: pointer to the variable.
 * _name: name of the variable in the telemetry section.
 * _type: type of the variable.
 */
#define TLM_PRODUCER_REG_ENTRY_SCALAR(_ptr, _name, _type) \
	_TLM_PRODUCER_REG_ENTRY_RAW(_ptr, _name, _type, sizeof(*(_ptr)), 1)

/** Consumer registration entry */
struct tlm_consumer_reg_entry {
	void               *ptr;  /**< Pointer to data, shall be valid during
				       the lifetime of the consumer */
	const char         *name; /**< Name of the variable
				       (including the section name) */
	enum tlm_var_type  type;  /**< Type of data */
	size_t             size;  /**< Size of one element of data */
	size_t             count; /**< Number of elements (> 1 for arrays) */
	struct timespec    *timestamp; /**< Optional pointer to a timestamp to
					    be filled during 'get' methods */
};

/** Consumer registration entry for an array of samples */
struct tlm_consumer_reg_samples_entry {
	void               *ptr;
	const char         *name;
	enum tlm_var_type  type;
	size_t             size;
	size_t             count;
	size_t             nb_samples;
	struct timespec    *timestamps;
};

/** Internal macro to fill a 'tlm_consumer_reg_entry' structure */
#define _TLM_CONSUMER_REG_ENTRY_RAW(_ptr, _name, _type, _size, _count) \
	{ \
		.ptr = _ptr, \
		.name = _name, \
		.type = _type, \
		.size = _size, \
		.count = _count, \
		.timestamp = NULL, \
	} \

/**
 * Macro to fill a 'tlm_consumer_reg_entry' structure with a scalar.
 * _ptr: pointer to the variable.
 * _name: name of the variable in the telemetry section.
 * _type: type of the variable.
 */
#define TLM_CONSUMER_REG_ENTRY_SCALAR(_ptr, _name, _type) \
	_TLM_CONSUMER_REG_ENTRY_RAW(_ptr, _name, _type, sizeof(*(_ptr)), 1)

/** Field registration structure */
struct tlm_reg_field {
	/** Offset of the field in the parent structure */
	size_t			off;

	/** Name of the field */
	const char		*name;

	/** Type of the field */
	enum tlm_var_type	type;

	/** Size of a single element */
	size_t			size;

	/** Number of elements (> 1 in the case of arrays) */
	size_t			count;

	/** Additional flags */
	uint32_t		flags;

	/** Sub-structure description if type is TLM_TYPE_STRUCT */
	const struct tlm_reg_struct	*desc;
};

/** Structure registration structure */
struct tlm_reg_struct {
	/**
	 * Name of the structure (informative, not used in telemetry section)
	 * */
	const char		*name;

	/** Number of fields in the structure */
	size_t			count;

	/** Array of field description */
	const struct tlm_reg_field	*fields;
};

/** Get the size of field inside a structure */
#define _TLM_FIELD_SIZE(_type, _member) \
	sizeof(((_type *)0)->_member)

/** Get the size of field array element inside a structure */
#define _TLM_FIELD_SIZE_ARRAY(_type, _member) \
	sizeof(((_type *)0)->_member[0])

/** Get the count of field array element inside a structure */
#define _TLM_FIELD_COUNT_ARRAY(_type, _member) \
	(sizeof(((_type *)0)->_member) / sizeof(((_type *)0)->_member[0]))

/** Internal macro to fill a 'tlm_reg_field' structure */
#define _TLM_REG_FIELD_RAW(_off, _name, _type, _size, _count, _flags, _desc) \
	{ \
		.off = _off, \
		.name = _name, \
		.type = _type, \
		.size = _size, \
		.count = _count, \
		.flags = _flags, \
		.desc = _desc, \
	} \

/** Fill a scalar field description */
#define TLM_REG_FIELD_SCALAR(_parent, _field, _type) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		#_field, _type, \
		_TLM_FIELD_SIZE(_parent, _field), \
		1, 0, NULL)
#define TLM_REG_FIELD_SCALAR_EX(_parent, _field, _name, _type) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		_name, _type, \
		_TLM_FIELD_SIZE(_parent, _field), \
		1, 0, NULL)

/** Fill an array of scalar field description */
#define TLM_REG_FIELD_SCALAR_ARRAY(_parent, _field, _type) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		#_field, _type, \
		_TLM_FIELD_SIZE_ARRAY(_parent, _field), \
		_TLM_FIELD_COUNT_ARRAY(_parent, _field), 0, NULL)
#define TLM_REG_FIELD_SCALAR_ARRAY_EX(_parent, _field, _name, _type) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		_name, _type, \
		_TLM_FIELD_SIZE_ARRAY(_parent, _field), \
		_TLM_FIELD_COUNT_ARRAY(_parent, _field), 0, NULL)

/** Fill a sub-structure field description */
#define TLM_REG_FIELD_STRUCT(_parent, _field, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		#_field, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE(_parent, _field), \
		1, 0, _desc)
#define TLM_REG_FIELD_STRUCT_EX(_parent, _field, _name, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		_name, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE(_parent, _field), \
		1, 0, _desc)

/** Fill a pointer to a sub-structure field description */
#define TLM_REG_FIELD_STRUCT_PTR(_parent, _field, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		#_field, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE(_parent, _field), \
		1, TLM_FLAG_POINTER, _desc)
#define TLM_REG_FIELD_STRUCT_PTR_EX(_parent, _field, _name, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		_name, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE(_parent, _field), \
		1, TLM_FLAG_POINTER, _desc)

/** Fill an array of sub-structure field description */
#define TLM_REG_FIELD_STRUCT_ARRAY(_parent, _field, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		#_field, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE_ARRAY(_parent, _field), \
		_TLM_FIELD_COUNT_ARRAY(_parent, _field), \
		0, _desc)
#define TLM_REG_FIELD_STRUCT_ARRAY_EX(_parent, _field, _name, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		_name, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE_ARRAY(_parent, _field), \
		_TLM_FIELD_COUNT_ARRAY(_parent, _field), \
		0, _desc)

/** Fill an array of pointer to a sub-structure field description */
#define TLM_REG_FIELD_STRUCT_PTR_ARRAY(_parent, _field, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		#_field, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE(_parent, _field), \
		_TLM_FIELD_COUNT_ARRAY(_parent, _field), \
		TLM_FLAG_POINTER, _desc)
#define TLM_REG_FIELD_STRUCT_PTR_ARRAY_EX(_parent, _field, _name, _desc) \
	_TLM_REG_FIELD_RAW(offsetof(_parent, _field), \
		_name, TLM_TYPE_STRUCT, \
		_TLM_FIELD_SIZE(_parent, _field), \
		_TLM_FIELD_COUNT_ARRAY(_parent, _field), \
		TLM_FLAG_POINTER, _desc)

/** Fill a structure description */
#define TLM_REG_STRUCT(_name, _fields) \
	{ \
		.name = _name, \
		.count = sizeof(_fields) / sizeof(_fields[0]), \
		.fields = _fields, \
	}

/**
 * Get runtime version of the library.
 * @param major: Pointer to major version.
 * @param minor: Pointer to minor version.
 *
 * @return 0 in case of success, negative errno in case of error.
 *
 * @remarks This function should never change even on major version updates.
 */
int tlm_get_version(uint32_t *major, uint32_t *minor);

/**
 * Convert a variable type to a human readable string.
 * @param type: type to convert.
 * @return string with type.
 */
const char *tlm_get_var_type_str(enum tlm_var_type type);

/**
 * Create a new producer.
 * @param section: name of the producer (section).
 * @param maxsamples: Maximum number of samples.
 * @param rate: Approximative rate of samples (in us).
 * @return created producer or NULL in case of error.
 * @remark a YAML alias map file can be set in environment variable
 * 'TLM_ALIAS_MAP_FILE'
 */
struct tlm_producer *tlm_producer_new(
		const char *section,
		uint32_t maxsamples,
		uint32_t rate);

/**
 * Create a new producer for a debug section. Debug sections can not be opened
 * by regular consumers, only by loggers.
 * @param section: name of the producer (section).
 * @param maxsamples: Maximum number of samples.
 * @param rate: Approximative rate of samples (in us).
 * @return created producer or NULL in case of error.
 * @remark a YAML alias map file can be set in environment variable
 * 'TLM_ALIAS_MAP_FILE'
 */
struct tlm_producer *tlm_producer_new_debug(
			const char *section,
			uint32_t maxsamples,
			uint32_t rate);

/**
 * Create a new producer.
 * @param section: name of the producer (section).
 * @param dir: directory where to create the shared memory.
 * @param maxsamples: Maximum number of samples.
 * @param rate: Approximative rate of samples (in us).
 * @return created producer or NULL in case of error.
 */
struct tlm_producer *tlm_producer_new_with_dir(
		const char *section,
		const char *dir,
		uint32_t maxsamples,
		uint32_t rate);

/**
 * Create a new producer for a debug section. Debug sections can not be opened
 * by regular consumers, only by loggers.
 * @param section: name of the producer (section).
 * @param dir: directory where to create the shared memory.
 * @param maxsamples: Maximum number of samples.
 * @param rate: Approximative rate of samples (in us).
 * @return created producer or NULL in case of error.
 */
struct tlm_producer *tlm_producer_new_debug_with_dir(
		const char *section,
		const char *dir,
		uint32_t maxsamples,
		uint32_t rate);

/**
 * Destroy a producer.
 * @param producer: producer to destroy.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_producer_destroy(struct tlm_producer *producer);

/**
 * Register a new variable.
 * @param producer: producer object.
 * @param ptr: pointer to variable.
 * @param name: name of variable.
 * @param type: type of variable.
 * @param size: size of variable.
 * @param count: number of variables for arrays.
 * @param flags: flags for the variable.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_producer_reg(struct tlm_producer *producer,
		void *ptr,
		const char *name,
		enum tlm_var_type type,
		size_t size,
		size_t count,
		uint32_t flags);

/**
 * Register an array of entries.
 * @param producer:  producer object.
 * @param entries: array of entries.
 * @param count: number of entries.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_producer_reg_array(struct tlm_producer *producer,
		const struct tlm_producer_reg_entry *entries,
		size_t count);

/**
 * Register variables using a recursive structure description and a pointer to
 * the base of the structure. Internally, the description will be analyzed and
 * variables automatically registered with the given pointer as base. Fields
 * can contain the flag 'TLM_FLAG_POINTER' to construct complex opaque
 * structures.
 *
 * @param producer: producer object.
 * @param ptr: pointer to the base of the structure. Its scope should be valid
 * until the producer is destroyed because 'tlm_put_sample' will implicitly
 * dereference it.
 * @param name: optional name to prefix to all fields. Useful when registering
 * multiple descriptions. The same behaviour can be achieved by creating a top
 * level structure description and calling this function just once.
 * @param desc: description of the structure.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_producer_reg_struct_ptr(struct tlm_producer *producer,
		const void *ptr,
		const char *name,
		const struct tlm_reg_struct *desc);
/**
 * Complete registration of variables.
 * Must be called after all variables have been registered.
 * @param producer: producer object.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_producer_reg_complete(struct tlm_producer *producer);

/**
 * Force recreation of shared memory sections.
 * @param producer: producer object.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_producer_reset(struct tlm_producer *producer);

/**
 * Put a new sample.
 * @param producer: producer object.
 * @param timestamp: timestamp of new sample or NULL to use current time.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_producer_put_sample(struct tlm_producer *producer,
		const struct timespec *timestamp);

/**
 * Create a new consumer.
 * @return created consumer or NULL in case of error.
 * @remark a YAML alias map file can be set in environment variable
 * 'TLM_ALIAS_MAP_FILE'
 */
struct tlm_consumer *tlm_consumer_new(void);

/**
 * Create a new consumer.
 * @param dir: directory where to open the shared memory.
 * @return created consumer or NULL in case of error.
 */
struct tlm_consumer *tlm_consumer_new_with_dir(const char *dir);

/**
 * Destroy a consumer.
 * @param consumer: consumer to destroy.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_consumer_destroy(struct tlm_consumer *consumer);

/**
 * Register a new variable.
 * @param consumer: consumer object.
 * @param ptr: pointer to variable.
 * @param name: name of variable.
 * @param type: type of variable.
 * @param size: size of variable.
 * @param count: number of variables for arrays.
 * @param timestamp: structure where to store timestamp of samples.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_consumer_reg(struct tlm_consumer *consumer,
		void *ptr,
		const char *name,
		enum tlm_var_type type,
		size_t size,
		size_t count,
		struct timespec *timestamp);

/**
 * Register an array of entries.
 * @param consumer:  consumer object.
 * @param entries: array of entries.
 * @param count: number of entries.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_consumer_reg_array(struct tlm_consumer *consumer,
		const struct tlm_consumer_reg_entry *entries,
		size_t count);

/**
 * Register an array of samples.
 * @param consumer: consumer object.
 * @param ptr: pointer to an array that will hold the variable samples.
 * It should be a 2D array if the parameter count is greater than 1.
 * @param name: name of variable.
 * @param type: type of variable.
 * @param size: size of variable.
 * @param count: number of elements in the variable. If the variable holds
 * more than 1 element then the parameter ptr points to a 2D array of the
 * form array[nb_samples][count].
 * @param nb_samples: the number of requested samples that will be stored
 * in the array pointed to by the parameter ptr.
 * @param timestamps: array that stores the timestamp of each sample.
 * This timestamps array should have the size of nb_samples.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_consumer_reg_array_of_samples(struct tlm_consumer *consumer,
					void *ptr,
					const char *name,
					enum tlm_var_type type,
					size_t size,
					size_t count,
					size_t nb_samples,
					struct timespec *timestamps);

/**
 * Register an array of entries describing arrays of samples.
 * @param consumer:  consumer object.
 * @param entries: array of entries.
 * @param count: number of entries.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_consumer_reg_entries_of_samples_array(struct tlm_consumer *consumer,
			const struct tlm_consumer_reg_samples_entry *entries,
			size_t count);
/**
 * Register variables using a recursive structure description and a pointer to
 * the base of the structure. Internally, the description will be analyzed and
 * variables automatically registered with the given pointer as base. Fields
 * can contain the flag 'TLM_FLAG_POINTER' to construct complex opaque
 * structures.
 * Note this takes a struct tlm_reg_struct, without timestamp. If you need the
 * timestamps, you should register only variables from the same section and use
 * tlm_consumer_get_sample_with_timestamp
 *
 * @param consumer: consumer object.
 * @param ptr: pointer to the base of the structure. Its scope should be valid
 * until the consumer is destroyed because 'tlm_get_sample' will implicitly
 * dereference it.
 * @param name: optional name to prefix to all fields. Useful when registering
 * multiple descriptions. The same behaviour can be achieved by creating a top
 * level structure description and calling this function just once.
 * @param desc: description of the structure.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_consumer_reg_struct_ptr(struct tlm_consumer *consumer,
		const void *ptr,
		const char *name,
		const struct tlm_reg_struct *desc);

/**
 * Complete the registration of variables.
 * @param consumer: consumer object.
 * @return 0 in case of success, negative errno value in case of error.
 */
int tlm_consumer_reg_complete(struct tlm_consumer *consumer);

/**
 * Get a sample.
 * @param consumer: consumer object.
 * @param timestamp: timestamp of query (can be NULL for LATEST method).
 * @param method: method of query.
 * @return 0 if at least one sample has been read in one of the shared memory
 * where variables are, negative errno value in case of error.
 *
 * @remarks -ENOENT is returned if no samples where retrieved.
 *
 */
int tlm_consumer_get_sample(struct tlm_consumer *consumer,
		const struct timespec *timestamp,
		enum tlm_method method);

/**
 * Get a sample and its associated timestamp.
 * @param consumer: consumer object.
 * @param timestamp: timestamp of query (can be NULL for LATEST method).
 * @param method: method of query.
 * @param out_timestamp: timestamp of the returned sample
 * @return 0 if at least one sample has been read in one of the shared memory
 * where variables are, negative errno value in case of error.
 *
 * @remarks -ENOENT is returned if no samples where retrieved.
 * @remarks: this will only work if all variables are part of the same
 * section.
 */
int tlm_consumer_get_sample_with_timestamp(struct tlm_consumer *consumer,
		const struct timespec *timestamp,
		enum tlm_method method,
		struct timespec *out_timestamp);

/**
 * Get sample before the given timestamp.
 * @param consumer: consumer object.
 * @param timestamp: timestamp read from a previous call.
 * @return 0 if a sample was found.
 *
 * @remarks -ENOENT is returned if no samples where retrieved.
 * @remarks: this will only work if all variables are part of the same
 * section.
 */
int tlm_consumer_get_prev_sample(struct tlm_consumer *consumer,
		const struct timespec *timestamp);

/**
 * Get sample after the given timestamp.
 * @param consumer: consumer object.
 * @param timestamp: timestamp read from a previous call.
 * @param timeout: max time to wait for the sample (in ms), 0 for no wait.
 * @return 0 if a sample was found.
 *
 * @remarks -ENOENT is returned if no samples where retrieved.
 * @remarks: this will only work if all variables are part of the same
 * section.
 */
int tlm_consumer_get_next_sample(struct tlm_consumer *consumer,
		const struct timespec *timestamp,
		uint32_t timeout);

/**
 * Get sample after the given timestamp.
 * @param consumer: consumer object.
 * @param timestamp: timestamp read from a previous call.
 * @param timeout: max time to wait for the sample (in ms), 0 for no wait.
 * @param out_timestamp: timestamp of the returned sample
 * @return 0 if a sample was found.
 * @remarks -ENOENT is returned if no samples where retrieved.
 * @remarks: this will only work if all variables are part of the same
 * section.
 */
int tlm_consumer_get_next_sample_with_timestamp(struct tlm_consumer *consumer,
		const struct timespec *timestamp,
		uint32_t timeout,
		struct timespec *out_timestamp);

/**
 * Get the samples with the number of returned samples by specifying the
 * desired number of samples before and after the reference timestamp.
 * @param consumer: consumer object.
 * @param timestamp: timestamp of query (can be NULL for LATEST method).
 * @param method: method of query.
 * @param nb_samples_before: number of requested samples before the timestamp.
 * @param nb_samples_after: number of requested samples after the timestamp.
 * Note: nb_samples_before + nb_samples_after +1 <= nb_samples.
 * @param nb_out_samples: number of actual returned samples.
 * @param ref_idx: index of the reference sample in the table.
 * It is related to the reference timestamp and depends on the method.
 * @return 0 if at least one sample has been read in one of the shared memory
 * where variables are, negative errno value in case of error.
 *
 * @remarks -ENOENT is returned if no samples where retrieved.
 *
 */
int tlm_consumer_get_samples(struct tlm_consumer *consumer,
			     const struct timespec *timestamp,
			     enum tlm_method method,
			     size_t nb_samples_before,
			     size_t nb_samples_after,
			     size_t *nb_out_samples,
			     size_t *ref_idx);

/**
 * Check the validity of the timestamp.
 * @param timestamp: timestamp.
 * @return 0 if the timestamp is not valid.
 */
int tlm_consumer_timestamp_is_valid(struct timespec *timestamp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_LIBTELEMETRY_H_ */
