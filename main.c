#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "professor/professor.h"
#include "sala/sala.h"
#include "fila/fila.h"
#include "pilha/pilha.h"
#include "busca/busca.h"

int main()
{
    ProfNode *raizProfessores = NULL;
    SalaNode *raizSalas = NULL;
    Fila filasEspera[MAX_SALAS];
    Pilha historico;

    // Inicializar filas de espera para cada sala
    for (int i = 0; i < MAX_SALAS; i++)
    {
        iniciarFila(&filasEspera[i]);
    }
    iniciarPilha(&historico);

    // Carregar dados fixos
    carregarProfessores(&raizProfessores);
    carregarSalas(&raizSalas);

    char cod[10], senha[10];
    ProfNode *professorLogado = NULL;

    printf("=== Sistema de Agendamento de Salas ===\n");
    printf("Login:\n");
    printf("Codigo: ");
    scanf("%s", cod);
    printf("Senha: ");
    scanf("%s", senha);

    professorLogado = buscarProfessor(raizProfessores, cod);
    if (!professorLogado || strcmp(professorLogado->prof.senha, senha) != 0)
    {
        printf("Login invalido.\n");
        liberarArvoreProfessores(raizProfessores);
        liberarArvoreSalas(raizSalas);
        return 1;
    }

    printf("Bem vindo, %s!\n", professorLogado->prof.nome);

    int opcao;
    char salaEscolhida[10];

    do
    {
        printf("\nMenu:\n");
        printf("1 - Listar todas as salas\n");
        printf("2 - Listar salas disponiveis\n");
        printf("3 - Reservar sala\n");
        printf("4 - Cancelar reserva\n");
        printf("5 - Visualizar historico de reservas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\nTodas as salas:\n");
            listarSalas(raizSalas);
            break;
        case 2:
            printf("\nSalas disponiveis:\n");
            listarSalasDisponiveis(raizSalas);
            break;
        case 3:
            printf("Digite o numero da sala para reservar: ");
            scanf("%s", salaEscolhida);

            SalaNode *salaNode = buscarSala(raizSalas, salaEscolhida);
            if (!salaNode)
            {
                printf("Sala nao encontrada.\n");
                break;
            }
            if (salaNode->sala.livre)
            {
                salaNode->sala.livre = 0;
                strcpy(salaNode->sala.professorCod, professorLogado->prof.cod);
                push(&historico, salaEscolhida);
                printf("Sala %s reservada com sucesso!\n", salaEscolhida);
            }
            else
            {
                printf("Sala ocupada, adicionando na fila de espera.\n");
                int idx = buscarIndiceSala(salaEscolhida);
                if (idx >= 0)
                {
                    enfileirar(&filasEspera[idx], professorLogado->prof.cod);
                }
            }

            break;
        case 4:
            if (pop(&historico, salaEscolhida))
            {
                SalaNode *salaNode = buscarSala(raizSalas, salaEscolhida);
                if (salaNode && strcmp(salaNode->sala.professorCod, professorLogado->prof.cod) == 0)
                {
                    salaNode->sala.livre = 1;
                    salaNode->sala.professorCod[0] = '\0';
                    printf("Reserva da sala %s cancelada.\n", salaEscolhida);

                    // Atender fila de espera
                    int idx = buscarIndiceSala(salaEscolhida);
                    if (idx >= 0)
                    {
                        char proxProf[10];
                        desenfileirar(&filasEspera[idx], proxProf);
                        if (proxProf[0] != '\0')
                        {
                            salaNode->sala.livre = 0;
                            strcpy(salaNode->sala.professorCod, proxProf);
                            printf("Sala %s agora reservada para professor %s da fila de espera.\n",
                                   salaEscolhida, proxProf);
                        }
                    }
                }
                else
                {
                    printf("Voce nao possui reserva para a sala %s.\n", salaEscolhida);
                }
            }
            else
            {
                printf("Nenhuma reserva para cancelar.\n");
            }
            break;
        case 5:
            printf("Historico de reservas:\n");
            mostrarPilha(&historico);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarArvoreProfessores(raizProfessores);
    liberarArvoreSalas(raizSalas);
    // Liberar filas e pilha
    for (int i = 0; i < MAX_SALAS; i++)
    {
        liberarFila(&filasEspera[i]);
    }
    liberarPilha(&historico);

    return 0;
}
