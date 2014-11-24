CC=gcc
CFLAGS=-std=c99 -pedantic -I. -lm
DEPS = MonitorStub.h Semaphore.h Bridge.h Car.h
OBJ = MonitorStub.o Semaphore.o Bridge.o Main.o Car.o

all: BridgePassing

clean:
	rm ./*.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
BridgePassing: $(OBJ)
	$(CC) -o BridgePassing.exe $(OBJ) $(CFLAGS)
