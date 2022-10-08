/*
 * Directory utilities.
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 * Copyright (C) 2014 Parrot S.A.
 */

#ifndef PUTILS_DIR_H
#define PUTILS_DIR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/*
 * mkdir_parents() is similar to mkdir(), except that:
 * - no error is returned if pathname already exists
 * - parent directories are created as needed
 */
int mkdir_parents(const char *pathname, mode_t mode);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PUTILS_DIR_H */
