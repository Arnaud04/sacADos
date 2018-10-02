CC = gcc
CFLAGS = -W -Wall
LDFLAGS =
EXEC = sacADos

all: $(EXEC)

sacADos: branchAndBound.o fichier.o
	$(CC) -o sacADos branchAndBound.o fichier.o $(LDFLAGS)

branchAndBound.o: branchAndBound.c
	$(CC) -o branchAndBound.o -c branchAndBound.c $(CFLAGS)

fichier.o: fichier.c branchAndBound.h
	$(CC) -o fichier.o -c fichier.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

