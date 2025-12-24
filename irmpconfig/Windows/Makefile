all: irmpconfig

CC=gcc
CXX=g++
COBJS=hid.o
CPPOBJS=irmpconfig.o
OBJS=$(COBJS) $(CPPOBJS)
CFLAGS=-g -c -Wall
ifeq ($(MSYSTEM),MINGW32)
LIBS= -lsetupapi -static-libgcc
else ifeq ($(MSYSTEM),MINGW64)
LIBS= -lsetupapi
endif
CXXFLAGS=-g -s

irmpconfig: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o irmpconfig

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f *.o irmpconfig.exe

.PHONY: clean
