/*
 * Copyright (c) 2020 Parrot Drones SAS
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
 * @file vipc_client_cfg.h
 * @copyright Copyright (c) 2020 Parrot Drones SAS
 */

#ifndef _VIPC_CLIENT_CFG_H_
#define _VIPC_CLIENT_CFG_H_

#include <video-ipc/vipc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Client configuration information
 */
struct vipcc_cfg_info {
	/** Remote address to connect to (in pomp_addr_parse format) */
	char *address;
	/** Backend name */
	char *backend;
	/** Callbacks for the backend */
	const struct vipc_be_cb *be_cbs;
};

/**
 * Get client configuration information based on stream name
 *
 * @param[in] stream the stream name
 * @param[out] info the information about the stream
 * @return 0 in case of success, -errno for failure
 */
VIPC_API
int vipcc_cfg_get_info(const char *stream, struct vipcc_cfg_info *info);

/**
 * Release client configuration information
 *
 * @param[in] info the information about the stream
 */
VIPC_API
void vipcc_cfg_release_info(struct vipcc_cfg_info *info);

/**
 * Reverse lookup of a stream name from the IPC address
 * Note: the ownership of the returned string is transferred to the caller and
 * it should be freed once no longer needed.
 *
 * @param[in] address the stream address
 * @return the stream name in case of success, NULL in case of failure
 */
VIPC_API
char *vipcc_cfg_reverse_lookup(const char *address);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* !_VIPC_CLIENT_CFG_H_*/
