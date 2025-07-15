#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

// Inicializa a pilha
void iniciarPilha(Pilha *p)
{
    p->top = NULL;
}

// Adiciona um novo nó na pilha
void push(Pilha *p, const char *salaNum, const char *professorCod)
{
    PilhaNode *novo = (PilhaNode *)malloc(sizeof(PilhaNode));
    strcpy(novo->salaNumero, salaNum);
    strcpy(novo->professorCod, professorCod);
    novo->next = p->top;
    p->top = novo;
}

// Remove o nó do topo da pilha
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

// Mostra o conteúdo da pilha
// Exibe o histórico de reservas
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
        printf("Sala: %s | Professor: %s", aux->salaNumero, aux->professorCod);
        aux = aux->next;
    }
}

// Libera a memória alocada para a pilha
void liberarPilha(Pilha *p)
{
    char temp[10];
    while (pop(p, temp))
    {
        // libera todos os nós
    }
}
