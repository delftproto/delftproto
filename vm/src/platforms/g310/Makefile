DEVICE ?= /dev/ttyUSB0

delftproto_dir := ../..

.PHONY: upload

output := dpvm.elf
generated := dpvm.ihex
CXX := msp430-g++
CXXFLAGS += -mmcu=msp430x2418 -Os -ffunction-sections --combine -Wl,--relax,--gc-sections -mendup-at=main -lm

include $(delftproto_dir)/vm.mk

dpvm.ihex: dpvm.elf Makefile
	msp430-objcopy -O ihex $< $@

upload: dpvm.ihex
	lnode-bsl --invert-sda --invert-scl -c $(DEVICE) -reIp $<

