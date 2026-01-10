CC ?= gcc
CXX ?= g++

CFLAGS ?= -Wall -g -c -O2
CXXFLAGS ?= -Wall -g -O2

PKG_CONFIG ?= pkg-config
PKGS := libusb-1.0 libudev
PKG_CFLAGS := $(shell $(PKG_CONFIG) --cflags $(PKGS))
PKG_LIBS   := $(shell $(PKG_CONFIG) --libs   $(PKGS))
FOX_CFLAGS := $(shell WANT_FOX="1.6" fox-config --cflags)
FOX_LIBS   := $(shell WANT_FOX="1.6" fox-config --libs)

CFLAGS += -DDATE_STR="\"$(DATE)\""
CXXFLAGS += -DDATE_STR="\"$(DATE)\""

COBJS = hid.o
CPPOBJS = irmpconfig_gui.o icons.o dfu.o stm32mem.o upgrade.o
OBJS = $(COBJS) $(CPPOBJS)

DATE := $(shell date +"%F_%H-%M")

ifeq ($(OS),Windows_NT)
ifeq ($(MSYSTEM),MINGW32)
CFLAGS=-I/mingw32/include/fox-1.6 -I/mingw64/include/libusb-1.0 -g -c -s -Wall -mno-ms-bitfields -O2 -DDATE_STR="\"$(DATE)\""
# -static
LIBS= -mwindows -Wl,-Bstatic -lFOX-1.6 -lpng -ljpeg -ltiff -lz -llzma -lws2_32 -lgdi32 -static-libgcc -static-libstdc++ -lkernel32 -lsetupapi -lusb-1.0
else ifeq ($(MSYSTEM),MINGW64)
CFLAGS=-I/mingw64/include/fox-1.6 -I/mingw64/include/libusb-1.0 -g -c -s -Wall -mno-ms-bitfields -O2 -DDATE_STR="\"$(DATE)\""
# -static
LIBS= -mwindows -Wl,-Bstatic -lFOX-1.6 -lpng -ljpeg -ltiff -lz -lzstd -llzma -lws2_32 -lgdi32 -static-libgcc -static-libstdc++ -lkernel32 -lsetupapi -lusb-1.0 -ldeflate -lWebP -llerc -ljbig -lturbojpeg -lsharpyuv
endif
CXXFLAGS=-g -s -Wall  -mno-ms-bitfields -O2
# -static // causes timing problems, libwinpthread-1.dll is needed
else

CFLAGS += $(PKG_CFLAGS) $(FOX_CFLAGS)
CXXFLAGS += $(PKG_CFLAGS) $(FOX_CFLAGS)
LIBS += $(PKG_LIBS) $(FOX_LIBS)

endif


irmpconfig_gui: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o irmpconfig_gui

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

all: irmpconfig_gui

clean:
	rm -f *.o irmpconfig_gui irmpconfig_gui.exe

.PHONY: clean
