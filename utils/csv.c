#include <stdio.h>
#include <string.h>
#include "csv.h"

void gravarReservaCSV(const char* nomeArquivo, const char* profCod, const char* salaNum) {
    FILE *fp = fopen(nomeArquivo, "a");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo %s para gravacao.\n", nomeArquivo);
        return;
    }
    fprintf(fp, "%s,%s\n", profCod, salaNum);
    fclose(fp);
}

void lerReservasCSV(const char* nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }
    char linha[100];
    printf("Reservas registradas:\n");
    while (fgets(linha, sizeof(linha), fp)) {
        char *profCod = strtok(linha, ",");
        char *salaNum = strtok(NULL, ",\n");
        if (profCod && salaNum)
            printf("Professor: %s | Sala: %s\n", profCod, salaNum);
    }
    fclose(fp);
}
