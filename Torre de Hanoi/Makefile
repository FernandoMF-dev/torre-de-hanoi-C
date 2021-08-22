CC = gcc
flags = -c -Wall
CFLAGS = -lm
ARQUIVOS = *.o
OBJS = pilha.o notification-enum.o array-utils.o confirm.o ddr-hanoi.o movimento-hanoi.o formacao-hanoi.o hanoi.o main.o
EXE = main
MAIN = main.c

all: main.o
	$(CC) $(OBJS) -o $(EXE)
	./main

main.o: hanoi.o notification-enum.o confirm.o main.c
	$(CC) $(flags) $(MAIN) $(CLFLAGS)

hanoi.o: pilha.o ddr-hanoi.o movimento-hanoi.o notification-enum.o formacao-hanoi.o hanoi.c
	$(CC) $(flags) hanoi.c

pilha.o: pilha.c
	$(CC) $(flags) pilha.c

ddr-hanoi.o: array-utils.o ddr-hanoi.c
	$(CC) $(flags) ddr-hanoi.c

movimento-hanoi.o: pilha.o notification-enum.o movimento-hanoi.c
	$(CC) $(flags) movimento-hanoi.c

formacao-hanoi.o: pilha.o movimento-hanoi.o formacao-hanoi.c
	$(CC) $(flags) formacao-hanoi.c

array-utils.o: array-utils.c
	$(CC) $(flags) array-utils.c

notification-enum.o: notification-enum.c
	$(CC) $(flags) notification-enum.c

confirm.o: notification-enum.o confirm.c
	$(CC) $(flags) confirm.c

passos: main.c
	gcc -E main.c -o main.i
	gcc -S main.i -o main.s
	gcc -c main.s -o main.o
	gcc main.o pilha.o notification-enum.o array-utils.o confirm.o ddr-hanoi.o movimento-hanoi.o formacao-hanoi.o hanoi.o -o main -lm

run:
	./main

listar:
	ls $(ARQUIVOS)

clean:
	rm -f *.o *.i *.s
	rm -f $(EXE)