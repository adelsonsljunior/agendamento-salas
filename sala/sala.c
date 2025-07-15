#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"

// Dados pre-definidos de salas
Sala salasFixas[MAX_SALAS] = {
    {"S101", 1, ""},
    {"S102", 1, ""},
    {"S103", 1, ""},
    {"S104", 1, ""},
    {"S105", 1, ""}};

void carregarSalas(SalaNode **raiz)
{
    *raiz = NULL;
    for (int i = 0; i < MAX_SALAS; i++)
    {
        *raiz = inserirSala(*raiz, salasFixas[i]);
    }
}

SalaNode *inserirSala(SalaNode *raiz, Sala s)
{
    if (raiz == NULL)
    {
        SalaNode *novo = (SalaNode *)malloc(sizeof(SalaNode));
        novo->sala = s;
        novo->ant = novo->prox = NULL;
        return novo;
    }
    if (strcmp(s.numero, raiz->sala.numero) < 0)
        raiz->ant = inserirSala(raiz->ant, s);
    else
        raiz->prox = inserirSala(raiz->prox, s);
    return raiz;
}

SalaNode *buscarSala(SalaNode *raiz, const char *numero)
{
    if (raiz == NULL)
        return NULL;
    int cmp = strcmp(numero, raiz->sala.numero);
    if (cmp == 0)
        return raiz;
    else if (cmp < 0)
        return buscarSala(raiz->ant, numero);
    else
        return buscarSala(raiz->prox, numero);
}

void listarSalas(SalaNode *raiz)
{
    if (raiz == NULL)
        return;
    listarSalas(raiz->ant);
    printf("Sala %s - %s\n", raiz->sala.numero, raiz->sala.livre ? "Livre" : "Ocupada");
    listarSalas(raiz->prox);
}

void listarSalasDisponiveis(SalaNode *raiz)
{
    if (raiz == NULL)
        return;
    listarSalasDisponiveis(raiz->ant);
    if (raiz->sala.livre)
        printf("Sala %s - Livre\n", raiz->sala.numero);
    listarSalasDisponiveis(raiz->prox);
}

void liberarArvoreSalas(SalaNode *raiz)
{
    if (raiz == NULL)
        return;
    liberarArvoreSalas(raiz->ant);
    liberarArvoreSalas(raiz->prox);
    free(raiz);
}

// Função auxiliar para buscar índice da sala no vetor fixo (para filasEspera[])
int buscarIndiceSala(const char *numero)
{
    for (int i = 0; i < MAX_SALAS; i++)
    {
        if (strcmp(salasFixas[i].numero, numero) == 0)
        {
            return i;
        }
    }
    return -1;
}
