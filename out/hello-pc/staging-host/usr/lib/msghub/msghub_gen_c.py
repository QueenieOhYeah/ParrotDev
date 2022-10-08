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
import re
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


def get_type(dotted_name):
    # Capitalize/title does not give expected result
    # We want foobar -> Foobar but FooBar -> FooBar
    return "__".join([x[0].upper() + x[1:]
            for x in dotted_name.strip(".").split(".")])


def get_function(dotted_name):
    return "__".join([to_snake_case(x)
            for x in dotted_name.strip(".").split(".")])


def get_enum(dotted_name):
    return "__".join([to_snake_case(x).upper()
            for x in dotted_name.strip(".").split(".")])


def get_c_header(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + ".pb-c.h"
    else:
        return filename + ".pb-c.h"


def get_msghub_header(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + ".msghub-c.h"
    else:
        return filename + ".msghub-c.h"


def get_msghub_source(filename):
    if filename.endswith(".proto"):
        return filename[:-6] + ".msghub-c.c"
    else:
        return filename + ".msghub-c.c"


_TO_SNAKE_CASE_RE = re.compile(r"(?<!^)(?=[A-Z])")
def to_snake_case(str, lower=True):
    return _TO_SNAKE_CASE_RE.sub("_", str).lower()


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


def get_arg_type(field, const=True):
    if field.type == FieldDescriptor.TYPE_MESSAGE:
        if const:
            return "const %s *" % (get_type(field.type_name))
        else:
            return "%s *" % (get_type(field.type_name))
    elif field.type == FieldDescriptor.TYPE_ENUM:
        return get_type(field.type_name) + " "
    elif field.type == FieldDescriptor.TYPE_STRING:
        if const:
            return "const char *"
        else:
            return "char *"
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

    sender_type = "%s.%sSender" % (package, kind)
    sender_ops_type = "%s.%sSender.Ops" % (package, kind)
    sender_type_name = get_type(sender_type)
    sender_ops_type_name = get_type(sender_ops_type)

    output.write("/**\n")
    output.write(" * %s sender\n" % kind)
    output.write(" */\n")
    output.write("\n")

    # Forward declaration of sender
    output.write("struct _%s;\n" % sender_type_name)
    output.write("typedef struct _%s\n" % sender_type_name)
    output.write("\t%s;\n" % sender_type_name)
    output.write("typedef struct _%s\n" % sender_ops_type_name)
    output.write("\t%s;\n" % sender_ops_type_name)
    output.write("\n")

    # Structure with sender operations
    output.write("struct _%s {\n" % sender_ops_type_name)

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

        output.write("\tint (*%s)(\n" % field.name)
        output.write("\t\t%s *sender,\n"% sender_type_name)
        output.write("\t\t%sarg,\n" % get_arg_type(field))
        output.write("\t\tstruct pomp_conn *conn);\n")
        output.write("\n")

    output.write("};\n")
    output.write("\n")

    # _new function
    output.write("int %s(\n" % get_function("%s.new" % sender_type))
    output.write("\t%s **ret_obj);\n" % sender_type_name)
    output.write("\n")

    # _destroy function
    output.write("void %s(\n" % get_function("%s.destroy" % sender_type))
    output.write("\t%s *sender);\n" % sender_type_name)
    output.write("\n")

    # _get_base function
    output.write("struct msghub_sender *\n")
    output.write("%s(\n" % get_function("%s.get_base" % sender_type))
    output.write("\t%s *sender);\n" % sender_type_name)
    output.write("\n")

    # _get_ops function
    output.write("const %s *\n" % sender_ops_type_name)
    output.write("%s(\n" % get_function("%s.get_ops" % sender_type))
    output.write("\t%s *sender);\n" % sender_type_name)
    output.write("\n")


def generate_message_sender_source(comment_map, message_idx, message_type,
        package, kind, output):

    sender_type = "%s.%sSender" % (package, kind)
    sender_ops_type = "%s.%sSender.Ops" % (package, kind)
    sender_type_name = get_type(sender_type)
    sender_ops_type_name = get_type(sender_ops_type)

    output.write("struct _%s {\n" % sender_type_name)
    output.write("\tstruct msghub_sender *base;\n")
    output.write("\tconst %s *ops;\n" % sender_ops_type_name)
    output.write("};\n")
    output.write("\n")

    # send functions
    for field in message_type.field:
        if not field.HasField("oneof_index"):
            continue

        output.write("static int send_%s_%s(\n" % (kind, field.name))
        output.write("\t%s *sender,\n"% sender_type_name)
        output.write("\t%sarg,\n" % get_arg_type(field))
        output.write("\tstruct pomp_conn *conn)\n")
        output.write("{\n")
        output.write("\t%s msg;\n" % get_type("%s.%s" % (package, kind)))
        output.write("\t%s(&msg);\n" %
                get_function("%s.%s.init" % (package, kind)))
        output.write("\tmsg.id_case = %s;\n" %
                get_enum("%s.%s.Id_%s" % (package, kind, field.name)))

        # Need cast to remove constness of input
        if field.type == FieldDescriptor.TYPE_MESSAGE or \
                field.type == FieldDescriptor.TYPE_STRING:
            output.write("\tmsg.%s = (%s)arg;\n" % (
                    field.name, get_arg_type(field, False)))
        else:
            output.write("\tmsg.%s = arg;\n" % field.name)

        output.write("\treturn msghub_sender_send_protobuf(\n")
        output.write("\t\tsender->base, msg.id_case, &msg.base, conn);\n")
        output.write("}\n")
        output.write("\n")

    # operations structure
    output.write("static const %s\n" % sender_ops_type_name)
    output.write("s_%s_ops = {\n" % sender_type_name)

    for field in message_type.field:
        if not field.HasField("oneof_index"):
            continue
        output.write("\t.%s = &send_%s_%s,\n" % (field.name, kind, field.name))

    output.write("};\n")
    output.write("\n")

    # _new function
    output.write("int %s(\n" % get_function("%s.new" % sender_type))
    output.write("\t%s **ret_obj)\n" % sender_type_name)
    output.write("{\n")
    output.write("\tint res = 0;\n")
    output.write("\t%s *sender = NULL;\n" % sender_type_name)
    output.write("\n")
    output.write("\tif (ret_obj == NULL)\n")
    output.write("\t\treturn -EINVAL;\n")
    output.write("\t*ret_obj = NULL;\n")
    output.write("\n")
    output.write("\tsender = calloc(1, sizeof(*sender));\n")
    output.write("\tif (sender == NULL)\n")
    output.write("\t\treturn -ENOMEM;\n")
    output.write("\n")
    output.write("\tres = msghub_sender_new(\"%s.%s\", &sender->base);\n" % (
            package, kind))
    output.write("\tif (res < 0)\n")
    output.write("\t\tgoto error;\n")
    output.write("\n")
    output.write("\tsender->ops = &s_%s_ops;\n" % sender_type_name)
    output.write("\t*ret_obj = sender;\n")
    output.write("\treturn 0;\n")
    output.write("\n")
    output.write("error:\n")
    output.write("\t%s(sender);\n" % get_function("%s.destroy" % sender_type))
    output.write("\treturn res;\n")
    output.write("}\n")
    output.write("\n")

    # _destroy function
    output.write("void %s(\n" % get_function("%s.destroy" % sender_type))
    output.write("\t%s *sender)\n" % sender_type_name)
    output.write("{\n")
    output.write("\tif (sender != NULL) {\n")
    output.write("\t\tmsghub_sender_destroy(sender->base);\n")
    output.write("\t\tfree(sender);\n")
    output.write("\t}\n")
    output.write("}\n")
    output.write("\n")

    # _get_base function
    output.write("struct msghub_sender *\n")
    output.write("%s(\n" % get_function("%s.get_base" % sender_type))
    output.write("\t%s *sender)\n" % sender_type_name)
    output.write("{\n")
    output.write("\treturn sender == NULL ? NULL : sender->base;\n")
    output.write("}\n")
    output.write("\n")

    # _get_ops function
    output.write("const %s *\n" % sender_ops_type_name)
    output.write("%s(\n" % get_function("%s.get_ops" % sender_type))
    output.write("\t%s *sender)\n" % sender_type_name)
    output.write("{\n")
    output.write("\treturn sender == NULL ? NULL : sender->ops;\n")
    output.write("}\n")
    output.write("\n")


def generate_message_handler_header(comment_map, message_idx, message_type,
        package, kind, output):

    handler_type = "%s.%sHandler" % (package, kind)
    handler_cbs_type = "%s.%sHandler.Cbs" % (package, kind)
    handler_type_name = get_type(handler_type)
    handler_cbs_type_name = get_type(handler_cbs_type)

    output.write("/**\n")
    output.write(" * %s handler\n" % kind)
    output.write(" */\n")
    output.write("\n")

    # Forward declaration of handler
    output.write("struct _%s;\n" % handler_type_name)
    output.write("typedef struct _%s\n\t%s;\n" % (
            handler_type_name, handler_type_name))
    output.write("typedef struct _%s\n\t%s;\n" % (
            handler_cbs_type_name, handler_cbs_type_name))
    output.write("\n")

    # Structure with handler callbacks
    output.write("struct _%s {\n" % handler_cbs_type_name)

    output.write("\tvoid (*handle_%s)(\n" % kind.lower())
    output.write("\t\tconst %s *arg,\n" % get_type("%s.%s" % (package, kind)))
    output.write("\t\tvoid *userdata);\n")

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

        output.write("\n")
        output.write("\tvoid (*%s)(\n" % field.name)
        output.write("\t\t%sarg,\n" % get_arg_type(field))
        output.write("\t\tvoid *userdata);\n")

    output.write("};\n")
    output.write("\n")

    # _new function
    output.write("int %s(\n" % get_function("%s.new" % handler_type))
    output.write("\tconst %s *cbs,\n" % handler_cbs_type_name)
    output.write("\tvoid *userdata,\n")
    output.write("\t%s **ret_obj);\n" % handler_type_name)
    output.write("\n")

    # _destroy function
    output.write("void %s(\n" % get_function("%s.destroy" % handler_type))
    output.write("\t%s *handler);\n" % handler_type_name)
    output.write("\n")

    # _get_base function
    output.write("struct msghub_handler *\n")
    output.write("%s(\n" % get_function("%s.get_base" % handler_type))
    output.write("\t%s *handler);\n" % handler_type_name)
    output.write("\n")


def generate_message_handler_source(comment_map, message_idx, message_type,
        package, kind, output):

    handler_type = "%s.%sHandler" % (package, kind)
    handler_cbs_type = "%s.%sHandler.Cbs" % (package, kind)
    handler_type_name = get_type(handler_type)
    handler_cbs_type_name = get_type(handler_cbs_type)

    output.write("struct _%s {\n" % handler_type_name)
    output.write("\tstruct msghub_handler *base;\n")
    output.write("\t%s cbs;\n" % handler_cbs_type_name)
    output.write("\tvoid *userdata;\n")
    output.write("};\n")
    output.write("\n")

    # Handler operations functions

    # handle Command/Event function
    output.write("static void %s(\n" %
            get_function("%s.handle_%s" % (handler_type, kind)))
    output.write("\tstruct msghub_handler *base,\n")
    output.write("\t%s *msg)\n" % get_type("%s.%s" % (package, kind)))
    output.write("{\n")
    output.write("\t%s *handler =\n" % handler_type_name)
    output.write("\t\tmsghub_handler_get_child(base);\n")
    output.write("\n")
    output.write("\tif (handler->cbs.handle_%s != NULL)\n" % kind.lower())
    output.write("\t\t(*handler->cbs.handle_%s)(msg, handler->userdata);\n" %
            kind.lower())
    output.write("\n")
    output.write("\tswitch (msg->id_case) {\n")

    for field in message_type.field:
        if not field.HasField("oneof_index"):
            continue

        output.write("\tcase %s:\n" %
                get_enum("%s.%s.Id_%s" % (package, kind, field.name)))
        output.write("\t\tif (handler->cbs.%s != NULL) {\n" % field.name)
        output.write("\t\t\t(*handler->cbs.%s)(\n"  % field.name)
        output.write("\t\t\t\tmsg->%s,\n"  % field.name)
        output.write("\t\t\t\thandler->userdata);\n")
        output.write("\t\t}\n")
        output.write("\t\tbreak;\n")
        output.write("\n")

    output.write("\tdefault:\n")
    output.write("\t\tbreak;\n")
    output.write("\t}\n")
    output.write("}\n")
    output.write("\n")

    # handle function
    output.write("static void %s(\n" %
            get_function("%s.handle" % handler_type))
    output.write("\tstruct msghub_handler *base,\n")
    output.write("\tconst struct msghub_msg *msg)\n")
    output.write("{\n")
    output.write("\t%s *m =\n" % get_type("%s.%s" % (package, kind)))
    output.write("\t\t%s(\n" % get_function("%s.%s.unpack" % (package, kind)))
    output.write("\t\t\tNULL, msg->len, msg->const_data);\n")
    output.write("\tif (m == NULL)\n")
    output.write("\t\treturn;\n")
    output.write("\t%s(base, m);\n" %
            get_function("%s.handle_%s" % (handler_type, kind)))
    output.write("\t%s(m, NULL);\n" %
            get_function("%s.%s.free_unpacked" % (package, kind)))
    output.write("}\n")
    output.write("\n")

    # operations structure
    output.write("static const struct msghub_handler_ops\n")
    output.write("s_%s_ops = {\n" % handler_type_name)
    output.write("\t.handle = &%s,\n" %
            get_function("%s.handle" % handler_type))
    output.write("};\n")
    output.write("\n")

    # _new function
    output.write("int %s(\n" % get_function("%s.new" % handler_type))
    output.write("\tconst %s *cbs,\n" % handler_cbs_type_name)
    output.write("\tvoid *userdata,\n")
    output.write("\t%s **ret_obj)\n" % handler_type_name)
    output.write("{\n")
    output.write("\tint res = 0;\n")
    output.write("\t%s *handler = NULL;\n" % handler_type_name)
    output.write("\n")
    output.write("\tif (cbs == NULL || ret_obj == NULL)\n")
    output.write("\t\treturn -EINVAL;\n")
    output.write("\t*ret_obj = NULL;\n")
    output.write("\n")
    output.write("\thandler = calloc(1, sizeof(*handler));\n")
    output.write("\tif (handler == NULL)\n")
    output.write("\t\treturn -ENOMEM;\n")
    output.write("\n")
    output.write("\tres = msghub_handler_new(\n")
    output.write("\t\thandler,\n")
    output.write("\t\t&s_%s_ops,\n" % handler_type_name)
    output.write("\t\t\"%s.%s\",\n" % (package, kind))
    output.write("\t\t&handler->base);\n")
    output.write("\tif (res < 0)\n")
    output.write("\t\tgoto error;\n")
    output.write("\n")
    output.write("\thandler->cbs = *cbs;\n")
    output.write("\thandler->userdata = userdata;\n")
    output.write("\t*ret_obj = handler;\n")
    output.write("\treturn 0;\n")
    output.write("\n")
    output.write("error:\n")
    output.write("\t%s(handler);\n" %
            get_function("%s.destroy" % handler_type))
    output.write("\treturn res;\n")
    output.write("}\n")
    output.write("\n")

    # _destroy function
    output.write("void %s(\n" % get_function("%s.destroy" % handler_type))
    output.write("\t%s *handler)\n" % handler_type_name)
    output.write("{\n")
    output.write("\tif (handler != NULL) {\n")
    output.write("\t\tmsghub_handler_destroy(handler->base);\n")
    output.write("\t\tfree(handler);\n")
    output.write("\t}\n")
    output.write("}\n")
    output.write("\n")

    # _get_base function
    output.write("struct msghub_handler *\n")
    output.write("%s(\n" % get_function("%s.get_base" % handler_type))
    output.write("\t%s *handler)\n" % handler_type_name)
    output.write("{\n")
    output.write("\treturn handler == NULL ? NULL : handler->base;\n")
    output.write("}\n")
    output.write("\n")



def generate_code(request, response):
    for proto_file in request.proto_file:
        if proto_file.name not in request.file_to_generate:
            continue
        output_h = StringIO()
        output_c = StringIO()

        # Build a comment map from path in source code info location
        comment_map = dict()
        for location in proto_file.source_code_info.location:
            comment_map[",".join([str(x) for x in location.path])] = location

        output_h.write("/**\n")
        output_h.write(" * GENERATED FILE, DO NOT EDIT.\n")
        output_h.write(" */\n")
        output_h.write("\n")
        output_h.write("#pragma once\n")
        output_h.write("\n")
        output_h.write("#include <msghub.h>\n")
        output_h.write("#include <libpomp.h>\n")
        output_h.write("#include \"%s\"\n" % get_c_header(proto_file.name))
        output_h.write("\n")

        output_c.write("/**\n")
        output_c.write(" * GENERATED FILE, DO NOT EDIT.\n")
        output_c.write(" */\n")
        output_c.write("\n")
        output_c.write("#include \"%s\"\n" %
                get_msghub_header(proto_file.name))
        output_c.write("\n")

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
                        output_c)
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
                        output_c)

        file_h = response.file.add()
        file_h.name = get_msghub_header(proto_file.name)
        file_h.content = output_h.getvalue()

        file_c = response.file.add()
        file_c.name = get_msghub_source(proto_file.name)
        file_c.content = output_c.getvalue()


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
