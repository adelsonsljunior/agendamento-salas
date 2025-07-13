# Arquivo: Makefile
# Localização: /projeto_agendamento/

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJ = main.o \
      professor/professor.o \
      sala/sala.o \
      fila/fila.o \
      pilha/pilha.o \
      busca/busca.o \
      utils/csv.o

all: agendamento

agendamento: $(OBJ)
	$(CC) $(CFLAGS) -o agendamento $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

professor/professor.o: professor/professor.c professor/professor.h
	$(CC) $(CFLAGS) -c professor/professor.c -o professor/professor.o

sala/sala.o: sala/sala.c sala/sala.h
	$(CC) $(CFLAGS) -c sala/sala.c -o sala/sala.o

fila/fila.o: fila/fila.c fila/fila.h
	$(CC) $(CFLAGS) -c fila/fila.c -o fila/fila.o

pilha/pilha.o: pilha/pilha.c pilha/pilha.h
	$(CC) $(CFLAGS) -c pilha/pilha.c -o pilha/pilha.o

busca/busca.o: busca/busca.c busca/busca.h
	$(CC) $(CFLAGS) -c busca/busca.c -o busca/busca.o

utils/csv.o: utils/csv.c utils/csv.h
	$(CC) $(CFLAGS) -c utils/csv.c -o utils/csv.o

clean:
	rm -f *.o professor/*.o sala/*.o fila/*.o pilha/*.o busca/*.o utils/*.o agendamento
