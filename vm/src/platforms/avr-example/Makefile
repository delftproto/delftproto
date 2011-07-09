delftproto_dir := ../..

output := dpvm.elf

CXX := avr-g++
CXXFLAGS := -mmcu=atmega168 -Os -funit-at-a-time -finline-limit=1 -ffunction-sections --combine -Wl,--relax,--gc-sections

include $(delftproto_dir)/vm.mk

