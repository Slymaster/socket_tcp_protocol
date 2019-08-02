CC = gcc
EXEC = server

all: $(EXEC)

server: server.o main.o
	gcc -o server server.o main.o

main.o: main.c lib.h
	gcc -o main.o -c main.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
