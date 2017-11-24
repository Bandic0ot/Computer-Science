# Sean Robson-Kullman
# skr519
# 11182480
# Matthew Mulenga
# mam558
# 11144528

#inspired from the make file that was provided in tutorial.
# CMPT 332 Fall 2017 - Week 1 Threads Makefile

CC       = gcc
CFLAGS   = -g -O2
CPPFLAGS = -std=c90 -Wall -pedantic -Wpedantic

.PHONEY: all clean unix windows

ARCH = $(shell uname -sm | tr -d ' ')

ifneq (,$(findstring MINGW,$(ARCH)))
TARGET = windows

else
TARGET = unix

PTHREADS  = /student/cmpt332/pthreads
CPPFLAGS += -I$(PTHREADS)
LDFLAGS  += -L$(PTHREADS)/lib/$(ARCH)
LDLIBS   += -lpthreads
endif

all: $(TARGET)

unix: filesys

filesys: filesys-sim-monitor.o
filesys-sim-monitor.o: filesys-sim-monitor.c libMonitor.a

liblist.a: liblist.a(list_adders.o list_movers.o list_removers.o list_alloc.o)

list_movers.o: list_movers.c list.h
list_removers.o: list_movers.c list_alloc.c list_alloc.h list.h
list_adders.o: list_adders.c list_alloc.c list_alloc.h list.h
list_alloc.o: list_alloc.c list_alloc.h

# make monitor library
libMonitor.a: libMonitor.a(Monitor.o) liblist.a
Monitor.o: Monitor.c Monitor.h list.h

%_$(ARCH).o %.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o liblist.a libMonitor.a
