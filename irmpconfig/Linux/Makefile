
PROJECTNAME=irmpconfig

CC              = g++

CFLAGS          = -O -Wall
//CFLAGS          = `$(PKG_CONFIG) --cflags libusb` -O -Wall
//LIBS            = `$(PKG_CONFIG) --libs libusb`

all: irmpconfig

.c.o:
	$(CC) $(CFLAGS) -c $<

irmpconfig: irmpconfig.o
	$(CC) -o irmpconfig irmpconfig.o

#$(LIBS)

clean:
	rm -f irmpconfig.o
	rm -f irmpconfig
