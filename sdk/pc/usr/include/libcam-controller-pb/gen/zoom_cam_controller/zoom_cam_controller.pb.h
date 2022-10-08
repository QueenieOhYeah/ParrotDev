// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: zoom_cam_controller/zoom_cam_controller.proto

#ifndef PROTOBUF_INCLUDED_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto
#define PROTOBUF_INCLUDED_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto

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
#include <google/protobuf/unknown_field_set.h>
#include "cam_controller/cam_controller.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto {
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
void AddDescriptors_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto();
namespace ZoomCamController {
namespace Messages {
class Command;
class CommandDefaultTypeInternal;
extern CommandDefaultTypeInternal _Command_default_instance_;
class Config;
class ConfigDefaultTypeInternal;
extern ConfigDefaultTypeInternal _Config_default_instance_;
class Config_Fov;
class Config_FovDefaultTypeInternal;
extern Config_FovDefaultTypeInternal _Config_Fov_default_instance_;
class Zoom;
class ZoomDefaultTypeInternal;
extern ZoomDefaultTypeInternal _Zoom_default_instance_;
}  // namespace Messages
}  // namespace ZoomCamController
namespace google {
namespace protobuf {
template<> ::ZoomCamController::Messages::Command* Arena::CreateMaybeMessage<::ZoomCamController::Messages::Command>(Arena*);
template<> ::ZoomCamController::Messages::Config* Arena::CreateMaybeMessage<::ZoomCamController::Messages::Config>(Arena*);
template<> ::ZoomCamController::Messages::Config_Fov* Arena::CreateMaybeMessage<::ZoomCamController::Messages::Config_Fov>(Arena*);
template<> ::ZoomCamController::Messages::Zoom* Arena::CreateMaybeMessage<::ZoomCamController::Messages::Zoom>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace ZoomCamController {
namespace Messages {

// ===================================================================

class Config_Fov :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ZoomCamController.Messages.Config.Fov) */ {
 public:
  Config_Fov();
  virtual ~Config_Fov();

  Config_Fov(const Config_Fov& from);

  inline Config_Fov& operator=(const Config_Fov& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Config_Fov(Config_Fov&& from) noexcept
    : Config_Fov() {
    *this = ::std::move(from);
  }

  inline Config_Fov& operator=(Config_Fov&& from) noexcept {
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
  static const Config_Fov& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Config_Fov* internal_default_instance() {
    return reinterpret_cast<const Config_Fov*>(
               &_Config_Fov_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Config_Fov* other);
  friend void swap(Config_Fov& a, Config_Fov& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Config_Fov* New() const final {
    return CreateMaybeMessage<Config_Fov>(nullptr);
  }

  Config_Fov* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Config_Fov>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Config_Fov& from);
  void MergeFrom(const Config_Fov& from);
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
  void InternalSwap(Config_Fov* other);
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

  // float bound_min = 1;
  void clear_bound_min();
  static const int kBoundMinFieldNumber = 1;
  float bound_min() const;
  void set_bound_min(float value);

  // float bound_max_lossless = 2;
  void clear_bound_max_lossless();
  static const int kBoundMaxLosslessFieldNumber = 2;
  float bound_max_lossless() const;
  void set_bound_max_lossless(float value);

  // float bound_max_lossy = 3;
  void clear_bound_max_lossy();
  static const int kBoundMaxLossyFieldNumber = 3;
  float bound_max_lossy() const;
  void set_bound_max_lossy(float value);

  // float ratio = 4;
  void clear_ratio();
  static const int kRatioFieldNumber = 4;
  float ratio() const;
  void set_ratio(float value);

  // @@protoc_insertion_point(class_scope:ZoomCamController.Messages.Config.Fov)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  float bound_min_;
  float bound_max_lossless_;
  float bound_max_lossy_;
  float ratio_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto;
};
// -------------------------------------------------------------------

class Config :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ZoomCamController.Messages.Config) */ {
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

  enum OptionalLockedCase {
    kLocked = 1,
    OPTIONAL_LOCKED_NOT_SET = 0,
  };

  enum OptionalFilteredCase {
    kFiltered = 2,
    OPTIONAL_FILTERED_NOT_SET = 0,
  };

  enum OptionalLossyCase {
    kLossy = 3,
    OPTIONAL_LOSSY_NOT_SET = 0,
  };

  enum OptionalMaxVelCase {
    kMaxVel = 4,
    OPTIONAL_MAX_VEL_NOT_SET = 0,
  };

  enum OptionalFovCase {
    kFov = 5,
    OPTIONAL_FOV_NOT_SET = 0,
  };

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

  typedef Config_Fov Fov;

  // accessors -------------------------------------------------------

  // bool locked = 1;
  private:
  bool has_locked() const;
  public:
  void clear_locked();
  static const int kLockedFieldNumber = 1;
  bool locked() const;
  void set_locked(bool value);

  // bool filtered = 2;
  private:
  bool has_filtered() const;
  public:
  void clear_filtered();
  static const int kFilteredFieldNumber = 2;
  bool filtered() const;
  void set_filtered(bool value);

  // bool lossy = 3;
  private:
  bool has_lossy() const;
  public:
  void clear_lossy();
  static const int kLossyFieldNumber = 3;
  bool lossy() const;
  void set_lossy(bool value);

  // float max_vel = 4;
  private:
  bool has_max_vel() const;
  public:
  void clear_max_vel();
  static const int kMaxVelFieldNumber = 4;
  float max_vel() const;
  void set_max_vel(float value);

  // .ZoomCamController.Messages.Config.Fov fov = 5;
  bool has_fov() const;
  void clear_fov();
  static const int kFovFieldNumber = 5;
  const ::ZoomCamController::Messages::Config_Fov& fov() const;
  ::ZoomCamController::Messages::Config_Fov* release_fov();
  ::ZoomCamController::Messages::Config_Fov* mutable_fov();
  void set_allocated_fov(::ZoomCamController::Messages::Config_Fov* fov);

  void clear_optional_locked();
  OptionalLockedCase optional_locked_case() const;
  void clear_optional_filtered();
  OptionalFilteredCase optional_filtered_case() const;
  void clear_optional_lossy();
  OptionalLossyCase optional_lossy_case() const;
  void clear_optional_max_vel();
  OptionalMaxVelCase optional_max_vel_case() const;
  void clear_optional_fov();
  OptionalFovCase optional_fov_case() const;
  // @@protoc_insertion_point(class_scope:ZoomCamController.Messages.Config)
 private:
  class HasBitSetters;
  void set_has_locked();
  void set_has_filtered();
  void set_has_lossy();
  void set_has_max_vel();
  void set_has_fov();

  inline bool has_optional_locked() const;
  inline void clear_has_optional_locked();

  inline bool has_optional_filtered() const;
  inline void clear_has_optional_filtered();

  inline bool has_optional_lossy() const;
  inline void clear_has_optional_lossy();

  inline bool has_optional_max_vel() const;
  inline void clear_has_optional_max_vel();

  inline bool has_optional_fov() const;
  inline void clear_has_optional_fov();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  union OptionalLockedUnion {
    OptionalLockedUnion() {}
    bool locked_;
  } optional_locked_;
  union OptionalFilteredUnion {
    OptionalFilteredUnion() {}
    bool filtered_;
  } optional_filtered_;
  union OptionalLossyUnion {
    OptionalLossyUnion() {}
    bool lossy_;
  } optional_lossy_;
  union OptionalMaxVelUnion {
    OptionalMaxVelUnion() {}
    float max_vel_;
  } optional_max_vel_;
  union OptionalFovUnion {
    OptionalFovUnion() {}
    ::ZoomCamController::Messages::Config_Fov* fov_;
  } optional_fov_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[5];

  friend struct ::TableStruct_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto;
};
// -------------------------------------------------------------------

class Zoom :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ZoomCamController.Messages.Zoom) */ {
 public:
  Zoom();
  virtual ~Zoom();

  Zoom(const Zoom& from);

  inline Zoom& operator=(const Zoom& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Zoom(Zoom&& from) noexcept
    : Zoom() {
    *this = ::std::move(from);
  }

  inline Zoom& operator=(Zoom&& from) noexcept {
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
  static const Zoom& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Zoom* internal_default_instance() {
    return reinterpret_cast<const Zoom*>(
               &_Zoom_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Zoom* other);
  friend void swap(Zoom& a, Zoom& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Zoom* New() const final {
    return CreateMaybeMessage<Zoom>(nullptr);
  }

  Zoom* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Zoom>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Zoom& from);
  void MergeFrom(const Zoom& from);
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
  void InternalSwap(Zoom* other);
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

  // .CamController.Messages.ControlMode.Enum ctrl_mode = 1;
  void clear_ctrl_mode();
  static const int kCtrlModeFieldNumber = 1;
  ::CamController::Messages::ControlMode::Enum ctrl_mode() const;
  void set_ctrl_mode(::CamController::Messages::ControlMode::Enum value);

  // float position = 2;
  void clear_position();
  static const int kPositionFieldNumber = 2;
  float position() const;
  void set_position(float value);

  // float velocity = 3;
  void clear_velocity();
  static const int kVelocityFieldNumber = 3;
  float velocity() const;
  void set_velocity(float value);

  // @@protoc_insertion_point(class_scope:ZoomCamController.Messages.Zoom)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  int ctrl_mode_;
  float position_;
  float velocity_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto;
};
// -------------------------------------------------------------------

class Command :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ZoomCamController.Messages.Command) */ {
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
    kSetConfig = 1,
    kSetZoom = 2,
    ID_NOT_SET = 0,
  };

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Command* internal_default_instance() {
    return reinterpret_cast<const Command*>(
               &_Command_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

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

  // .ZoomCamController.Messages.Config set_config = 1;
  bool has_set_config() const;
  void clear_set_config();
  static const int kSetConfigFieldNumber = 1;
  const ::ZoomCamController::Messages::Config& set_config() const;
  ::ZoomCamController::Messages::Config* release_set_config();
  ::ZoomCamController::Messages::Config* mutable_set_config();
  void set_allocated_set_config(::ZoomCamController::Messages::Config* set_config);

  // .ZoomCamController.Messages.Zoom set_zoom = 2;
  bool has_set_zoom() const;
  void clear_set_zoom();
  static const int kSetZoomFieldNumber = 2;
  const ::ZoomCamController::Messages::Zoom& set_zoom() const;
  ::ZoomCamController::Messages::Zoom* release_set_zoom();
  ::ZoomCamController::Messages::Zoom* mutable_set_zoom();
  void set_allocated_set_zoom(::ZoomCamController::Messages::Zoom* set_zoom);

  void clear_id();
  IdCase id_case() const;
  // @@protoc_insertion_point(class_scope:ZoomCamController.Messages.Command)
 private:
  class HasBitSetters;
  void set_has_set_config();
  void set_has_set_zoom();

  inline bool has_id() const;
  inline void clear_has_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  union IdUnion {
    IdUnion() {}
    ::ZoomCamController::Messages::Config* set_config_;
    ::ZoomCamController::Messages::Zoom* set_zoom_;
  } id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend struct ::TableStruct_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Config_Fov

// float bound_min = 1;
inline void Config_Fov::clear_bound_min() {
  bound_min_ = 0;
}
inline float Config_Fov::bound_min() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.Fov.bound_min)
  return bound_min_;
}
inline void Config_Fov::set_bound_min(float value) {
  
  bound_min_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.Fov.bound_min)
}

// float bound_max_lossless = 2;
inline void Config_Fov::clear_bound_max_lossless() {
  bound_max_lossless_ = 0;
}
inline float Config_Fov::bound_max_lossless() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.Fov.bound_max_lossless)
  return bound_max_lossless_;
}
inline void Config_Fov::set_bound_max_lossless(float value) {
  
  bound_max_lossless_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.Fov.bound_max_lossless)
}

// float bound_max_lossy = 3;
inline void Config_Fov::clear_bound_max_lossy() {
  bound_max_lossy_ = 0;
}
inline float Config_Fov::bound_max_lossy() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.Fov.bound_max_lossy)
  return bound_max_lossy_;
}
inline void Config_Fov::set_bound_max_lossy(float value) {
  
  bound_max_lossy_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.Fov.bound_max_lossy)
}

// float ratio = 4;
inline void Config_Fov::clear_ratio() {
  ratio_ = 0;
}
inline float Config_Fov::ratio() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.Fov.ratio)
  return ratio_;
}
inline void Config_Fov::set_ratio(float value) {
  
  ratio_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.Fov.ratio)
}

// -------------------------------------------------------------------

// Config

// bool locked = 1;
inline bool Config::has_locked() const {
  return optional_locked_case() == kLocked;
}
inline void Config::set_has_locked() {
  _oneof_case_[0] = kLocked;
}
inline void Config::clear_locked() {
  if (has_locked()) {
    optional_locked_.locked_ = false;
    clear_has_optional_locked();
  }
}
inline bool Config::locked() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.locked)
  if (has_locked()) {
    return optional_locked_.locked_;
  }
  return false;
}
inline void Config::set_locked(bool value) {
  if (!has_locked()) {
    clear_optional_locked();
    set_has_locked();
  }
  optional_locked_.locked_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.locked)
}

// bool filtered = 2;
inline bool Config::has_filtered() const {
  return optional_filtered_case() == kFiltered;
}
inline void Config::set_has_filtered() {
  _oneof_case_[1] = kFiltered;
}
inline void Config::clear_filtered() {
  if (has_filtered()) {
    optional_filtered_.filtered_ = false;
    clear_has_optional_filtered();
  }
}
inline bool Config::filtered() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.filtered)
  if (has_filtered()) {
    return optional_filtered_.filtered_;
  }
  return false;
}
inline void Config::set_filtered(bool value) {
  if (!has_filtered()) {
    clear_optional_filtered();
    set_has_filtered();
  }
  optional_filtered_.filtered_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.filtered)
}

// bool lossy = 3;
inline bool Config::has_lossy() const {
  return optional_lossy_case() == kLossy;
}
inline void Config::set_has_lossy() {
  _oneof_case_[2] = kLossy;
}
inline void Config::clear_lossy() {
  if (has_lossy()) {
    optional_lossy_.lossy_ = false;
    clear_has_optional_lossy();
  }
}
inline bool Config::lossy() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.lossy)
  if (has_lossy()) {
    return optional_lossy_.lossy_;
  }
  return false;
}
inline void Config::set_lossy(bool value) {
  if (!has_lossy()) {
    clear_optional_lossy();
    set_has_lossy();
  }
  optional_lossy_.lossy_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.lossy)
}

// float max_vel = 4;
inline bool Config::has_max_vel() const {
  return optional_max_vel_case() == kMaxVel;
}
inline void Config::set_has_max_vel() {
  _oneof_case_[3] = kMaxVel;
}
inline void Config::clear_max_vel() {
  if (has_max_vel()) {
    optional_max_vel_.max_vel_ = 0;
    clear_has_optional_max_vel();
  }
}
inline float Config::max_vel() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.max_vel)
  if (has_max_vel()) {
    return optional_max_vel_.max_vel_;
  }
  return 0;
}
inline void Config::set_max_vel(float value) {
  if (!has_max_vel()) {
    clear_optional_max_vel();
    set_has_max_vel();
  }
  optional_max_vel_.max_vel_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Config.max_vel)
}

// .ZoomCamController.Messages.Config.Fov fov = 5;
inline bool Config::has_fov() const {
  return optional_fov_case() == kFov;
}
inline void Config::set_has_fov() {
  _oneof_case_[4] = kFov;
}
inline void Config::clear_fov() {
  if (has_fov()) {
    delete optional_fov_.fov_;
    clear_has_optional_fov();
  }
}
inline ::ZoomCamController::Messages::Config_Fov* Config::release_fov() {
  // @@protoc_insertion_point(field_release:ZoomCamController.Messages.Config.fov)
  if (has_fov()) {
    clear_has_optional_fov();
      ::ZoomCamController::Messages::Config_Fov* temp = optional_fov_.fov_;
    optional_fov_.fov_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::ZoomCamController::Messages::Config_Fov& Config::fov() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Config.fov)
  return has_fov()
      ? *optional_fov_.fov_
      : *reinterpret_cast< ::ZoomCamController::Messages::Config_Fov*>(&::ZoomCamController::Messages::_Config_Fov_default_instance_);
}
inline ::ZoomCamController::Messages::Config_Fov* Config::mutable_fov() {
  if (!has_fov()) {
    clear_optional_fov();
    set_has_fov();
    optional_fov_.fov_ = CreateMaybeMessage< ::ZoomCamController::Messages::Config_Fov >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:ZoomCamController.Messages.Config.fov)
  return optional_fov_.fov_;
}

inline bool Config::has_optional_locked() const {
  return optional_locked_case() != OPTIONAL_LOCKED_NOT_SET;
}
inline void Config::clear_has_optional_locked() {
  _oneof_case_[0] = OPTIONAL_LOCKED_NOT_SET;
}
inline bool Config::has_optional_filtered() const {
  return optional_filtered_case() != OPTIONAL_FILTERED_NOT_SET;
}
inline void Config::clear_has_optional_filtered() {
  _oneof_case_[1] = OPTIONAL_FILTERED_NOT_SET;
}
inline bool Config::has_optional_lossy() const {
  return optional_lossy_case() != OPTIONAL_LOSSY_NOT_SET;
}
inline void Config::clear_has_optional_lossy() {
  _oneof_case_[2] = OPTIONAL_LOSSY_NOT_SET;
}
inline bool Config::has_optional_max_vel() const {
  return optional_max_vel_case() != OPTIONAL_MAX_VEL_NOT_SET;
}
inline void Config::clear_has_optional_max_vel() {
  _oneof_case_[3] = OPTIONAL_MAX_VEL_NOT_SET;
}
inline bool Config::has_optional_fov() const {
  return optional_fov_case() != OPTIONAL_FOV_NOT_SET;
}
inline void Config::clear_has_optional_fov() {
  _oneof_case_[4] = OPTIONAL_FOV_NOT_SET;
}
inline Config::OptionalLockedCase Config::optional_locked_case() const {
  return Config::OptionalLockedCase(_oneof_case_[0]);
}
inline Config::OptionalFilteredCase Config::optional_filtered_case() const {
  return Config::OptionalFilteredCase(_oneof_case_[1]);
}
inline Config::OptionalLossyCase Config::optional_lossy_case() const {
  return Config::OptionalLossyCase(_oneof_case_[2]);
}
inline Config::OptionalMaxVelCase Config::optional_max_vel_case() const {
  return Config::OptionalMaxVelCase(_oneof_case_[3]);
}
inline Config::OptionalFovCase Config::optional_fov_case() const {
  return Config::OptionalFovCase(_oneof_case_[4]);
}
// -------------------------------------------------------------------

// Zoom

// .CamController.Messages.ControlMode.Enum ctrl_mode = 1;
inline void Zoom::clear_ctrl_mode() {
  ctrl_mode_ = 0;
}
inline ::CamController::Messages::ControlMode::Enum Zoom::ctrl_mode() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Zoom.ctrl_mode)
  return static_cast< ::CamController::Messages::ControlMode::Enum >(ctrl_mode_);
}
inline void Zoom::set_ctrl_mode(::CamController::Messages::ControlMode::Enum value) {
  
  ctrl_mode_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Zoom.ctrl_mode)
}

// float position = 2;
inline void Zoom::clear_position() {
  position_ = 0;
}
inline float Zoom::position() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Zoom.position)
  return position_;
}
inline void Zoom::set_position(float value) {
  
  position_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Zoom.position)
}

// float velocity = 3;
inline void Zoom::clear_velocity() {
  velocity_ = 0;
}
inline float Zoom::velocity() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Zoom.velocity)
  return velocity_;
}
inline void Zoom::set_velocity(float value) {
  
  velocity_ = value;
  // @@protoc_insertion_point(field_set:ZoomCamController.Messages.Zoom.velocity)
}

// -------------------------------------------------------------------

// Command

// .ZoomCamController.Messages.Config set_config = 1;
inline bool Command::has_set_config() const {
  return id_case() == kSetConfig;
}
inline void Command::set_has_set_config() {
  _oneof_case_[0] = kSetConfig;
}
inline void Command::clear_set_config() {
  if (has_set_config()) {
    delete id_.set_config_;
    clear_has_id();
  }
}
inline ::ZoomCamController::Messages::Config* Command::release_set_config() {
  // @@protoc_insertion_point(field_release:ZoomCamController.Messages.Command.set_config)
  if (has_set_config()) {
    clear_has_id();
      ::ZoomCamController::Messages::Config* temp = id_.set_config_;
    id_.set_config_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::ZoomCamController::Messages::Config& Command::set_config() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Command.set_config)
  return has_set_config()
      ? *id_.set_config_
      : *reinterpret_cast< ::ZoomCamController::Messages::Config*>(&::ZoomCamController::Messages::_Config_default_instance_);
}
inline ::ZoomCamController::Messages::Config* Command::mutable_set_config() {
  if (!has_set_config()) {
    clear_id();
    set_has_set_config();
    id_.set_config_ = CreateMaybeMessage< ::ZoomCamController::Messages::Config >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:ZoomCamController.Messages.Command.set_config)
  return id_.set_config_;
}

// .ZoomCamController.Messages.Zoom set_zoom = 2;
inline bool Command::has_set_zoom() const {
  return id_case() == kSetZoom;
}
inline void Command::set_has_set_zoom() {
  _oneof_case_[0] = kSetZoom;
}
inline void Command::clear_set_zoom() {
  if (has_set_zoom()) {
    delete id_.set_zoom_;
    clear_has_id();
  }
}
inline ::ZoomCamController::Messages::Zoom* Command::release_set_zoom() {
  // @@protoc_insertion_point(field_release:ZoomCamController.Messages.Command.set_zoom)
  if (has_set_zoom()) {
    clear_has_id();
      ::ZoomCamController::Messages::Zoom* temp = id_.set_zoom_;
    id_.set_zoom_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::ZoomCamController::Messages::Zoom& Command::set_zoom() const {
  // @@protoc_insertion_point(field_get:ZoomCamController.Messages.Command.set_zoom)
  return has_set_zoom()
      ? *id_.set_zoom_
      : *reinterpret_cast< ::ZoomCamController::Messages::Zoom*>(&::ZoomCamController::Messages::_Zoom_default_instance_);
}
inline ::ZoomCamController::Messages::Zoom* Command::mutable_set_zoom() {
  if (!has_set_zoom()) {
    clear_id();
    set_has_set_zoom();
    id_.set_zoom_ = CreateMaybeMessage< ::ZoomCamController::Messages::Zoom >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:ZoomCamController.Messages.Command.set_zoom)
  return id_.set_zoom_;
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
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Messages
}  // namespace ZoomCamController

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_zoom_5fcam_5fcontroller_2fzoom_5fcam_5fcontroller_2eproto
