/**
 * Android-like properties
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 * Copyright (C) 2013 Parrot S.A.
 */

#ifndef __PUTILS_PROPERTIES_INTERNAL_H
#define __PUTILS_PROPERTIES_INTERNAL_H

/* This file is intended for inclusion by the init process */

#include <putils/properties.h>

#define PROP_ENV_VAR             "SYS_PROP_FD"
#define PROP_DEVICE              "/dev/__sys_properties__"

/* it looks like we try to have PROP_AREA_SIZE rounded
 * on a page size.
 * The nb of prop is (PROP_AREA_SIZE-8*4)/(4+128) - 1
 * I don't know why the initial code add - 1 ?
 */
/* (8 header words + 495 toc words) = 1992 bytes */
/* 2048 bytes header and toc + 495 prop_infos @ 128 bytes = 65408 bytes */
#define PROP_COUNT_MAX		 495
#define PROP_INFO_START		 2048
#define PROP_AREA_SIZE		 65536
#define PROP_AREA_MAGIC		 0x504f5250   /* PROP */
#define PROP_AREA_VERSION	 0x52415076   /* vPAR */
#define PROP_SERVICE_NAME        "sys_property_service"
#define PROP_SOCKET_FILE         "/dev/socket/"PROP_SERVICE_NAME
#define PROP_MSG_SETPROP         1
#define PROP_MSG_CMPXCHG	 2
#define PROP_STATUS_OK		"OK"
#define PROP_STATUS_KO		"KO"
#define PROP_STATUS_SIZE	2

#define SERIAL_VALUE_LEN(serial) ((serial) >> 24)
#define SERIAL_DIRTY(serial)	 ((serial) & 1)
#define TOC_KEY_LEN(toc)	 ((toc) >> 24)
#define TOC_TO_INFO(area, toc) \
	((struct property_info *) (((char *) area) + ((toc) & 0xFFFFFF)))

/* This message is sent by propertyd to clients to ensure properties are
 * initialized
 */
#define SYNC_MSG		"syncw0rd"

struct property_area {
	/* codecheck_ignore[VOLATILE] */
	unsigned int volatile count;
	/* codecheck_ignore[VOLATILE] */
	unsigned int volatile serial;
	unsigned int          magic;
	unsigned int          version;
	unsigned int          reserved[4];
	unsigned int          toc[1];
};

struct property_info {
	char                  key[SYS_PROP_KEY_MAX];
	/* codecheck_ignore[VOLATILE] */
	unsigned int volatile serial;
	char                  value[SYS_PROP_VALUE_MAX];
};

struct property_msg {
	unsigned              cmd;
	char                  key[SYS_PROP_KEY_MAX];
	char                  value[SYS_PROP_VALUE_MAX];
	char                  old_value[SYS_PROP_VALUE_MAX];
};

#endif
