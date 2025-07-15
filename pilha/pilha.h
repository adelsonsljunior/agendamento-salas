#ifndef PILHA_H
#define PILHA_H

typedef struct PilhaNode {
    char salaNumero[10];
    struct PilhaNode *next;
} PilhaNode;

typedef struct {
    PilhaNode *top;
} Pilha;

void iniciarPilha(Pilha* p);
void push(Pilha* p, const char* salaNum);
int pop(Pilha* p, char* salaNum);
void mostrarPilha(Pilha* p);
void liberarPilha(Pilha* p);

#endif
