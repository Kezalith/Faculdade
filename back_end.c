#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definições de limites para categorias, cards e tamanhos de texto
#define MAX_CATEGORIES 100
#define MAX_CARDS 100
#define MAX_TITLE 100
#define MAX_DESCRIPTION 255
#define MAX_IMAGE_PATH 255

// Estrutura que define um card, com título, descrição e caminho da imagem
typedef struct {
    char titulo[MAX_TITLE];
    char descricao[MAX_DESCRIPTION];
    char caminhoImagem[MAX_IMAGE_PATH];
} Card;

// Estrutura que define uma categoria contendo vários cards
typedef struct {
    char nomeCategoria[MAX_TITLE];
    Card cards[MAX_CARDS];
    int quantidadeCards;
} Categoria;

// Declaração de variáveis globais: um array de categorias e o número de categorias criadas
Categoria categorias[MAX_CATEGORIES];
int quantidadeCategorias = 0;

// Declaração de funções utilizadas no programa
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
    setlocale(LC_ALL, "Portuguese"); // Configura a localidade para suporte ao português

    // Carrega as categorias de um arquivo ao iniciar o programa
    carregarCategorias();

    // Loop principal para exibição do menu
    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Criar uma categoria\n");
        printf("2. Entrar em uma categoria\n");
        printf("3. Excluir uma categoria\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer do teclado

        // Executa a opção escolhida
        switch (opcao) {
            case 1:
                criarCategoria(); // Cria uma nova categoria
                break;
            case 2:
                entrarCategoria(); // Acessa uma categoria para gerenciar cards
                break;
            case 3:
                excluirCategoria(); // Remove uma categoria existente
                break;
            case 0:
                salvarCategorias(); // Salva todas as categorias e cards no arquivo antes de sair
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

    // Solicita o nome da nova categoria
    printf("Digite o nome da nova categoria: ");
    fgets(categorias[quantidadeCategorias].nomeCategoria, MAX_TITLE, stdin);
    categorias[quantidadeCategorias].nomeCategoria[strcspn(categorias[quantidadeCategorias].nomeCategoria, "\n")] = 0; // Remove o '\n' do final

    // Inicializa a quantidade de cards na nova categoria
    categorias[quantidadeCategorias].quantidadeCards = 0;
    quantidadeCategorias++;

    printf("Categoria criada com sucesso!\n");
}

// Função para listar todas as categorias disponíveis
void listarCategorias() {
    printf("\nCategorias existentes:\n");
    for (int i = 0; i < quantidadeCategorias; i++) {
        printf("%d. %s\n", i, categorias[i].nomeCategoria);
    }
}

// Função para gerenciar uma categoria específica
void entrarCategoria() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria criada ainda. Volte e crie uma.\n");
        return;
    }

    listarCategorias(); // Mostra todas as categorias criadas
    printf("%d. Voltar\n", quantidadeCategorias);
    int escolha;
    printf("Escolha uma categoria para entrar: ");
    scanf("%d", &escolha);
    getchar();  // Limpa o buffer do teclado

    if (escolha == quantidadeCategorias) {
        return;  // Volta ao menu principal se o usuário escolher a última opção
    } else if (escolha >= 0 && escolha < quantidadeCategorias) {
        Categoria *categoriaSelecionada = &categorias[escolha];
        int opcao;

        // Loop para gerenciar a categoria selecionada
        while (1) {
            printf("\nVocê está na categoria '%s'\n", categoriaSelecionada->nomeCategoria);
            printf("1. Ver cards\n");
            printf("2. Adicionar card\n");
            printf("3. Excluir card\n");
            printf("0. Voltar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            getchar();  // Limpa o buffer do teclado

            // Executa a função correspondente à opção escolhida
            switch (opcao) {
                case 1:
                    verCards(categoriaSelecionada); // Exibe todos os cards da categoria
                    break;
                case 2:
                    adicionarCard(categoriaSelecionada); // Adiciona um novo card à categoria
                    break;
                case 3:
                    excluirCard(categoriaSelecionada); // Remove um card da categoria
                    break;
                case 0:
                    return; // Sai do gerenciamento da categoria
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

    Card novoCard; // Cria um novo card

    // Solicita o título do card
    printf("Digite o título do card: ");
    fgets(novoCard.titulo, MAX_TITLE, stdin);
    novoCard.titulo[strcspn(novoCard.titulo, "\n")] = 0;  // Remove o '\n'

    // Solicita a descrição do card
    printf("Digite a descrição do card: ");
    fgets(novoCard.descricao, MAX_DESCRIPTION, stdin);
    novoCard.descricao[strcspn(novoCard.descricao, "\n")] = 0;  // Remove o '\n'

    // Solicita o caminho da imagem do card
    printf("Digite o caminho da imagem: ");
    fgets(novoCard.caminhoImagem, MAX_IMAGE_PATH, stdin);
    novoCard.caminhoImagem[strcspn(novoCard.caminhoImagem, "\n")] = 0;  // Remove o '\n'

    // Adiciona o novo card à categoria
    categoria->cards[categoria->quantidadeCards] = novoCard;
    categoria->quantidadeCards++;

    printf("Card adicionado com sucesso!\n");
}

// Função para exibir todos os cards de uma categoria
void verCards(Categoria *categoria) {
    if (categoria->quantidadeCards == 0) {
        printf("Nenhum card criado nesta categoria ainda.\n");
        return;
    }

    // Exibe as informações de cada card
    printf("\nCards na categoria '%s':\n", categoria->nomeCategoria);
    for (int i = 0; i < categoria->quantidadeCards; i++) {
        printf("Card %d:\n", i + 1);
        printf("Título: %s\n", categoria->cards[i].titulo);
        printf("Descrição: %s\n", categoria->cards[i].descricao);
        printf("Caminho da imagem: %s\n", categoria->cards[i].caminhoImagem);
        printf("------------------------------\n");
    }
}

// Função para excluir uma categoria específica
void excluirCategoria() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria para excluir.\n");
        return;
    }

    listarCategorias(); // Mostra todas as categorias
    printf("Escolha uma categoria para excluir: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();  // Limpa o buffer do teclado

    if (escolha < 0 || escolha >= quantidadeCategorias) {
        printf("Escolha inválida! Tente novamente.\n");
        return;
    }

    // Remove a categoria deslocando as categorias posteriores
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

    verCards(categoria); // Exibe os cards da categoria
    printf("Escolha um card para excluir: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();  // Limpa o buffer do teclado

    if (escolha < 1 || escolha > categoria->quantidadeCards) {
        printf("Escolha inválida! Tente novamente.\n");
        return;
    }

    // Remove o card selecionado deslocando os cards posteriores
    for (int i = escolha - 1; i < categoria->quantidadeCards - 1; i++) {
        categoria->cards[i] = categoria->cards[i + 1];
    }
    categoria->quantidadeCards--;

    printf("Card excluído com sucesso!\n");
}

// Função para salvar todas as categorias e cards em um arquivo
void salvarCategorias() {
    FILE *arquivo = fopen("categorias.dat", "wb"); // Abre o arquivo binário para escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Escreve o número de categorias e, em seguida, cada categoria com seus cards no arquivo
    fwrite(&quantidadeCategorias, sizeof(int), 1, arquivo);
    fwrite(categorias, sizeof(Categoria), quantidadeCategorias, arquivo);

    fclose(arquivo); // Fecha o arquivo após a escrita
    printf("Categorias salvas com sucesso!\n");
}

// Função para carregar as categorias e cards de um arquivo
void carregarCategorias() {
    FILE *arquivo = fopen("categorias.dat", "rb"); // Abre o arquivo binário para leitura
    if (arquivo == NULL) {
        printf("Nenhum arquivo de categorias encontrado. Iniciando um novo.\n");
        return;
    }

    // Lê o número de categorias e, em seguida, as categorias com seus cards do arquivo
    fread(&quantidadeCategorias, sizeof(int), 1, arquivo);
    fread(categorias, sizeof(Categoria), quantidadeCategorias, arquivo);

    fclose(arquivo); // Fecha o arquivo após a leitura
    printf("Categorias carregadas com sucesso!\n");
}
