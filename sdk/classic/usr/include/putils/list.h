/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef _PUTILS_LIST_H_
#define _PUTILS_LIST_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct listnode {
	struct listnode *next;
	struct listnode *prev;
};

#define node_to_item(node, container, member) \
	((container *) (((char *) (node)) - offsetof(container, member)))

#define list_declare(name)			\
	struct listnode name = {		\
		.next = &name,			\
		.prev = &name,			\
	}

#define list_for_each(node, list)					\
	for (node = (list)->next; node != (list); node = node->next)

#define list_for_each_safe(node, list, tmpnode)		\
	for (node = (list)->next,			\
		tmpnode = node->next; node != (list);	\
		node = tmpnode, tmpnode = node->next)

#define list_for_each_reverse(node, list)				\
	for (node = (list)->prev; node != (list); node = node->prev)

void putils_list_init(struct listnode *list);
void putils_list_add_tail(struct listnode *list, struct listnode *item);
void putils_list_remove(struct listnode *item);

/* Define aliases for functions for compatibility with the previous API:
 * we need symbol names to be prefixed only, not the actual definition
 * in the header */

#define list_init(list) putils_list_init(list)
#define list_add_tail(list, item) putils_list_add_tail(list, item)
#define list_remove(item) putils_list_remove(item)

#define list_empty(list) ((list) == (list)->next)
#define list_head(list) ((list)->next)
#define list_tail(list) ((list)->prev)

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif
