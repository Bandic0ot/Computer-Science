#Matthew Mulenga
#mam558
#1144528
#Sean Robson-Kullman
#skr519
#11182480
#   Makefile
#	cmpt332
#	Assignment 1
# 	Sept 15, 2017

#inspired from the make file that was provided in tutorial.
# CMPT 332 Fall 2017 - Week 1 Threads Makefile



CC       = gcc
CFLAGS   = -g -O2
CPPFLAGS = -std=c99 -Wall -pedantic

.PHONEY: all clean unix windows test

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

unix: pthread
windows: wthread

thread_$(ARCH).o: thread.c thread.h

pthread: pthread.o thread_$(ARCH).o
pthread.o: pthread.c thread.h

wthread: wthread.o thread_$(ARCH).o
wthread.o: wthread.c thread.h

all:$(TARGET)

unix: mytestlist
windows: clean

test: test.o
test.o: liblist.a testlist.c list.h

list_adders.o: list_adders.c list.h
list_removers.o: list_removers.c list.h
list_movers.o: list_movers.c list.h

liblist.a: list_adders.o list_removers.o list_movers.o
	ar rcs liblist.a list_adders.o list_removers.o list_movers.o

mytestlist: liblist.a mytestlist.o
mytestlist.o: mytestlist.c list.h



%_$(ARCH).o %.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf *.o pthread whtread.exe
