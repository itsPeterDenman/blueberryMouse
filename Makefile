CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lbluetooth
DEPS=include/bluetoothSetup.h
OBJ=bluetoothSetup.o main.o

.DEFAULT_GOAL := main.out

%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main.out: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean: 
	rm -f *.o main.o