/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PUTILS_PROPERTIES_H
#define __PUTILS_PROPERTIES_H

#ifdef __cplusplus
extern "C" {
#endif

/* System properties are *small* name value pairs managed by the
** property service.  If your data doesn't fit in the provided
** space it is not appropriate for a system property.
*/
#define SYS_PROP_KEY_MAX    32
#define SYS_PROP_VALUE_MAX  92

/* sys_prop_is_available: returns 1 if system properties are available
 * on this system, or 0 otherwise. */
int sys_prop_is_available(void);

/* sys_prop_get: returns the length of the value which will never be
** greater than SYS_PROP_VALUE_MAX - 1 and will always be zero terminated.
** (the length does not include the terminating zero).
**
** If the property read fails or returns an empty value, the default
** value is used (if nonnull).
*/
int sys_prop_get(const char *key, char *value, const char *default_value);

/* sys_prop_set: returns 0 on success, < 0 on failure */
int sys_prop_set(const char *key, const char *value);

/* sys_prop_update: update key only if its value is different
 * returns 1 if the key already contains the value
 * returns 0 on success, < 0 on failure
 */
int sys_prop_update(const char *key, const char *value);

/* sys_prop_cmpxchg:
 * returns 1 on compare and exchange success,
 * 0 on compare and exchange failure (current_value != oldvalue),
 * < 0 on failure
 *
 * Unlikely "sys_prop_set", sys_prop_cmpxchg is synchronous with init.
 **/
int sys_prop_cmpxchg(const char *key, const char *oldvalue,
		     const char *newvalue);

void sys_prop_list(void (*propfn)(const char *key, const char *value,
				  void *cookie), void *cookie);
/*
 * Wait until a property named 'key' is added or updated (i.e. its value is
 * different from 'oldvalue').
 *
 * If timeout_ms is > 0, do not wait for more than timeout_ms milliseconds.
 * If key is NULL, wait until any property changes.
 *
 * This function may return even if the property value has not changed.
 * It is up to the caller to check the property value, and call sys_prop_wait()
 * again if necessary.
 */
void sys_prop_wait(const char *key, const char *oldvalue, int timeout_ms);

/*
 * Wait until a property named 'key' has value 'target'.
 *
 * If timeout_ms is > 0, do not wait for more than timeout_ms milliseconds.
 * Returns -1 if timeout was reached, 0 otherwise.
 */
int sys_prop_wait_value(const char *key, const char *target, int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif
