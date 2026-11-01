#include <stdio.h>
#include <string.h>

#define MAX_NOME 50
#define CAPACIDADE_MAX 100

typedef struct {
    int id;
    char nome[MAX_NOME];
    int preco_centavos;
    int quantidade_estoque;
    int ativo;
} Produto;

// Descarta o que sobrou na linha digitada (inclusive o '\n')
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int cadastrar_produto(Produto estoque[], int *total_produtos) {
    if (*total_produtos >= CAPACIDADE_MAX) {
        printf("\n[Erro] Capacidade maxima de estoque atingida!\n");
        return 0;
    }

    Produto novo = {0};
    novo.id = *total_produtos + 1;
    novo.ativo = 1;

    printf("\n--- Cadastrar Novo Produto (ID: %d) ---\n", novo.id);

    // Nome: nao aceita vazio e descarta o excesso se passar do limite
    size_t len;
    do {
        printf("Nome do produto: ");
        if (fgets(novo.nome, sizeof(novo.nome), stdin) == NULL) {
            return 0;
        }
        len = strcspn(novo.nome, "\n");
        if (novo.nome[len] == '\0') {
            limpar_buffer(); // linha maior que o vetor: joga fora o resto
        }
        novo.nome[len] = '\0';
        if (len == 0) {
            printf("[Erro] O nome nao pode ficar vazio.\n");
        }
    } while (len == 0);

    // Preco: le em reais, valida e converte para centavos
    float preco_lido = 0.0f;
    while (1) {
        printf("Preco (ex: 25.50): R$ ");
        int ok = scanf("%f", &preco_lido);
        if (ok == EOF) {
            return 0;
        }
        limpar_buffer();
        if (ok == 1 && preco_lido >= 0.0f) {
            break;
        }
        printf("[Erro] Preco invalido. Digite um numero positivo.\n");
    }
    novo.preco_centavos = (int)(preco_lido * 100.0f + 0.5f);

    // Quantidade: inteiro, nao negativo
    while (1) {
        printf("Quantidade em estoque: ");
        int ok = scanf("%d", &novo.quantidade_estoque);
        if (ok == EOF) {
            return 0;
        }
        limpar_buffer();
        if (ok == 1 && novo.quantidade_estoque >= 0) {
            break;
        }
        printf("[Erro] Quantidade invalida. Digite um inteiro maior ou igual a zero.\n");
    }

    estoque[*total_produtos] = novo;
    (*total_produtos)++;

    printf("\n[Sucesso] Produto '%s' cadastrado com exito!\n", novo.nome);
    return 1;
}

void listar_produtos(const Produto estoque[], int total_produtos) {
    printf("\n=================== LISTA DE PRODUTOS ===================\n");

    if (total_produtos == 0) {
        printf("Nenhum produto cadastrado ate o momento.\n");
        printf("=========================================================\n");
        return;
    }

    printf("%-5s | %-25s | %-12s | %-8s\n", "ID", "Nome", "Preco", "Estoque");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < total_produtos; i++) {
        if (!estoque[i].ativo) {
            continue;
        }

        // 2550 / 100 = 25 (reais) e 2550 % 100 = 50 (centavos)
        int reais = estoque[i].preco_centavos / 100;
        int centavos = estoque[i].preco_centavos % 100;

        printf("%-5d | %-25s | R$ %6d,%02d | %-8d\n",
               estoque[i].id,
               estoque[i].nome,
               reais,
               centavos,
               estoque[i].quantidade_estoque);
    }

    printf("=========================================================\n");
}

int main(void) {
    Produto estoque[CAPACIDADE_MAX];
    int total_produtos = 0;
    int opcao = 0;

    do {
        printf("\n=== SISTEMA DE GESTAO DE ESTOQUE ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        int ok = scanf("%d", &opcao);
        if (ok == EOF) {
            break;
        }
        if (ok != 1) {
            printf("\n[Erro] Entrada invalida. Digite um numero.\n");
            limpar_buffer();
            opcao = -1; // evita que o valor antigo encerre o laco sem querer
            continue;
        }

        limpar_buffer();

        switch (opcao) {
            case 1:
                cadastrar_produto(estoque, &total_produtos);
                break;
            case 2:
                listar_produtos(estoque, total_produtos);
                break;
            case 0:
                printf("\nEncerrando o programa... Ate mais!\n");
                break;
            default:
                printf("\n[Aviso] Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
