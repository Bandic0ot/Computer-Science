# Matthew Mulenga
# mam558
# 11144528

CC = gcc
CFLAGS = -g -I -Wall -pedantic 
LDLIBS = -pthread

.PHONY: clean

all: node logger

node: node.o tcp.o
	$(CC) -o node node.o tcp.o $(LDLIBS)

logger: logger.o tcp.o
	$(CC) -o logger logger.o tcp.o $(LDLIBS)

clean:
	rm -rf *.o node logger