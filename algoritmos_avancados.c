#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest

// Estrutura que representa uma mansão
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct Pista {
    char conteudo[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro alocar memória para a sala.\n");
        exit(1); // encerra com código de erro
    }
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

Pista* inserirPista(Pista* raiz, const char* conteudo) {
    if (raiz == NULL) {
        Pista* nova = (Pista*)malloc(sizeof(Pista));
        if (nova == NULL) {
            printf("Erro ao alocar memória para a pista.\n");
            exit(1);
        }
        strcpy(nova->conteudo, conteudo);
        nova->esquerda = NULL;
        nova->direita= NULL;
        return nova;
    }

    if (strcmp(conteudo, raiz->conteudo) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, conteudo);
    else if (strcmp(conteudo, raiz->conteudo) > 0)
        raiz->direita = inserirPista(raiz->direita, conteudo);

    return raiz;
}

// Função que permite o jogador explorar a mansão
void explorarSalasComPistas(Sala* atual, Pista** arvorePistas) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        printf("Escolha um caminho: (e) esquerda, (d) direita, (s) sair: ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Não há caminho à esquerda.\n");
        } else if (escolha == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Não há caminho à direita.\n");
        } else if (escolha == 's') {
            printf("Exploração encerrada.\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    
    }
}

// Imprime as pistas emordem alfabética
void exibirPistas(Pista* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->conteudo);
        exibirPistas(raiz->direita);
    }
}

void liberarSalas(Sala* raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

void liberarPistas(Pista* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// Função principal que monta o mapa e inicia a exploração
int main() {
    // Criação manual da árvore binária da mansão
    Sala* hall = criarSala("Hall de Entrada", "Pegadas misteriosas");
    Sala* salaEstar = criarSala("Sala de Estar", "Copo quebrado");
    Sala* cozinha = criarSala("Cozinha", "");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala* jardim = criarSala("Jardim", "Luvas sujas");

    //Montagem de árvore
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    // Árvore de pistas inicializada como vazia
    Pista* arvorePistas = NULL;

    //Início da exploração
    printf("=====================================\n");
    printf("Bem-vindo ao Detective Quest!\nExplore a mansão e encontre pistas...\n");
    printf("=====================================\n");
    explorarSalasComPistas(hall, &arvorePistas);

    // Exibição das pistas coletadas
     printf("\nPistas coletadas (em ordem alfabética):\n");
     exibirPistas(arvorePistas);

     //Liberação de memória
     liberarSalas(hall);
     liberarPistas(arvorePistas);

     return 0;

}
