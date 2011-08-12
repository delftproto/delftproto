delftproto_dir := ../..

dpvm_EXTENSIONS += $(delftproto_dir)/vm-extensions/example $(delftproto_dir)/vm-extensions/ctrl-c-trigger

include $(delftproto_dir)/vm.mk

dpvm_CXXFLAGS = -Wall

dpvm: $(dpvm_DEPENDENCIES)
	$(dpvm_COMPILE) -o $@

.PHONY: clean
clean:
	rm -f dpvm
