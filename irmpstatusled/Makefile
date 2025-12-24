
PROJECTNAME=irmpstatusled

CC              = g++

CFLAGS          = -O -Wall

all: irmpstatusled

.c.o:
	$(CC) $(CFLAGS) -c $<

irmpstatusled: irmpstatusled.o
	$(CC) -o irmpstatusled irmpstatusled.o

clean:
	rm -f irmpstatusled.o
	rm -f irmpstatusled
