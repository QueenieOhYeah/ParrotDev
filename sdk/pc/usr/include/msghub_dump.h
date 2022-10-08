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

#ifndef MSGHUB_DUMP_H
#define MSGHUB_DUMP_H

#include <stdlib.h>
#include <stdint.h>

#include "msghub_exports.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct msghub_dump {
	int fd;
	char label[32];
	size_t label_size;
};

MSGHUB_API
void msghub_dump_init(struct msghub_dump *dump);

MSGHUB_API
int msghub_dump_open(struct msghub_dump *dump);

MSGHUB_API
int msghub_dump_close(struct msghub_dump *dump);

MSGHUB_API
int msghub_dump_log_tx(struct msghub_dump *dump,
	uint32_t msgid,
	const void *buf,
	size_t len);

MSGHUB_API
int msghub_dump_log_rx(struct msghub_dump *dump,
	uint32_t msgid,
	const void *buf,
	size_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !MSGHUB_DUMP_H */
