ifeq ($(OS),Windows_NT)
SUBDIRS := irmpalarm/Windows irmpconfig/Windows irmpconfig_gui/Windows
else
SUBDIRS := irmpalarm/Linux irmpconfig/Linux irmpconfig_gui/Linux irmpstatusled
endif

all:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d all || exit 1; \
	done

release_linux: clean all
	mkdir binaries_for_linux || rm -rf binaries_for_linux/*
	cp -p irmpalarm/Linux/irmpalarm irmpconfig/Linux/irmpconfig irmpconfig_gui/Linux/irmpconfig_gui irmpstatusled/irmpstatusled binaries_for_linux/
	tar -cJf binaries_for_linux.tar.xz binaries_for_linux/*

clean:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d clean || exit 1; \
	done

.PHONY: all clean release_linux $(SUBDIRS)
