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

def get_cpp_namespace(package):
    return package.replace(".", "::")


def get_cpp_header(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + ".pb.h"
    else:
        return filename + ".pb.h"


def get_msghub_header(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + ".msghub.h"
    else:
        return filename + ".msghub.h"


def get_msghub_source(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + ".msghub.cc"
    else:
        return filename + ".msghub.cc"


def to_camel_case(snake_str, lower=True):
    components = snake_str.split('_')
    # We capitalize the first letter of each component except the first one
    # with the 'title' method and join them together.
    if lower:
        return components[0] + ''.join(x.title() for x in components[1:])
    else:
        return ''.join(x.title() for x in components)


NATIVE_TYPES = {
    FieldDescriptor.TYPE_DOUBLE: "double",
    FieldDescriptor.TYPE_FLOAT: "float",
    FieldDescriptor.TYPE_INT64: "int64_t",
    FieldDescriptor.TYPE_UINT64: "uint64_t",
    FieldDescriptor.TYPE_INT32: "int32_t",
    FieldDescriptor.TYPE_FIXED64: "uint64_t",
    FieldDescriptor.TYPE_FIXED32: "uint32_t",
    FieldDescriptor.TYPE_BOOL: "bool",
    FieldDescriptor.TYPE_UINT32: "uint32_t",
    FieldDescriptor.TYPE_SFIXED32: "int32_t",
    FieldDescriptor.TYPE_SFIXED64: "int64_t",
    FieldDescriptor.TYPE_SINT32: "int32_t",
    FieldDescriptor.TYPE_SINT64: "int64_t",
}


def get_arg_type(field):
    if field.type == FieldDescriptor.TYPE_MESSAGE:
        return "const %s &" % (get_cpp_namespace(field.type_name))
    elif field.type == FieldDescriptor.TYPE_ENUM:
        return get_cpp_namespace(field.type_name) + " "
    elif field.type == FieldDescriptor.TYPE_STRING:
        return "const std::string &"
    else:
        return NATIVE_TYPES[field.type] + " "


def get_comment(comment_map, comment_path):
    try:
        location = comment_map[",".join([str(x) for x in comment_path])]
        return location.leading_comments
    except KeyError:
        return ""


def generate_message_sender_header(comment_map, message_idx, message_type,
        package, kind, output):
    output.write("class %sSender : public ::msghub::MessageSender {\n" % kind)
    output.write("public:\n")

    output.write("\tstatic constexpr const char *")
    output.write("sServiceName = \"%s.%s\";\n" % (package, kind))
    output.write("\n")

    output.write("\t%sSender();\n" % kind)
    output.write("\n")

    output.write("\tvirtual void beforeSend(%s::%s &msg);\n" % (
            get_cpp_namespace(package), kind))
    output.write("\n")

    output.write("\tusing ::msghub::MessageSender::send;\n")
    output.write("\n")

    output.write("\tvirtual int send(\n")
    output.write("\t\tconst %s::%s &msg,\n" % (
            get_cpp_namespace(package),
            kind))
    output.write("\t\tpomp::Connection *conn=nullptr);\n")
    output.write("\n")

    for idx, field in enumerate(message_type.field):
        if not field.HasField("oneof_index"):
            continue

        comment = get_comment(comment_map,
                [PATH_MESSAGE_TYPE, message_idx, PATH_FIELD, idx])
        if comment:
            output.write("\t/**\n")
            for line in comment.strip().split("\n"):
                output.write("\t * %s\n" % line.strip())
            output.write("\t */\n")

        output.write("\tint %s(\n" % to_camel_case(field.name))
        output.write("\t\t%sarg,\n" % get_arg_type(field))
        output.write("\t\tpomp::Connection *conn=nullptr);\n")
        output.write("\n")

    output.write("};\n")
    output.write("\n")


def generate_message_sender_source(comment_map, message_idx, message_type,
        package, kind, output):
    # Constructor
    output.write("%sSender::%sSender()\n" % (kind, kind))
    output.write("\t: ::msghub::MessageSender(sServiceName)\n")
    output.write("{\n")
    output.write("}\n")
    output.write("\n")

    output.write("void %sSender::beforeSend(%s::%s &msg)\n" % (
            kind, get_cpp_namespace(package), kind))
    output.write("{\n")
    output.write("}\n")
    output.write("\n")

    output.write("int %sSender::send(\n" % kind)
    output.write("\tconst %s::%s &msg,\n" % (
            get_cpp_namespace(package),
            kind))
    output.write("\tpomp::Connection *conn)\n")

    output.write("{\n")
    output.write("\treturn ::msghub::MessageSender::send(\n")
    output.write("\t\tstatic_cast<uint16_t>(msg.id_case()),\n")
    output.write("\t\tmsg,\n")
    output.write("\t\tconn);\n")
    output.write("}\n")
    output.write("\n")

    for field in message_type.field:
        if not field.HasField("oneof_index"):
            continue
        output.write("int %sSender::%s(\n" % (
                kind,
                to_camel_case(field.name)))
        output.write("\t%sarg,\n" % get_arg_type(field))
        output.write("\tpomp::Connection *conn)\n")

        output.write("{\n")
        output.write("\t%s::%s msg;\n" % (get_cpp_namespace(package), kind))

        # Avoid reallocation by using arg in place, requires a const cast
        if field.type == FieldDescriptor.TYPE_MESSAGE:
            output.write("\tmsg.set_allocated_%s(remove_const(arg));\n" %
                    field.name)
        elif field.type == FieldDescriptor.TYPE_STRING:
            output.write("\tmsg.set_allocated_%s(remove_const(arg));\n" %
                    field.name)
        else:
            output.write("\tmsg.set_%s(arg);\n" % field.name)

        output.write("\tbeforeSend(msg);\n")
        output.write("\tint res = send(msg, conn);\n")

        # Release arg used in place
        if field.type == FieldDescriptor.TYPE_MESSAGE or \
                field.type == FieldDescriptor.TYPE_STRING:
            output.write("\tmsg.release_%s();\n" % field.name)

        output.write("\treturn res;\n")
        output.write("}\n")
        output.write("\n")


def generate_message_handler_header(comment_map, message_idx, message_type,
        package, kind, output):
    output.write("class %sHandler : public ::msghub::MessageHandler {\n" % kind)
    output.write("public:\n")

    output.write("\tstatic constexpr const char *")
    output.write("sServiceName = \"%s.%s\";\n" % (package, kind))
    output.write("\n")

    output.write("\t%sHandler();\n" % kind)
    output.write("\n")

    output.write("\tvirtual void handle(\n")
    output.write("\t\tconst ::msghub::Message &msg) override;\n")
    output.write("\n")

    output.write("\tvirtual void handle%s(\n" % kind)
    output.write("\t\tconst %s::%s &arg);\n" % (
            get_cpp_namespace(package),
            kind))
    output.write("\n")

    for idx, field in enumerate(message_type.field):
        if not field.HasField("oneof_index"):
            continue

        comment = get_comment(comment_map,
                [PATH_MESSAGE_TYPE, message_idx, PATH_FIELD, idx])
        if comment:
            output.write("\t/**\n")
            for line in comment.strip().split("\n"):
                output.write("\t * %s\n" % line.strip())
            output.write("\t */\n")

        output.write("\tvirtual void %s(\n" % to_camel_case(field.name))
        output.write("\t\t%smsg);\n" % get_arg_type(field))
        output.write("\n")

    output.write("};\n")
    output.write("\n")


def generate_message_handler_source(comment_map, message_idx, message_type,
        package, kind, output):
    # Constructor
    output.write("%sHandler::%sHandler()\n" % (kind, kind))
    output.write("\t: ::msghub::MessageHandler(sServiceName)\n")
    output.write("{\n")
    output.write("}\n")
    output.write("\n")

    # Handler with top level parsing
    output.write("void %sHandler::handle(\n" % kind)
    output.write("\tconst ::msghub::Message &msg)\n")
    output.write("{\n")
    output.write("\t%s::%s m;\n" % (get_cpp_namespace(package), kind))
    output.write("\tif (!m.ParseFromArray(msg.getData(), msg.getLen()))\n")
    output.write("\t\treturn;\n")
    output.write("\tthis->handle%s(m);\n" % kind)
    output.write("}\n")
    output.write("\n")

    # Handler with switch case
    output.write("void %sHandler::handle%s(\n" % (kind, kind))
    output.write("\tconst %s::%s &msg)\n" % (
            get_cpp_namespace(package),
            kind))

    output.write("{\n")
    output.write("\tswitch (msg.id_case()) {\n")
    for field in message_type.field:
        if not field.HasField("oneof_index"):
            continue
        output.write("\tcase %s::%s::k%s:\n" % (
                get_cpp_namespace(package),
                kind,
                to_camel_case(field.name, False)))
        output.write("\t\tthis->%s(msg.%s());\n" % (
                to_camel_case(field.name), field.name))
        output.write("\t\tbreak;\n")
        output.write("\n")
    output.write("\tdefault:\n")
    output.write("\t\tbreak;\n")
    output.write("\t}\n")
    output.write("}\n")
    output.write("\n")

    # Default empty handlers
    for field in message_type.field:
        if not field.HasField("oneof_index"):
            continue
        output.write("void %sHandler::%s(\n" % (
                kind,
                to_camel_case(field.name)))
        output.write("\t%sarg)\n" % get_arg_type(field))
        output.write("{\n")
        output.write("}\n")
        output.write("\n")


def generate_code(request, response):
    for proto_file in request.proto_file:
        if proto_file.name not in request.file_to_generate:
            continue
        output_h = StringIO()
        output_cc = StringIO()

        # Build a comment map from path in source code info location
        comment_map = dict()
        for location in proto_file.source_code_info.location:
            comment_map[",".join([str(x) for x in location.path])] = location

        namespace = get_cpp_namespace(proto_file.package).split("::")

        output_h.write("/**\n")
        output_h.write(" * GENERATED FILE, DO NOT EDIT.\n")
        output_h.write(" */\n")
        output_h.write("\n")
        output_h.write("#pragma once\n")
        output_h.write("\n")
        output_h.write("#include <msghub.hpp>\n")
        output_h.write("#include \"%s\"\n" % get_cpp_header(proto_file.name))
        output_h.write("\n")
        output_h.write("namespace pomp {\n")
        output_h.write("\tclass Conn;\n")
        output_h.write("}\n")
        output_h.write("\n")

        for n in namespace:
            output_h.write("namespace %s {\n" % n)
        output_h.write("namespace msghub {\n")
        output_h.write("\n")

        output_cc.write("/**\n")
        output_cc.write(" * GENERATED FILE, DO NOT EDIT.\n")
        output_cc.write(" */\n")
        output_cc.write("\n")
        output_cc.write("#include \"%s\"\n" %
                get_msghub_header(proto_file.name))
        output_cc.write("\n")
        for n in namespace:
            output_cc.write("namespace %s {\n" % n)
        output_cc.write("namespace msghub {\n")
        output_cc.write("\n")

        output_cc.write("template<typename T>\n")
        output_cc.write("inline static T *remove_const(const T &val)\n")
        output_cc.write("{\n")
        output_cc.write("\treturn const_cast<T *>(&val);\n")
        output_cc.write("}\n")
        output_cc.write("\n")

        for message_idx, message_type in enumerate(proto_file.message_type):
            if message_type.name in ["Command", "Event"]:
                generate_message_sender_header(
                        comment_map,
                        message_idx,
                        message_type,
                        proto_file.package,
                        message_type.name,
                        output_h)
                generate_message_sender_source(
                        comment_map,
                        message_idx,
                        message_type,
                        proto_file.package,
                        message_type.name,
                        output_cc)
                generate_message_handler_header(
                        comment_map,
                        message_idx,
                        message_type,
                        proto_file.package,
                        message_type.name,
                        output_h)
                generate_message_handler_source(
                        comment_map,
                        message_idx,
                        message_type,
                        proto_file.package,
                        message_type.name,
                        output_cc)

        output_h.write("} // namespace msghub\n")
        for n in reversed(namespace):
            output_h.write("} // namespace %s\n" % n)

        output_cc.write("} // namespace msghub\n")
        for n in reversed(namespace):
            output_cc.write("} // namespace %s\n" % n)

        file_h = response.file.add()
        file_h.name = get_msghub_header(proto_file.name)
        file_h.content = output_h.getvalue()

        file_cc = response.file.add()
        file_cc.name = get_msghub_source(proto_file.name)
        file_cc.content = output_cc.getvalue()


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
