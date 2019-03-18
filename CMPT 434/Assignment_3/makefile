# Matthew Mulenga
# mam558
# 11144528

CC = gcc
CFLAGS = -g -I -Wall -pedantic

.PHONY: clean

all: node logger sandbox

node: node.o tcp.o
	$(CC) -o node node.o tcp.o

logger: logger.o tcp.o
	$(CC) -o logger logger.o tcp.o

sandbox: sandbox.o
	$(CC) -o sandbox sandbox.o

clean:
	rm -rf *.o node logger sandbox 