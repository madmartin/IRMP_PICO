CXX ?= g++

CXXFLAGS ?= -Wall -O

.c.o:
	$(CXX) $(CXXFLAGS) -c $<

irmpalarm: irmpalarm.o
	$(CXX) -o irmpalarm irmpalarm.o

all: irmpalarm

clean:
	rm -f *.o irmpalarm
