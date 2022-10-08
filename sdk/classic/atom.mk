# GENERATED FILE, DO NOT EDIT

LOCAL_PATH := $(call my-dir)

ifneq ("$(TARGET_OS)","linux")
  $(error This sdk is for TARGET_OS=linux)
endif

ifneq ("$(TARGET_OS_FLAVOUR)","parrot")
  $(error This sdk is for TARGET_OS_FLAVOUR=parrot)
endif

ifneq ("$(TARGET_ARCH)","aarch64")
  $(error This sdk is for TARGET_ARCH=aarch64)
endif

ifneq ("$(TARGET_CPU)","hi3559")
  $(error This sdk is for TARGET_CPU=hi3559)
endif

ifneq ("$(TARGET_CC_FLAVOUR)","gcc")
  $(error This sdk is for TARGET_CC_FLAVOUR=gcc)
endif

ifneq ("$(TARGET_TOOLCHAIN_TRIPLET)","aarch64-linux-gnu")
  $(error This sdk is for TARGET_TOOLCHAIN_TRIPLET=aarch64-linux-gnu)
endif

ifneq ("$(TARGET_LIBC)","eglibc")
  $(error This sdk is for TARGET_LIBC=eglibc)
endif

ifneq ("$(TARGET_CC_VERSION)","6.3.0")
  $(error This sdk is for TARGET_CC_VERSION=6.3.0)
endif

include $(CLEAR_VARS)
LOCAL_MODULE := eigen
LOCAL_DESCRIPTION := C++ template library for linear algebra
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := c1ed80e6434c828a08f8b91eea2295aeecd37e54
LOCAL_REVISION_DESCRIBE := upstream-3.3.4-200-gc1ed80e64
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/eigen
LOCAL_EXPORT_CFLAGS := -DEIGEN_MPL2_ONLY -DEIGEN_QUATERNIONBASE_PLUGIN=\"QuaternionBaseAddons.hpp\"
LOCAL_EXPORT_CXXFLAGS := -Wno-deprecated-copy -Wno-deprecated-declarations
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/eigen3
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := glib
LOCAL_DESCRIPTION := GLib meta package with optional gobject-introspection dependency
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 460be4503af852a957cfca354284dc63db02c5ab
LOCAL_REVISION_DESCRIBE := 2.48.1-28-g460be4503
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/glib
LOCAL_EXPORT_LDLIBS := \
	-lglib-2.0 \
	-lgio-2.0 \
	-lgobject-2.0 \
	-lgmodule-2.0 \
	-lgthread-2.0
LOCAL_LIBRARIES := glib-base
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := glib-base
LOCAL_DESCRIPTION := GLib is the low-level core library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 460be4503af852a957cfca354284dc63db02c5ab
LOCAL_REVISION_DESCRIBE := 2.48.1-28-g460be4503
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/glib
LOCAL_EXPORT_LDLIBS := \
	-lglib-2.0 \
	-lgio-2.0 \
	-lgobject-2.0 \
	-lgmodule-2.0 \
	-lgthread-2.0
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/lib/glib-2.0/include \
	$(LOCAL_PATH)/usr/include/glib-2.0 \
	$(LOCAL_PATH)/usr/include/gio-unix-2.0
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := gst-plugins-bad
LOCAL_DESCRIPTION := GStreamer streaming media framework bad plug-ins
LOCAL_CATEGORY_PATH := multimedia/gstreamer
LOCAL_REVISION := 045a13d06760fdd08d084ee531386bb5b6d842fc
LOCAL_REVISION_DESCRIBE := 1.12.1-37-g045a13d06
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/gstreamer/gst-plugins-bad
LOCAL_EXPORT_LDLIBS := \
	-lgstcodecparsers-1.0 \
	-lgstinsertbin-1.0 \
	-lgstmpegts-1.0 \
	-lgstbadbase-1.0
LOCAL_CONFIG_FILES := 1
sdk.gst-plugins-bad.config := $(LOCAL_PATH)/config/gst-plugins-bad.config
$(call load-config)
LOCAL_LIBRARIES := gstreamer gst-plugins-base
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := gst-plugins-base
LOCAL_DESCRIPTION := GStreamer streaming media framework base plug-ins
LOCAL_CATEGORY_PATH := multimedia/gstreamer
LOCAL_REVISION := 5484c681f7b6f93c94756c4334db4173ff2dbfd6
LOCAL_REVISION_DESCRIBE := 1.12.0-104-g5484c681f
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/gstreamer/gst-plugins-base
LOCAL_EXPORT_LDLIBS := \
	-lgstallocators-1.0 \
	-lgstapp-1.0 \
	-lgstaudio-1.0 \
	-lgstfft-1.0 \
	-lgstpbutils-1.0 \
	-lgstriff-1.0 \
	-lgstrtp-1.0 \
	-lgstrtsp-1.0 \
	-lgstsdp-1.0 \
	-lgsttag-1.0 \
	-lgstvideo-1.0
LOCAL_CONFIG_FILES := 1
sdk.gst-plugins-base.config := $(LOCAL_PATH)/config/gst-plugins-base.config
$(call load-config)
LOCAL_LIBRARIES := gstreamer
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := gstreamer
LOCAL_DESCRIPTION := GStreamer streaming media framework runtime
LOCAL_CATEGORY_PATH := multimedia/gstreamer
LOCAL_REVISION := 954b1bd42dbaf3286563ca5a91cf158a742008b2
LOCAL_REVISION_DESCRIBE := 1.12.1-71-g954b1bd42
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/gstreamer/gstreamer
LOCAL_EXPORT_LDLIBS := \
	-lgstreamer-1.0 \
	-lgstbase-1.0 \
	-lgstcontroller-1.0 \
	-lgstnet-1.0 \
	-lgstparrot-1.0
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/gstreamer-1.0
LOCAL_CONFIG_FILES := 1
sdk.gstreamer.config := $(LOCAL_PATH)/config/gstreamer.config
$(call load-config)
LOCAL_LIBRARIES := glib
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_HOST_MODULE := msghub-gen
LOCAL_REVISION := bd0a2dca81533df9a80285db53063643bd81c66a
LOCAL_REVISION_DESCRIBE := bd0a2dc
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libmsghub
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_HOST_MODULE := protobuf
LOCAL_REVISION := 72770aed22c6fd3ec2ad3a89397cb0b5d307b35b
LOCAL_REVISION_DESCRIBE := 72770ae
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/protobuf
LOCAL_EXPORT_LDLIBS := \
	-lprotobuf
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_HOST_MODULE := protobuf-c
LOCAL_DESCRIPTION := Protocol Buffers implementation in C
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 6aaf18e750f108fea31bea8d82765b9d5574676e
LOCAL_REVISION_DESCRIBE := 6aaf18e
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/protobuf-c
LOCAL_LIBRARIES := host.protobuf
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_HOST_MODULE := python
LOCAL_DESCRIPTION := Python metapackage to select correct underlying module
LOCAL_CATEGORY_PATH := python
LOCAL_REVISION := 01828a499a3c89c74561ab9757d08fd281ca2ef0
LOCAL_REVISION_DESCRIBE := 01828a4
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/python/python3
LOCAL_LIBRARIES := host.python3
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_HOST_MODULE := python-setuptools
LOCAL_DESCRIPTION := Easily download, build, install, upgrade, and uninstall Python packages
LOCAL_CATEGORY_PATH := python
LOCAL_REVISION := 72bc3c2a5339cf6c821c0f671dd310f8246394fe
LOCAL_REVISION_DESCRIBE := 72bc3c2
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/python/python-packages
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_HOST_MODULE := python3
LOCAL_DESCRIPTION := Python package for host build
LOCAL_CATEGORY_PATH := python
LOCAL_REVISION := 01828a499a3c89c74561ab9757d08fd281ca2ef0
LOCAL_REVISION_DESCRIBE := 01828a4
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/python/python3
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := json
LOCAL_DESCRIPTION := JSON-C
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 274ef8be76797d026b18597bc301ac1b383cb2fa
LOCAL_REVISION_DESCRIBE := json-c-0.15-20200726-6-g274ef8b
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/json
LOCAL_EXPORT_LDLIBS := \
	-ljson-c
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libarsdk-pb
LOCAL_DESCRIPTION := Protobuf types for AR-SDK
LOCAL_REVISION := dc0672bb8214f85c3c07ce4194c99d38ee9bb899
LOCAL_REVISION_DESCRIBE := dc0672b
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/arsdk-xml
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libarsdk-pb/gen
LOCAL_LIBRARIES := parrot-protobuf-extensions-cpp protobuf
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libarsdk-pb.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libarsdk-pbc
LOCAL_DESCRIPTION := Protobuf types for AR-SDK
LOCAL_REVISION := dc0672bb8214f85c3c07ce4194c99d38ee9bb899
LOCAL_REVISION_DESCRIBE := dc0672b
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/arsdk-xml
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libarsdk-pbc/gen
LOCAL_LIBRARIES := libprotobuf-c-base parrot-protobuf-extensions-c protobuf-c
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libarsdk-pbc.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libarsdk-pbpy
LOCAL_DESCRIPTION := Protobuf types for AR-SDK
LOCAL_REVISION := dc0672bb8214f85c3c07ce4194c99d38ee9bb899
LOCAL_REVISION_DESCRIBE := dc0672b
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/arsdk-xml
LOCAL_LIBRARIES := parrot-protobuf-extensions-py protobuf-python
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libc
LOCAL_REVISION := 575c6cefb58b5bd787332bbaffc7d1d7573a1023
LOCAL_REVISION_DESCRIBE := alchemy-1.3.4-159-g575c6ce
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/build/Alchemy
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libcam-controller-pb
LOCAL_DESCRIPTION := Protobuf types for cam-controller
LOCAL_CATEGORY_PATH := camcontroller
LOCAL_REVISION := 148f15ea98896eb21f63123a3a0d54790748b955
LOCAL_REVISION_DESCRIBE := 148f15e
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/cam_controller
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libcam-controller-pb/gen
LOCAL_LIBRARIES := protobuf
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libcam-controller-pb.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcolibrylite-pb
LOCAL_DESCRIPTION := Protobuf types for libcolibrylite
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 5b39951eb43037919277398965643964e84d0c0a
LOCAL_REVISION_DESCRIBE := minidrones-before-removal-from-master-20171226-2572-g5b39951eb
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/aftermarket/Mykonos3/libColibry
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libcolibrylite-pb/gen
LOCAL_LIBRARIES := protobuf
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libcolibrylite-pb.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libconfig
LOCAL_DESCRIPTION := Simple library for processing structured configuration files
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 68aea35ed67e989e6b7ceb31c9786c6c419eaeff
LOCAL_REVISION_DESCRIBE := 68aea35
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/libconfig
LOCAL_EXPORT_LDLIBS := \
	-lconfig \
	-lconfig++
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libconfigreader
LOCAL_DESCRIPTION := C++ wrapper over libconfig
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 5c7aea0734fa43abfa02b249182cc529d5910507
LOCAL_REVISION_DESCRIBE := 5c7aea0
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libconfig-reader
LOCAL_EXPORT_LDLIBS := \
	-lconfig++
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := eigen libconfig
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libconfigreader.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libdrone-controller-msghub
LOCAL_DESCRIPTION := Msghub integration of protobuf types for drone-controller
LOCAL_CATEGORY_PATH := drone-controller
LOCAL_REVISION := 3fb12f270d44ed8ddd11570858cf27ce7a074d57
LOCAL_REVISION_DESCRIBE := 3fb12f2
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/drone_controller
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libdrone-controller-msghub/gen
LOCAL_LIBRARIES := libdrone-controller-pb libmsghub protobuf
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libdrone-controller-msghub.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libdrone-controller-pb
LOCAL_DESCRIPTION := Protobuf types for drone-controller
LOCAL_CATEGORY_PATH := drone-controller
LOCAL_REVISION := 3fb12f270d44ed8ddd11570858cf27ce7a074d57
LOCAL_REVISION_DESCRIBE := 3fb12f2
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/drone_controller
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libdrone-controller-pb/gen
LOCAL_LIBRARIES := protobuf libcolibrylite-pb
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libdrone-controller-pb.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libflightplan-pb
LOCAL_DESCRIPTION := Protocol buffer and wrapper for flightplan messages
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 0e878c62d10b9be5805dfc399f9597fd8416b830
LOCAL_REVISION_DESCRIBE := 0e878c6
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/tds/libflightplan
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libflightplan-pb/gen
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libflightplan-pb.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libflightplan-pb-helper
LOCAL_DESCRIPTION := Protobuf helper functions
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 0e878c62d10b9be5805dfc399f9597fd8416b830
LOCAL_REVISION_DESCRIBE := 0e878c6
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/tds/libflightplan
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libflightplan-pb-helper/gen
LOCAL_LIBRARIES := eigen libflightplan-pb libguidance-utils libparrot-physics
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libflightplan-pb-helper.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libfutils
LOCAL_DESCRIPTION := c utility functions
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 6c85d468bb649828d351b5f3738ae6fc27af6546
LOCAL_REVISION_DESCRIBE := 6c85d46
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libfutils
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libfutils.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libguidance-msghub
LOCAL_DESCRIPTION := Msghub helpers for guidance
LOCAL_CATEGORY_PATH := guidance
LOCAL_REVISION := 0cdb3d68548b4ff8362caec42c2f6c91b2f91d62
LOCAL_REVISION_DESCRIBE := 0cdb3d6
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/guidance
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libguidance-msghub/gen
LOCAL_LIBRARIES := protobuf libguidance-pb libmsghub
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libguidance-msghub.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libguidance-pb
LOCAL_DESCRIPTION := Protobuf types for guidance
LOCAL_CATEGORY_PATH := guidance
LOCAL_REVISION := 0cdb3d68548b4ff8362caec42c2f6c91b2f91d62
LOCAL_REVISION_DESCRIBE := 0cdb3d6
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/guidance
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libguidance-pb/gen
LOCAL_LIBRARIES := libcam-controller-pb libcolibrylite-pb libdrone-controller-msghub libdrone-controller-pb libflightplan-pb libflightplan-pb-helper protobuf
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libguidance-pb.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libguidance-plugin
LOCAL_CATEGORY_PATH := guidance
LOCAL_REVISION := 0cdb3d68548b4ff8362caec42c2f6c91b2f91d62
LOCAL_REVISION_DESCRIBE := 0cdb3d6
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/guidance
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := libguidance-msghub libguidance-pb eigen libguidance-utils
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libguidance-plugin.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libguidance-utils
LOCAL_DESCRIPTION := Types and utils shared by guidance libs
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 0cdb3d68548b4ff8362caec42c2f6c91b2f91d62
LOCAL_REVISION_DESCRIBE := 0cdb3d6
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/guidance
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := eigen
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libguidance-utils.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libh264
LOCAL_DESCRIPTION := H.264 bitstream reader/writer library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := afe45a9f9e2c102f5bee05ea7476a332cbab109d
LOCAL_REVISION_DESCRIBE := afe45a9
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libh264
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libh264.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libh265
LOCAL_DESCRIPTION := H.265 bitstream reader/writer library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := a8285825814bfdb6894832f7a77b463504ceaf54
LOCAL_REVISION_DESCRIBE := a828582
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libh265
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libh265.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libmsghub
LOCAL_DESCRIPTION := Message routing and dispatching using protobuf messages and libpomp
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := bd0a2dca81533df9a80285db53063643bd81c66a
LOCAL_REVISION_DESCRIBE := bd0a2dc
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libmsghub
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libmsghub/gen \
	$(LOCAL_PATH)/usr/include/libmsghub/gen
LOCAL_LIBRARIES := libpomp
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libmsghub.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libmsghub-py
LOCAL_DESCRIPTION := Python implementation of libmsghub
LOCAL_CATEGORY_PATH := msghub
LOCAL_REVISION := bd0a2dca81533df9a80285db53063643bd81c66a
LOCAL_REVISION_DESCRIBE := bd0a2dc
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libmsghub
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libparrot-physics
LOCAL_DESCRIPTION := Physics utility library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 2d5865f467984785287a08d2a70cc39369e99a29
LOCAL_REVISION_DESCRIBE := 2d5865f
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libparrot-physics
LOCAL_EXPORT_CXXFLAGS := -std=c++11
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := eigen
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libparrot-physics.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libpomp
LOCAL_DESCRIPTION := Printf Oriented Message Protocol
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 6d7ac50d6775d54112297578074df30aba6bd3a2
LOCAL_REVISION_DESCRIBE := fc60x0-libpomp-0.1.0-lib-234-g6d7ac50
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/libpomp
LOCAL_EXPORT_CUSTOM_VARIABLES := \
	LIBPOMP_HEADERS=$(LOCAL_PATH)/include/libpomp.h;;
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libpomp.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libpomp-py
LOCAL_DESCRIPTION := Python binding for libpomp
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 6d7ac50d6775d54112297578074df30aba6bd3a2
LOCAL_REVISION_DESCRIBE := fc60x0-libpomp-0.1.0-lib-234-g6d7ac50
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/libpomp
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libprotobuf-c-base
LOCAL_DESCRIPTION := Google Protocol Buffers basics in C
LOCAL_REVISION := 6aaf18e750f108fea31bea8d82765b9d5574676e
LOCAL_REVISION_DESCRIBE := 6aaf18e
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/protobuf-c
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/libprotobuf-c-base/gen
LOCAL_LIBRARIES := protobuf-base protobuf-c
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libprotobuf-c-base.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libputils
LOCAL_DESCRIPTION := Parrot utils library (a few repackaged Android cutils)
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := b106e8be98ea4af09d080f10dfd777eaeebc36ee
LOCAL_REVISION_DESCRIBE := b106e8b
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/libputils
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libputils.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libputils-py
LOCAL_DESCRIPTION := Python binding for libputils
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := b106e8be98ea4af09d080f10dfd777eaeebc36ee
LOCAL_REVISION_DESCRIBE := b106e8b
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/libputils
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libtelemetry
LOCAL_DESCRIPTION := Telemetry library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 68cd1e616356f21b8a3cd6021fc2a7bbb14c379f
LOCAL_REVISION_DESCRIBE := 68cd1e6
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/telemetry
LOCAL_EXPORT_CXXFLAGS := -std=c++0x -D__STDC_FORMAT_MACROS
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libtelemetry.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libulog
LOCAL_DESCRIPTION := A minimalistic logging library derived from Android logger
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := cbe353e09693f835660fa27b1c2357440d26bbbe
LOCAL_REVISION_DESCRIBE := ulog-1.10
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/ulog
LOCAL_EXPORT_CUSTOM_VARIABLES := \
	LIBULOG_HEADERS=$(LOCAL_PATH)/include/ulog.h:$(LOCAL_PATH)/include/ulograw.h;;
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libulog.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libulog-glib
LOCAL_DESCRIPTION := Redirect glib logging to ulog
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := cbe353e09693f835660fa27b1c2357440d26bbbe
LOCAL_REVISION_DESCRIBE := ulog-1.10
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/ulog
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libulog-glib.a
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libulog-gst
LOCAL_DESCRIPTION := Redirect gstreamer logging to ulog
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := cbe353e09693f835660fa27b1c2357440d26bbbe
LOCAL_REVISION_DESCRIBE := ulog-1.10
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/pulsar/ulog
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libulog-gst.a
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libvideo-acquisition
LOCAL_DESCRIPTION := Video acquisition library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 4d7798facb1490e7bfd9e16cc36f7b3e8cb0df04
LOCAL_REVISION_DESCRIBE := 4d7798f
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libvideo-acquisition
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := libconfig libvideo-defs
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libvideo-acquisition.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libvideo-defs
LOCAL_DESCRIPTION := Video definitions library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := eafa3cb752457f16b10cc068698fafc6538b35b6
LOCAL_REVISION_DESCRIBE := eafa3cb
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libvideo-defs
LOCAL_EXPORT_CUSTOM_VARIABLES := \
	LIBVIDEODEFS_HEADERS=$(LOCAL_PATH)/include/video-defs/vdefs.h;;
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := libh264 libh265
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libvideo-defs.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libvideo-ipc
LOCAL_DESCRIPTION := Video IPC library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 39200f4117928a80969dd3f28b6c9220c71f6662
LOCAL_REVISION_DESCRIBE := 39200f4
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libvideo-ipc
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := libpomp libvideo-acquisition libvideo-defs
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libvideo-ipc.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libvideo-ipc-client-config
LOCAL_DESCRIPTION := Video IPC client configuration library
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 39200f4117928a80969dd3f28b6c9220c71f6662
LOCAL_REVISION_DESCRIBE := 39200f4
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/libvideo-ipc
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_LIBRARIES := libpomp libvideo-acquisition
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := libvideo-ipc-client-config.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := opencv4
LOCAL_DESCRIPTION := open source computer vision library (version 4)
LOCAL_CATEGORY_PATH := tds/image
LOCAL_REVISION := 234c87fd9349bb1a691e3c5b83b67f69cb3efb29
LOCAL_REVISION_DESCRIBE := 234c87fd9
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/tds/image/OpenCV
LOCAL_EXPORT_LDLIBS := \
	-lopencv4_world
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/opencv4
LOCAL_CONFIG_FILES := 1
sdk.opencv4.config := $(LOCAL_PATH)/config/opencv4.config
$(call load-config)
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := parrot-protobuf-extensions-c
LOCAL_DESCRIPTION := Parrot SDKs common protobuf extensions generated C code
LOCAL_CATEGORY_PATH := libs/protobuf
LOCAL_REVISION := 06f6d35e39a964e7c996aff63ccd35b5c15ba415
LOCAL_REVISION_DESCRIBE := 06f6d35
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/protobuf-extensions
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/parrot-protobuf-extensions-c/gen
LOCAL_LIBRARIES := protobuf-c libprotobuf-c-base
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := parrot-protobuf-extensions-c.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := parrot-protobuf-extensions-cpp
LOCAL_DESCRIPTION := Parrot SDKs common protobuf extensions generated C++ code
LOCAL_CATEGORY_PATH := libs/protobuf
LOCAL_REVISION := 06f6d35e39a964e7c996aff63ccd35b5c15ba415
LOCAL_REVISION_DESCRIBE := 06f6d35
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/protobuf-extensions
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/parrot-protobuf-extensions-cpp/gen
LOCAL_LIBRARIES := protobuf
LOCAL_SDK := $(LOCAL_PATH)
LOCAL_DESTDIR := usr/lib
LOCAL_MODULE_FILENAME := parrot-protobuf-extensions-cpp.so
include $(BUILD_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := parrot-protobuf-extensions-py
LOCAL_DESCRIPTION := Parrot SDKs common protobuf extensions generated Python code
LOCAL_CATEGORY_PATH := libs/protobuf
LOCAL_REVISION := 06f6d35e39a964e7c996aff63ccd35b5c15ba415
LOCAL_REVISION_DESCRIBE := 06f6d35
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/protobuf-extensions
LOCAL_LIBRARIES := protobuf-python python
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := protobuf
LOCAL_DESCRIPTION := Protocol Buffers - Google data interchange format - Full Runtime
LOCAL_CATEGORY_PATH := libs/protobuf
LOCAL_REVISION := 72770aed22c6fd3ec2ad3a89397cb0b5d307b35b
LOCAL_REVISION_DESCRIBE := 72770ae
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/protobuf
LOCAL_EXPORT_CXXFLAGS := -std=c++11
LOCAL_EXPORT_LDLIBS := \
	-lprotobuf
LOCAL_LIBRARIES := protobuf-base
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := protobuf-base
LOCAL_DESCRIPTION := Protocol Buffers - Google data interchange format
LOCAL_CATEGORY_PATH := libs/protobuf
LOCAL_REVISION := 72770aed22c6fd3ec2ad3a89397cb0b5d307b35b
LOCAL_REVISION_DESCRIBE := 72770ae
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/protobuf
LOCAL_EXPORT_LDLIBS := \
	-lprotoc
LOCAL_CONFIG_FILES := 1
sdk.protobuf-base.config := $(LOCAL_PATH)/config/protobuf-base.config
$(call load-config)
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := protobuf-c
LOCAL_DESCRIPTION := Protocol Buffers implementation in C
LOCAL_CATEGORY_PATH := libs
LOCAL_REVISION := 6aaf18e750f108fea31bea8d82765b9d5574676e
LOCAL_REVISION_DESCRIBE := 6aaf18e
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/protobuf-c
LOCAL_EXPORT_LDLIBS := \
	-lprotobuf-c
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := protobuf-python
LOCAL_DESCRIPTION := Protocol Buffers - Google data interchange format - Python Runtime
LOCAL_CATEGORY_PATH := libs/protobuf
LOCAL_REVISION := 72770aed22c6fd3ec2ad3a89397cb0b5d307b35b
LOCAL_REVISION_DESCRIBE := 72770ae
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/drones/external/protobuf
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := python
LOCAL_DESCRIPTION := Python metapackage to select correct underlying module
LOCAL_CATEGORY_PATH := python
LOCAL_REVISION := 01828a499a3c89c74561ab9757d08fd281ca2ef0
LOCAL_REVISION_DESCRIBE := 01828a4
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/python/python3
LOCAL_LIBRARIES := python3
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := python3
LOCAL_DESCRIPTION := Python package for host build
LOCAL_CATEGORY_PATH := python
LOCAL_REVISION := 01828a499a3c89c74561ab9757d08fd281ca2ef0
LOCAL_REVISION_DESCRIBE := 01828a4
LOCAL_REVISION_URL := ssh://gerrit-doc.parrot.biz/python/python3
LOCAL_EXPORT_LDLIBS := \
	-lpython3.7m
LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/usr/include/python3.7m
LOCAL_CONFIG_FILES := 1
sdk.python3.config := $(LOCAL_PATH)/config/python3.config
$(call load-config)
LOCAL_SDK := $(LOCAL_PATH)
include $(BUILD_PREBUILT)

define arsdkgen-macro

         
# Setup some internal variables
arsdkgen_python := arsdkgen.py $(if $(call streq,$(V),1),-v)
arsdkgen_generator_path := $1
arsdkgen_module_build_dir := $(call local-get-build-dir)
arsdkgen_out_dir := $(if $(call is-path-absolute,$2),$2,$$(arsdkgen_module_build_dir)/$2)
arsdkgen_done_file := $$(arsdkgen_module_build_dir)/$(LOCAL_MODULE)-arsdkgen.done
$(if $(wildcard $(arsdkgen-macro-path)/arsdkgen.py), arsdkgen_gen_files := $$(shell $(arsdkgen-macro-path)/$$(arsdkgen_python) -f -o $$(arsdkgen_out_dir) $1 -- $(subst $(colon),$(space),$3) || echo FAILED)
	, arsdkgen_gen_files := $$(shell $(HOST_OUT_STAGING)/usr/lib/arsdkgen/$$(arsdkgen_python) -f -o $$(arsdkgen_out_dir) $1 -- $(subst $(colon),$(space),$3) || echo FAILED)
)
$$(if $$(call streq,$$(arsdkgen_gen_files),FAILED),$$(error Failed to list files))

# Create a dependency between generated files and .done file with an empty
# command to make sure regeneration is correctly triggered to files
# depending on them
$$(arsdkgen_gen_files): $$(arsdkgen_done_file)
	$(empty)

# Actual generation rule
# The copy of xml is staging is done in 2 steps because several modules could use
# the same xml the move ensure atomicity of the copy.
$$(arsdkgen_done_file): $(addprefix $(HOST_OUT_STAGING)/usr/lib/arsdkgen/,$(arsdkgen_files))
$$(arsdkgen_done_file): PRIVATE_OUT_DIR := $$(arsdkgen_out_dir)
$$(arsdkgen_done_file): .FORCE
	@echo "$$(PRIVATE_MODULE): Generating arsdk files"
ifneq ("$(arsdkgen_files)", "")
	$(Q) cd $(HOST_OUT_STAGING)/usr/lib/arsdkgen; rm -f $$$$(grep -Fxv "$$$$(echo $(arsdkgen_files) | xargs -n 1)" <<< "$$$$(ls xml | sed 's:^:xml/:')")
endif
	$(Q) $(HOST_OUT_STAGING)/usr/lib/arsdkgen/$$(arsdkgen_python) -o $$(PRIVATE_OUT_DIR) $1 -- $(subst $(colon),$(space),$3)
	@mkdir -p $$(dir $$@)
	@touch $$@

# Update alchemy variables for the module
LOCAL_CLEAN_FILES += $$(arsdkgen_done_file) $(if $(call is-path-absolute,$2),$(empty),$$(arsdkgen_gen_files))
LOCAL_EXPORT_PREREQUISITES += $$(arsdkgen_gen_files) $$(arsdkgen_done_file)
LOCAL_PREREQUISITES += $$(arsdkgen_gen_files) $$(arsdkgen_done_file)
LOCAL_DEPENDS_HOST_MODULES += host.arsdkgen
LOCAL_C_INCLUDES += $$(arsdkgen_out_dir)
LOCAL_DONE_FILES += $$(notdir $$(arsdkgen_done_file))

     
endef
$(call local-register-custom-macro,arsdkgen-macro)
define pybinding-macro

         
# - The call to TARGET_CC is to extract default incude directories
# - We extract other includes and flag from the alchemy generated file objects.flags
# - We force -fno-unsigned-char to make sure the binding uses ctype.c_char
#   for the type char even on arm where it is supposed to be unsigned
#   This assumes that the library does not depend on this...
# - the define "__PYBINDING_MACRO__" is passed to the headers in the goal of
#   adapting some code parts for python when necessary.


PRIVATE_SO_FILES = $(shell echo "$4" | sed "s#:# #g")
$(call local-get-build-dir)/$1.py: PRIVATE_SO_FILES := $$(PRIVATE_SO_FILES)
$(call local-get-build-dir)/$1.py: PRIVATE_CTYPESLIB_STAGED_FILES := $$(PRIVATE_CTYPESLIB_STAGED_FILES)
$(call local-get-build-dir)/$1.py: PRIVATE_SRC_FILES = $$(foreach header, $$(shell echo "$3" | sed "s#:# #g"), $$(if $$(findstring undefined,$$(origin PRIVATE_CUSTOM_$$(header))), $$(header), $$(shell echo $$(PRIVATE_CUSTOM_$$(header)) | sed "s#:# #g") ) )
$(call local-get-build-dir)/$1.py: PRIVATE_OBJECT_FLAGS := $$(foreach lib, $$(shell echo "$2" | sed "s#:# #g"), $$(call module-get-build-dir,$$(lib))/$$(lib).objects.flags)
$(call local-get-build-dir)/$1.py: $$(PRIVATE_CTYPESLIB_STAGED_FILES) $(shell echo "$4" | sed "s#:# #g")
	@echo "$$(PRIVATE_MODULE): Generating $1 python binding"
	@echo "Private object flags: $$(PRIVATE_OBJECT_FLAGS)"
	@echo "Private so files: $$(PRIVATE_SO_FILES)"

	$(Q) PYTHONPATH=$(HOST_OUT_STAGING)/usr/lib/python/site-packages $(HOST_OUT_STAGING)/usr/lib/python/site-packages/ctypeslib/clang2py.py --kind acdefstu $$(PRIVATE_SRC_FILES) $$$$(echo $$(PRIVATE_SO_FILES) | tr ' ' '\n' | sed -E 's/^(.+)/-l \1/') --target=$(if $(call streq,$(TARGET_ARCH),x64),x86_64,$(TARGET_ARCH)) -o $$@ --clang-args=" $$$$(echo | $(TARGET_CC) $(TARGET_GLOBAL_CFLAGS) -E -Wp,-v - 2>&1 | grep '^ /' | sed -E 's/^ (.+)/-I\1/' | tr '\n' ' ') $$$$(sed -n -e 's/PRIVATE_C_INCLUDES :=//p' $$(PRIVATE_OBJECT_FLAGS) | tr ' ' '\n' | sed -E 's/^(.+)/-I\1/') $$$$(sed -n -e 's/TARGET_GLOBAL_C_INCLUDES :=//p' $$(PRIVATE_OBJECT_FLAGS) | tr ' ' '\n' | sed -E 's/^(.+)/-I\1/') $$$$(sed -n -e 's/PRIVATE_GLOBAL_CFLAGS :=//p' $$(PRIVATE_OBJECT_FLAGS)) $$$$(sed -n -e 's/PRIVATE_CFLAGS :=//p' $$(PRIVATE_OBJECT_FLAGS)) -D__PYBINDING_MACRO__=1 -fno-unsigned-char "

LOCAL_CLEAN_FILES += $(call local-get-build-dir)/$1.py
LOCAL_COPY_FILES += $(call local-get-build-dir)/$1.py:usr/lib/python/site-packages/
LOCAL_DEPENDS_HOST_MODULES += host.pybinding
LOCAL_DEPENDS_MODULES := python
LOCAL_PRIVATE_LIBRARIES += $(shell echo "$2" | sed "s#:# #g")

     
endef
$(call local-register-custom-macro,pybinding-macro)
define msghub-macro

         
msghub_in_file := $3
msghub_proto_path := $(call remove-trailing-slash,$(or $4,$(dir $3)))
msghub_out_subdir := $$(call remove-trailing-slash,$$(patsubst $$(msghub_proto_path)/%,%,$(dir $3)))

msghub_module_build_dir := $(call local-get-build-dir)
msghub_out_rootdir := $$(call remove-trailing-slash,$$(if $$(call is-path-absolute,$2),$2,$$(msghub_module_build_dir)/$2))
msghub_out_dir := $$(call remove-trailing-slash,$$(msghub_out_rootdir)/$$(msghub_out_subdir))
msghub_done_file := $$(msghub_module_build_dir)/$$(subst $(colon),_,$$(subst /,_,$$(call path-from-top,$$(msghub_in_file)))).$1.finished
msghub_dep_file := $$(msghub_module_build_dir)/$$(subst $(colon),_,$$(subst /,_,$$(call path-from-top,$$(msghub_in_file)))).$1.d

$(if $(call streq,$1,cpp), msghub_src_file := $$(addprefix $$(msghub_out_dir)/,$$(patsubst %.proto,%.msghub.cc,$(notdir $3))) $(endl) msghub_inc_file := $$(addprefix $$(msghub_out_dir)/,$$(patsubst %.proto,%.msghub.h,$(notdir $3))) $(endl) )
$(if $(call streq,$1,c), msghub_src_file := $$(addprefix $$(msghub_out_dir)/,$$(patsubst %.proto,%.msghub-c.c,$(notdir $3))) $(endl) msghub_inc_file := $$(addprefix $$(msghub_out_dir)/,$$(patsubst %.proto,%.msghub-c.h,$(notdir $3))) $(endl) )
$(if $(call streq,$1,python), msghub_src_file := $$(addprefix $$(msghub_out_dir)/,$$(patsubst %.proto,%_msghub.py,$(notdir $3))) $(endl) msghub_inc_file := $(empty) $(endl) )

msghub_gen_files := $$(msghub_src_file) $$(msghub_inc_file)

# Create a dependency between generated files and .done file with an empty
# command to make sure regeneration is correctly triggered to files
# depending on them
$$(msghub_gen_files): $$(msghub_done_file)
	$(empty)

# Actual generation rule
$$(msghub_done_file): PRIVATE_OUT_ROOTDIR := $$(msghub_out_rootdir)
$$(msghub_done_file): PRIVATE_PROTO_PATH := $$(msghub_proto_path)
$$(msghub_done_file): PRIVATE_PROTO_SRC_FILE := $$(msghub_src_file)
$$(msghub_done_file): PRIVATE_PROTO_OUT_CP_PROTO := $$(msghub_out_cp_proto)
$$(msghub_done_file): PRIVATE_DEP_FILE := $$(msghub_dep_file)

$$(msghub_done_file): $(HOST_OUT_STAGING)/usr/lib/msghub/msghub_gen_$1.py
$$(msghub_done_file): $$(msghub_in_file)
	$$(call print-banner1,"Generating",$$(call path-from-top,$$(PRIVATE_PROTO_SRC_FILE)),$$(call path-from-top,$3))
	@mkdir -p $$(PRIVATE_OUT_ROOTDIR)

	$(Q) $(HOST_OUT_STAGING)/usr/bin/protoc --plugin=protoc-gen-custom=$(HOST_OUT_STAGING)/usr/lib/msghub/msghub_gen_$1.py --custom_out=$$(PRIVATE_OUT_ROOTDIR) --proto_path=$$(PRIVATE_PROTO_PATH) --proto_path=$(TARGET_OUT_STAGING)/usr/share/protobuf $(foreach __dir,$(TARGET_SDK_DIRS), $(if $(wildcard $(__dir)/usr/share/protobuf), --proto_path=$(__dir)/usr/share/protobuf ) ) --dependency_out=$$(PRIVATE_DEP_FILE) $3

#	Add a license file for generated code
	@echo "Generated code." > $$(PRIVATE_OUT_ROOTDIR)/.MODULE_LICENSE_BSD

	@mkdir -p $$(dir $$@)
	@touch $$@

-include $$(msghub_dep_file)

# Update either LOCAL_SRC_FILES or LOCAL_GENERATED_SRC_FILES
$(if $(call strneq,$1,python), $(if $(call is-path-absolute,$2), LOCAL_SRC_FILES += $$(patsubst $$(LOCAL_PATH)/%,%,$$(protoc_src_file)) , LOCAL_GENERATED_SRC_FILES += $$(patsubst $$(msghub_module_build_dir)/%,%,$$(msghub_src_file)) ))

# Update alchemy variables for the module
LOCAL_CXXFLAGS += -std=c++11
LOCAL_CLEAN_FILES += $$(msghub_done_file) $$(msghub_gen_files)
LOCAL_EXPORT_PREREQUISITES += $$(msghub_gen_files) $$(msghub_done_file)
LOCAL_DEPENDS_HOST_MODULES += host.msghub-gen host.protobuf

     
endef
$(call local-register-custom-macro,msghub-macro)
define mavgen-macro

         
# Setup some internal variables
mavgen_xml_file := $3
mavgen_module_build_dir := $(call local-get-build-dir)
mavgen_out_dir := $(if $(call is-path-absolute,$2),$2,$$(mavgen_module_build_dir)/$2)
mavgen_done_file := $$(mavgen_module_build_dir)/$$(notdir $$(mavgen_xml_file)).done
mavgen_dep_file := $$(mavgen_module_build_dir)/$$(notdir $$(mavgen_xml_file)).d

# Actual generation rule
# The copy of xml is staging is done in 2 steps because several modules could use
# the same xml the move ensure atomicity of the copy.
$$(mavgen_done_file): PRIVATE_OUT_DIR := $$(mavgen_out_dir)/mavlink
$$(mavgen_done_file): PRIVATE_DEP_FILE := $$(mavgen_dep_file)
$$(mavgen_done_file): $$(mavgen_xml_file) $(LOCAL_PATH)/atom.mk
	@echo "$$(PRIVATE_MODULE): Generating mavlink files from $$(call path-from-top,$3)"
	$(Q) cd $(HOST_OUT_STAGING)/usr/lib/mavgen && python3 -m pymavlink.tools.mavgen --wire-protocol=2.0 --lang $1 -o $$(PRIVATE_OUT_DIR) $3
	@mkdir -p $(TARGET_OUT_STAGING)/usr/share/mavlink
	$(Q) cp -af $3 $(TARGET_OUT_STAGING)/usr/share/mavlink/$(notdir $3).$$(PRIVATE_MODULE)
	$(Q) mv -f $(TARGET_OUT_STAGING)/usr/share/mavlink/$(notdir $3).$$(PRIVATE_MODULE) $(TARGET_OUT_STAGING)/usr/share/mavlink/$(notdir $3)
	@mkdir -p $$(dir $$@)
	@:>$$(PRIVATE_DEP_FILE)
	@for header in $$$$(find $$(PRIVATE_OUT_DIR) -name '*.h'); do echo "$$$${header}: $$@" >> $$(PRIVATE_DEP_FILE); echo -e "\t@:" >> $$(PRIVATE_DEP_FILE); done
	@touch $$@
	@mkdir -p $(TARGET_OUT_BUILD)/mavlink/wireshark/plugins
	$(Q) cd $(HOST_OUT_STAGING)/usr/lib/mavgen && python3 -m pymavlink.tools.mavgen --lang=WLua -o $(TARGET_OUT_BUILD)/mavlink/wireshark/plugins/mymavlink.lua $3
-include $$(mavgen_dep_file)

# Update alchemy variables for the module
LOCAL_CLEAN_FILES += $$(mavgen_done_file) $$(mavgen_dep_file)
LOCAL_EXPORT_PREREQUISITES += $$(mavgen_done_file)
LOCAL_DEPENDS_HOST_MODULES += host.mavgen
LOCAL_C_INCLUDES += $$(mavgen_out_dir)

     
endef
$(call local-register-custom-macro,mavgen-macro)
define luajit-macro

         
# Setup some internal variables
luajit_input := $1
luajit_build_dir := $(call local-get-build-dir)
luajit_cdef_file := $$(luajit_build_dir)/$(LOCAL_MODULE).cdef
luajit_dep_file := $$(luajit_build_dir)/$(LOCAL_MODULE).cdef.d

# Actual generation rule
# 4 '$' are needed to escape '$' in bash (macro is evaluated 2 times)
$$(luajit_cdef_file): PRIVATE_INPUT := $$(luajit_input)
$$(luajit_cdef_file):
	@echo "$$(PRIVATE_MODULE): Generating luajit binding"
	@mkdir -p $$(dir $$@)
	@( if [ -d "$$(PRIVATE_INPUT)" ]; then headers=$$$$(find $$(PRIVATE_INPUT) -name "*.h"); else headers="$$(subst |,$(space),$$(PRIVATE_INPUT))"; fi; rm -f $$@.tmp.h; for header in $$$${headers}; do echo "#include <$$$${header}>" >> $$@.tmp.h; done; cat $$@.tmp.h | $(TARGET_CC) $(TARGET_GLOBAL_CFLAGS) $$(call normalize-c-includes-rel, $$(call module-get-listed-export, $$(call module-get-all-depends,$$(PRIVATE_MODULE)),C_INCLUDES)) -MMD -MP -MF $$@.d -MT $$@ -P -E - -o $$@; rm -f $$@.tmp.h; )
	$$(call fix-deps-file,$$@.d)
-include $$(luajit_dep_file)

# Update alchemy variables for the module
LOCAL_CLEAN_FILES += $$(luajit_cdef_file) $$(luajit_dep_file)
LOCAL_CUSTOM_TARGETS += $$(luajit_cdef_file)
LOCAL_COPY_FILES += $$(luajit_cdef_file):usr/share/$(LOCAL_MODULE)/

     
endef
$(call local-register-custom-macro,luajit-macro)
define protoc-c-macro

         # Setup some internal variables
protoc_c_in_file := $3
protoc_c_proto_path := $(call remove-trailing-slash,$(or $4,$(dir $3)))
# reproduce what -I/--proto_path does, so that we can have some sort of namespacing
protoc_c_out_subdir := $$(call remove-trailing-slash, $$(patsubst $$(protoc_c_proto_path)/%,%,$(dir $3)))

protoc_c_module_build_dir := $(call local-get-build-dir)
protoc_c_out := $$(call remove-trailing-slash,$$(if $$(call is-path-absolute,$2),$2,$$(protoc_c_module_build_dir)/$2))
protoc_c_out_dir := $$(call remove-trailing-slash,$$(protoc_c_out)/$$(protoc_c_out_subdir))
protoc_c_dep_file := $$(protoc_c_module_build_dir)/$$(subst $(colon),_,$$(subst /,_,$$(call path-from-top,$$(protoc_c_in_file)))).$1.d
protoc_c_done_file := $$(protoc_c_module_build_dir)/$$(subst $(colon),_,$$(subst /,_,$$(call path-from-top,$$(protoc_c_in_file)))).$1.done

# Directory where to copy the input .proto file
protoc_c_out_cp_proto := $$(if $$(protoc_c_out_subdir), $(TARGET_OUT_STAGING)/usr/share/protobuf/$$(protoc_c_out_subdir)/$(notdir $3), $(TARGET_OUT_STAGING)/usr/share/protobuf/$(notdir $3) )

# The C generation case is handled here (endl is to force new line even if macro
# requires single line)
$(if $(call streq,$1,c), protoc_c_src_files := $$(addprefix $$(protoc_c_out_dir)/,$$(patsubst %.proto,%.pb-c.c,$(notdir $3))) $(endl) protoc_c_inc_files := $$(addprefix $$(protoc_c_out_dir)/,$$(patsubst %.proto,%.pb-c.h,$(notdir $3))) $(endl) protoc_c_gen_files := $$(protoc_c_src_files) $$(protoc_c_inc_files) )

# Create a dependency between generated files and .done file with an empty
# command to make sure regeneration is correctly triggered to files
# depending on them
$$(protoc_c_gen_files): $$(protoc_c_done_file)
	$(empty)

# Actual generation rule
$$(protoc_c_done_file): PRIVATE_OUT_DIR := $$(protoc_c_out)
$$(protoc_c_done_file): PRIVATE_PROTO_PATH := $$(protoc_c_proto_path)
$$(protoc_c_done_file): PRIVATE_PROTO_SRC_FILES := $$(protoc_c_src_files)
$$(protoc_c_done_file): PRIVATE_PROTO_OUT_CP_PROTO := $$(protoc_c_out_cp_proto)
$$(protoc_c_done_file): PRIVATE_PROTO_DEP_FILE := $$(protoc_c_dep_file)

$$(protoc_c_done_file): PRIVATE_PROTOC_GEN_C_EXE := $(HOST_OUT_STAGING)/usr/bin/protoc-gen-c$(HOST_EXE_SUFFIX)

# Use built-in protoc compiler on windows
ifneq ("$(HOST_OS)","windows")
$$(protoc_c_done_file): PRIVATE_PROTOC_EXE := $(HOST_OUT_STAGING)/usr/bin/protoc$(HOST_EXE_SUFFIX)
else
$$(protoc_c_done_file): PRIVATE_PROTOC_EXE := $(shell which protoc$(HOST_EXE_SUFFIX))
endif

$$(protoc_c_done_file): $$(protoc_c_in_file)
	$$(call print-banner1,"Generating",$$(call path-from-top,$$(PRIVATE_PROTO_SRC_FILES)),$$(call path-from-top,$3))
	@mkdir -p $$(PRIVATE_OUT_DIR)
	$(Q) $$(PRIVATE_PROTOC_EXE) --plugin=protoc-gen-c=$$(PRIVATE_PROTOC_GEN_C_EXE) --$1_out=$$(PRIVATE_OUT_DIR) --proto_path=$$(PRIVATE_PROTO_PATH) --proto_path=$(TARGET_OUT_STAGING)/usr/share/protobuf $(foreach __dir,$(TARGET_SDK_DIRS), $(if $(wildcard $(__dir)/usr/share/protobuf), --proto_path=$(__dir)/usr/share/protobuf ) ) --dependency_out=$$(PRIVATE_PROTO_DEP_FILE) $3

#	Add a license file for generated code
	@echo "Generated code." > $$(PRIVATE_OUT_DIR)/.MODULE_LICENSE_BSD

#	Input file is in the form
#		a.cc a.h: c.proto d.proto ...
#	With potentially lines split with continuation lines '\'
#	We need to get the list of files after the ':' to generated a line of
#	this form for each dependency
#		c.proto:
#		d.proto:
#		....
#
#	Sed will see a single '$' for each '$$$$'.
#
#	The hard part is to be compatible with macos...
#
#	1: remove continuation lines and concatenates lines
#	2: remove everithinh before the ':'
#	3: split files one per line (the folowing sed fails on macos: 's/ */"\n"/g')
#	4: strip spaces on lines
#	5: remove empty lines
#	6: add ':' at the end of lines
	$(Q) sed -e ':x' -e '/\\$$$$/{N;bx' -e '}' -e 's/\\\n//g' -e 's/.*://' $$(PRIVATE_PROTO_DEP_FILE) | fmt -1 | sed -e 's/^ *//' -e '/^$$$$/d' -e 's/$$$$/:/' > $$(PRIVATE_PROTO_DEP_FILE).tmp

#	Add contents at the end of original file (with a new line before)
	@( echo ""; cat $$(PRIVATE_PROTO_DEP_FILE).tmp ) >> $$(PRIVATE_PROTO_DEP_FILE)
	@rm $$(PRIVATE_PROTO_DEP_FILE).tmp

#	The copy of .proto file is done via a temp copy and move to ensure atomicity
#	of copy in case of parallel copy of the same file
#	Use flock when possible to avoid race conditions in some mv implementations
	@if [ $$(PRIVATE_MODULE) != libprotobuf-c-base ]; then mkdir -p $$(dir $$(PRIVATE_PROTO_OUT_CP_PROTO)); fi
ifeq ("$(HOST_OS)","darwin")
	@if [ $$(PRIVATE_MODULE) != libprotobuf-c-base ]; then tmpfile=`mktemp $$(PRIVATE_BUILD_DIR)/tmp.XXXXXXXX`; cp -af $3 $$$${tmpfile}; mv -f $$$${tmpfile} $$(PRIVATE_PROTO_OUT_CP_PROTO); fi
else
	@if [ $$(PRIVATE_MODULE) != libprotobuf-c-base ]; then flock --wait 60 $$(dir $$(PRIVATE_PROTO_OUT_CP_PROTO)) cp -af $3 $$(PRIVATE_PROTO_OUT_CP_PROTO); fi
endif

	@mkdir -p $$(dir $$@)
	@touch $$@

-include $$(protoc_c_dep_file)

# Update either LOCAL_SRC_FILES or LOCAL_GENERATED_SRC_FILES
$(if $(call is-path-absolute,$2), LOCAL_SRC_FILES += $$(patsubst $$(LOCAL_PATH)/%,%,$$(protoc_c_src_files)) , LOCAL_GENERATED_SRC_FILES += $$(patsubst $$(protoc_c_module_build_dir)/%,%,$$(protoc_c_src_files)) )

# Update alchemy variables for the module
LOCAL_CLEAN_FILES += $$(protoc_c_done_file) $$(protoc_c_out_cp_proto) $$(protoc_dep_file)
LOCAL_EXPORT_PREREQUISITES += $$(protoc_c_gen_files) $$(protoc_c_done_file)
LOCAL_DEPENDS_HOST_MODULES += host.protobuf-c

     
endef
$(call local-register-custom-macro,protoc-c-macro)
define protoc-macro

         
# Setup some internal variables
protoc_in_file := $3
protoc_proto_path := $(call remove-trailing-slash,$(or $4,$(dir $3)))
# reproduce what -I/--proto_path does, so that we can have some sort of namespacing
protoc_out_subdir := $$(call remove-trailing-slash,$$(patsubst $$(protoc_proto_path)/%,%,$(dir $3)))

protoc_module_build_dir := $(call local-get-build-dir)
protoc_out_rootdir := $$(call remove-trailing-slash,$$(if $$(call is-path-absolute,$2),$2,$$(protoc_module_build_dir)/$2))
protoc_out_dir := $$(call remove-trailing-slash,$$(protoc_out_rootdir)/$$(protoc_out_subdir))
protoc_dep_file := $$(protoc_module_build_dir)/$$(subst $(colon),_,$$(subst /,_,$$(call path-from-top,$$(protoc_in_file)))).$1.d
protoc_aux_file := $$(protoc_module_build_dir)/$$(subst $(colon),_,$$(subst /,_,$$(call path-from-top,$$(protoc_in_file)))).$1.d.tmp
protoc_done_file := $$(protoc_module_build_dir)/$$(subst $(colon),_,$$(subst /,_,$$(call path-from-top,$$(protoc_in_file)))).$1.done

# Directory where to copy the input .proto file
protoc_out_cp_proto := $$(if $$(protoc_out_subdir), $(TARGET_OUT_STAGING)/usr/share/protobuf/$$(protoc_out_subdir)/$(notdir $3), $(TARGET_OUT_STAGING)/usr/share/protobuf/$(notdir $3) )

# The CPP generation case is handled here (endl is to force new line even if macro
# requires single line)
$(if $(call streq,$1,cpp), protoc_src_file := $$(addprefix $$(protoc_out_dir)/,$$(patsubst %.proto,%.pb.cc,$(notdir $3))) $(endl) protoc_inc_file := $$(addprefix $$(protoc_out_dir)/,$$(patsubst %.proto,%.pb.h,$(notdir $3))) $(endl) )

# the Java generation case is handled here (endl is to force new line even if macro
# requires single line)
$(if $(call streq,$1,java), protoc_src_file := $$(addprefix $$(protoc_out_dir)/,$$(patsubst %.proto,%.java,$(notdir $3))) $(endl) protoc_inc_file := $(endl) )

# the Python generation case is handled here (endl is to force new line even if macro
# requires single line)
$(if $(call streq,$1,python), protoc_src_file := $$(addprefix $$(protoc_out_dir)/,$$(patsubst %.proto,%_pb2.py,$(notdir $3))) $(endl) protoc_inc_file := $(endl) )

protoc_gen_files := $$(protoc_src_file) $$(protoc_inc_file)

# Create a dependency between generated files and .done file with an empty
# command to make sure regeneration is correctly triggered to files
# depending on them
$$(protoc_gen_files): $$(protoc_done_file)
	$(empty)

# Actual generation rule
$$(protoc_done_file): PRIVATE_OUT_ROOTDIR := $$(protoc_out_rootdir)
$$(protoc_done_file): PRIVATE_PROTO_PATH := $$(protoc_proto_path)
$$(protoc_done_file): PRIVATE_PROTO_SRC_FILE := $$(protoc_src_file)
$$(protoc_done_file): PRIVATE_PROTO_OUT_CP_PROTO := $$(protoc_out_cp_proto)
$$(protoc_done_file): PRIVATE_PROTO_DEP_FILE := $$(protoc_dep_file)
$$(protoc_done_file): PRIVATE_PROTO_AUX_FILE := $$(protoc_aux_file)

ifeq ("$(HOST_OS)","windows")
$$(protoc_done_file): PRIVATE_PROTOC_EXE := protoc
else ifeq ("$(CONFIG_PROTOBUF_PACKAGE_PROTOC)","y")
$$(protoc_done_file): PRIVATE_PROTOC_EXE := $(HOST_OUT_STAGING)/usr/bin/protoc
else
$$(protoc_done_file): PRIVATE_PROTOC_EXE := protoc
endif

$$(protoc_done_file): $$(protoc_in_file) $$(PRIVATE_PROTOC_EXE)
	$$(call print-banner1,"Generating",$$(call path-from-top,$$(PRIVATE_PROTO_SRC_FILE)),$$(call path-from-top,$3))
	@mkdir -p $$(PRIVATE_OUT_ROOTDIR)

	$(Q) $$(PRIVATE_PROTOC_EXE) --$1_out=$$(PRIVATE_OUT_ROOTDIR) --proto_path=$$(PRIVATE_PROTO_PATH) --proto_path=$(TARGET_OUT_STAGING)/usr/share/protobuf $(foreach __dir,$(TARGET_SDK_DIRS), $(if $(wildcard $(__dir)/usr/share/protobuf), --proto_path=$(__dir)/usr/share/protobuf ) ) --dependency_out=$$(PRIVATE_PROTO_DEP_FILE) $3

#	Add a license file for generated code
	@echo "Generated code." > $$(PRIVATE_OUT_ROOTDIR)/.MODULE_LICENSE_BSD

#	Input file is in the form
#		a.cc a.h: c.proto d.proto ...
#	With potentially lines split with continuation lines '\'
#	We need to get the list of files after the ':' to generated a line of
#	this form for each dependency
#		c.proto:
#		d.proto:
#		....
#
#	Sed will see a single '$' for each '$$$$'.
#
#	The hard part is to be compatible with macos...
#
#	1: remove continuation lines and concatenates lines
#	2: remove everithinh before the ':'
#	3: split files one per line (the folowing sed fails on macos: 's/ */"\n"/g')
#	4: strip spaces on lines
#	5: remove empty lines
#	6: add ':' at the end of lines
	$(Q) sed -e ':x' -e '/\\$$$$/{N;bx' -e '}' -e 's/\\\n//g' -e 's/.*://' $$(PRIVATE_PROTO_DEP_FILE) | fmt -1 | sed -e 's/^ *//' -e '/^$$$$/d' -e 's/$$$$/:/' > $$(PRIVATE_PROTO_AUX_FILE)

#	Add contents at the end of original file (with a new line before)
	@( echo ""; cat $$(PRIVATE_PROTO_AUX_FILE) ) >> $$(PRIVATE_PROTO_DEP_FILE)
	@rm $$(PRIVATE_PROTO_AUX_FILE)

#	The copy of .proto file is done via a temp copy and move to ensure atomicity
#	of copy in case of parallel copy of the same file
#	Use flock when possible to avoid race conditions in some mv implementations
	@mkdir -p $$(dir $$(PRIVATE_PROTO_OUT_CP_PROTO))
ifeq ("$(HOST_OS)","darwin")
	@( tmpfile=`mktemp $$(PRIVATE_BUILD_DIR)/tmp.XXXXXXXX`; cp -af $3 $$$${tmpfile}; mv -f $$$${tmpfile} $$(PRIVATE_PROTO_OUT_CP_PROTO); )
else
	@flock --wait 60 $$(dir $$(PRIVATE_PROTO_OUT_CP_PROTO)) cp -af $3 $$(PRIVATE_PROTO_OUT_CP_PROTO)
endif
	@mkdir -p $$(dir $$@)
	@touch $$@

-include $$(protoc_dep_file)

# Update either LOCAL_SRC_FILES or LOCAL_GENERATED_SRC_FILES
$(if $(call strneq,$1,python), $(if $(call is-path-absolute,$2), LOCAL_SRC_FILES += $$(patsubst $$(LOCAL_PATH)/%,%,$$(protoc_src_file)) , LOCAL_GENERATED_SRC_FILES += $$(patsubst $$(protoc_module_build_dir)/%,%,$$(protoc_src_file)) ))

# Update alchemy variables for the module
LOCAL_CLEAN_FILES += $$(protoc_done_file) $$(protoc_gen_files) $$(protoc_out_cp_proto) $$(protoc_dep_file)
LOCAL_EXPORT_PREREQUISITES += $$(protoc_gen_files) $$(protoc_done_file)

ifneq ("$(HOST_OS)","windows")
LOCAL_DEPENDS_HOST_MODULES += host.protobuf
endif

     
endef
$(call local-register-custom-macro,protoc-macro)
