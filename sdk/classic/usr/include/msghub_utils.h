/**
 * Copyright (C) 2019 Parrot Drones SAS
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in
 *  the documentation and/or other materials provided with the
 *  distribution.
 *  * Neither the name of Parrot nor the names
 *  of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written
 *  permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */

#ifndef MSGHUB_UTILS_H
#define MSGHUB_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "msghub_exports.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Get the service Id from a service name.
 * @param name service name.
 * @return service Id associated with the given service name.
 */
MSGHUB_API
uint16_t msghub_utils_get_service_id(const char *name);

/**
 * Construct a message Id from service Id and message number.
 * @param service_id service Id.
 * @param msg_num message number.
 * @return 32-bit message Id
 */
static inline uint32_t msghub_utils_construct_msg_id(uint16_t service_id,
	uint16_t msg_num)
{
	return ((uint32_t)service_id << 16) | msg_num;
}

/**
 * Extract the service Id from a message id.
 * @param msg_id 32-bit message Id.
 * @return service Id.
 */
static inline uint32_t msghub_utils_extract_service_id(uint32_t msg_id)
{
	return (uint16_t)((msg_id >> 16) & 0xffff);
}

/**
 * Extract the message number from a message id.
 * @param msg_id 32-bit message Id.
 * @return message number.
 */
static inline uint32_t msghub_utils_extract_msg_num(uint32_t msg_id)
{
	return (uint16_t)(msg_id & 0xffff);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !MSGHUB_UTILS_H */
