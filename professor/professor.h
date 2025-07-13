#ifndef PROFESSOR_H
#define PROFESSOR_H

#define MAX_PROFESSORES 3

typedef struct Professor {
    char cod[10];
    char nome[50];
    char email[50];
    char senha[10];
} Professor;

typedef struct ProfNode {
    Professor prof;
    struct ProfNode *esq, *dir;
} ProfNode;

void carregarProfessores(ProfNode** raiz);
ProfNode* inserirProfessor(ProfNode* raiz, Professor p);
ProfNode* buscarProfessor(ProfNode* raiz, const char* cod);
void liberarArvoreProfessores(ProfNode* raiz);

#endif
