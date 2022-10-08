/**
 * A simple implementation of a small (~100 items) string-indexed hash table.
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 * Copyright (C) 2013 Parrot S.A.
 */
#ifndef _PUTILS_MINIHASH_H_
#define _PUTILS_MINIHASH_H_

/*
 * NOTE: implementation is not thread-safe; single item removal not
 * implemented
 */

struct minihash;

struct minihash **mh_init(void);
void mh_destroy(struct minihash **ht, void (*pfn)(const char *key, void *data));
void *mh_lookup(struct minihash **ht, const char *key);
int mh_insert(struct minihash **ht, const char *key, void *data);
int mh_insert_nocheck(struct minihash **ht, const char *key, void *data);

#endif /* _PUTILS_MINIHASH_H_ */
