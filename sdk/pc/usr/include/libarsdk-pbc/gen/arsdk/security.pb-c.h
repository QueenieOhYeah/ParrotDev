/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: arsdk/security.proto */

#ifndef PROTOBUF_C_arsdk_2fsecurity_2eproto__INCLUDED
#define PROTOBUF_C_arsdk_2fsecurity_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "parrot/protobuf/extensions.pb-c.h"

typedef struct _Arsdk__Security__Command Arsdk__Security__Command;
typedef struct _Arsdk__Security__Command__RegisterApcToken Arsdk__Security__Command__RegisterApcToken;
typedef struct _Arsdk__Security__Command__RegisterApcDroneList Arsdk__Security__Command__RegisterApcDroneList;


/* --- enums --- */


/* --- messages --- */

struct  _Arsdk__Security__Command__RegisterApcToken
{
  ProtobufCMessage base;
  char *token;
};
#define ARSDK__SECURITY__COMMAND__REGISTER_APC_TOKEN__TOKEN__FIELD_NUMBER 1
#define ARSDK__SECURITY__COMMAND__REGISTER_APC_TOKEN__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__security__command__register_apc_token__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  _Arsdk__Security__Command__RegisterApcDroneList
{
  ProtobufCMessage base;
  char *list;
};
#define ARSDK__SECURITY__COMMAND__REGISTER_APC_DRONE_LIST__LIST__FIELD_NUMBER 1
#define ARSDK__SECURITY__COMMAND__REGISTER_APC_DRONE_LIST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__security__command__register_apc_drone_list__descriptor) \
    , (char *)protobuf_c_empty_string }


typedef enum {
  ARSDK__SECURITY__COMMAND__ID__NOT_SET = 0,
  ARSDK__SECURITY__COMMAND__ID_REGISTER_APC_TOKEN = 16,
  ARSDK__SECURITY__COMMAND__ID_REGISTER_APC_DRONE_LIST = 17
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__SECURITY__COMMAND__ID)
} Arsdk__Security__Command__IdCase;

/*
 * This is the entry point to send messages to the device
 */
struct  _Arsdk__Security__Command
{
  ProtobufCMessage base;
  Arsdk__Security__Command__IdCase id_case;
  union {
    Arsdk__Security__Command__RegisterApcToken *register_apc_token;
    Arsdk__Security__Command__RegisterApcDroneList *register_apc_drone_list;
  };
};
#define ARSDK__SECURITY__COMMAND__REGISTER_APC_TOKEN__FIELD_NUMBER 16
#define ARSDK__SECURITY__COMMAND__REGISTER_APC_DRONE_LIST__FIELD_NUMBER 17
#define ARSDK__SECURITY__COMMAND__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__security__command__descriptor) \
    , ARSDK__SECURITY__COMMAND__ID__NOT_SET, {0} }


/* Arsdk__Security__Command__RegisterApcToken methods */
void   arsdk__security__command__register_apc_token__init
                     (Arsdk__Security__Command__RegisterApcToken         *message);
/* Arsdk__Security__Command__RegisterApcDroneList methods */
void   arsdk__security__command__register_apc_drone_list__init
                     (Arsdk__Security__Command__RegisterApcDroneList         *message);
/* Arsdk__Security__Command methods */
void   arsdk__security__command__init
                     (Arsdk__Security__Command         *message);
size_t arsdk__security__command__get_packed_size
                     (const Arsdk__Security__Command   *message);
size_t arsdk__security__command__pack
                     (const Arsdk__Security__Command   *message,
                      uint8_t             *out);
size_t arsdk__security__command__pack_to_buffer
                     (const Arsdk__Security__Command   *message,
                      ProtobufCBuffer     *buffer);
Arsdk__Security__Command *
       arsdk__security__command__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   arsdk__security__command__free_unpacked
                     (Arsdk__Security__Command *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Arsdk__Security__Command__RegisterApcToken_Closure)
                 (const Arsdk__Security__Command__RegisterApcToken *message,
                  void *closure_data);
typedef void (*Arsdk__Security__Command__RegisterApcDroneList_Closure)
                 (const Arsdk__Security__Command__RegisterApcDroneList *message,
                  void *closure_data);
typedef void (*Arsdk__Security__Command_Closure)
                 (const Arsdk__Security__Command *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor arsdk__security__command__descriptor;
extern const ProtobufCMessageDescriptor arsdk__security__command__register_apc_token__descriptor;
extern const ProtobufCMessageDescriptor arsdk__security__command__register_apc_drone_list__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_arsdk_2fsecurity_2eproto__INCLUDED */
