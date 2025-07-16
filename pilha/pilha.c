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
void push(Pilha *p, const char *salaNum, const char *professorNome)
{
    PilhaNode *novo = (PilhaNode *)malloc(sizeof(PilhaNode));
    strcpy(novo->salaNumero, salaNum);
    strcpy(novo->professorNome, professorNome);
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
        printf("Sala: %s | Professor: %s\n", aux->salaNumero, aux->professorNome);
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

int cancelarReserva(Pilha *p, const char *professorCod, char *salaCancelada)
{
    Pilha temp;
    iniciarPilha(&temp);
    int encontrado = 0;

    while (p->top != NULL)
    {
        PilhaNode *topo = p->top;
        if (strcmp(topo->professorNome, professorCod) == 0 && !encontrado)
        {
            strcpy(salaCancelada, topo->salaNumero);
            PilhaNode *remover = p->top;
            p->top = remover->next;
            free(remover);
            encontrado = 1;
            break;
        }
        else
        {
            push(&temp, topo->salaNumero, topo->professorNome);
            PilhaNode *remover = p->top;
            p->top = remover->next;
            free(remover);
        }
    }

    while (temp.top != NULL)
    {
        push(p, temp.top->salaNumero, temp.top->professorNome);
        PilhaNode *remover = temp.top;
        temp.top = remover->next;
        free(remover);
    }

    return encontrado;
}
