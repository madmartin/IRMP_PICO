all: irmpalarm

CC=gcc
CXX=g++
COBJS=hid.o
CPPOBJS=irmpalarm.o
OBJS=$(COBJS) $(CPPOBJS)
CFLAGS=-g -c -Wall
ifeq ($(MSYSTEM),MINGW32)
LIBS= -lsetupapi -static-libgcc
else ifeq ($(MSYSTEM),MINGW64)
LIBS= -lsetupapi
endif
CXXFLAGS=-g -s

irmpalarm: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o irmpalarm

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f *.o irmpalarm.exe

.PHONY: clean
