CC = gcc
CFLAGS = -W -Wall
LDFLAGS =
EXEC = sacADos

all: $(EXEC)

sacADos: branchAndBound.o lecture.o
	$(CC) -o sacADos branchAndBound.o lecture.o $(LDFLAGS)

branchAndBound.o: branchAndBound.c
	$(CC) -o branchAndBound.o -c branchAndBound.c $(CFLAGS)

lecture.o: lecture.c branchAndBound.h
	$(CC) -o lecture.o -c lecture.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

