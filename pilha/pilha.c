#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void iniciarPilha(Pilha *p)
{
    p->top = NULL;
}

void push(Pilha *p, const char *salaNum)
{
    PilhaNode *novo = (PilhaNode *)malloc(sizeof(PilhaNode));
    strcpy(novo->salaNumero, salaNum);
    novo->next = p->top;
    p->top = novo;
}

int pop(Pilha *p, char *salaNum)
{
    if (p->top == NULL)
        return 0;
    PilhaNode *temp = p->top;
    strcpy(salaNum, temp->salaNumero);
    p->top = temp->next;
    free(temp);
    return 1;
}

void mostrarPilha(Pilha *p)
{
    PilhaNode *aux = p->top;
    if (aux == NULL)
    {
        printf("Nenhuma reserva no historico.\n");
        return;
    }
    while (aux != NULL)
    {
        printf("Sala: %s\n", aux->salaNumero);
        aux = aux->next;
    }
}

void liberarPilha(Pilha *p)
{
    char temp[10];
    while (pop(p, temp))
    {
        // libera todos os nós
    }
}
