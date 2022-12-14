// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: guidance/lookat.proto

#ifndef PROTOBUF_INCLUDED_guidance_2flookat_2eproto
#define PROTOBUF_INCLUDED_guidance_2flookat_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/empty.pb.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_guidance_2flookat_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_guidance_2flookat_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_guidance_2flookat_2eproto();
namespace Guidance {
namespace LookAt {
namespace Messages {
class Command;
class CommandDefaultTypeInternal;
extern CommandDefaultTypeInternal _Command_default_instance_;
class Config;
class ConfigDefaultTypeInternal;
extern ConfigDefaultTypeInternal _Config_default_instance_;
class Event;
class EventDefaultTypeInternal;
extern EventDefaultTypeInternal _Event_default_instance_;
class FramingOffset;
class FramingOffsetDefaultTypeInternal;
extern FramingOffsetDefaultTypeInternal _FramingOffset_default_instance_;
}  // namespace Messages
}  // namespace LookAt
}  // namespace Guidance
namespace google {
namespace protobuf {
template<> ::Guidance::LookAt::Messages::Command* Arena::CreateMaybeMessage<::Guidance::LookAt::Messages::Command>(Arena*);
template<> ::Guidance::LookAt::Messages::Config* Arena::CreateMaybeMessage<::Guidance::LookAt::Messages::Config>(Arena*);
template<> ::Guidance::LookAt::Messages::Event* Arena::CreateMaybeMessage<::Guidance::LookAt::Messages::Event>(Arena*);
template<> ::Guidance::LookAt::Messages::FramingOffset* Arena::CreateMaybeMessage<::Guidance::LookAt::Messages::FramingOffset>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace Guidance {
namespace LookAt {
namespace Messages {

enum Type {
  TYPE_NONE = 0,
  TYPE_TARGET = 1,
  TYPE_PILOT = 2,
  Type_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::min(),
  Type_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::max()
};
bool Type_IsValid(int value);
const Type Type_MIN = TYPE_NONE;
const Type Type_MAX = TYPE_PILOT;
const int Type_ARRAYSIZE = Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Type_descriptor();
inline const ::std::string& Type_Name(Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Type_descriptor(), value);
}
inline bool Type_Parse(
    const ::std::string& name, Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Type>(
    Type_descriptor(), name, value);
}
// ===================================================================

class FramingOffset :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.LookAt.Messages.FramingOffset) */ {
 public:
  FramingOffset();
  virtual ~FramingOffset();

  FramingOffset(const FramingOffset& from);

  inline FramingOffset& operator=(const FramingOffset& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  FramingOffset(FramingOffset&& from) noexcept
    : FramingOffset() {
    *this = ::std::move(from);
  }

  inline FramingOffset& operator=(FramingOffset&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const FramingOffset& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const FramingOffset* internal_default_instance() {
    return reinterpret_cast<const FramingOffset*>(
               &_FramingOffset_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(FramingOffset* other);
  friend void swap(FramingOffset& a, FramingOffset& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline FramingOffset* New() const final {
    return CreateMaybeMessage<FramingOffset>(nullptr);
  }

  FramingOffset* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<FramingOffset>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const FramingOffset& from);
  void MergeFrom(const FramingOffset& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FramingOffset* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // sint32 horizontal = 1;
  void clear_horizontal();
  static const int kHorizontalFieldNumber = 1;
  ::google::protobuf::int32 horizontal() const;
  void set_horizontal(::google::protobuf::int32 value);

  // sint32 vertical = 2;
  void clear_vertical();
  static const int kVerticalFieldNumber = 2;
  ::google::protobuf::int32 vertical() const;
  void set_vertical(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Guidance.LookAt.Messages.FramingOffset)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 horizontal_;
  ::google::protobuf::int32 vertical_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_guidance_2flookat_2eproto;
};
// -------------------------------------------------------------------

class Config :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.LookAt.Messages.Config) */ {
 public:
  Config();
  virtual ~Config();

  Config(const Config& from);

  inline Config& operator=(const Config& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Config(Config&& from) noexcept
    : Config() {
    *this = ::std::move(from);
  }

  inline Config& operator=(Config&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Config& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Config* internal_default_instance() {
    return reinterpret_cast<const Config*>(
               &_Config_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Config* other);
  friend void swap(Config& a, Config& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Config* New() const final {
    return CreateMaybeMessage<Config>(nullptr);
  }

  Config* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Config>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Config& from);
  void MergeFrom(const Config& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Config* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .Guidance.LookAt.Messages.Type type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::Guidance::LookAt::Messages::Type type() const;
  void set_type(::Guidance::LookAt::Messages::Type value);

  // @@protoc_insertion_point(class_scope:Guidance.LookAt.Messages.Config)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  int type_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_guidance_2flookat_2eproto;
};
// -------------------------------------------------------------------

class Command :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.LookAt.Messages.Command) */ {
 public:
  Command();
  virtual ~Command();

  Command(const Command& from);

  inline Command& operator=(const Command& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Command(Command&& from) noexcept
    : Command() {
    *this = ::std::move(from);
  }

  inline Command& operator=(Command&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Command& default_instance();

  enum IdCase {
    kSetFramingOffset = 1,
    ID_NOT_SET = 0,
  };

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Command* internal_default_instance() {
    return reinterpret_cast<const Command*>(
               &_Command_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Command* other);
  friend void swap(Command& a, Command& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Command* New() const final {
    return CreateMaybeMessage<Command>(nullptr);
  }

  Command* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Command>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Command& from);
  void MergeFrom(const Command& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Command* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .Guidance.LookAt.Messages.FramingOffset set_framing_offset = 1;
  bool has_set_framing_offset() const;
  void clear_set_framing_offset();
  static const int kSetFramingOffsetFieldNumber = 1;
  const ::Guidance::LookAt::Messages::FramingOffset& set_framing_offset() const;
  ::Guidance::LookAt::Messages::FramingOffset* release_set_framing_offset();
  ::Guidance::LookAt::Messages::FramingOffset* mutable_set_framing_offset();
  void set_allocated_set_framing_offset(::Guidance::LookAt::Messages::FramingOffset* set_framing_offset);

  void clear_id();
  IdCase id_case() const;
  // @@protoc_insertion_point(class_scope:Guidance.LookAt.Messages.Command)
 private:
  class HasBitSetters;
  void set_has_set_framing_offset();

  inline bool has_id() const;
  inline void clear_has_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  union IdUnion {
    IdUnion() {}
    ::Guidance::LookAt::Messages::FramingOffset* set_framing_offset_;
  } id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend struct ::TableStruct_guidance_2flookat_2eproto;
};
// -------------------------------------------------------------------

class Event :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.LookAt.Messages.Event) */ {
 public:
  Event();
  virtual ~Event();

  Event(const Event& from);

  inline Event& operator=(const Event& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Event(Event&& from) noexcept
    : Event() {
    *this = ::std::move(from);
  }

  inline Event& operator=(Event&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Event& default_instance();

  enum IdCase {
    kEmpty = 1,
    ID_NOT_SET = 0,
  };

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Event* internal_default_instance() {
    return reinterpret_cast<const Event*>(
               &_Event_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(Event* other);
  friend void swap(Event& a, Event& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Event* New() const final {
    return CreateMaybeMessage<Event>(nullptr);
  }

  Event* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Event>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Event& from);
  void MergeFrom(const Event& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Event* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .google.protobuf.Empty empty = 1;
  bool has_empty() const;
  void clear_empty();
  static const int kEmptyFieldNumber = 1;
  const ::google::protobuf::Empty& empty() const;
  ::google::protobuf::Empty* release_empty();
  ::google::protobuf::Empty* mutable_empty();
  void set_allocated_empty(::google::protobuf::Empty* empty);

  void clear_id();
  IdCase id_case() const;
  // @@protoc_insertion_point(class_scope:Guidance.LookAt.Messages.Event)
 private:
  class HasBitSetters;
  void set_has_empty();

  inline bool has_id() const;
  inline void clear_has_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  union IdUnion {
    IdUnion() {}
    ::google::protobuf::Empty* empty_;
  } id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend struct ::TableStruct_guidance_2flookat_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// FramingOffset

// sint32 horizontal = 1;
inline void FramingOffset::clear_horizontal() {
  horizontal_ = 0;
}
inline ::google::protobuf::int32 FramingOffset::horizontal() const {
  // @@protoc_insertion_point(field_get:Guidance.LookAt.Messages.FramingOffset.horizontal)
  return horizontal_;
}
inline void FramingOffset::set_horizontal(::google::protobuf::int32 value) {
  
  horizontal_ = value;
  // @@protoc_insertion_point(field_set:Guidance.LookAt.Messages.FramingOffset.horizontal)
}

// sint32 vertical = 2;
inline void FramingOffset::clear_vertical() {
  vertical_ = 0;
}
inline ::google::protobuf::int32 FramingOffset::vertical() const {
  // @@protoc_insertion_point(field_get:Guidance.LookAt.Messages.FramingOffset.vertical)
  return vertical_;
}
inline void FramingOffset::set_vertical(::google::protobuf::int32 value) {
  
  vertical_ = value;
  // @@protoc_insertion_point(field_set:Guidance.LookAt.Messages.FramingOffset.vertical)
}

// -------------------------------------------------------------------

// Config

// .Guidance.LookAt.Messages.Type type = 1;
inline void Config::clear_type() {
  type_ = 0;
}
inline ::Guidance::LookAt::Messages::Type Config::type() const {
  // @@protoc_insertion_point(field_get:Guidance.LookAt.Messages.Config.type)
  return static_cast< ::Guidance::LookAt::Messages::Type >(type_);
}
inline void Config::set_type(::Guidance::LookAt::Messages::Type value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:Guidance.LookAt.Messages.Config.type)
}

// -------------------------------------------------------------------

// Command

// .Guidance.LookAt.Messages.FramingOffset set_framing_offset = 1;
inline bool Command::has_set_framing_offset() const {
  return id_case() == kSetFramingOffset;
}
inline void Command::set_has_set_framing_offset() {
  _oneof_case_[0] = kSetFramingOffset;
}
inline void Command::clear_set_framing_offset() {
  if (has_set_framing_offset()) {
    delete id_.set_framing_offset_;
    clear_has_id();
  }
}
inline ::Guidance::LookAt::Messages::FramingOffset* Command::release_set_framing_offset() {
  // @@protoc_insertion_point(field_release:Guidance.LookAt.Messages.Command.set_framing_offset)
  if (has_set_framing_offset()) {
    clear_has_id();
      ::Guidance::LookAt::Messages::FramingOffset* temp = id_.set_framing_offset_;
    id_.set_framing_offset_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::Guidance::LookAt::Messages::FramingOffset& Command::set_framing_offset() const {
  // @@protoc_insertion_point(field_get:Guidance.LookAt.Messages.Command.set_framing_offset)
  return has_set_framing_offset()
      ? *id_.set_framing_offset_
      : *reinterpret_cast< ::Guidance::LookAt::Messages::FramingOffset*>(&::Guidance::LookAt::Messages::_FramingOffset_default_instance_);
}
inline ::Guidance::LookAt::Messages::FramingOffset* Command::mutable_set_framing_offset() {
  if (!has_set_framing_offset()) {
    clear_id();
    set_has_set_framing_offset();
    id_.set_framing_offset_ = CreateMaybeMessage< ::Guidance::LookAt::Messages::FramingOffset >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:Guidance.LookAt.Messages.Command.set_framing_offset)
  return id_.set_framing_offset_;
}

inline bool Command::has_id() const {
  return id_case() != ID_NOT_SET;
}
inline void Command::clear_has_id() {
  _oneof_case_[0] = ID_NOT_SET;
}
inline Command::IdCase Command::id_case() const {
  return Command::IdCase(_oneof_case_[0]);
}
// -------------------------------------------------------------------

// Event

// .google.protobuf.Empty empty = 1;
inline bool Event::has_empty() const {
  return id_case() == kEmpty;
}
inline void Event::set_has_empty() {
  _oneof_case_[0] = kEmpty;
}
inline ::google::protobuf::Empty* Event::release_empty() {
  // @@protoc_insertion_point(field_release:Guidance.LookAt.Messages.Event.empty)
  if (has_empty()) {
    clear_has_id();
      ::google::protobuf::Empty* temp = id_.empty_;
    id_.empty_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::google::protobuf::Empty& Event::empty() const {
  // @@protoc_insertion_point(field_get:Guidance.LookAt.Messages.Event.empty)
  return has_empty()
      ? *id_.empty_
      : *reinterpret_cast< ::google::protobuf::Empty*>(&::google::protobuf::_Empty_default_instance_);
}
inline ::google::protobuf::Empty* Event::mutable_empty() {
  if (!has_empty()) {
    clear_id();
    set_has_empty();
    id_.empty_ = CreateMaybeMessage< ::google::protobuf::Empty >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:Guidance.LookAt.Messages.Event.empty)
  return id_.empty_;
}

inline bool Event::has_id() const {
  return id_case() != ID_NOT_SET;
}
inline void Event::clear_has_id() {
  _oneof_case_[0] = ID_NOT_SET;
}
inline Event::IdCase Event::id_case() const {
  return Event::IdCase(_oneof_case_[0]);
}
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Messages
}  // namespace LookAt
}  // namespace Guidance

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::Guidance::LookAt::Messages::Type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Guidance::LookAt::Messages::Type>() {
  return ::Guidance::LookAt::Messages::Type_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_guidance_2flookat_2eproto
