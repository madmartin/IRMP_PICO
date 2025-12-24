
PROJECTNAME=irmpalarm

CC              = g++

CFLAGS          = -O -Wall

TMPDIR = /tmp


all: irmpalarm

.c.o:
	$(CC) $(CFLAGS) -c $<

irmpalarm: irmpalarm.o
	$(CC) -o irmpalarm irmpalarm.o

clean:
	rm -f irmpalarm.o
	rm -f irmpalarm
