/**
 * futex API
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 * Copyright (C) 2013 Parrot S.A.
 */
#ifndef _PUTILS_FUTEX_H_
#define _PUTILS_FUTEX_H_

#define _GNU_SOURCE
#include <unistd.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <putils/compiler.h>

/* codecheck_ignore[VOLATILE] */
static __UNUSED inline int __futex_wait(volatile void *ftx, int val,
					const struct timespec *timeout)
{
	return syscall(__NR_futex, ftx, FUTEX_WAIT, val, timeout, NULL, 0);
}

/* codecheck_ignore[VOLATILE] */
static __UNUSED inline int __futex_wake(volatile void *ftx, int count)
{
	return syscall(__NR_futex, ftx, FUTEX_WAKE, count, NULL, NULL, 0);
}

#endif /* _PUTILS_FUTEX_H_ */
