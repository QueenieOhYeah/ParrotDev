# GENERATED FILE, DO NOT MODIFY

.SUFFIXES:
%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
ALL :=
V ?= 0
ifeq ("$(V)","0")
  PRINT =
else
  PRINT = @echo $1
endif
.PHONY: all
all: do-all

ALL += file0
.PHONY: file0
file0:
	$(call PRINT,"Alchemy install: out/hello-pc/final/native-chroot-wrapper.sh")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/native-chroot-wrapper.sh" "/home/queenie/airsdk/out/hello-pc/final/native-chroot-wrapper.sh"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/native-chroot-wrapper.sh"

ALL += file1
.PHONY: file1
file1:
	$(call PRINT,"Alchemy install: out/hello-pc/final/native-wrapper.sh")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/native-wrapper.sh" "/home/queenie/airsdk/out/hello-pc/final/native-wrapper.sh"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/native-wrapper.sh"

ALL += file2
.PHONY: file2
file2:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/guidance/hello.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/guidance/hello.py" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/guidance/hello.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/guidance/hello.py"

ALL += file3
.PHONY: file3
file3:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/services/airsdk-hello-cv-service")
	@strip -o "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/services/airsdk-hello-cv-service" "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/services/airsdk-hello-cv-service"
	@chmod 0775 "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/services/airsdk-hello-cv-service"
	@touch -r "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/services/airsdk-hello-cv-service" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/services/airsdk-hello-cv-service"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/services/airsdk-hello-cv-service"

ALL += file4
.PHONY: file4
file4:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/__init__.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/fsup/__init__.py" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/__init__.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/__init__.py"

ALL += file5
.PHONY: file5
file5:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/mission.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/fsup/mission.py" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/mission.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/mission.py"

ALL += file6
.PHONY: file6
file6:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/flying/__init__.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/fsup/flying/__init__.py" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/flying/__init__.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/flying/__init__.py"

ALL += file7
.PHONY: file7
file7:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/flying/stage.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/fsup/flying/stage.py" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/flying/stage.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/flying/stage.py"

ALL += file8
.PHONY: file8
file8:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/ground/__init__.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/fsup/ground/__init__.py" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/ground/__init__.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/ground/__init__.py"

ALL += file9
.PHONY: file9
file9:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/ground/stage.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/missions/com.parrot.missions.samples.hello/payload/fsup/ground/stage.py" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/ground/stage.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/payload/fsup/ground/stage.py"

ALL += file10
.PHONY: file10
file10:
	$(call PRINT,"Alchemy install: out/hello-pc/final/etc/build.prop")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/etc/build.prop" "/home/queenie/airsdk/out/hello-pc/final/etc/build.prop"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/etc/build.prop"

ALL += file11
.PHONY: file11
file11:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-msghub.so")
	@strip -o "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-msghub.so" "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/libairsdk-hello-cv-service-msghub.so"
	@chmod 0775 "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-msghub.so"
	@touch -r "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/libairsdk-hello-cv-service-msghub.so" "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-msghub.so"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-msghub.so"

ALL += file12
.PHONY: file12
file12:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-pb.so")
	@strip -o "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-pb.so" "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/libairsdk-hello-cv-service-pb.so"
	@chmod 0775 "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-pb.so"
	@touch -r "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/libairsdk-hello-cv-service-pb.so" "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-pb.so"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/lib/libairsdk-hello-cv-service-pb.so"

ALL += file13
.PHONY: file13
file13:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/lib/python3.7/site-packages/.MODULE_LICENSE_BSD")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/python3.7/site-packages/.MODULE_LICENSE_BSD" "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/.MODULE_LICENSE_BSD"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/.MODULE_LICENSE_BSD"

ALL += file14
.PHONY: file14
file14:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/lib/python3.7/site-packages/samples/hello/cv_service/messages_pb2.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/python3.7/site-packages/samples/hello/cv_service/messages_pb2.py" "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/samples/hello/cv_service/messages_pb2.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/samples/hello/cv_service/messages_pb2.py"

ALL += file15
.PHONY: file15
file15:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/lib/python3.7/site-packages/samples/hello/guidance/messages_pb2.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/python3.7/site-packages/samples/hello/guidance/messages_pb2.py" "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/samples/hello/guidance/messages_pb2.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/samples/hello/guidance/messages_pb2.py"

ALL += file16
.PHONY: file16
file16:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/lib/python3.7/site-packages/parrot/missions/samples/hello/airsdk/messages_pb2.py")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/usr/lib/python3.7/site-packages/parrot/missions/samples/hello/airsdk/messages_pb2.py" "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/parrot/missions/samples/hello/airsdk/messages_pb2.py"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/lib/python3.7/site-packages/parrot/missions/samples/hello/airsdk/messages_pb2.py"

ALL += file17
.PHONY: file17
file17:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/share/protobuf/samples/hello/guidance/messages.proto")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/usr/share/protobuf/samples/hello/guidance/messages.proto" "/home/queenie/airsdk/out/hello-pc/final/usr/share/protobuf/samples/hello/guidance/messages.proto"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/share/protobuf/samples/hello/guidance/messages.proto"

ALL += file18
.PHONY: file18
file18:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/share/protobuf/samples/hello/cv-service/messages.proto")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/usr/share/protobuf/samples/hello/cv-service/messages.proto" "/home/queenie/airsdk/out/hello-pc/final/usr/share/protobuf/samples/hello/cv-service/messages.proto"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/share/protobuf/samples/hello/cv-service/messages.proto"

ALL += file19
.PHONY: file19
file19:
	$(call PRINT,"Alchemy install: out/hello-pc/final/usr/share/protobuf/parrot/missions/samples/hello/airsdk/messages.proto")
	@cp -af "/home/queenie/airsdk/out/hello-pc/staging/usr/share/protobuf/parrot/missions/samples/hello/airsdk/messages.proto" "/home/queenie/airsdk/out/hello-pc/final/usr/share/protobuf/parrot/missions/samples/hello/airsdk/messages.proto"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/usr/share/protobuf/parrot/missions/samples/hello/airsdk/messages.proto"

ALL += file20
.PHONY: file20
file20:
	$(call PRINT,"Alchemy install: out/hello-pc/final/missions/com.parrot.missions.samples.hello/mission.json")
	@cp -af "/home/queenie/airsdk/products/hello/common/config/../skel/missions/com.parrot.missions.samples.hello/mission.json" "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/mission.json"
	@chmod g-w,o-w "/home/queenie/airsdk/out/hello-pc/final/missions/com.parrot.missions.samples.hello/mission.json"

.PHONY: do-all
do-all: $(ALL)

