#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void iniciarFila(Fila *f)
{
    f->front = f->rear = NULL;
}

int filaVazia(Fila *f)
{
    return (f->front == NULL);
}

void enfileirar(Fila *f, const char *profCod)
{
    FilaNode *novo = (FilaNode *)malloc(sizeof(FilaNode));
    strcpy(novo->professorCod, profCod);
    novo->next = NULL;
    if (filaVazia(f))
    {
        f->front = f->rear = novo;
    }
    else
    {
        f->rear->next = novo;
        f->rear = novo;
    }
}

void desenfileirar(Fila *f, char *profCod)
{
    if (filaVazia(f))
    {
        profCod[0] = '\0';
        return;
    }
    FilaNode *temp = f->front;
    strcpy(profCod, temp->professorCod);
    f->front = f->front->next;
    if (f->front == NULL)
        f->rear = NULL;
    free(temp);
}

void liberarFila(Fila *f)
{
    while (!filaVazia(f))
    {
        char temp[10];
        desenfileirar(f, temp);
    }
}
