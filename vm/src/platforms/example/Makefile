delftproto_dir := ../..

dpvm_EXTENSIONS += $(delftproto_dir)/vm-extensions/example

include $(delftproto_dir)/vm.mk

dpvm_CXXFLAGS = -Wall

dpvm: $(dpvm_DEPENDENCIES)
	$(dpvm_COMPILE) -o $@

.PHONY: clean
clean:
	rm -f dpvm
