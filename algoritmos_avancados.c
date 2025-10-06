#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest

// Estrutura que representa uma mansão
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro alocar memória para a sala.\n");
        exit(1); // encerra com código de erro
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função que permite o jogador explorar a mansão
void explorarSalas(Sala* atual) {
    char escolha;
    while (atual != NULL) {
        printf("\nVocê está na: %s\n", atual->nome);

        // verifica se é um nó ou uma folha(sem camilhos)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho. Você chegou a um cômodo sem saída.\n");
            break;
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

// Função principal que monta o mapa e inicia a exploração
int main() {
    // Criação manual da árvore binária da mansão
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");

    //Montagem de árvore
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    //Início da exploração
    printf("=====================================\n");
    printf("Bem-vindo ao Detective Quest!\nExplore a mansão e encontre pistas...\n");
    printf("=====================================\n");
    explorarSalas(hall);

    //Liberação de memória
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);

}
