#ifndef SALA_H
#define SALA_H

#define MAX_SALAS 5

typedef struct Sala
{
    char numero[10];
    int livre; // 1 = livre, 0 = ocupada
    char professorCod[10];
} Sala;

typedef struct SalaNode
{
    Sala sala;
    struct SalaNode *ant, *prox;
} SalaNode;

void carregarSalas(SalaNode **raiz);
SalaNode *inserirSala(SalaNode *raiz, Sala s);
SalaNode *buscarSala(SalaNode *raiz, const char *numero);
void listarSalas(SalaNode *raiz);
void listarSalasDisponiveis(SalaNode *raiz);
void liberarArvoreSalas(SalaNode *raiz);

// Retorna índice da sala para filas (necessário para filasEspera[])
int buscarIndiceSala(SalaNode *raiz, const char *numero);

#endif
