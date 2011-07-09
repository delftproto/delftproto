# To use this in your Makefile:
#   delftproto_dir := path to this file (such as, /usr/local/share/delftproto-vm)
#   include $(delftproto_dir)/vm.mk

.PHONY: clean

output ?= dpvm
generated += $(output)

delftproto_dir ?= ../..
platform_dir ?= .

vm_dir := $(delftproto_dir)/vm

sources += $(wildcard $(vm_dir)/*.cpp)
sources += $(wildcard $(platform_dir)/*.cpp)
dependencies += $(wildcard $(vm_dir)/instructions/*)
dependencies += $(wildcard $(platform_dir)/instructions/*)

extension_dir := $(extensions)

-include $(extension_dir:%=%/extension.mk)

sources += $(wildcard $(extension_dir:%=%/*.cpp))
dependencies += $(wildcard $(extension_dir:%=%/*))

include_dir += $(delftproto_dir)
include_dir += $(platform_dir)
include_dir += $(vm_dir)

sources := $(sort $(sources))

dependencies += $(sources)
dependencies += $(wildcard $(include_dir:%=%/*.hpp))

$(output): $(dependencies)
	$(CXX) $(CXXFLAGS) $(include_dir:%=-I%) $(sources) -o $@

clean:
	rm -f $(generated)
