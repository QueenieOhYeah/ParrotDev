// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: guidance/magic_carpet.proto

#ifndef PROTOBUF_INCLUDED_guidance_2fmagic_5fcarpet_2eproto
#define PROTOBUF_INCLUDED_guidance_2fmagic_5fcarpet_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_guidance_2fmagic_5fcarpet_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_guidance_2fmagic_5fcarpet_2eproto {
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
void AddDescriptors_guidance_2fmagic_5fcarpet_2eproto();
namespace Guidance {
namespace MagicCarpet {
namespace Messages {
class Command;
class CommandDefaultTypeInternal;
extern CommandDefaultTypeInternal _Command_default_instance_;
class Event;
class EventDefaultTypeInternal;
extern EventDefaultTypeInternal _Event_default_instance_;
class ForceHeading;
class ForceHeadingDefaultTypeInternal;
extern ForceHeadingDefaultTypeInternal _ForceHeading_default_instance_;
class Trajectory;
class TrajectoryDefaultTypeInternal;
extern TrajectoryDefaultTypeInternal _Trajectory_default_instance_;
}  // namespace Messages
}  // namespace MagicCarpet
}  // namespace Guidance
namespace google {
namespace protobuf {
template<> ::Guidance::MagicCarpet::Messages::Command* Arena::CreateMaybeMessage<::Guidance::MagicCarpet::Messages::Command>(Arena*);
template<> ::Guidance::MagicCarpet::Messages::Event* Arena::CreateMaybeMessage<::Guidance::MagicCarpet::Messages::Event>(Arena*);
template<> ::Guidance::MagicCarpet::Messages::ForceHeading* Arena::CreateMaybeMessage<::Guidance::MagicCarpet::Messages::ForceHeading>(Arena*);
template<> ::Guidance::MagicCarpet::Messages::Trajectory* Arena::CreateMaybeMessage<::Guidance::MagicCarpet::Messages::Trajectory>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace Guidance {
namespace MagicCarpet {
namespace Messages {

enum Axis {
  AXIS_NORTH = 0,
  AXIS_EAST = 1,
  AXIS_DOWN = 2,
  AXIS_YAW = 3,
  Axis_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::min(),
  Axis_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::max()
};
bool Axis_IsValid(int value);
const Axis Axis_MIN = AXIS_NORTH;
const Axis Axis_MAX = AXIS_YAW;
const int Axis_ARRAYSIZE = Axis_MAX + 1;

const ::google::protobuf::EnumDescriptor* Axis_descriptor();
inline const ::std::string& Axis_Name(Axis value) {
  return ::google::protobuf::internal::NameOfEnum(
    Axis_descriptor(), value);
}
inline bool Axis_Parse(
    const ::std::string& name, Axis* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Axis>(
    Axis_descriptor(), name, value);
}
// ===================================================================

class Trajectory :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.MagicCarpet.Messages.Trajectory) */ {
 public:
  Trajectory();
  virtual ~Trajectory();

  Trajectory(const Trajectory& from);

  inline Trajectory& operator=(const Trajectory& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Trajectory(Trajectory&& from) noexcept
    : Trajectory() {
    *this = ::std::move(from);
  }

  inline Trajectory& operator=(Trajectory&& from) noexcept {
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
  static const Trajectory& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Trajectory* internal_default_instance() {
    return reinterpret_cast<const Trajectory*>(
               &_Trajectory_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Trajectory* other);
  friend void swap(Trajectory& a, Trajectory& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Trajectory* New() const final {
    return CreateMaybeMessage<Trajectory>(nullptr);
  }

  Trajectory* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Trajectory>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Trajectory& from);
  void MergeFrom(const Trajectory& from);
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
  void InternalSwap(Trajectory* other);
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

  // .Guidance.MagicCarpet.Messages.Axis axis = 1;
  void clear_axis();
  static const int kAxisFieldNumber = 1;
  ::Guidance::MagicCarpet::Messages::Axis axis() const;
  void set_axis(::Guidance::MagicCarpet::Messages::Axis value);

  // uint32 type = 2;
  void clear_type();
  static const int kTypeFieldNumber = 2;
  ::google::protobuf::uint32 type() const;
  void set_type(::google::protobuf::uint32 value);

  // float duration = 3;
  void clear_duration();
  static const int kDurationFieldNumber = 3;
  float duration() const;
  void set_duration(float value);

  // float position = 4;
  void clear_position();
  static const int kPositionFieldNumber = 4;
  float position() const;
  void set_position(float value);

  // float speed = 5;
  void clear_speed();
  static const int kSpeedFieldNumber = 5;
  float speed() const;
  void set_speed(float value);

  // float phase = 6;
  void clear_phase();
  static const int kPhaseFieldNumber = 6;
  float phase() const;
  void set_phase(float value);

  // @@protoc_insertion_point(class_scope:Guidance.MagicCarpet.Messages.Trajectory)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  int axis_;
  ::google::protobuf::uint32 type_;
  float duration_;
  float position_;
  float speed_;
  float phase_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_guidance_2fmagic_5fcarpet_2eproto;
};
// -------------------------------------------------------------------

class ForceHeading :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.MagicCarpet.Messages.ForceHeading) */ {
 public:
  ForceHeading();
  virtual ~ForceHeading();

  ForceHeading(const ForceHeading& from);

  inline ForceHeading& operator=(const ForceHeading& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ForceHeading(ForceHeading&& from) noexcept
    : ForceHeading() {
    *this = ::std::move(from);
  }

  inline ForceHeading& operator=(ForceHeading&& from) noexcept {
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
  static const ForceHeading& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ForceHeading* internal_default_instance() {
    return reinterpret_cast<const ForceHeading*>(
               &_ForceHeading_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(ForceHeading* other);
  friend void swap(ForceHeading& a, ForceHeading& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ForceHeading* New() const final {
    return CreateMaybeMessage<ForceHeading>(nullptr);
  }

  ForceHeading* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ForceHeading>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ForceHeading& from);
  void MergeFrom(const ForceHeading& from);
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
  void InternalSwap(ForceHeading* other);
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

  // float heading = 1;
  void clear_heading();
  static const int kHeadingFieldNumber = 1;
  float heading() const;
  void set_heading(float value);

  // @@protoc_insertion_point(class_scope:Guidance.MagicCarpet.Messages.ForceHeading)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  float heading_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_guidance_2fmagic_5fcarpet_2eproto;
};
// -------------------------------------------------------------------

class Command :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.MagicCarpet.Messages.Command) */ {
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
    kSetTrajectory = 1,
    kSetForceHeading = 2,
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

  // .Guidance.MagicCarpet.Messages.Trajectory set_trajectory = 1;
  bool has_set_trajectory() const;
  void clear_set_trajectory();
  static const int kSetTrajectoryFieldNumber = 1;
  const ::Guidance::MagicCarpet::Messages::Trajectory& set_trajectory() const;
  ::Guidance::MagicCarpet::Messages::Trajectory* release_set_trajectory();
  ::Guidance::MagicCarpet::Messages::Trajectory* mutable_set_trajectory();
  void set_allocated_set_trajectory(::Guidance::MagicCarpet::Messages::Trajectory* set_trajectory);

  // .Guidance.MagicCarpet.Messages.ForceHeading set_force_heading = 2;
  bool has_set_force_heading() const;
  void clear_set_force_heading();
  static const int kSetForceHeadingFieldNumber = 2;
  const ::Guidance::MagicCarpet::Messages::ForceHeading& set_force_heading() const;
  ::Guidance::MagicCarpet::Messages::ForceHeading* release_set_force_heading();
  ::Guidance::MagicCarpet::Messages::ForceHeading* mutable_set_force_heading();
  void set_allocated_set_force_heading(::Guidance::MagicCarpet::Messages::ForceHeading* set_force_heading);

  void clear_id();
  IdCase id_case() const;
  // @@protoc_insertion_point(class_scope:Guidance.MagicCarpet.Messages.Command)
 private:
  class HasBitSetters;
  void set_has_set_trajectory();
  void set_has_set_force_heading();

  inline bool has_id() const;
  inline void clear_has_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  union IdUnion {
    IdUnion() {}
    ::Guidance::MagicCarpet::Messages::Trajectory* set_trajectory_;
    ::Guidance::MagicCarpet::Messages::ForceHeading* set_force_heading_;
  } id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend struct ::TableStruct_guidance_2fmagic_5fcarpet_2eproto;
};
// -------------------------------------------------------------------

class Event :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Guidance.MagicCarpet.Messages.Event) */ {
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
  // @@protoc_insertion_point(class_scope:Guidance.MagicCarpet.Messages.Event)
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

  friend struct ::TableStruct_guidance_2fmagic_5fcarpet_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Trajectory

// .Guidance.MagicCarpet.Messages.Axis axis = 1;
inline void Trajectory::clear_axis() {
  axis_ = 0;
}
inline ::Guidance::MagicCarpet::Messages::Axis Trajectory::axis() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Trajectory.axis)
  return static_cast< ::Guidance::MagicCarpet::Messages::Axis >(axis_);
}
inline void Trajectory::set_axis(::Guidance::MagicCarpet::Messages::Axis value) {
  
  axis_ = value;
  // @@protoc_insertion_point(field_set:Guidance.MagicCarpet.Messages.Trajectory.axis)
}

// uint32 type = 2;
inline void Trajectory::clear_type() {
  type_ = 0u;
}
inline ::google::protobuf::uint32 Trajectory::type() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Trajectory.type)
  return type_;
}
inline void Trajectory::set_type(::google::protobuf::uint32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:Guidance.MagicCarpet.Messages.Trajectory.type)
}

// float duration = 3;
inline void Trajectory::clear_duration() {
  duration_ = 0;
}
inline float Trajectory::duration() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Trajectory.duration)
  return duration_;
}
inline void Trajectory::set_duration(float value) {
  
  duration_ = value;
  // @@protoc_insertion_point(field_set:Guidance.MagicCarpet.Messages.Trajectory.duration)
}

// float position = 4;
inline void Trajectory::clear_position() {
  position_ = 0;
}
inline float Trajectory::position() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Trajectory.position)
  return position_;
}
inline void Trajectory::set_position(float value) {
  
  position_ = value;
  // @@protoc_insertion_point(field_set:Guidance.MagicCarpet.Messages.Trajectory.position)
}

// float speed = 5;
inline void Trajectory::clear_speed() {
  speed_ = 0;
}
inline float Trajectory::speed() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Trajectory.speed)
  return speed_;
}
inline void Trajectory::set_speed(float value) {
  
  speed_ = value;
  // @@protoc_insertion_point(field_set:Guidance.MagicCarpet.Messages.Trajectory.speed)
}

// float phase = 6;
inline void Trajectory::clear_phase() {
  phase_ = 0;
}
inline float Trajectory::phase() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Trajectory.phase)
  return phase_;
}
inline void Trajectory::set_phase(float value) {
  
  phase_ = value;
  // @@protoc_insertion_point(field_set:Guidance.MagicCarpet.Messages.Trajectory.phase)
}

// -------------------------------------------------------------------

// ForceHeading

// float heading = 1;
inline void ForceHeading::clear_heading() {
  heading_ = 0;
}
inline float ForceHeading::heading() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.ForceHeading.heading)
  return heading_;
}
inline void ForceHeading::set_heading(float value) {
  
  heading_ = value;
  // @@protoc_insertion_point(field_set:Guidance.MagicCarpet.Messages.ForceHeading.heading)
}

// -------------------------------------------------------------------

// Command

// .Guidance.MagicCarpet.Messages.Trajectory set_trajectory = 1;
inline bool Command::has_set_trajectory() const {
  return id_case() == kSetTrajectory;
}
inline void Command::set_has_set_trajectory() {
  _oneof_case_[0] = kSetTrajectory;
}
inline void Command::clear_set_trajectory() {
  if (has_set_trajectory()) {
    delete id_.set_trajectory_;
    clear_has_id();
  }
}
inline ::Guidance::MagicCarpet::Messages::Trajectory* Command::release_set_trajectory() {
  // @@protoc_insertion_point(field_release:Guidance.MagicCarpet.Messages.Command.set_trajectory)
  if (has_set_trajectory()) {
    clear_has_id();
      ::Guidance::MagicCarpet::Messages::Trajectory* temp = id_.set_trajectory_;
    id_.set_trajectory_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::Guidance::MagicCarpet::Messages::Trajectory& Command::set_trajectory() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Command.set_trajectory)
  return has_set_trajectory()
      ? *id_.set_trajectory_
      : *reinterpret_cast< ::Guidance::MagicCarpet::Messages::Trajectory*>(&::Guidance::MagicCarpet::Messages::_Trajectory_default_instance_);
}
inline ::Guidance::MagicCarpet::Messages::Trajectory* Command::mutable_set_trajectory() {
  if (!has_set_trajectory()) {
    clear_id();
    set_has_set_trajectory();
    id_.set_trajectory_ = CreateMaybeMessage< ::Guidance::MagicCarpet::Messages::Trajectory >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:Guidance.MagicCarpet.Messages.Command.set_trajectory)
  return id_.set_trajectory_;
}

// .Guidance.MagicCarpet.Messages.ForceHeading set_force_heading = 2;
inline bool Command::has_set_force_heading() const {
  return id_case() == kSetForceHeading;
}
inline void Command::set_has_set_force_heading() {
  _oneof_case_[0] = kSetForceHeading;
}
inline void Command::clear_set_force_heading() {
  if (has_set_force_heading()) {
    delete id_.set_force_heading_;
    clear_has_id();
  }
}
inline ::Guidance::MagicCarpet::Messages::ForceHeading* Command::release_set_force_heading() {
  // @@protoc_insertion_point(field_release:Guidance.MagicCarpet.Messages.Command.set_force_heading)
  if (has_set_force_heading()) {
    clear_has_id();
      ::Guidance::MagicCarpet::Messages::ForceHeading* temp = id_.set_force_heading_;
    id_.set_force_heading_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::Guidance::MagicCarpet::Messages::ForceHeading& Command::set_force_heading() const {
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Command.set_force_heading)
  return has_set_force_heading()
      ? *id_.set_force_heading_
      : *reinterpret_cast< ::Guidance::MagicCarpet::Messages::ForceHeading*>(&::Guidance::MagicCarpet::Messages::_ForceHeading_default_instance_);
}
inline ::Guidance::MagicCarpet::Messages::ForceHeading* Command::mutable_set_force_heading() {
  if (!has_set_force_heading()) {
    clear_id();
    set_has_set_force_heading();
    id_.set_force_heading_ = CreateMaybeMessage< ::Guidance::MagicCarpet::Messages::ForceHeading >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:Guidance.MagicCarpet.Messages.Command.set_force_heading)
  return id_.set_force_heading_;
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
  // @@protoc_insertion_point(field_release:Guidance.MagicCarpet.Messages.Event.empty)
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
  // @@protoc_insertion_point(field_get:Guidance.MagicCarpet.Messages.Event.empty)
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
  // @@protoc_insertion_point(field_mutable:Guidance.MagicCarpet.Messages.Event.empty)
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
}  // namespace MagicCarpet
}  // namespace Guidance

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::Guidance::MagicCarpet::Messages::Axis> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Guidance::MagicCarpet::Messages::Axis>() {
  return ::Guidance::MagicCarpet::Messages::Axis_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_guidance_2fmagic_5fcarpet_2eproto
