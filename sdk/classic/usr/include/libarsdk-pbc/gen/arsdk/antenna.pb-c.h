/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: arsdk/antenna.proto */

#ifndef PROTOBUF_C_arsdk_2fantenna_2eproto__INCLUDED
#define PROTOBUF_C_arsdk_2fantenna_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "parrot/protobuf/extensions.pb-c.h"

typedef struct _Arsdk__Antenna__Command Arsdk__Antenna__Command;
typedef struct _Arsdk__Antenna__Command__GetState Arsdk__Antenna__Command__GetState;
typedef struct _Arsdk__Antenna__Command__SetAntennaType Arsdk__Antenna__Command__SetAntennaType;
typedef struct _Arsdk__Antenna__Event Arsdk__Antenna__Event;
typedef struct _Arsdk__Antenna__Event__State Arsdk__Antenna__Event__State;
typedef struct _Arsdk__Antenna__Capabilities Arsdk__Antenna__Capabilities;


/* --- enums --- */

typedef enum _Arsdk__Antenna__AntennaType {
  ARSDK__ANTENNA__ANTENNA_TYPE__ANTENNA_TYPE_INTERNAL = 0,
  ARSDK__ANTENNA__ANTENNA_TYPE__ANTENNA_TYPE_EXTERNAL = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__ANTENNA__ANTENNA_TYPE)
} Arsdk__Antenna__AntennaType;

/* --- messages --- */

struct  _Arsdk__Antenna__Command__GetState
{
  ProtobufCMessage base;
  protobuf_c_boolean include_default_capabilities;
};
#define ARSDK__ANTENNA__COMMAND__GET_STATE__INCLUDE_DEFAULT_CAPABILITIES__FIELD_NUMBER 1
#define ARSDK__ANTENNA__COMMAND__GET_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__antenna__command__get_state__descriptor) \
    , 0 }


struct  _Arsdk__Antenna__Command__SetAntennaType
{
  ProtobufCMessage base;
  Arsdk__Antenna__AntennaType type;
};
#define ARSDK__ANTENNA__COMMAND__SET_ANTENNA_TYPE__TYPE__FIELD_NUMBER 1
#define ARSDK__ANTENNA__COMMAND__SET_ANTENNA_TYPE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__antenna__command__set_antenna_type__descriptor) \
    , ARSDK__ANTENNA__ANTENNA_TYPE__ANTENNA_TYPE_INTERNAL }


typedef enum {
  ARSDK__ANTENNA__COMMAND__ID__NOT_SET = 0,
  ARSDK__ANTENNA__COMMAND__ID_GET_STATE = 16,
  ARSDK__ANTENNA__COMMAND__ID_SET_ANTENNA_TYPE = 17
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__ANTENNA__COMMAND__ID)
} Arsdk__Antenna__Command__IdCase;

/*
 * This is the entry point to send messages to SkyController
 */
struct  _Arsdk__Antenna__Command
{
  ProtobufCMessage base;
  Arsdk__Antenna__Command__IdCase id_case;
  union {
    Arsdk__Antenna__Command__GetState *get_state;
    Arsdk__Antenna__Command__SetAntennaType *set_antenna_type;
  };
};
#define ARSDK__ANTENNA__COMMAND__GET_STATE__FIELD_NUMBER 16
#define ARSDK__ANTENNA__COMMAND__SET_ANTENNA_TYPE__FIELD_NUMBER 17
#define ARSDK__ANTENNA__COMMAND__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__antenna__command__descriptor) \
    , ARSDK__ANTENNA__COMMAND__ID__NOT_SET, {0} }


typedef enum {
  ARSDK__ANTENNA__EVENT__STATE__OPTIONAL_ANTENNA_TYPE__NOT_SET = 0,
  ARSDK__ANTENNA__EVENT__STATE__OPTIONAL_ANTENNA_TYPE_ANTENNA_TYPE = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__ANTENNA__EVENT__STATE__OPTIONAL_ANTENNA_TYPE)
} Arsdk__Antenna__Event__State__OptionalAntennaTypeCase;

struct  _Arsdk__Antenna__Event__State
{
  ProtobufCMessage base;
  Arsdk__Antenna__Capabilities *default_capabilities;
  Arsdk__Antenna__Event__State__OptionalAntennaTypeCase optional_antenna_type_case;
  union {
    Arsdk__Antenna__AntennaType antenna_type;
  };
};
#define ARSDK__ANTENNA__EVENT__STATE__DEFAULT_CAPABILITIES__FIELD_NUMBER 1
#define ARSDK__ANTENNA__EVENT__STATE__ANTENNA_TYPE__FIELD_NUMBER 2
#define ARSDK__ANTENNA__EVENT__STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__antenna__event__state__descriptor) \
    , NULL, ARSDK__ANTENNA__EVENT__STATE__OPTIONAL_ANTENNA_TYPE__NOT_SET, {0} }


typedef enum {
  ARSDK__ANTENNA__EVENT__ID__NOT_SET = 0,
  ARSDK__ANTENNA__EVENT__ID_STATE = 16
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__ANTENNA__EVENT__ID)
} Arsdk__Antenna__Event__IdCase;

/*
 * This is the entry point to receive messages from SkyController
 */
struct  _Arsdk__Antenna__Event
{
  ProtobufCMessage base;
  Arsdk__Antenna__Event__IdCase id_case;
  union {
    Arsdk__Antenna__Event__State *state;
  };
};
#define ARSDK__ANTENNA__EVENT__STATE__FIELD_NUMBER 16
#define ARSDK__ANTENNA__EVENT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__antenna__event__descriptor) \
    , ARSDK__ANTENNA__EVENT__ID__NOT_SET, {0} }


struct  _Arsdk__Antenna__Capabilities
{
  ProtobufCMessage base;
  size_t n_supported_antenna_types;
  Arsdk__Antenna__AntennaType *supported_antenna_types;
};
#define ARSDK__ANTENNA__CAPABILITIES__SUPPORTED_ANTENNA_TYPES__FIELD_NUMBER 1
#define ARSDK__ANTENNA__CAPABILITIES__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__antenna__capabilities__descriptor) \
    , 0,NULL }


/* Arsdk__Antenna__Command__GetState methods */
void   arsdk__antenna__command__get_state__init
                     (Arsdk__Antenna__Command__GetState         *message);
/* Arsdk__Antenna__Command__SetAntennaType methods */
void   arsdk__antenna__command__set_antenna_type__init
                     (Arsdk__Antenna__Command__SetAntennaType         *message);
/* Arsdk__Antenna__Command methods */
void   arsdk__antenna__command__init
                     (Arsdk__Antenna__Command         *message);
size_t arsdk__antenna__command__get_packed_size
                     (const Arsdk__Antenna__Command   *message);
size_t arsdk__antenna__command__pack
                     (const Arsdk__Antenna__Command   *message,
                      uint8_t             *out);
size_t arsdk__antenna__command__pack_to_buffer
                     (const Arsdk__Antenna__Command   *message,
                      ProtobufCBuffer     *buffer);
Arsdk__Antenna__Command *
       arsdk__antenna__command__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   arsdk__antenna__command__free_unpacked
                     (Arsdk__Antenna__Command *message,
                      ProtobufCAllocator *allocator);
/* Arsdk__Antenna__Event__State methods */
void   arsdk__antenna__event__state__init
                     (Arsdk__Antenna__Event__State         *message);
/* Arsdk__Antenna__Event methods */
void   arsdk__antenna__event__init
                     (Arsdk__Antenna__Event         *message);
size_t arsdk__antenna__event__get_packed_size
                     (const Arsdk__Antenna__Event   *message);
size_t arsdk__antenna__event__pack
                     (const Arsdk__Antenna__Event   *message,
                      uint8_t             *out);
size_t arsdk__antenna__event__pack_to_buffer
                     (const Arsdk__Antenna__Event   *message,
                      ProtobufCBuffer     *buffer);
Arsdk__Antenna__Event *
       arsdk__antenna__event__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   arsdk__antenna__event__free_unpacked
                     (Arsdk__Antenna__Event *message,
                      ProtobufCAllocator *allocator);
/* Arsdk__Antenna__Capabilities methods */
void   arsdk__antenna__capabilities__init
                     (Arsdk__Antenna__Capabilities         *message);
size_t arsdk__antenna__capabilities__get_packed_size
                     (const Arsdk__Antenna__Capabilities   *message);
size_t arsdk__antenna__capabilities__pack
                     (const Arsdk__Antenna__Capabilities   *message,
                      uint8_t             *out);
size_t arsdk__antenna__capabilities__pack_to_buffer
                     (const Arsdk__Antenna__Capabilities   *message,
                      ProtobufCBuffer     *buffer);
Arsdk__Antenna__Capabilities *
       arsdk__antenna__capabilities__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   arsdk__antenna__capabilities__free_unpacked
                     (Arsdk__Antenna__Capabilities *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Arsdk__Antenna__Command__GetState_Closure)
                 (const Arsdk__Antenna__Command__GetState *message,
                  void *closure_data);
typedef void (*Arsdk__Antenna__Command__SetAntennaType_Closure)
                 (const Arsdk__Antenna__Command__SetAntennaType *message,
                  void *closure_data);
typedef void (*Arsdk__Antenna__Command_Closure)
                 (const Arsdk__Antenna__Command *message,
                  void *closure_data);
typedef void (*Arsdk__Antenna__Event__State_Closure)
                 (const Arsdk__Antenna__Event__State *message,
                  void *closure_data);
typedef void (*Arsdk__Antenna__Event_Closure)
                 (const Arsdk__Antenna__Event *message,
                  void *closure_data);
typedef void (*Arsdk__Antenna__Capabilities_Closure)
                 (const Arsdk__Antenna__Capabilities *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    arsdk__antenna__antenna_type__descriptor;
extern const ProtobufCMessageDescriptor arsdk__antenna__command__descriptor;
extern const ProtobufCMessageDescriptor arsdk__antenna__command__get_state__descriptor;
extern const ProtobufCMessageDescriptor arsdk__antenna__command__set_antenna_type__descriptor;
extern const ProtobufCMessageDescriptor arsdk__antenna__event__descriptor;
extern const ProtobufCMessageDescriptor arsdk__antenna__event__state__descriptor;
extern const ProtobufCMessageDescriptor arsdk__antenna__capabilities__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_arsdk_2fantenna_2eproto__INCLUDED */
