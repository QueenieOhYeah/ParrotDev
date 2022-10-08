/*
 * Copyright (C) 2007 The Android Open Source Project
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

#ifndef __PUTILS_IOSCHED_POLICY_H
#define __PUTILS_IOSCHED_POLICY_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * These are the io priority groups as implemented by CFQ. RT is the realtime
 * class, it always gets premium service. BE is the best-effort scheduling
 * class, the default for any process. IDLE is the idle scheduling class, it
 * is only served when no one else is using the disk.
 */
enum {
	PUTILS_IOPRIO_CLASS_NONE,
	PUTILS_IOPRIO_CLASS_RT,
	PUTILS_IOPRIO_CLASS_BE,
	PUTILS_IOPRIO_CLASS_IDLE,
};

int set_ioprio(int pid, int clazz, int ioprio);
int get_ioprio(int pid, int *clazz, int *ioprio);

#ifdef __cplusplus
}
#endif

#endif /* __PUTILS_IOSCHED_POLICY_H */
