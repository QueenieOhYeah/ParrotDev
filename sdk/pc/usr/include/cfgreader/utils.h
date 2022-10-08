/**
 *  Copyright (c) 2019 Parrot Drones SAS
 */

#ifndef CFGREADER_UTILS_H
#define CFGREADER_UTILS_H

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

/**
 * @brief Return the input argument test, but log an error if it is false.
 */
static inline bool check(bool test, const char *on_error_msg)
{
	if (!test)
		ULOGE("%s", on_error_msg);
	return test;
}

/* CFG_LOOKUP_AND_CONVERT_OR_RETURN helper macro.
 * ==============================================
 *
 * A call to CFG_LOOKUP_AND_CONVERT_OR_RETURN accesses a config_t
 * field using a temporary variable of the type understood by
 * libconfig (C API), and coerces the temporary value to the type
 * associated with TARGET using a conversion function (see below). If
 * any of those steps fails, it fails with ULOGE and "return -ERANGE;"
 * statements.
 *
 * WHY
 * ---
 *
 * libconfig defines lookup functions like config_lookup_float,
 * config_lookup_int, but does not define functions for all C types;
 * for example config_lookup_float in fact reads a double; in our
 * cases, data-types includes types such as float, int8_t, uint32_t,
 * etc. Instead of silently failing to convert types or relying on
 * undefined behaviours, we explictly check the range of values before
 * assigning the target fields.
 *
 * PARAMETERS
 * ----------
 *
 * ACCESSOR: "config_lookup_X" function from libconfig
 *
 * CONFIG: variable holding a pointer to config_t
 *
 * PATH: string literal like "section.name", used both when calling
 * ACCESSOR and logging errors.
 *
 * TMP: place where intermediate data is read using ACCESSOR.
 *
 * CONVERT: name of conversion function from TMP's type to TARGET's type.
 *
 * TARGET: pointer to location where to write the resulting value.
 *
 * EXAMPLE
 * -------
 *
 *  int test(config_t *config, struct { int8_t i8; float f; } *o)
 *  {
 *      struct { int i32; double d ; } tmp;
 *
 *	CFG_LOOKUP_AND_CONVERT_OR_RETURN
 *		(config_lookup_int,
 *		 config,
 *		 "test_section.i8_field",
 *		 tmp.i32,
 *		 int_to_int8,
 *		 &o->i8);
 *
 *	CFG_LOOKUP_AND_CONVERT_OR_RETURN
 *		(config_lookup_float,
 *		 config,
 *		 "test_section.float_field",
 *		 tmp.d,
 *		 double_to_float,
 *		 &o->f);
 *
 *      return 0;
 *  }
 */
/* codecheck_ignore[COMPLEX_MACRO] */
#define CFG_LOOKUP_AND_CONVERT_OR_RETURN(ACCESSOR,			    \
					 CONFIG,			    \
					 PATH,				    \
					 TMP,				    \
					 CONVERT,			    \
					 TARGET)			    \
	if (ACCESSOR(CONFIG, PATH, &TMP)) {				    \
		if (!CONVERT(TMP, TARGET)) {				    \
			ULOGE("conversion " # CONVERT " failed for " PATH); \
			return -ERANGE;					    \
		}							    \
	} else {							    \
		ULOGE("failed to load '" PATH "' in configuration");	    \
		return -ERANGE;						    \
	}

/* Special case of the above where no conversion is necessary */
/* codecheck_ignore[COMPLEX_MACRO] */
#define CFG_LOOKUP_OR_RETURN(ACCESSOR, CONFIG, PATH, TARGET)		\
	if (!ACCESSOR(CONFIG, PATH, TARGET)) {				\
		ULOGE("failed to load " PATH " in configuration");      \
		return -ERANGE;						\
	}

static inline bool int_to_uint32(int in, uint32_t *out)
{
	/* typically the range of *out is 0..2147483647, since the
	 * input is a signed (32 bits) but the output is non-negative.
	 */

	if (0 <= in) {
		*out = (uint32_t) in;
		return true;
	}
	return false;
}

static inline bool int_to_bool(int in, bool *out)
{
	*out = (in != 0);
	return true;
}

static inline bool int_to_uint(int in, uint32_t *out)
{
	return int_to_uint32(in, out);
}

static inline bool int_to_int8(int in, int8_t *out)
{
	if (INT8_MIN <= in && in <= INT8_MAX) {
		*out = (int8_t) in;
		return true;
	}
	return false;
}

static inline bool int_to_int16(int in, int16_t *out)
{
	if (INT16_MIN <= in && in <= INT16_MAX) {
		*out = (int16_t) in;
		return true;
	}
	return false;
}

static inline bool double_to_float(double in, float *out)
{
	if (!isfinite(in))
		return false;

	if (((double)(-FLT_MAX) <= in) && (in <= (double)FLT_MAX)) {
		*out = (float) in;
		return true;
	}
	return false;
}

#endif
