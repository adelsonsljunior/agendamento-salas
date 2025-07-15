#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professor.h"

// Dados pre-definidos de professores
Professor professoresFixos[MAX_PROFESSORES] = {
    {"P01", "Cledja Rolim", "cledja@ifal.edu.br", "1234"},
    {"P02", "Tarsis Marinho", "tarsis@ifal.edu.br", "1234"},
    {"P03", "Fernando Antonio", "fernando@ifal.edu.br", "1234"}};

void carregarProfessores(ProfNode **raiz)
{
    *raiz = NULL;
    for (int i = 0; i < MAX_PROFESSORES; i++)
    {
        *raiz = inserirProfessor(*raiz, professoresFixos[i]);
    }
}

ProfNode *inserirProfessor(ProfNode *raiz, Professor p)
{
    if (raiz == NULL)
    {
        ProfNode *novo = (ProfNode *)malloc(sizeof(ProfNode));
        novo->prof = p;
        novo->ant = novo->prox = NULL;
        return novo;
    }
    if (strcmp(p.cod, raiz->prof.cod) < 0)
        raiz->ant = inserirProfessor(raiz->ant, p);
    else
        raiz->prox = inserirProfessor(raiz->prox, p);
    return raiz;
}

ProfNode *buscarProfessor(ProfNode *raiz, const char *cod)
{
    if (raiz == NULL)
        return NULL;
    int cmp = strcmp(cod, raiz->prof.cod);
    if (cmp == 0)
        return raiz;
    else if (cmp < 0)
        return buscarProfessor(raiz->ant, cod);
    else
        return buscarProfessor(raiz->prox, cod);
}

void liberarArvoreProfessores(ProfNode *raiz)
{
    if (raiz == NULL)
        return;
    liberarArvoreProfessores(raiz->ant);
    liberarArvoreProfessores(raiz->prox);
    free(raiz);
}
