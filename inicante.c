#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // número máximo de peças na fila

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;  // tipo da peça ('I', 'O', 'T', 'L')
    int id;     // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ---------- Funções de controle da fila ----------

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Insere uma peça no final da fila (enqueue)
void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf(" Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Remove a peça da frente da fila (dequeue)
void remover(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf(" Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

// Mostra todas as peças na fila
void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("  Fila de peças vazia.\n");
        return;
    }

    printf("\n Fila de peças:\n");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

// ---------- Funções auxiliares ----------

// Gera automaticamente uma nova peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // escolhe uma forma aleatória
    nova.id = id;
    return nova;
}

// ---------- Função principal ----------

int main() {
    Fila f;
    inicializarFila(&f);
    srand(time(NULL)); // para gerar peças aleatórias diferentes

    int idAtual = 0;
    int opcao;
    Peca p;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserir(&f, gerarPeca(idAtual++));
    }

    printf(" Bem-vindo ao TETRIS STACK - Sistema de Fila de Peças!\n");

    // Menu principal
    do {
        mostrarFila(&f);
        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                remover(&f, &p);
                if (!filaVazia(&f) || f.total < MAX)
                    printf("  Peça jogada: [%c %d]\n", p.nome, p.id);
                break;

            case 2:
                if (!filaCheia(&f)) {
                    inserir(&f, gerarPeca(idAtual++));
                    printf(" Nova peça adicionada!\n");
                } else {
                    printf("  A fila já está cheia, jogue uma peça antes!\n");
                }
                break;

            case 0:
                printf(" Encerrando o jogo...\n");
                break;

            default:
                printf(" Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
