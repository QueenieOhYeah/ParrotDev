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

#ifndef MSGHUB_PARSER_H
#define MSGHUB_PARSER_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "msghub_exports.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct msghub_parser;

/**
 * Description of a parsed json message.
 */
struct msghub_parser_json {
	/** Service id */
	uint16_t service_id;
	/** Message number */
	uint16_t msg_num;
	/** Service name */
	char *service_name;
	/** Message name */
	char *msg_name;
	/** Data as a json string */
	char *data;
};

/**
 * Description of a parsed binary message.
 */
struct msghub_parser_binary {
	/** Service id */
	uint16_t service_id;
	/** Message number */
	uint16_t msg_num;
	/** Service name */
	char *service_name;
	/** Message name */
	char *msg_name;
	/** Binary tata buffer */
	void *data;
	/** Data buffer size */
	size_t datalen;
};

/**
 * Description of a message hub service found in a protobuf file.
 */
struct msghub_parser_service {
	/** Service id */
	uint16_t id;
	/** Service name */
	const char *name;
	/** Protobuf file in which the service was found */
	const char *filename;
};

struct msghub_parser_message {
	/** Service id */
	uint16_t service_id;
	/** Message number */
	uint16_t msg_num;
	/** Service name */
	const char *service_name;
	/** Message name */
	const char *msg_name;
};

/**
 * Prototype of callback for msghub_parser_walk_services.
 * @param service service enumerated.
 * @param userdata user data associated with the listing.
 * @return 1 to continue the enumeration, 0 to stop it.
 */
typedef int (*msghub_parser_walk_services_cb_t)(
	const struct msghub_parser_service *service,
	void *userdata);

/**
 * Prototype of callback for msghub_parser_walk_messages.
 * @param message message enumerated.
 * @param userdata user data associated with the listing.
 * @return 1 to continue the enumeration, 0 to stop it.
 */
typedef int (*msghub_parser_walk_messages_cb_t)(
	const struct msghub_parser_message *message,
	void *userdata);

/**
 * Create a new parser object.
 * @param ret_obj pointer to return parser object.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_new(struct msghub_parser **ret_obj);

/**
 * Destroy a parser object.
 * @param parser parser object.
 */
MSGHUB_API
void msghub_parser_destroy(struct msghub_parser *parser);

/**
 * Add a directory in the search path for protobuf files.
 * @param parser parser object.
 * @param dirpath directory path to add.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_add_proto_dir(struct msghub_parser *parser,
	const char *dirpath);

/**
 * Add a mapping between a real protobuf file in the file system and the
 * location in the search path it should have.
 * @param parser parser object.
 * @param virtfilepath virtual location in the search tree.
 * @param filepath real location in the fils system.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_add_file_mapping(struct msghub_parser *parser,
	const char *virtfilepath,
	const char *filepath);

/**
 * Load a protobuf file.
 * @param parser parser object.
 * @param filepath file path.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_load_proto_file(struct msghub_parser *parser,
	const char *filepath);

/**
 * Load protobuf files from a directory.
 * @param parser parser object.
 * @param dirpath directory path.
 * @param recursive indicate if load should be recursive.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_load_proto_files(struct msghub_parser *parser,
	const char *dirpath,
	int recursive);

/**
 * List message hub services found in loaded protobuf files.
 * @param parser parser object.
 * @param sort indicate if list should be sorted.
 * @param cb function to call for each found service.
 * @param userdata user data to give to the callback.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_walk_services(struct msghub_parser *parser,
	int sort,
	msghub_parser_walk_services_cb_t cb,
	void *userdata);

/**
 * List message found in a service.
 * @param parser parser object.
 * @param service_id service to query.
 * @param cb function to call for each found message.
 * @param userdata user data to give to the callback.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_walk_messages(struct msghub_parser *parser,
	uint16_t service_id,
	msghub_parser_walk_messages_cb_t cb,
	void *userdata);

/**
 * Convert a binary form of the protobuf message to a json form.
 * @param parser parser object.
 * @param msgid message id of the message.
 * @param data binary data buffer.
 * @param datalen size of data buffer.
 * @param json structure to fill with result.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_binary_to_json(struct msghub_parser *parser,
	uint32_t msgid,
	const void *data,
	size_t datalen,
	struct msghub_parser_json *json);

/**
 * Initialize a json parser structure.
 * @param json json parser structure
 */
MSGHUB_API
void msghub_parser_json_init(struct msghub_parser_json *json);

/**
 * Clear a json parser structure (and free memory).
 * @param json json parser structure
 */
MSGHUB_API
void msghub_parser_json_clear(struct msghub_parser_json *json);

/**
 * Convert a json form of the protobuf message to a binary form.
 * @param parser parser object.
 * @param msgid message id of the message.
 * @param data data as json string.
 * @param binary structure to fill with result.
 * @return 0 in case of success, negative errno in case of error.
 */
MSGHUB_API
int msghub_parser_json_to_binary(struct msghub_parser *parser,
	const char *service_name,
	const char *data,
	struct msghub_parser_binary *binary);

/**
 * Initialize a binary parser structure.
 * @param binary binary parser structure
 */
MSGHUB_API
void msghub_parser_binary_init(struct msghub_parser_binary *binary);

/**
 * Clear a binary parser structure (and free memory).
 * @param binary binary parser structure
 */
MSGHUB_API
void msghub_parser_binary_clear(struct msghub_parser_binary *binary);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !MSGHUB_PARSER_H */
