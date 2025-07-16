#ifndef PILHA_H
#define PILHA_H

typedef struct PilhaNode
{
    char salaNumero[10];
    char professorNome[50];
    struct PilhaNode *next;
} PilhaNode;

typedef struct
{
    PilhaNode *top;
} Pilha;

void iniciarPilha(Pilha *p);
void push(Pilha *p, const char *salaNum, const char *professorNome);
int pop(Pilha *p, char *salaNum);
void mostrarPilha(Pilha *p);
void liberarPilha(Pilha *p);
int cancelarReserva(Pilha *p, const char *professorCod, char *salaCancelada);

#endif
