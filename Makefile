CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Wwrite-strings -O3
DBGFLAGS = -std=gnu99 -pedantic -Wall -Wwrite-strings -ggdb3 -DDEBUG
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
DBGOBJS=$(patsubst %.c,%.dbg.o,$(SRCS))
.PHONY: clean depend all
all: ganylogs ganylogs-debug
ganylogs: $(OBJS)
	   gcc -o $@ -O3 $(OBJS)
ganylogs-debug: $(DBGOBJS)
		 gcc -o $@ -ggdb3 $(DBGOBJS)
%.dbg.o: %.c
	 gcc $(DBGFLAGS) -c -o $@ $<
clean:
	rm -f ganylogs ganylogs-debug *.o *.c~ *.h~
depend:
	makedepend $(SRCS)
	makedepend -a -o .dbg.o  $(SRCS)
# DO NOT DELETE
anotherFile.o: anotherHeader.h someHeader.h
oneFile.o: oneHeader.h someHeader.h
