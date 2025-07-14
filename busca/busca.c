#include <string.h>
#include "busca.h"

int buscaBinaria(Sala salas[], int n, const char *numero)
{
    int inicio = 0, fim = n - 1;
    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(numero, salas[meio].numero);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}
