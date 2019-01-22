# Matthew Mulenga
# mam558
# 11144528

CC = gcc
CFLAGS = -g -Wall -pedantic

.PHONY: clean

all: tcp_client tcp_server

tcp_client: tcp_client.o
	$(CC) -o tcp_client tcp_client.o

tcp_server: tcp_server.o
	$(CC) -o tcp_server tcp_server.o

clean:
	rm -rf *.o *_client *_server