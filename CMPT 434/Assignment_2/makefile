# Matthew Mulenga
# mam558
# 11144528

CC = gcc
CFLAGS = -g -I -Wall -pedantic

.PHONY: clean

all: sender receiver

sender: sender.o udp.o queue.o
	$(CC) -o sender sender.o udp.o queue.o

receiver: receiver.o udp.o queue.o
	$(CC) -o receiver receiver.o udp.o queue.o


clean:
	rm -rf *.o sender receiver