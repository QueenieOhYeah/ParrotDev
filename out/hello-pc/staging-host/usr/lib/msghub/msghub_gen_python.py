#!/usr/bin/env python3

# Copyright (C) 2019 Parrot Drones SAS
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#  * Redistributions of source code must retain the above copyright
#  notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#  notice, this list of conditions and the following disclaimer in
#  the documentation and/or other materials provided with the
#  distribution.
#  * Neither the name of Parrot nor the names
#  of its contributors may be used to endorse or promote products
#  derived from this software without specific prior written
#  permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
#  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
#  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
#  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
#  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  SUCH DAMAGE.

import os
import sys

from io import StringIO

from google.protobuf.compiler import plugin_pb2 as plugin
from google.protobuf.descriptor import FieldDescriptor
from google.protobuf.descriptor_pb2 import FileDescriptorProto, DescriptorProto


# Get some field numbers to construct source code location path
# See google/protobuf/descriptor.proto for more information
PATH_MESSAGE_TYPE = \
        FileDescriptorProto.DESCRIPTOR.fields_by_name["message_type"].number
PATH_FIELD = \
        DescriptorProto.DESCRIPTOR.fields_by_name["field"].number


def get_proto_package(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + "_pb2"
    else:
        return filename + "_pb2"

def get_msghub_python(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + "_msghub.py"
    else:
        return filename + "_msghub.py"

def get_comment(comment_map, comment_path):
    try:
        location = comment_map[",".join([str(x) for x in comment_path])]
        return location.leading_comments
    except KeyError:
        return ""


def generate_message_sender(comment_map, message_idx, message_type,
        package, kind, output, proto_package):
    output.write("class %sSender(msghub.MessageSender):\n" % kind)

    output.write("\tdef __init__(self):\n")
    output.write("\t\tsuper().__init__(\"%s.%s\")\n" % (package, kind))
    output.write("\n")

    output.write("\tdef before_send(self, msg):\n")
    output.write("\t\tpass\n")
    output.write("\n")

    for idx, field in enumerate(message_type.field):
        if not field.HasField("oneof_index"):
            continue

        comment = get_comment(comment_map,
                [PATH_MESSAGE_TYPE, message_idx, PATH_FIELD, idx])
        if comment:
            output.write("\t\"\"\"\n")
            for line in comment.strip().split("\n"):
                output.write("\t%s\n" % line.strip())
            output.write("\t\"\"\"\n")

        output.write("\tdef %s(self, arg):\n" % field.name)
        output.write("\t\tpbmsg = %s.%s()\n" % (proto_package, kind))
        output.write("\t\tpbmsg.%s.CopyFrom(arg)\n" % field.name)
        output.write("\t\tself.before_send(pbmsg)\n")
        output.write("\t\tmsg = msghub.Message.from_pbuf_msg(self.service_id, pbmsg)\n")
        output.write("\t\tres = self.send(msg)\n")
        output.write("\t\treturn res\n")
        output.write("\n")
    output.write("\n")

def generate_message_handler(comment_map, message_idx, message_type,
        package, kind, output, proto_package):
    output.write("class %sHandler(msghub.MessageHandler):\n" % kind)

    output.write("\tdef __init__(self):\n")
    output.write("\t\tsuper().__init__(\"%s.%s\")\n" % (package, kind))
    output.write("\n")

    output.write("\tdef handle(self, msg):\n")
    output.write("\t\tself.handle%s(msg)\n" % kind)
    output.write("\n")

    output.write("\tdef handle%s(self, msg):\n" % kind)
    output.write("\t\tm = %s.%s()\n" % (proto_package, kind))
    output.write("\t\tif not m.ParseFromString(msg.data):\n")
    output.write("\t\t\treturn\n")

    for field in message_type.field:
        if not field.HasField("oneof_index"):
            continue

        output.write("\t\tif m.HasField('%s'):\n" % field.name)
        output.write("\t\t\tself.%s(m.%s)\n" % (field.name, field.name))
        output.write("\n")

    for idx, field in enumerate(message_type.field):
        if not field.HasField("oneof_index"):
            continue

        comment = get_comment(comment_map,
                [PATH_MESSAGE_TYPE, message_idx, PATH_FIELD, idx])
        if comment:
            output.write("\t\"\"\"\n")
            for line in comment.strip().split("\n"):
                output.write("\t%s\n" % line.strip())
            output.write("\t\"\"\"\n")

        output.write("\tdef %s(self, msg):\n" % field.name)
        output.write("\t\tpass\n")
        output.write("\n")
    output.write("\n")

def generate_code(request, response):
    for proto_file in request.proto_file:
        if proto_file.name not in request.file_to_generate:
            continue
        output = StringIO()

        # Build a comment map from path in source code info location
        comment_map = dict()
        for location in proto_file.source_code_info.location:
            comment_map[",".join([str(x) for x in location.path])] = location

        proto_package = get_proto_package(proto_file.name)

        output.write("\"\"\"\n")
        output.write("GENERATED FILE, DO NOT EDIT.\n")
        output.write("\"\"\"\n")
        output.write("\n")
        output.write("import msghub\n")
        output.write("import %s\n" % proto_package)
        output.write("\n")

        for message_idx, message_type in enumerate(proto_file.message_type):
            if message_type.name in ["Command", "Event"]:
                generate_message_sender(
                        comment_map,
                        message_idx,
                        message_type,
                        proto_file.package,
                        message_type.name,
                        output,
                        proto_package)
                generate_message_handler(
                        comment_map,
                        message_idx,
                        message_type,
                        proto_file.package,
                        message_type.name,
                        output,
                        proto_package)

        file_o = response.file.add()
        file_o.name = get_msghub_python(proto_file.name)
        file_o.content = output.getvalue()

def main():
    # Read request message from stdin
    data = sys.stdin.buffer.read()

    # Parse request
    request = plugin.CodeGeneratorRequest()
    request.ParseFromString(data)

    # Create response
    response = plugin.CodeGeneratorResponse()

    # Generate code
    generate_code(request, response)

    # Serialize response message
    output = response.SerializeToString()

    # Write to stdout
    sys.stdout.buffer.write(output)


if __name__ == "__main__":
    main()
