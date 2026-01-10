ifeq ($(OS),Windows_NT)
SUBDIRS := irmpalarm/Windows irmpconfig/Windows irmpconfig_gui/Windows
else
SUBDIRS := irmpalarm/Linux irmpconfig/Linux irmpconfig_gui/Linux irmpstatusled
endif

all:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d all || exit 1; \
	done

clean:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d clean || exit 1; \
	done

.PHONY: all clean $(SUBDIRS)
