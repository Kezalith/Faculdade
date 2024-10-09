#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Estrutura que representa um botão com suas dimensões e textura
typedef struct {
    int x, y, w, h;
    SDL_Texture* texture;
} Button;

// Verifica se o mouse está dentro dos limites do botão
bool IsIn(Button* button, int mouseX, int mouseY) {
    return (mouseX > button->x && mouseX < (button->x + button->w) &&
            mouseY > button->y && mouseY < (button->y + button->h));
}

// Renderiza um botão na tela
void RenderButton(SDL_Renderer* renderer, Button* button) {
    SDL_Rect buttonRect = { button->x, button->y, button->w, button->h };
    SDL_RenderCopy(renderer, button->texture, NULL, &buttonRect);
}

int main(int argc, char** argv) {
    // Inicializa a SDL para vídeo
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL não pôde ser inicializada! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Inicializa a extensão para imagens
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("SDL_image não pôde ser inicializada! IMG_Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Cria uma janela com tamanho e posição centralizados
    SDL_Window* window = SDL_CreateWindow("Projeto Faculdade",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1360, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);

    if (window == NULL) {
        printf("A janela não pôde ser criada! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Carrega e define um ícone para a janela
    SDL_Surface* icon = SDL_LoadBMP("icone.bmp");
    if (icon != NULL) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    // Cria um renderer para desenhar na janela
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("O renderer não pôde ser criado! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Obtém o tamanho da janela
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);

    // Define dimensões e espaçamento entre os botões
    const int buttonWidth = 205;
    const int buttonHeight = 30;
    const int spacing = 50;

    // Calcula a posição inicial dos botões
    int startX = (screenWidth - (3 * buttonWidth + 2 * spacing)) / 2;

    // Inicializa os botões com suas posições e dimensões
    Button button1 = { startX, 25, buttonWidth, buttonHeight, NULL };
    Button button2 = { startX + buttonWidth + spacing, 25, buttonWidth, buttonHeight, NULL };
    Button button3 = { startX + 2 * (buttonWidth + spacing), 25, buttonWidth, buttonHeight, NULL };
    Button button4 = { 0, 0, 0, 0, NULL };
    Button button5 = { 0, 0, 0, 0, NULL };

    // Carrega imagens para os botões
    SDL_Surface* buttonImage1 = IMG_Load("bnt_categoria.png");
    SDL_Surface* buttonImage2 = IMG_Load("bnt_add_categoria.png");
    SDL_Surface* buttonImage3 = IMG_Load("bnt_add_card.png");
    SDL_Surface* buttonImage4 = IMG_Load("bnt_nova_janela.png");
    SDL_Surface* buttonImage5 = IMG_Load("bnt_config.png");

    if (buttonImage1 == NULL || buttonImage2 == NULL || buttonImage3 == NULL) {
        printf("Não foi possível carregar as imagens! IMG_Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Cria texturas a partir das imagens carregadas
    button1.texture = SDL_CreateTextureFromSurface(renderer, buttonImage1);
    button2.texture = SDL_CreateTextureFromSurface(renderer, buttonImage2);
    button3.texture = SDL_CreateTextureFromSurface(renderer, buttonImage3);
    button4.texture = SDL_CreateTextureFromSurface(renderer, buttonImage4);
    button5.texture = SDL_CreateTextureFromSurface(renderer, buttonImage5);

    // Libera as superfícies após criar as texturas
    SDL_FreeSurface(buttonImage1);
    SDL_FreeSurface(buttonImage2);
    SDL_FreeSurface(buttonImage3);
    SDL_FreeSurface(buttonImage4);
    SDL_FreeSurface(buttonImage5);

    // Variáveis para os botões dinâmicos
    Button* dynamicButtons = NULL;
    int numDynamicButtons = 0;

    // Loop principal do programa
    bool running = true;
    SDL_Event event;
    while (running) {
        // Processa eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Verifica se o botão esquerdo do mouse foi clicado
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Se o botão 2 for clicado, cria dois novos botões dinâmicos
                if (IsIn(&button2, mouseX, mouseY)) {
                    printf("Botão 2 foi clicado! Criando dois novos botões...\n");

                    // Realoca memória para novos botões
                    numDynamicButtons += 2;
                    dynamicButtons = realloc(dynamicButtons, numDynamicButtons * sizeof(Button));

                    // Configura o primeiro novo botão
                    dynamicButtons[numDynamicButtons - 2].x = startX;
                    dynamicButtons[numDynamicButtons - 2].y = spacing + (numDynamicButtons / 2) * (2 * buttonHeight);
                    dynamicButtons[numDynamicButtons - 2].w = 3 * buttonWidth + (spacing / 2.5);
                    dynamicButtons[numDynamicButtons - 2].h = 2 * buttonHeight;
                    dynamicButtons[numDynamicButtons - 2].texture = button4.texture;

                    // Configura o segundo novo botão
                    dynamicButtons[numDynamicButtons - 1].x = startX + 3 * buttonWidth + (spacing / 3);
                    dynamicButtons[numDynamicButtons - 1].y = spacing + (numDynamicButtons / 2) * (2 * buttonHeight) - 1;
                    dynamicButtons[numDynamicButtons - 1].w = 84;
                    dynamicButtons[numDynamicButtons - 1].h = 62;
                    dynamicButtons[numDynamicButtons - 1].texture = button5.texture;
                }
            }
        }

        // Define a cor de fundo e limpa a tela
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
        SDL_RenderClear(renderer);

        // Renderiza os botões
        RenderButton(renderer, &button1);
        RenderButton(renderer, &button2);
        RenderButton(renderer, &button3);

        // Renderiza os botões dinâmicos
        for (int i = 0; i < numDynamicButtons; i++) {
            RenderButton(renderer, &dynamicButtons[i]);
        }

        // Atualiza a tela
        SDL_RenderPresent(renderer);
    }

    // Limpeza e desalocação de recursos
    SDL_DestroyTexture(button1.texture);
    SDL_DestroyTexture(button2.texture);
    SDL_DestroyTexture(button3.texture);
    SDL_DestroyTexture(button4.texture);
    SDL_DestroyTexture(button5.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    // Libera a memória dos botões dinâmicos
    free(dynamicButtons);

    return 0;
}
