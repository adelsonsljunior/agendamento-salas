#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "professor/professor.h"
#include "sala/sala.h"
#include "fila/fila.h"
#include "pilha/pilha.h"

ProfNode *login(ProfNode *raizProfessores)
{
    char cod[10], senha[10];
    printf("=== Sistema de Agendamento de Salas - IFAL ===\n");
    printf("Login:\n");
    printf("Codigo: ");
    scanf("%s", cod);
    printf("Senha: ");
    scanf("%s", senha);

    ProfNode *professor = buscarProfessor(raizProfessores, cod);
    if (!professor || strcmp(professor->prof.senha, senha) != 0)
    {
        printf("Login invalido.\n");
        return NULL;
    }

    printf("Bem vindo, %s!\n", professor->prof.nome);
    return professor;
}

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

    carregarProfessores(&raizProfessores);
    carregarSalas(&raizSalas);

    int opcao;
    char salaEscolhida[10];

    // Loop que permite o login sem encerra o programa
    while (1)
    {
        ProfNode *professorLogado = login(raizProfessores);
        if (!professorLogado)
            continue;

        // Loop do menu principal
        do
        {
            printf("\nMenu:\n");
            printf("1 - Listar todas as salas\n");
            printf("2 - Listar salas disponiveis\n");
            printf("3 - Reservar sala\n");
            printf("4 - Cancelar reserva\n");
            printf("5 - Visualizar historico de reservas\n");
            printf("6 - Deslogar\n");
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
                    push(&historico, salaEscolhida, professorLogado->prof.nome);
                    printf("Sala %s reservada com sucesso!\n", salaEscolhida);
                }
                else
                {
                    printf("Sala ocupada.\n");
                    int idx = buscarIndiceSala(salaEscolhida);
                    if (idx >= 0)
                    {
                        if (!estaNaFila(&filasEspera[idx], professorLogado->prof.cod))
                        {
                            enfileirar(&filasEspera[idx], professorLogado->prof.cod);
                            printf("Adicionado à fila de espera da sala %s.\n", salaEscolhida);
                        }
                        else
                        {
                            printf("Voce ja esta na fila de espera para esta sala.\n");
                        }
                    }
                }
                break;

            case 4:
                if (cancelarReserva(&historico, professorLogado->prof.nome, salaEscolhida))
                {
                    SalaNode *salaNode = buscarSala(raizSalas, salaEscolhida);
                    if (salaNode)
                    {
                        salaNode->sala.livre = 1;
                        salaNode->sala.professorCod[0] = '\0';
                        printf("Reserva da sala %s cancelada.\n", salaEscolhida);

                        // Atender fila de espera
                        int idx = buscarIndiceSala(salaEscolhida);
                        if (idx >= 0)
                        {
                            char proxProfCod[10];
                            desenfileirar(&filasEspera[idx], proxProfCod);
                            if (proxProfCod[0] != '\0')
                            {
                                ProfNode *proxProf = buscarProfessor(raizProfessores, proxProfCod);
                                if (proxProf)
                                {
                                    salaNode->sala.livre = 0;
                                    strcpy(salaNode->sala.professorCod, proxProf->prof.cod);
                                    push(&historico, salaEscolhida, proxProf->prof.nome);
                                    printf("Sala %s agora reservada para professor %s da fila de espera.\n",
                                           salaEscolhida, proxProf->prof.nome);
                                }
                            }
                        }
                    }
                }
                else
                {
                    printf("Voce nao possui reserva ativa para cancelar.\n");
                }
                break;

            case 5:
                printf("Historico de reservas:\n");
                mostrarPilha(&historico);
                break;

            case 6:
                printf("Deslogando...\n\n");
                break;

            case 0:
                printf("Saindo...\n");
                liberarArvoreProfessores(raizProfessores);
                liberarArvoreSalas(raizSalas);
                // Liberar filas e pilha
                for (int i = 0; i < MAX_SALAS; i++)
                    liberarFila(&filasEspera[i]);
                liberarPilha(&historico);
                return 0;

            default:
                printf("Opcao invalida.\n");
            }

        } while (opcao != 6);
    }

    return 0;
}
