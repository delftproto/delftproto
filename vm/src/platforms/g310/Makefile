DEVICE ?= /dev/ttyUSB0

delftproto_dir := ../..

include $(delftproto_dir)/vm.mk

CXX := msp430-g++
dpvm_CXXFLAGS += -mmcu=msp430x2418 -Os -ffunction-sections --combine -Wl,--relax,--gc-sections -mendup-at=main -lm

dpvm.elf: $(dpvm_DEPENDENCIES)
	$(dpvm_COMPILE) -o $@

dpvm.ihex: dpvm.elf Makefile
	msp430-objcopy -O ihex $< $@

.PHONY: upload
upload: dpvm.ihex
	lnode-bsl --invert-sda --invert-scl -c $(DEVICE) -reIp $<

.PHONY: clean
clean:
	rm -f dpvm.elf dpvm.ihex

