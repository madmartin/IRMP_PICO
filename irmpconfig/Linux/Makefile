CXX ?= g++

CXXFLAGS = -O -Wall

all: irmpconfig

.c.o:
	$(CXX) $(CXXFLAGS) -c $<

irmpconfig: irmpconfig.o
	$(CXX) -o irmpconfig irmpconfig.o

#$(LIBS)

clean:
	rm -f *.o irmpconfig
