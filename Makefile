CC = gcc
CFLAGS = -W -Wall
LDFLAGS =
EXEC = sacADos

all: $(EXEC)

sacADos: sacADos.o
	$(CC) -o sacADos sacADos.o $(LDFLAGS)

sacADos.o: sacADos.c sacADos.h
	$(CC) -o sacADos.o -c sacADos.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

