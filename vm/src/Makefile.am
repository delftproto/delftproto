vmsrcdir := $(datadir)/delftproto
nobase_dist_vmsrc_DATA = vm/*.hpp vm/*.cpp vm/delftproto.instructions vm.mk vm/instructions/*.cpp

bin_SCRIPTS = delftproto-dir
CLEANFILES = delftproto-dir

delftproto-dir: Makefile
	( \
		echo '#/usr/bin/env sh'; \
		echo 'echo' $(datadir)/delftproto \
	) > $@
	chmod +x $@

