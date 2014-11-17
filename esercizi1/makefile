CC=gcc
CFLAGS=-D DEBUG_SHOW_MAP=1 -Wall -std=c99 -pedantic -I. -lm
DEPS = List.h Hash.h PriorityQueue.h PathFinding.h
OBJ = Hash.o List.o PriorityQueue.o PathFinding.o Main.o

all: PathFind

clean:
	rm ./*.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
PathFind: $(OBJ)
	$(CC) -o PathFind.exe $(OBJ) $(CFLAGS)
