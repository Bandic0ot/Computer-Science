# Matthew Mulenga
# mam558
# 11144528

CC = gcc
CFLAGS = -g -I -Wall -pedantic

.PHONY: clean

all: tcp_client tcp_server

tcp_client: tcp_client.o file_transfer.o
	$(CC) -o tcp_client tcp_client.o file_transfer.o

tcp_server: tcp_server.o file_transfer.o
	$(CC) -o tcp_server tcp_server.o file_transfer.o

clean:
	rm -rf *.o *_client *_server