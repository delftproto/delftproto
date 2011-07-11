# To use this in your Makefile:
#   delftproto_dir := $(shell delftproto-dir) # The path to the delftproto shared directory.
#   include $(delftproto_dir)/vm.mk

.PHONY: clean

dpvm ?= dpvm
delftproto_dir ?= ../..

dpvm_dir := $(delftproto_dir)/vm

$(dpvm)_SOURCES ?= $(wildcard *.cpp)
$(dpvm)_SOURCES += $(wildcard $(dpvm_dir)/*.cpp)

$(dpvm)_DEPENDENCIES ?= $(wildcard instructions/*)
$(dpvm)_DEPENDENCIES += $(wildcard $(dpvm_dir)/instructions/*)

-include $($(dpvm)_EXTENSIONS:%=%/extension.mk)

$(dpvm)_SOURCES += $(wildcard $($(dpvm)_EXTENSIONS:%=%/*.cpp))
$(dpvm)_DEPENDENCIES += $(wildcard $($(dpvm)_EXTENSIONS:%=%/*))

$(dpvm)_INCLUDE_DIRS += $(delftproto_dir)
$(dpvm)_INCLUDE_DIRS += .
$(dpvm)_INCLUDE_DIRS += $(dpvm_dir)

$(dpvm)_INCLUDES := $($(dpvm)_INCLUDE_DIRS:%=-I%)

$(dpvm)_SOURCES := $(sort $($(dpvm)_SOURCES))

$(dpvm)_DEPENDENCIES += $(sources)
$(dpvm)_DEPENDENCIES += $(wildcard $(include_dir:%=%/*.hpp))

$(dpvm)_CPPFLAGS += $($(dpvm)_INCLUDES) $(CPPFLAGS)
$(dpvm)_CXXFLAGS += $(CXXFLAGS)
$(dpvm)_LDFLAGS  += $(LDFLAGS)

$(dpvm)_COMPILE = $(CXX) $($(dpvm)_CPPFLAGS) $($(dpvm)_CXXFLAGS) $($(dpvm)_LDFLAGS) $($(dpvm)_SOURCES)
