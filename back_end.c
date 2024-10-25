#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>

#define MAX_CATEGORIES 100
#define MAX_CARDS 100
#define MAX_TITLE 100
#define MAX_DESCRIPTION 255
#define MAX_IMAGE_PATH 255
#define MAX_FILENAME_LENGTH 260

typedef struct {
    char titulo[MAX_TITLE];
    char descricao[MAX_DESCRIPTION];
    char caminhoImagem[MAX_IMAGE_PATH];
} Card;

typedef struct {
    char nomeCategoria[MAX_TITLE];
    Card cards[MAX_CARDS];
    int quantidadeCards;
} Categoria;

Categoria categorias[MAX_CATEGORIES];
int quantidadeCategorias = 0;

void lerString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void criarCategoria();
void entrarCategoria();
void adicionarCard(Categoria *categoria);
void verCards(const Categoria *categoria);
void listarCategorias();
void salvarCategoria(Categoria *categoria);
void carregarCategorias();
void excluirCategoria();
void excluirCard(Categoria *categoria);
void editarCategoria();
void editarCard(Categoria *categoria);
void encontrarCardEspecifico();

int main() {
    int opcao;
    setlocale(LC_ALL, "Portuguese");
    carregarCategorias();

    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Entrar em uma categoria\n");
        printf("2. Criar uma categoria\n");
        printf("3. Editar uma categoria\n");
        printf("4. Excluir uma categoria\n");
        printf("5. Encontrar Card Específico\n");
        printf("0. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                entrarCategoria();
                break;
            case 2:
                criarCategoria();
                break;
            case 3:
                editarCategoria();
                break;
            case 4:
                excluirCategoria();
                break;
            case 5:
                encontrarCardEspecifico();
                break;
            case 0:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}

void criarCategoria() {
    if (quantidadeCategorias >= MAX_CATEGORIES) {
        printf("Número máximo de categorias atingido!\n");
        return;
    }

    printf("Digite o nome da nova categoria: ");
    lerString(categorias[quantidadeCategorias].nomeCategoria, MAX_TITLE);
    categorias[quantidadeCategorias].quantidadeCards = 0;

    salvarCategoria(&categorias[quantidadeCategorias]);
    quantidadeCategorias++;
    printf("Categoria criada com sucesso!\n");
}

void listarCategorias() {
    printf("\nCategorias existentes:\n");
    for (int i = 0; i < quantidadeCategorias; i++) {
        printf("%d. %s\n", i + 1, categorias[i].nomeCategoria);
    }
}

void entrarCategoria() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria criada ainda.\n");
        return;
    }

    listarCategorias();
    printf("0. Voltar\n");
    int escolha;
    printf("Escolha uma categoria para entrar: ");
    scanf("%d", &escolha);
    getchar();

    if (escolha == 0) {
        return;
    } else if (escolha >= 1 && escolha <= quantidadeCategorias) {
        Categoria *categoriaSelecionada = &categorias[escolha - 1];
        int opcao;

        while (1) {
            printf("\nVocê está na categoria '%s'\n", categoriaSelecionada->nomeCategoria);
            printf("1. Ver cards\n");
            printf("2. Adicionar card\n");
            printf("3. Editar card\n");
            printf("4. Excluir card\n");
            printf("0. Voltar\n\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            getchar();

            switch (opcao) {
                case 1:
                    verCards(categoriaSelecionada);
                    break;
                case 2:
                    adicionarCard(categoriaSelecionada);
                    salvarCategoria(categoriaSelecionada);
                    break;
                case 3:
                    if (categoriaSelecionada->quantidadeCards > 0) {
                        editarCard(categoriaSelecionada);
                        salvarCategoria(categoriaSelecionada);
                    } else {
                        printf("Nenhum card disponível para editar.\n");
                    }
                    break;
                case 4:
                    if (categoriaSelecionada->quantidadeCards > 0) {
                        excluirCard(categoriaSelecionada);
                        salvarCategoria(categoriaSelecionada);
                    } else {
                        printf("Nenhum card disponível para excluir.\n");
                    }
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

void adicionarCard(Categoria *categoria) {
    if (categoria->quantidadeCards >= MAX_CARDS) {
        printf("Número máximo de cards atingido nesta categoria!\n");
        return;
    }

    Card novoCard;

    printf("Digite o título do card: ");
    fgets(novoCard.titulo, MAX_TITLE, stdin);
    novoCard.titulo[strcspn(novoCard.titulo, "\n")] = 0;

    printf("Digite a descrição do card: ");
    fgets(novoCard.descricao, MAX_DESCRIPTION, stdin);
    novoCard.descricao[strcspn(novoCard.descricao, "\n")] = 0;

    printf("Digite o caminho da imagem: ");
    fgets(novoCard.caminhoImagem, MAX_IMAGE_PATH, stdin);
    novoCard.caminhoImagem[strcspn(novoCard.caminhoImagem, "\n")] = 0;

    categoria->cards[categoria->quantidadeCards] = novoCard;
    categoria->quantidadeCards++;

    printf("Card adicionado com sucesso!\n");
}

void verCards(const Categoria *categoria) {
    if (categoria->quantidadeCards == 0) {
        printf("Nenhum card criado nesta categoria ainda.\n");
        return;
    }

    printf("\nCards na categoria '%s':\n", categoria->nomeCategoria);
    printf("------------------------------\n\n");
    for (int i = 0; i < categoria->quantidadeCards; i++) {
        printf("Card %d:\n", i + 1);
        printf("Título: %s\n", categoria->cards[i].titulo);
        printf("Descrição: %s\n", categoria->cards[i].descricao);
        printf("Caminho da imagem: %s\n", categoria->cards[i].caminhoImagem);
        printf("------------------------------\n");
    }
}

void salvarCategoria(Categoria *categoria) {
    char nomeArquivo[260];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.csv", categoria->nomeCategoria);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a categoria.\n");
        return;
    }

    fprintf(arquivo, "Titulo,Descricao,CaminhoImagem\n");

    for (int i = 0; i < categoria->quantidadeCards; i++) {
        fprintf(arquivo, "\"%s\",\"%s\",\"%s\"\n",
                categoria->cards[i].titulo,
                categoria->cards[i].descricao,
                categoria->cards[i].caminhoImagem);
    }

    fclose(arquivo);
    printf("Categoria '%s' salva com sucesso!\n", categoria->nomeCategoria);
}

void carregarCategorias() {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".csv")) {
                FILE *arquivo = fopen(ent->d_name, "r");
                if (arquivo == NULL) {
                    continue;
                }

                char linha[1024];
                fgets(linha, sizeof(linha), arquivo);

                Categoria novaCategoria;
                strcpy(novaCategoria.nomeCategoria, strtok(ent->d_name, "."));
                novaCategoria.quantidadeCards = 0;

                while (fgets(linha, sizeof(linha), arquivo)) {
                    Card novoCard;
                    strcpy(novoCard.titulo, strtok(linha, ","));
                    strcpy(novoCard.descricao, strtok(NULL, ","));
                    strcpy(novoCard.caminhoImagem, strtok(NULL, ","));
                    novaCategoria.cards[novaCategoria.quantidadeCards++] = novoCard;
                }

                categorias[quantidadeCategorias++] = novaCategoria;
                fclose(arquivo);
            }
        }
        closedir(dir);
    }
}

void excluirCategoria() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria criada ainda.\n");
        return;
    }
    listarCategorias();
    printf("0. Voltar\n");
    printf("Escolha uma categoria para excluir: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();

    if (escolha == 0) {
        printf("Ação de exclusão cancelada.\n");
        return;
    }

    if (escolha < 1 || escolha > quantidadeCategorias) {
        printf("Escolha inválida!\n");
        return;
    }

    for (int i = escolha - 1; i < quantidadeCategorias - 1; i++) {
        categorias[i] = categorias[i + 1];
    }
    quantidadeCategorias--;
    printf("Categoria excluída com sucesso!\n");
}

void excluirCard(Categoria *categoria) {
    verCards(categoria);
    printf("Escolha o número do card para excluir: ");
    int numero;
    scanf("%d", &numero);
    getchar();

    if (numero < 1 || numero > categoria->quantidadeCards) {
        printf("Número de card inválido!\n");
        return;
    }

    for (int i = numero - 1; i < categoria->quantidadeCards - 1; i++) {
        categoria->cards[i] = categoria->cards[i + 1];
    }
    categoria->quantidadeCards--;
    printf("Card excluído com sucesso!\n");
}

void editarCategoria() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria criada ainda.\n");
        return;
    }
    listarCategorias();
    printf("Escolha uma categoria para editar: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();

    if (escolha < 1 || escolha > quantidadeCategorias) {
        printf("Escolha inválida!\n");
        return;
    }

    printf("Digite o novo nome da categoria: ");
    lerString(categorias[escolha - 1].nomeCategoria, MAX_TITLE);
    printf("Categoria editada com sucesso!\n");
}

void editarCard(Categoria *categoria) {
    verCards(categoria);
    printf("Escolha o número do card para editar: ");
    int numero;
    scanf("%d", &numero);
    getchar();

    if (numero < 1 || numero > categoria->quantidadeCards) {
        printf("Número de card inválido!\n");
        return;
    }

    Card *cardSelecionado = &categoria->cards[numero - 1];
    printf("Digite o novo título do card (deixe em branco para manter): ");
    char novoTitulo[MAX_TITLE];
    lerString(novoTitulo, MAX_TITLE);
    if (strlen(novoTitulo) > 0) {
        strcpy(cardSelecionado->titulo, novoTitulo);
    }

    printf("Digite a nova descrição do card (deixe em branco para manter): ");
    char novaDescricao[MAX_DESCRIPTION];
    lerString(novaDescricao, MAX_DESCRIPTION);
    if (strlen(novaDescricao) > 0) {
        strcpy(cardSelecionado->descricao, novaDescricao);
    }

    printf("Digite o novo caminho da imagem do card (deixe em branco para manter): ");
    char novoCaminhoImagem[MAX_IMAGE_PATH];
    lerString(novoCaminhoImagem, MAX_IMAGE_PATH);
    if (strlen(novoCaminhoImagem) > 0) {
        strcpy(cardSelecionado->caminhoImagem, novoCaminhoImagem);
    }

    printf("Card editado com sucesso!\n");
}

void encontrarCardEspecifico() {
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria criada ainda.\n");
        return;
    }

    char tituloBuscado[MAX_TITLE];
    printf("Digite o título do card que deseja encontrar: ");
    lerString(tituloBuscado, MAX_TITLE);

    int foundAny = 0;

    int precisaDeAspas = tituloBuscado[0] != '"' || tituloBuscado[strlen(tituloBuscado) - 1] != '"';

    if (precisaDeAspas) {
        char tituloComAspas[MAX_TITLE];
        snprintf(tituloComAspas, sizeof(tituloComAspas), "\"%s\"", tituloBuscado);
        strcpy(tituloBuscado, tituloComAspas);
    }
    printf("\n------------------------------\n\n");
    for (int i = 0; i < quantidadeCategorias; i++) {
        Categoria *categoria = &categorias[i];
        for (int j = 0; j < categoria->quantidadeCards; j++) {
            Card *card = &categoria->cards[j];
            if (strcmp(card->titulo, tituloBuscado) == 0) {
                printf("Card encontrado na categoria '%s':\n", categoria->nomeCategoria);
                printf("Título: %s\n", card->titulo);
                printf("Descrição: %s\n", card->descricao);
                printf("Caminho da imagem: %s\n", card->caminhoImagem);
                printf("------------------------------\n");
                foundAny = 1;
            }
        }
    }

    if (!foundAny) {
        printf("Nenhum card encontrado com o título '%s'.\n", tituloBuscado);
    }
}
