#include <string.h>
#include "busca.h"

int buscaBinaria(Sala salas[], int n, const char* numero) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(numero, salas[meio].numero);
        if (cmp == 0) return meio;
        else if (cmp < 0) dir = meio - 1;
        else esq = meio + 1;
    }
    return -1;
}
