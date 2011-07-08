.PHONY: clean

# extensions += example ...

output ?= dpvm
generated += $(output)

vm_dir ?= ../../
extensions_dir ?= ../../extensions/
platform_dir ?= ./

sources += $(wildcard $(vm_dir)*.cpp)
sources += $(wildcard $(platform_dir)*.cpp)
dependencies += $(wildcard $(vm_dir)instructions/*)
dependencies += $(wildcard $(platform_dir)instructions/*)

extension_dir := $(extensions:%=$(extensions_dir)%)

-include $(extension_dir:%=%/extension.mk)

sources += $(wildcard $(extension_dir:%=%/*.cpp))
dependencies += $(wildcard $(extension_dir:%=%/*))

include_dir += $(extensions_dir)
include_dir += $(platform_dir)
include_dir += $(vm_dir)

sources := $(sort $(sources)) # remove duplicates

dependencies += $(sources)
dependencies += $(wildcard $(include_dir:%=%/*.hpp))

$(output): $(dependencies)
	$(CXX) $(CXXFLAGS) $(include_dir:%=-I%) $(sources) -o $@

clean:
	rm -f $(generated)
