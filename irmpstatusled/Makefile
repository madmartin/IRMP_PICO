CXX ?= g++

CXXFLAGS ?= -Wall -O

.c.o:
	$(CXX) $(CXXFLAGS) -c $<

irmpstatusled: irmpstatusled.o
	$(CXX) -o irmpstatusled irmpstatusled.o

all: irmpstatusled

clean:
	rm -f *.o irmpstatusled
