#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void iniciarFila(Fila *f)
{
    f->front = f->rear = NULL;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f)
{
    return (f->front == NULL);
}

// Adiciona um novo professor à fila
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

// Remove o professor do início da fila e retorna seu código
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

// Libera a memória alocada para a fila
void liberarFila(Fila *f)
{
    while (!filaVazia(f))
    {
        char temp[10];
        desenfileirar(f, temp);
    }
}

// Verifica se um professor está na fila
int estaNaFila(Fila *f, const char *profCod)
{
    FilaNode *atual = f->front;
    while (atual != NULL)
    {
        if (strcmp(atual->professorCod, profCod) == 0)
            return 1;
        atual = atual->next;
    }
    return 0;
}
