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

unix: s-chat reader-writer-test

list_adders.o: list_adders.c list.h
list_removers.o: list_removers.c list.h
list_movers.o: list_movers.c list.h

monitor.o: monitor.c monitor.h liblist.a
reader-writer-monitor.o: monitor.o reader-writer.c reader-writer-monitor.h liblist.a

reader-writer-test: reader-writer-test.o libMonitor.a liblist.a
reader-writer-test.o: reader-writer-monitor.c reader-writer.c reader-writer-monitor.h

s-chat: s-chat.o libMonitor.a
s-chat.o: s-chat.c

liblist.a: list_adders.o list_removers.o list_movers.o
	ar rcs liblist.a list_adders.o list_removers.o list_movers.o


libMonitor.a: reader-writer-monitor.o reader-writer.o monitor.o
	ar rcs libMonitor.a monitor.o reader-writer-monitor.o


%_$(ARCH).o %.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o s-chat mytestlist liblist.a libMonitor.a
