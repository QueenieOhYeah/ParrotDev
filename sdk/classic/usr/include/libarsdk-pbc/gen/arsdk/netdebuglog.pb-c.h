/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: arsdk/netdebuglog.proto */

#ifndef PROTOBUF_C_arsdk_2fnetdebuglog_2eproto__INCLUDED
#define PROTOBUF_C_arsdk_2fnetdebuglog_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "parrot/protobuf/extensions.pb-c.h"

typedef struct _Arsdk__Netdebuglog__Event Arsdk__Netdebuglog__Event;
typedef struct _Arsdk__Netdebuglog__Event__Log Arsdk__Netdebuglog__Event__Log;


/* --- enums --- */


/* --- messages --- */

/*
 * Log message. 
 */
struct  _Arsdk__Netdebuglog__Event__Log
{
  ProtobufCMessage base;
  /*
   * Serial number of sender. 
   */
  char *serial;
  /*
   * Log message. 
   */
  char *msg;
};
#define ARSDK__NETDEBUGLOG__EVENT__LOG__SERIAL__FIELD_NUMBER 1
#define ARSDK__NETDEBUGLOG__EVENT__LOG__MSG__FIELD_NUMBER 2
#define ARSDK__NETDEBUGLOG__EVENT__LOG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__netdebuglog__event__log__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


typedef enum {
  ARSDK__NETDEBUGLOG__EVENT__ID__NOT_SET = 0,
  ARSDK__NETDEBUGLOG__EVENT__ID_LOG = 17
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__NETDEBUGLOG__EVENT__ID)
} Arsdk__Netdebuglog__Event__IdCase;

/*
 * This is the entry point to receive messages from the drone. 
 */
struct  _Arsdk__Netdebuglog__Event
{
  ProtobufCMessage base;
  Arsdk__Netdebuglog__Event__IdCase id_case;
  union {
    Arsdk__Netdebuglog__Event__Log *log;
  };
};
#define ARSDK__NETDEBUGLOG__EVENT__LOG__FIELD_NUMBER 17
#define ARSDK__NETDEBUGLOG__EVENT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__netdebuglog__event__descriptor) \
    , ARSDK__NETDEBUGLOG__EVENT__ID__NOT_SET, {0} }


/* Arsdk__Netdebuglog__Event__Log methods */
void   arsdk__netdebuglog__event__log__init
                     (Arsdk__Netdebuglog__Event__Log         *message);
/* Arsdk__Netdebuglog__Event methods */
void   arsdk__netdebuglog__event__init
                     (Arsdk__Netdebuglog__Event         *message);
size_t arsdk__netdebuglog__event__get_packed_size
                     (const Arsdk__Netdebuglog__Event   *message);
size_t arsdk__netdebuglog__event__pack
                     (const Arsdk__Netdebuglog__Event   *message,
                      uint8_t             *out);
size_t arsdk__netdebuglog__event__pack_to_buffer
                     (const Arsdk__Netdebuglog__Event   *message,
                      ProtobufCBuffer     *buffer);
Arsdk__Netdebuglog__Event *
       arsdk__netdebuglog__event__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   arsdk__netdebuglog__event__free_unpacked
                     (Arsdk__Netdebuglog__Event *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Arsdk__Netdebuglog__Event__Log_Closure)
                 (const Arsdk__Netdebuglog__Event__Log *message,
                  void *closure_data);
typedef void (*Arsdk__Netdebuglog__Event_Closure)
                 (const Arsdk__Netdebuglog__Event *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor arsdk__netdebuglog__event__descriptor;
extern const ProtobufCMessageDescriptor arsdk__netdebuglog__event__log__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_arsdk_2fnetdebuglog_2eproto__INCLUDED */
