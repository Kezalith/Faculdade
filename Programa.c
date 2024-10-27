#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>
#include <windows.h>
#include <unistd.h>

#define MAX_CATEGORIES 100
#define MAX_CARDS 1000
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
void mostrarCards(const Categoria *categoria);
void verCards(const Categoria *categoria);
void listarCategorias();
void salvarCategoria(Categoria *categoria);
void carregarCategorias();
void excluirCategoria();
void excluirCard(Categoria *categoria);
void editarCategoria();
void editarCard(Categoria *categoria);
void encontrarCardEspecifico();

void telaCheia() {
    keybd_event(VK_MENU, 0, 0, 0); // Pressiona 'Alt'
    keybd_event(VK_RETURN, 0, 0, 0); // Pressiona 'Enter'
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // Solta 'Enter'
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); // Solta 'Alt'
    for (int i = 0; i < 8; i++) {
        keybd_event(VK_CONTROL, 0, 0, 0); // Pressiona 'Ctrl'
        keybd_event(VK_ADD, 0, 0, 0);      // Pressiona '+'
        keybd_event(VK_ADD, 0, KEYEVENTF_KEYUP, 0); // Solta '+'
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // Solta 'Ctrl'
        Sleep(100); // Aguarda um pouco entre as pressões, se necessário
    }
}

int main() {
    telaCheia(); // Coloca o programa em tela cheia ao iniciar
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
    system("cls");
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
        system("cls");
        return;
    } else if (escolha >= 1 && escolha <= quantidadeCategorias) {
        Categoria *categoriaSelecionada = &categorias[escolha - 1];
        int opcao;
        system("cls");
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
                    mostrarCards(categoriaSelecionada);
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
                    system("cls");
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

void mostrarCards(const Categoria *categoria) {
    system("cls");
    if (categoria->quantidadeCards == 0) {
        printf("Nenhum card criado nesta categoria ainda.\n");
        return;
    }

    // Define o diretório onde o HTML será salvo
    const char *diretorio = "C:\\Faculdade\\";

    // Cria o nome do arquivo HTML com o diretório completo
    char nomeArquivo[260];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s%s.html", diretorio, categoria->nomeCategoria);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo HTML.\n");
        return;
    }

    // Adiciona o conteúdo HTML
    fprintf(arquivo, "<!DOCTYPE html>\n");
    fprintf(arquivo, "<html lang='pt-BR'><head><meta charset='UTF-8'><title>Cards de %s</title>\n", categoria->nomeCategoria);
    fprintf(arquivo, "<style>\n");
    fprintf(arquivo, "    body { background-color: rgb(20, 20, 20); color: white; text-align: center; margin: 0; padding: 20px; }\n");
    fprintf(arquivo, "    .container { display: flex; flex-direction: column; align-items: center; }\n");
    fprintf(arquivo, "    div.card { display: block; text-align: center; margin: 10px; border: 1px solid white; padding: 10px; border-radius: 5px; width: 80%%; }\n");
    fprintf(arquivo, "</style>\n");
    fprintf(arquivo, "</head><body>\n");
    fprintf(arquivo, "<div class='container'>\n");
    fprintf(arquivo, "<h1>Cards na categoria '%s'</h1>\n", categoria->nomeCategoria);

    for (int i = 0; i < categoria->quantidadeCards; i++) {
        fprintf(arquivo, "<div class='card'>\n");
        fprintf(arquivo, "<h2>%s</h2>\n", categoria->cards[i].titulo);
        fprintf(arquivo, "<p>%s</p>\n", categoria->cards[i].descricao);
        fprintf(arquivo, "<img src='%s' alt='%s' style='max-width: 300px; max-height: 300px;'>\n", categoria->cards[i].caminhoImagem, categoria->cards[i].titulo);
        fprintf(arquivo, "</div>\n");
    }

    fprintf(arquivo, "</div>\n");
    fprintf(arquivo, "</body></html>\n");
    fclose(arquivo);

    const char *caminhoIndex = "Cards\\index.js";

    FILE *indexFile = fopen(caminhoIndex, "w");
    if (indexFile == NULL) {
        printf("Erro ao criar o arquivo index.js.\n");
        return;
    }

    fprintf(indexFile, "const { app, BrowserWindow } = require('electron');\n");
    fprintf(indexFile, "const { screen } = require('electron');\n\n");
    fprintf(indexFile, "let mainWindow;\n\n");
    fprintf(indexFile, "app.on('ready', () => {\n");
    fprintf(indexFile, "    const { width, height } = screen.getPrimaryDisplay().workAreaSize;\n\n");
    fprintf(indexFile, "    mainWindow = new BrowserWindow({\n");
    fprintf(indexFile, "        width: 960,\n");
    fprintf(indexFile, "        height: height,\n");
    fprintf(indexFile, "        resizable: false,\n");
    fprintf(indexFile, "        autoHideMenuBar: true,\n");
    fprintf(indexFile, "        icon: __dirname + '/icone.ico',\n");
    fprintf(indexFile, "        x: width / 2,\n");
    fprintf(indexFile, "        y: 0,\n");
    fprintf(indexFile, "        frame: true,\n");
    fprintf(indexFile, "        webPreferences: { nodeIntegration: true, contextIsolation: false }\n");
    fprintf(indexFile, "    });\n\n");
    fprintf(indexFile, "    mainWindow.setFullScreenable(false);\n");
    fprintf(indexFile, "    mainWindow.setMinimizable(false);\n");
    fprintf(indexFile, "    mainWindow.loadURL('file:///C:/Faculdade/%s.html');\n", categoria->nomeCategoria);
    fprintf(indexFile, "    mainWindow.on('blur', () => { mainWindow.close(); });\n");
    fprintf(indexFile, "    mainWindow.webContents.on('before-input-event', (event, input) => {\n");
    fprintf(indexFile, "        if (input.key === 'Escape') mainWindow.close();\n");
    fprintf(indexFile, "    });\n");
    fprintf(indexFile, "});\n");
    fclose(indexFile);

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Define o caminho para o diretório "Cards"
        char caminhoCards[1024];
        snprintf(caminhoCards, sizeof(caminhoCards), "%s\\Cards", cwd);

        // Muda para o diretório "Cards" para executar o comando npm
        if (_chdir(caminhoCards) != 0) {
            printf("Erro ao mudar para o diretório 'Cards'.\n");
            return;
        }

        system("cls");
        verCards(categoria);
        system("npm run dev");

        // Retorna ao diretório original
        if (_chdir(cwd) != 0) {
            printf("Erro ao retornar ao diretório original.\n");
            return;
        }
    } else {
        printf("Erro ao obter o diretório atual.\n");
    }
        system("cls");
}


void verCards(const Categoria *categoria) {
    system("cls");
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

    fprintf(arquivo, "Titulo|Descricao|CaminhoImagem\n"); // Usando | como delimitador

    for (int i = 0; i < categoria->quantidadeCards; i++) {
        fprintf(arquivo, "%s|%s|%s\n",
                categoria->cards[i].titulo,
                categoria->cards[i].descricao,
                categoria->cards[i].caminhoImagem);
    }

    fclose(arquivo);
    system("cls");
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
                    strcpy(novoCard.titulo, strtok(linha, "|")); // Usando | como delimitador
                    strcpy(novoCard.descricao, strtok(NULL, "|"));
                    strcpy(novoCard.caminhoImagem, strtok(NULL, "|"));
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
    system("cls");
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
    system("cls");
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
    system("cls");
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
    system("cls");
    if (quantidadeCategorias == 0) {
        printf("Nenhuma categoria criada ainda.\n");
        return;
    }

    char tituloBuscado[MAX_TITLE];
    printf("Digite o título do card que deseja encontrar: ");
    lerString(tituloBuscado, MAX_TITLE);

    int foundAny = 0;

    // Verificar cada categoria em busca do card
    for (int i = 0; i < quantidadeCategorias; i++) {
        Categoria *categoria = &categorias[i];
        for (int j = 0; j < categoria->quantidadeCards; j++) {
            if (strcmp(categoria->cards[j].titulo, tituloBuscado) == 0) {
                printf("Card encontrado na categoria '%s':\n", categoria->nomeCategoria);
                printf("Título: %s\n", categoria->cards[j].titulo);
                printf("Descrição: %s\n", categoria->cards[j].descricao);
                printf("Caminho da imagem: %s\n", categoria->cards[j].caminhoImagem);
                foundAny = 1;
            }
        }
    }

    if (!foundAny) {
        printf("Card com o título '%s' não encontrado em nenhuma categoria.\n", tituloBuscado);
    }
}
