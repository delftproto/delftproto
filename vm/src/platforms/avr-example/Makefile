delftproto_dir := ../..

include $(delftproto_dir)/vm.mk

CXX := avr-g++ -lm
dpvm_CXXFLAGS += -mmcu=atmega168 -Os -funit-at-a-time -finline-limit=1 -ffunction-sections --combine -Wl,--relax,--gc-sections

dpvm.elf: $(dpvm_DEPENDENCIES)
	$(dpvm_COMPILE) -lm -o $@

.PHONY: clean
clean:
	rm -f dpvm.elf

