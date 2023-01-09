# Split decompiled files...
import sys
import re

RGX_COMMENT = re.compile(r"^//.*$")
RGX_STRUCT = re.compile(r"struct .*$")
RGX_TYPEDEF = re.compile(r"typedef .*$")
RGX_ENUM = re.compile(r"enum .*$")
RGX_FUNCTION = re.compile(r"^\w+\s+(?P<name>\w+)\(.*$")
RGX_OBJFILE = re.compile(r"^(?P<file>\w+)\.o:$")
RGX_CONTAINS = re.compile(r"^\w+\s+[Tt]\s+(?P<function>\w+)$")

def discard(decompiled):
    line = decompiled.readline()
    while not line.startswith("};"):
        line = decompiled.readline()

def capture(decompiled):
    function = []
    line = decompiled.readline()
    line = line.rstrip()
    function.append(line)

    while not line.startswith("}"):
        line = decompiled.readline()
        line = line.rstrip()
        function.append(line)

    return function

comments = []
functions = {}

print("Reading decompiled file '%s'..." % sys.argv[1])
with open(sys.argv[1], "r") as decompiled:
    line = decompiled.readline()
    while line:
        match = RGX_COMMENT.match(line)
        if match:
            line = line.rstrip()
            comments.append(line)

        match = RGX_STRUCT.match(line)
        if match:
            discard(decompiled)

        match = RGX_TYPEDEF.match(line)
        if match:
            discard(decompiled)

        match = RGX_ENUM.match(line)
        if match:
            discard(decompiled)

        match = RGX_FUNCTION.match(line)
        if match:
            line = line.rstrip()
            # print("function: %s" % match.group("name"))
            functions[match.group("name")] = []
            functions[match.group("name")].extend(comments)
            functions[match.group("name")].append(line)
            functions[match.group("name")].extend(capture(decompiled))
            comments = []

        line = decompiled.readline()

# for line in functions["uart_dma_send"]:
#     print(line)

print("Reading symbols file '%s'..." % sys.argv[2])
source = {}
filename = None
with open(sys.argv[2], "r") as symbols:
    line = symbols.readline()
    while line:
        match = RGX_OBJFILE.match(line)
        if match:
            filename = match.group("file")
            source[filename] = []
            print(filename)

        match = RGX_CONTAINS.match(line)
        if match:
            source[filename].append(match.group("function"))

        line = symbols.readline()

# print(source["second_clock"])

print("Writing source files...")
filenames = list(source.keys())

for filename in filenames:
    with open(filename + ".c", "w") as target:
        for function in source[filename]:
            if function not in functions:
                print("ERROR: '%s' missing from '%s.o'!" % (function, filename))
            else:
                for line in functions[function]:
                    target.write(line)
                    target.write("\n")

                # Discard the function written to the file.
                functions.pop(function)

print("Writing remnants...")
with open("remnants.c_", "w") as target:
    for function in list(functions.keys()):
        for line in functions[function]:
            target.write(line)
            target.write("\n")

