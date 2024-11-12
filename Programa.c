#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>
#include <windows.h>

#define MAX_CATEGORIES 100
#define MAX_CARDS 1000
#define MAX_TITLE 100
#define MAX_DESCRIPTION 1000
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

int lerString(char *buffer, int tamanho, int permiteVazio) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    if (strlen(buffer) >= tamanho - 1) {
        printf("Entrada muito longa, diminua para o tamanho máximo permitido.\n");
    }
    if (strlen(buffer) == 0 && !permiteVazio) {
        printf("Entrada vazia não é permitida.\n");
        return 0;
    }
    return 1;
}

void criarCategoria();
void entrarCategoria();
void adicionarCard(Categoria *categoria);
void mostrarCards(const Categoria *categoria);
void verCards(const Categoria *categoria);
void listarCategorias();
void criarDesign(const Categoria *categoria);
void salvarCategoria(Categoria *categoria);
void carregarCategorias();
void excluirCategoria();
void excluirCard(Categoria *categoria);
void editarCategoria();
void editarCard(Categoria *categoria);
void encontrarCardEspecifico();
void telaCheia();
void entrarCards();
void diretorioPadrao(char *diretorioOriginal);

int main() {
    telaCheia();
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
        printf("0. Sair\n");
        printf("\nObs: Sempre escreva sem acentos!\n\n");
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
        system("cls");
        printf("Número máximo de categorias atingido!\n");
        return;
    }

    printf("Digite o nome da nova categoria: ");
    if (!lerString(categorias[quantidadeCategorias].nomeCategoria, MAX_TITLE,0)) {
        system("cls");
        printf("Não foi possível criar a categoria. Nome inválido.\n");
        return;
    }

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
            printf("\nObs: Para ver os cards é necessario do Node.js!\n\n");
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

void excluirCategoria() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        entrarCards();
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
            system("cls");
            printf("Ação de exclusão cancelada.\n");
            return;
        }

        if (escolha < 1 || escolha > quantidadeCategorias) {
            system("cls");
            printf("Escolha inválida!\n");
            return;
        }

        printf("Tem certeza que deseja excluir a categoria '%s'? (s/n): ", categorias[escolha - 1].nomeCategoria);
        char confirmacao;
        scanf("%c", &confirmacao);
        getchar();
        if (confirmacao != 's' && confirmacao != 'S') {
            printf("Ação de exclusão cancelada.\n");
            return;
        }

        char nomeArquivo[MAX_FILENAME_LENGTH];
        snprintf(nomeArquivo, MAX_FILENAME_LENGTH, "%s.csv", categorias[escolha - 1].nomeCategoria);

        if (remove(nomeArquivo) == 0) {
            printf("Arquivo %s excluído com sucesso!\n", nomeArquivo);
        } else {
            printf("Erro ao excluir o arquivo %s.\n", nomeArquivo);
        }

        for (int i = escolha - 1; i < quantidadeCategorias - 1; i++) {
            categorias[i] = categorias[i + 1];
        }

        quantidadeCategorias--;
        system("cls");
        printf("Categoria excluída com sucesso!\n");
        diretorioPadrao(cwd);
    }
}

void editarCategoria() {
    listarCategorias();
    printf("Escolha o número da categoria para editar: ");
    int indice;
    scanf("%d", &indice);
    getchar();
    indice--;

    if (indice < 0 || indice >= quantidadeCategorias) {
        system("cls");
        printf("Categoria inválida!\n");
        return;
    }

    char novoNome[MAX_TITLE];
    printf("Digite o novo nome da categoria (ou deixe em branco para manter o atual): ");
    if (lerString(novoNome, MAX_TITLE, 1) && strlen(novoNome) > 0) {
        strncpy(categorias[indice].nomeCategoria, novoNome, MAX_TITLE);
    }

    salvarCategoria(&categorias[indice]);
    printf("Categoria editada com sucesso!\n");
}


void adicionarCard(Categoria *categoria) {
    if (categoria->quantidadeCards >= MAX_CARDS) {
        system("cls");
        printf("Número máximo de cards atingido!\n");
        return;
    }

    printf("Digite o título do card: ");
    if (!lerString(categoria->cards[categoria->quantidadeCards].titulo, MAX_TITLE,0)) {
        system("cls");
        printf("Não foi possível adicionar o card. Título inválido.\n");
        return;
    }

    printf("\nDigite a descrição do card: ");
    if (!lerString(categoria->cards[categoria->quantidadeCards].descricao, MAX_DESCRIPTION,0)) {
        system("cls");
        printf("Não foi possível adicionar o card. Descrição inválida.\n");
        return;
    }

    printf("\nObs: Arrate a imagem | O caminho não deve ter aspas | Não pode conter espaços no arquivos e pastas\n\n");
    printf("Digite o caminho da imagem do card: ");
    if (!lerString(categoria->cards[categoria->quantidadeCards].caminhoImagem, MAX_IMAGE_PATH,0)) {
        system("cls");
        printf("Não foi possível adicionar o card. Caminho da imagem inválido.\n");
        return;
    }

    categoria->quantidadeCards++;
    system("cls");
    printf("Card adicionado com sucesso!\n");
}

void excluirCard(Categoria *categoria) {
    system("cls");
    verCards(categoria);
    printf("Escolha o número do card para excluir: ");
    int numero;
    scanf("%d", &numero);
    getchar();

    if (numero < 1 || numero > categoria->quantidadeCards) {
        system("cls");
        printf("Número de card inválido!\n");
        return;
    }

    printf("Tem certeza que deseja excluir o card %d? (s/n): ", numero);
    char confirmacao;
    scanf("%c", &confirmacao);
    getchar();
    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Ação de exclusão cancelada.\n");
        return;
    }

    for (int i = numero - 1; i < categoria->quantidadeCards - 1; i++) {
        categoria->cards[i] = categoria->cards[i + 1];
    }
    categoria->quantidadeCards--;
    system("cls");
    printf("Card excluído com sucesso!\n");
}

void editarCard(Categoria *categoria) {
    if (categoria->quantidadeCards == 0) {
        printf("Esta categoria não possui cards.\n");
        return;
    }

    verCards(categoria);
    printf("Escolha o número do card para editar: ");
    int indice;
    scanf("%d", &indice);
    getchar();
    indice--;

    if (indice < 0 || indice >= categoria->quantidadeCards) {
        system("cls");
        printf("Card inválido!\n");
        return;
    }

    char novoTitulo[MAX_TITLE];
    printf("Digite o novo título do card (ou deixe em branco para manter o atual): ");
    if (lerString(novoTitulo, MAX_TITLE, 1) && strlen(novoTitulo) > 0) {
        strncpy(categoria->cards[indice].titulo, novoTitulo, MAX_TITLE);
    }

    char novaDescricao[MAX_DESCRIPTION];
    printf("Digite a nova descrição do card (ou deixe em branco para manter o atual): ");
    if (lerString(novaDescricao, MAX_DESCRIPTION, 1) && strlen(novaDescricao) > 0) {
        strncpy(categoria->cards[indice].descricao, novaDescricao, MAX_DESCRIPTION);
    }

    char novoCaminhoImagem[MAX_IMAGE_PATH];
    printf("Digite o novo caminho da imagem do card (ou deixe em branco para manter o atual): ");
    if (lerString(novoCaminhoImagem, MAX_IMAGE_PATH, 1) && strlen(novoCaminhoImagem) > 0) {
        strncpy(categoria->cards[indice].caminhoImagem, novoCaminhoImagem, MAX_IMAGE_PATH);
    }
    system("cls");
    printf("Card editado com sucesso!\n");
}

void mostrarCards(const Categoria *categoria) {
    system("cls");
    criarDesign(categoria);
    if (categoria->quantidadeCards == 0) {
        printf("Nenhum card criado nesta categoria ainda.\n");
        return;
    }
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
        char caminhoCards[1024];
        snprintf(caminhoCards, sizeof(caminhoCards), "%s\\Cards", cwd);

        if (_chdir(caminhoCards) != 0) {
            printf("Erro ao mudar para o diretório 'Cards'.\n");
            return;
        }

        system("cls");
        verCards(categoria);
        system("npm run dev");

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

void encontrarCardEspecifico() {
    system("cls");
    if (quantidadeCategorias == 0) {
        system("cls");
        printf("Nenhuma categoria criada ainda.\n");
        return;
    }

    printf("Digite o título do card a ser encontrado: ");
    char tituloBusca[MAX_TITLE];
    if (!lerString(tituloBusca, MAX_TITLE,0)) {
        system("cls");
        printf("Título inválido. A busca foi cancelada.\n");
        return;
    }
    int encontrado = 0;
    Categoria categoriaEncontrada;
    categoriaEncontrada.quantidadeCards = 0;
    for (int i = 0; i < quantidadeCategorias; i++) {
        for (int j = 0; j < categorias[i].quantidadeCards; j++) {
            if (strcmp(categorias[i].cards[j].titulo, tituloBusca) == 0) {
                printf("------------------------------\n");
                printf("Título: %s\n", categorias[i].cards[j].titulo);
                printf("Descrição: %s\n", categorias[i].cards[j].descricao);
                printf("Caminho da Imagem: %s\n", categorias[i].cards[j].caminhoImagem);
                printf("------------------------------\n");
                categoriaEncontrada.cards[categoriaEncontrada.quantidadeCards] = categorias[i].cards[j];
                categoriaEncontrada.quantidadeCards++;
                encontrado = 1;
            }
        }
    }

    if (!encontrado) {
        printf("Card com o título '%s' não encontrado.\n", tituloBusca);
    } else {
        criarDesign(&categoriaEncontrada);
        mostrarCards(&categoriaEncontrada);
    }
}


void entrarCards() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char caminhoCards[1024];
        snprintf(caminhoCards, sizeof(caminhoCards), "%s\\Cards", cwd);

        if (_chdir(caminhoCards) != 0) {
            printf("Erro ao mudar para o diretório 'Cards'. Verifique se o diretório existe.\n");
            return;
        }
    } else {
        printf("Erro ao obter o diretório atual.\n");
    }
}

void salvarCategoria(Categoria *categoria) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        entrarCards();

        char nomeArquivo[260];
        snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.csv", categoria->nomeCategoria);

        FILE *arquivo = fopen(nomeArquivo, "w");
        if (arquivo == NULL) {
            printf("Erro ao salvar a categoria. Verifique se o diretório 'Cards' existe.\n");
            return;
        }

        fprintf(arquivo, "Titulo|Descricao|CaminhoImagem\n");

        for (int i = 0; i < categoria->quantidadeCards; i++) {
            if (strlen(categoria->cards[i].titulo) > 0) {
                fprintf(arquivo, "%s|%s|%s\n",
                        categoria->cards[i].titulo,
                        categoria->cards[i].descricao,
                        categoria->cards[i].caminhoImagem);
            }
        }

        fclose(arquivo);
        printf("Categoria '%s' salva com sucesso!\n", categoria->nomeCategoria);

        diretorioPadrao(cwd);
    }
}

void carregarCategorias() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        entrarCards();

        DIR *dir;
        struct dirent *ent;

        if ((dir = opendir(".")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (strstr(ent->d_name, ".csv")) {
                    FILE *arquivo = fopen(ent->d_name, "r");
                    if (arquivo == NULL) {
                        printf("Erro ao abrir o arquivo %s.\n", ent->d_name);
                        continue;
                    }

                    char linha[1024];
                    fgets(linha, sizeof(linha), arquivo);

                    Categoria novaCategoria;
                    strncpy(novaCategoria.nomeCategoria, strtok(ent->d_name, "."), MAX_TITLE - 1);
                    novaCategoria.nomeCategoria[MAX_TITLE - 1] = '\0';
                    novaCategoria.quantidadeCards = 0;

                    while (fgets(linha, sizeof(linha), arquivo)) {
                        if (strlen(linha) > 1) {
                            Card novoCard;
                            strncpy(novoCard.titulo, strtok(linha, "|"), MAX_TITLE - 1);
                            novoCard.titulo[MAX_TITLE - 1] = '\0';

                            strncpy(novoCard.descricao, strtok(NULL, "|"), MAX_DESCRIPTION - 1);
                            novoCard.descricao[MAX_DESCRIPTION - 1] = '\0';

                            strncpy(novoCard.caminhoImagem, strtok(NULL, "|"), MAX_IMAGE_PATH - 1);
                            novoCard.caminhoImagem[MAX_IMAGE_PATH - 1] = '\0';

                            novaCategoria.cards[novaCategoria.quantidadeCards++] = novoCard;
                        }
                    }

                    categorias[quantidadeCategorias++] = novaCategoria;
                    fclose(arquivo);
                }
            }
            closedir(dir);
        } else {
            printf("Erro ao abrir o diretório 'Cards'.\n");
        }

        diretorioPadrao(cwd);
    }
}

void diretorioPadrao(char *diretorioOriginal) {
    if (_chdir(diretorioOriginal) != 0) {
        printf("Erro ao retornar ao diretório original: %s\n", diretorioOriginal);
    }
}

void criarDesign(const Categoria *categoria) {
    system("cls");
    const char *diretorio = "C:\\Faculdade\\";
    char nomeArquivo[260];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s%s.html", diretorio, categoria->nomeCategoria);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo HTML: %s\n", nomeArquivo);
        return;
    }

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
}

void telaCheia() {
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    for (int i = 0; i < 8; i++) {
        keybd_event(VK_CONTROL, 0, 0, 0);
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
        Sleep(100);
    }
}

