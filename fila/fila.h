#ifndef FILA_H
#define FILA_H

typedef struct FilaNode {
    char professorCod[10];
    struct FilaNode *next;
} FilaNode;

typedef struct {
    FilaNode *front, *rear;
} Fila;

void initFila(Fila* f);
int filaVazia(Fila* f);
void enfileirar(Fila* f, const char* profCod);
void desenfileirar(Fila* f, char* profCod);
void liberarFila(Fila* f);

#endif
