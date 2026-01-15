CXX ?= g++

CXXFLAGS ?= -Wall -O

.c.o:
	$(CXX) $(CXXFLAGS) -c $<

irmpconfig: irmpconfig.o
	$(CXX) -o irmpconfig irmpconfig.o

all: irmpconfig

clean:
	rm -f *.o irmpconfig
