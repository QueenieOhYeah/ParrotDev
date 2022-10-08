/**
 * /etc/passwd fast access library.
 *
 * This small library builds a cache of all /etc/passwd entries.
 * This is useful for processes like boxinit which:
 * - assumes the contents of /etc/passwd will not change
 * - needs to massively translate symbolic user names into uids
 *  (250 conversions for a standard init.rc file)
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 * Copyright (C) 2013 Parrot S.A.
 */
#ifndef _PUTILS_PWCACHE_H_
#define _PUTILS_PWCACHE_H_

void *pwcache_init(const char *passwd_file);
void pwcache_destroy(void *handle);
unsigned int pwcache_lookup(void *handle, const char *name);

#endif /* _PUTILS_PWCACHE_H_ */
