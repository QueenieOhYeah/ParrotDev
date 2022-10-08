/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: arsdk/led.proto */

#ifndef PROTOBUF_C_arsdk_2fled_2eproto__INCLUDED
#define PROTOBUF_C_arsdk_2fled_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "google/protobuf/empty.pb-c.h"
#include "parrot/protobuf/extensions.pb-c.h"

typedef struct _Arsdk__Led__Command Arsdk__Led__Command;
typedef struct _Arsdk__Led__Command__SetLuminosity Arsdk__Led__Command__SetLuminosity;
typedef struct _Arsdk__Led__Event Arsdk__Led__Event;
typedef struct _Arsdk__Led__Event__Luminosity Arsdk__Led__Event__Luminosity;


/* --- enums --- */


/* --- messages --- */

struct  _Arsdk__Led__Command__SetLuminosity
{
  ProtobufCMessage base;
  /*
   * the value is in %
   */
  uint32_t value;
};
#define ARSDK__LED__COMMAND__SET_LUMINOSITY__VALUE__FIELD_NUMBER 1
#define ARSDK__LED__COMMAND__SET_LUMINOSITY__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__led__command__set_luminosity__descriptor) \
    , 0 }


typedef enum {
  ARSDK__LED__COMMAND__ID__NOT_SET = 0,
  ARSDK__LED__COMMAND__ID_GET_LUMINOSITY = 16,
  ARSDK__LED__COMMAND__ID_SET_LUMINOSITY = 17
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__LED__COMMAND__ID)
} Arsdk__Led__Command__IdCase;

/*
 * This is the entry point to send messages to SkyController
 * or drones in the futur
 */
struct  _Arsdk__Led__Command
{
  ProtobufCMessage base;
  Arsdk__Led__Command__IdCase id_case;
  union {
    Google__Protobuf__Empty *get_luminosity;
    Arsdk__Led__Command__SetLuminosity *set_luminosity;
  };
};
#define ARSDK__LED__COMMAND__GET_LUMINOSITY__FIELD_NUMBER 16
#define ARSDK__LED__COMMAND__SET_LUMINOSITY__FIELD_NUMBER 17
#define ARSDK__LED__COMMAND__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__led__command__descriptor) \
    , ARSDK__LED__COMMAND__ID__NOT_SET, {0} }


struct  _Arsdk__Led__Event__Luminosity
{
  ProtobufCMessage base;
  /*
   * the value is in %
   */
  uint32_t value;
};
#define ARSDK__LED__EVENT__LUMINOSITY__VALUE__FIELD_NUMBER 1
#define ARSDK__LED__EVENT__LUMINOSITY__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__led__event__luminosity__descriptor) \
    , 0 }


typedef enum {
  ARSDK__LED__EVENT__ID__NOT_SET = 0,
  ARSDK__LED__EVENT__ID_LUMINOSITY = 16
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ARSDK__LED__EVENT__ID)
} Arsdk__Led__Event__IdCase;

/*
 * This is the entry point to receive messages from SkyController
 * and could be extended to drones in the futur
 */
struct  _Arsdk__Led__Event
{
  ProtobufCMessage base;
  Arsdk__Led__Event__IdCase id_case;
  union {
    Arsdk__Led__Event__Luminosity *luminosity;
  };
};
#define ARSDK__LED__EVENT__LUMINOSITY__FIELD_NUMBER 16
#define ARSDK__LED__EVENT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&arsdk__led__event__descriptor) \
    , ARSDK__LED__EVENT__ID__NOT_SET, {0} }


/* Arsdk__Led__Command__SetLuminosity methods */
void   arsdk__led__command__set_luminosity__init
                     (Arsdk__Led__Command__SetLuminosity         *message);
/* Arsdk__Led__Command methods */
void   arsdk__led__command__init
                     (Arsdk__Led__Command         *message);
size_t arsdk__led__command__get_packed_size
                     (const Arsdk__Led__Command   *message);
size_t arsdk__led__command__pack
                     (const Arsdk__Led__Command   *message,
                      uint8_t             *out);
size_t arsdk__led__command__pack_to_buffer
                     (const Arsdk__Led__Command   *message,
                      ProtobufCBuffer     *buffer);
Arsdk__Led__Command *
       arsdk__led__command__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   arsdk__led__command__free_unpacked
                     (Arsdk__Led__Command *message,
                      ProtobufCAllocator *allocator);
/* Arsdk__Led__Event__Luminosity methods */
void   arsdk__led__event__luminosity__init
                     (Arsdk__Led__Event__Luminosity         *message);
/* Arsdk__Led__Event methods */
void   arsdk__led__event__init
                     (Arsdk__Led__Event         *message);
size_t arsdk__led__event__get_packed_size
                     (const Arsdk__Led__Event   *message);
size_t arsdk__led__event__pack
                     (const Arsdk__Led__Event   *message,
                      uint8_t             *out);
size_t arsdk__led__event__pack_to_buffer
                     (const Arsdk__Led__Event   *message,
                      ProtobufCBuffer     *buffer);
Arsdk__Led__Event *
       arsdk__led__event__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   arsdk__led__event__free_unpacked
                     (Arsdk__Led__Event *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Arsdk__Led__Command__SetLuminosity_Closure)
                 (const Arsdk__Led__Command__SetLuminosity *message,
                  void *closure_data);
typedef void (*Arsdk__Led__Command_Closure)
                 (const Arsdk__Led__Command *message,
                  void *closure_data);
typedef void (*Arsdk__Led__Event__Luminosity_Closure)
                 (const Arsdk__Led__Event__Luminosity *message,
                  void *closure_data);
typedef void (*Arsdk__Led__Event_Closure)
                 (const Arsdk__Led__Event *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor arsdk__led__command__descriptor;
extern const ProtobufCMessageDescriptor arsdk__led__command__set_luminosity__descriptor;
extern const ProtobufCMessageDescriptor arsdk__led__event__descriptor;
extern const ProtobufCMessageDescriptor arsdk__led__event__luminosity__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_arsdk_2fled_2eproto__INCLUDED */