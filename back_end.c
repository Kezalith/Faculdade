#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_CATEGORIES 100
#define MAX_CARDS 100
#define MAX_TITLE 100
#define MAX_DESCRIPTION 255
#define MAX_IMAGE_PATH 255

// Estrutura que representa um card
typedef struct {
    char titulo[MAX_TITLE];
    char descricao[MAX_DESCRIPTION];
    char caminhoImagem[MAX_IMAGE_PATH];
} Card;

// Estrutura que representa uma categoria com vários cards
typedef struct {
    char nomeCategoria[MAX_TITLE];
    Card cards[MAX_CARDS];
    int quantidadeCards;
} Categoria;

// Variáveis globais
Categoria categorias[MAX_CATEGORIES];
int quantidadeCategorias = 0;

// Prototipação das funções
void criarCategoria();
void entrarCategoria();
void adicionarCard(Categoria *categoria);
void verCards(Categoria *categoria);
void listarCategorias();
void salvarCategorias();
void carregarCategorias();
void excluirCategoria();
void excluirCard(Categoria *categoria);

int main() {
    int opcao;
    setlocale(LC_ALL, "Portuguese");

    // Carregar categorias de um arquivo ao iniciar (se existir)
    carregarCategorias();

    while (1) {
        // Exibe o menu principal
        printf("\nMenu Principal:\n");
        printf("1. Criar uma categoria\n");
        printf("2. Entrar em uma categoria\n");
        printf("3. Excluir uma categoria\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer

        // Trata a opção escolhida
        switch (opcao) {
            case 1:
                criarCategoria();
                break;
            case 2:
                entrarCategoria();
                break;
            case 3:
                excluirCategoria();
                break;
            case 0:
                salvarCategorias(); // Salva as categorias ao sair
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}

// Função para criar uma nova categoria
void criarCategoria() {
    if (quantidadeCategorias >= MAX_CATEGORIES) {
        printf("Número máximo de categorias atingido!\n");
        return;
    }

    printf("Digite o nome da nova categoria: ");
    fgets(categorias[quantidadeCategorias].nomeCategoria, MAX_TITLE, stdin);
    categorias[quantidadeCategorias].nomeCategoria[strcspn(categorias[quantidadeCategorias].nomeCategoria, "\n")] = 0; // Remove o \n

    categorias[quantidadeCategorias].quantidadeCards = 0;
    quantidadeCategorias++;

    printf("Categoria criada com sucesso!\n");
}

// Função para listar todas as categorias
void listarCategorias() {
    printf("\nCategorias existentes:\n");
    for (int i = 0; i < quantidadeCategorias; i++) {
        printf("%d. %s\n", i, categorias[i].nomeCategoria);
    }
}

// Função para entrar em uma categoria existente
void entrarCategoria() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria criada ainda. Volte e crie uma.\n");
        return;
    }

    listarCategorias();
    printf("%d. Voltar\n", quantidadeCategorias);
    int escolha;
    printf("Escolha uma categoria para entrar: ");
    scanf("%d", &escolha);
    getchar();  // Limpar o buffer

    if (escolha == quantidadeCategorias) {
        return;  // Voltar
    } else if (escolha >= 0 && escolha < quantidadeCategorias) {
        Categoria *categoriaSelecionada = &categorias[escolha];
        int opcao;
        while (1) {
            printf("\nVocê está na categoria '%s'\n", categoriaSelecionada->nomeCategoria);
            printf("1. Ver cards\n");
            printf("2. Adicionar card\n");
            printf("3. Excluir card\n");
            printf("0. Voltar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            getchar();  // Limpar o buffer

            switch (opcao) {
                case 1:
                    verCards(categoriaSelecionada);
                    break;
                case 2:
                    adicionarCard(categoriaSelecionada);
                    break;
                case 3:
                    excluirCard(categoriaSelecionada);
                    break;
                case 0:
                    return;
                default:
                    printf("Opção inválida! Tente novamente.\n");
            }
        }
    } else {
        printf("Escolha inválida! Tente novamente.\n");
    }
}

// Função para adicionar um novo card a uma categoria
void adicionarCard(Categoria *categoria) {
    if (categoria->quantidadeCards >= MAX_CARDS) {
        printf("Número máximo de cards atingido nesta categoria!\n");
        return;
    }

    Card novoCard;
    printf("Digite o título do card: ");
    fgets(novoCard.titulo, MAX_TITLE, stdin);
    novoCard.titulo[strcspn(novoCard.titulo, "\n")] = 0;  // Remove o \n

    printf("Digite a descrição do card: ");
    fgets(novoCard.descricao, MAX_DESCRIPTION, stdin);
    novoCard.descricao[strcspn(novoCard.descricao, "\n")] = 0;  // Remove o \n

    printf("Digite o caminho da imagem: ");
    fgets(novoCard.caminhoImagem, MAX_IMAGE_PATH, stdin);
    novoCard.caminhoImagem[strcspn(novoCard.caminhoImagem, "\n")] = 0;  // Remove o \n

    categoria->cards[categoria->quantidadeCards] = novoCard;
    categoria->quantidadeCards++;

    printf("Card adicionado com sucesso!\n");
}

// Função para ver os cards de uma categoria
void verCards(Categoria *categoria) {
    if (categoria->quantidadeCards == 0) {
        printf("Nenhum card criado nesta categoria ainda.\n");
        return;
    }

    printf("\nCards na categoria '%s':\n", categoria->nomeCategoria);
    for (int i = 0; i < categoria->quantidadeCards; i++) {
        printf("Card %d:\n", i + 1);
        printf("Título: %s\n", categoria->cards[i].titulo);
        printf("Descrição: %s\n", categoria->cards[i].descricao);
        printf("Caminho da imagem: %s\n", categoria->cards[i].caminhoImagem);
        printf("------------------------------\n");
    }
}

// Função para excluir uma categoria
void excluirCategoria() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria para excluir.\n");
        return;
    }

    listarCategorias();
    printf("Escolha uma categoria para excluir: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();  // Limpar o buffer

    if (escolha < 0 || escolha >= quantidadeCategorias) {
        printf("Escolha inválida! Tente novamente.\n");
        return;
    }

    // Remove a categoria
    for (int i = escolha; i < quantidadeCategorias - 1; i++) {
        categorias[i] = categorias[i + 1];
    }
    quantidadeCategorias--;

    printf("Categoria excluída com sucesso!\n");
}

// Função para excluir um card de uma categoria
void excluirCard(Categoria *categoria) {
    if (categoria->quantidadeCards == 0) {
        printf("Nenhum card para excluir nesta categoria.\n");
        return;
    }

    verCards(categoria);
    printf("Escolha um card para excluir: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();  // Limpar o buffer

    if (escolha < 1 || escolha > categoria->quantidadeCards) {
        printf("Escolha inválida! Tente novamente.\n");
        return;
    }

    // Remove o card
    for (int i = escolha - 1; i < categoria->quantidadeCards - 1; i++) {
        categoria->cards[i] = categoria->cards[i + 1];
    }
    categoria->quantidadeCards--;

    printf("Card excluído com sucesso!\n");
}

// Função para salvar categorias e cards em um arquivo
void salvarCategorias() {
    FILE *arquivo = fopen("categorias.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }
    fwrite(&quantidadeCategorias, sizeof(int), 1, arquivo);
    fwrite(categorias, sizeof(Categoria), quantidadeCategorias, arquivo);
    fclose(arquivo);
    printf("Categorias salvas com sucesso!\n");
}

// Função para carregar categorias e cards de um arquivo
void carregarCategorias() {
    FILE *arquivo = fopen("categorias.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de categorias encontrado. Continuando...\n");
        return;
    }
    fread(&quantidadeCategorias, sizeof(int), 1, arquivo);
    fread(categorias, sizeof(Categoria), quantidadeCategorias, arquivo);
    fclose(arquivo);
    printf("Categorias carregadas com sucesso!\n");
}
