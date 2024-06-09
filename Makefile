CC=gcc
CFLAGS=-Wall

all: server

server: main.o  server.o
	gcc main.o server.o -o server

main.o: main.c
	gcc -c main.c

server.o: server.c
	gcc -c server.c

clean:
	rm -rf *.o server