#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"

Sala salasFixas[MAX_SALAS] = {
    {"S101", 1, ""},
    {"S102", 1, ""},
    {"S103", 1, ""},
    {"S104", 1, ""},
    {"S105", 1, ""}
};

void carregarSalas(SalaNode** raiz) {
    *raiz = NULL;
    for (int i = 0; i < MAX_SALAS; i++) {
        *raiz = inserirSala(*raiz, salasFixas[i]);
    }
}

SalaNode* inserirSala(SalaNode* raiz, Sala s) {
    if (raiz == NULL) {
        SalaNode* novo = (SalaNode*)malloc(sizeof(SalaNode));
        novo->sala = s;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(s.numero, raiz->sala.numero) < 0)
        raiz->esq = inserirSala(raiz->esq, s);
    else
        raiz->dir = inserirSala(raiz->dir, s);
    return raiz;
}

SalaNode* buscarSala(SalaNode* raiz, const char* numero) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(numero, raiz->sala.numero);
    if (cmp == 0) return raiz;
    else if (cmp < 0) return buscarSala(raiz->esq, numero);
    else return buscarSala(raiz->dir, numero);
}

void listarSalasInOrder(SalaNode* raiz) {
    if (raiz == NULL) return;
    listarSalasInOrder(raiz->esq);
    printf("Sala %s - %s\n", raiz->sala.numero, raiz->sala.livre ? "Livre" : "Ocupada");
    listarSalasInOrder(raiz->dir);
}

void listarSalasDisponiveis(SalaNode* raiz) {
    if (raiz == NULL) return;
    listarSalasDisponiveis(raiz->esq);
    if (raiz->sala.livre)
        printf("Sala %s - Livre\n", raiz->sala.numero);
    listarSalasDisponiveis(raiz->dir);
}

void liberarArvoreSalas(SalaNode* raiz) {
    if (raiz == NULL) return;
    liberarArvoreSalas(raiz->esq);
    liberarArvoreSalas(raiz->dir);
    free(raiz);
}

// Função auxiliar para buscar índice da sala no vetor fixo (para filasEspera[])
int buscarIndiceSala(SalaNode* raiz, const char* numero) {
    for (int i = 0; i < MAX_SALAS; i++) {
        if (strcmp(salasFixas[i].numero, numero) == 0) {
            return i;
        }
    }
    return -1;
}
