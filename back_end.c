#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��es de limites para categorias, cards e tamanhos de texto
#define MAX_CATEGORIES 100
#define MAX_CARDS 100
#define MAX_TITLE 100
#define MAX_DESCRIPTION 255
#define MAX_IMAGE_PATH 255

// Estrutura que define um card, com t�tulo, descri��o e caminho da imagem
typedef struct {
    char titulo[MAX_TITLE];
    char descricao[MAX_DESCRIPTION];
    char caminhoImagem[MAX_IMAGE_PATH];
} Card;

// Estrutura que define uma categoria contendo v�rios cards
typedef struct {
    char nomeCategoria[MAX_TITLE];
    Card cards[MAX_CARDS];
    int quantidadeCards;
} Categoria;

// Declara��o de vari�veis globais: um array de categorias e o n�mero de categorias criadas
Categoria categorias[MAX_CATEGORIES];
int quantidadeCategorias = 0;

// Declara��o de fun��es utilizadas no programa
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
    setlocale(LC_ALL, "Portuguese"); // Configura a localidade para suporte ao portugu�s

    // Carrega as categorias de um arquivo ao iniciar o programa
    carregarCategorias();

    // Loop principal para exibi��o do menu
    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Criar uma categoria\n");
        printf("2. Entrar em uma categoria\n");
        printf("3. Excluir uma categoria\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer do teclado

        // Executa a op��o escolhida
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
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    }
    return 0;
}

// Fun��o para criar uma nova categoria
void criarCategoria() {
    if (quantidadeCategorias >= MAX_CATEGORIES) {
        printf("N�mero m�ximo de categorias atingido!\n");
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

// Fun��o para listar todas as categorias dispon�veis
void listarCategorias() {
    printf("\nCategorias existentes:\n");
    for (int i = 0; i < quantidadeCategorias; i++) {
        printf("%d. %s\n", i, categorias[i].nomeCategoria);
    }
}

// Fun��o para gerenciar uma categoria espec�fica
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
        return;  // Volta ao menu principal se o usu�rio escolher a �ltima op��o
    } else if (escolha >= 0 && escolha < quantidadeCategorias) {
        Categoria *categoriaSelecionada = &categorias[escolha];
        int opcao;

        // Loop para gerenciar a categoria selecionada
        while (1) {
            printf("\nVoc� est� na categoria '%s'\n", categoriaSelecionada->nomeCategoria);
            printf("1. Ver cards\n");
            printf("2. Adicionar card\n");
            printf("3. Excluir card\n");
            printf("0. Voltar\n");
            printf("Escolha uma op��o: ");
            scanf("%d", &opcao);
            getchar();  // Limpa o buffer do teclado

            // Executa a fun��o correspondente � op��o escolhida
            switch (opcao) {
                case 1:
                    verCards(categoriaSelecionada); // Exibe todos os cards da categoria
                    break;
                case 2:
                    adicionarCard(categoriaSelecionada); // Adiciona um novo card � categoria
                    break;
                case 3:
                    excluirCard(categoriaSelecionada); // Remove um card da categoria
                    break;
                case 0:
                    return; // Sai do gerenciamento da categoria
                default:
                    printf("Op��o inv�lida! Tente novamente.\n");
            }
        }
    } else {
        printf("Escolha inv�lida! Tente novamente.\n");
    }
}

// Fun��o para adicionar um novo card a uma categoria
void adicionarCard(Categoria *categoria) {
    if (categoria->quantidadeCards >= MAX_CARDS) {
        printf("N�mero m�ximo de cards atingido nesta categoria!\n");
        return;
    }

    Card novoCard; // Cria um novo card

    // Solicita o t�tulo do card
    printf("Digite o t�tulo do card: ");
    fgets(novoCard.titulo, MAX_TITLE, stdin);
    novoCard.titulo[strcspn(novoCard.titulo, "\n")] = 0;  // Remove o '\n'

    // Solicita a descri��o do card
    printf("Digite a descri��o do card: ");
    fgets(novoCard.descricao, MAX_DESCRIPTION, stdin);
    novoCard.descricao[strcspn(novoCard.descricao, "\n")] = 0;  // Remove o '\n'

    // Solicita o caminho da imagem do card
    printf("Digite o caminho da imagem: ");
    fgets(novoCard.caminhoImagem, MAX_IMAGE_PATH, stdin);
    novoCard.caminhoImagem[strcspn(novoCard.caminhoImagem, "\n")] = 0;  // Remove o '\n'

    // Adiciona o novo card � categoria
    categoria->cards[categoria->quantidadeCards] = novoCard;
    categoria->quantidadeCards++;

    printf("Card adicionado com sucesso!\n");
}

// Fun��o para exibir todos os cards de uma categoria
void verCards(Categoria *categoria) {
    if (categoria->quantidadeCards == 0) {
        printf("Nenhum card criado nesta categoria ainda.\n");
        return;
    }

    // Exibe as informa��es de cada card
    printf("\nCards na categoria '%s':\n", categoria->nomeCategoria);
    for (int i = 0; i < categoria->quantidadeCards; i++) {
        printf("Card %d:\n", i + 1);
        printf("T�tulo: %s\n", categoria->cards[i].titulo);
        printf("Descri��o: %s\n", categoria->cards[i].descricao);
        printf("Caminho da imagem: %s\n", categoria->cards[i].caminhoImagem);
        printf("------------------------------\n");
    }
}

// Fun��o para excluir uma categoria espec�fica
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
        printf("Escolha inv�lida! Tente novamente.\n");
        return;
    }

    // Remove a categoria deslocando as categorias posteriores
    for (int i = escolha; i < quantidadeCategorias - 1; i++) {
        categorias[i] = categorias[i + 1];
    }
    quantidadeCategorias--;

    printf("Categoria exclu�da com sucesso!\n");
}

// Fun��o para excluir um card de uma categoria
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
        printf("Escolha inv�lida! Tente novamente.\n");
        return;
    }

    // Remove o card selecionado deslocando os cards posteriores
    for (int i = escolha - 1; i < categoria->quantidadeCards - 1; i++) {
        categoria->cards[i] = categoria->cards[i + 1];
    }
    categoria->quantidadeCards--;

    printf("Card exclu�do com sucesso!\n");
}

// Fun��o para salvar todas as categorias e cards em um arquivo
void salvarCategorias() {
    FILE *arquivo = fopen("categorias.dat", "wb"); // Abre o arquivo bin�rio para escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Escreve o n�mero de categorias e, em seguida, cada categoria com seus cards no arquivo
    fwrite(&quantidadeCategorias, sizeof(int), 1, arquivo);
    fwrite(categorias, sizeof(Categoria), quantidadeCategorias, arquivo);

    fclose(arquivo); // Fecha o arquivo ap�s a escrita
    printf("Categorias salvas com sucesso!\n");
}

// Fun��o para carregar as categorias e cards de um arquivo
void carregarCategorias() {
    FILE *arquivo = fopen("categorias.dat", "rb"); // Abre o arquivo bin�rio para leitura
    if (arquivo == NULL) {
        printf("Nenhum arquivo de categorias encontrado. Iniciando um novo.\n");
        return;
    }

    // L� o n�mero de categorias e, em seguida, as categorias com seus cards do arquivo
    fread(&quantidadeCategorias, sizeof(int), 1, arquivo);
    fread(categorias, sizeof(Categoria), quantidadeCategorias, arquivo);

    fclose(arquivo); // Fecha o arquivo ap�s a leitura
    printf("Categorias carregadas com sucesso!\n");
}
