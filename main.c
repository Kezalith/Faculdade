#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Estrutura que representa um bot�o com suas dimens�es e textura
typedef struct {
    int x, y, w, h;
    SDL_Texture* texture;
} Button;

// Verifica se o mouse est� dentro dos limites do bot�o
bool IsIn(Button* button, int mouseX, int mouseY) {
    return (mouseX > button->x && mouseX < (button->x + button->w) &&
            mouseY > button->y && mouseY < (button->y + button->h));
}

// Renderiza um bot�o na tela
void RenderButton(SDL_Renderer* renderer, Button* button) {
    SDL_Rect buttonRect = { button->x, button->y, button->w, button->h };
    SDL_RenderCopy(renderer, button->texture, NULL, &buttonRect);
}

int main(int argc, char** argv) {
    // Inicializa a SDL para v�deo
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n�o p�de ser inicializada! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Inicializa a extens�o para imagens
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("SDL_image n�o p�de ser inicializada! IMG_Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Cria uma janela com tamanho e posi��o centralizados
    SDL_Window* window = SDL_CreateWindow("Projeto Faculdade",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1360, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);

    if (window == NULL) {
        printf("A janela n�o p�de ser criada! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Carrega e define um �cone para a janela
    SDL_Surface* icon = SDL_LoadBMP("icone.bmp");
    if (icon != NULL) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    // Cria um renderer para desenhar na janela
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("O renderer n�o p�de ser criado! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Obt�m o tamanho da janela
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);

    // Define dimens�es e espa�amento entre os bot�es
    const int buttonWidth = 205;
    const int buttonHeight = 30;
    const int spacing = 50;

    // Calcula a posi��o inicial dos bot�es
    int startX = (screenWidth - (3 * buttonWidth + 2 * spacing)) / 2;

    // Inicializa os bot�es com suas posi��es e dimens�es
    Button button1 = { startX, 25, buttonWidth, buttonHeight, NULL };
    Button button2 = { startX + buttonWidth + spacing, 25, buttonWidth, buttonHeight, NULL };
    Button button3 = { startX + 2 * (buttonWidth + spacing), 25, buttonWidth, buttonHeight, NULL };
    Button button4 = { 0, 0, 0, 0, NULL };
    Button button5 = { 0, 0, 0, 0, NULL };

    // Carrega imagens para os bot�es
    SDL_Surface* buttonImage1 = IMG_Load("bnt_categoria.png");
    SDL_Surface* buttonImage2 = IMG_Load("bnt_add_categoria.png");
    SDL_Surface* buttonImage3 = IMG_Load("bnt_add_card.png");
    SDL_Surface* buttonImage4 = IMG_Load("bnt_nova_janela.png");
    SDL_Surface* buttonImage5 = IMG_Load("bnt_config.png");

    if (buttonImage1 == NULL || buttonImage2 == NULL || buttonImage3 == NULL) {
        printf("N�o foi poss�vel carregar as imagens! IMG_Error: %s\n", IMG_GetError());
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

    // Libera as superf�cies ap�s criar as texturas
    SDL_FreeSurface(buttonImage1);
    SDL_FreeSurface(buttonImage2);
    SDL_FreeSurface(buttonImage3);
    SDL_FreeSurface(buttonImage4);
    SDL_FreeSurface(buttonImage5);

    // Vari�veis para os bot�es din�micos
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

            // Verifica se o bot�o esquerdo do mouse foi clicado
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Se o bot�o 2 for clicado, cria dois novos bot�es din�micos
                if (IsIn(&button2, mouseX, mouseY)) {
                    printf("Bot�o 2 foi clicado! Criando dois novos bot�es...\n");

                    // Realoca mem�ria para novos bot�es
                    numDynamicButtons += 2;
                    dynamicButtons = realloc(dynamicButtons, numDynamicButtons * sizeof(Button));

                    // Configura o primeiro novo bot�o
                    dynamicButtons[numDynamicButtons - 2].x = startX;
                    dynamicButtons[numDynamicButtons - 2].y = spacing + (numDynamicButtons / 2) * (2 * buttonHeight);
                    dynamicButtons[numDynamicButtons - 2].w = 3 * buttonWidth + (spacing / 2.5);
                    dynamicButtons[numDynamicButtons - 2].h = 2 * buttonHeight;
                    dynamicButtons[numDynamicButtons - 2].texture = button4.texture;

                    // Configura o segundo novo bot�o
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

        // Renderiza os bot�es
        RenderButton(renderer, &button1);
        RenderButton(renderer, &button2);
        RenderButton(renderer, &button3);

        // Renderiza os bot�es din�micos
        for (int i = 0; i < numDynamicButtons; i++) {
            RenderButton(renderer, &dynamicButtons[i]);
        }

        // Atualiza a tela
        SDL_RenderPresent(renderer);
    }

    // Limpeza e desaloca��o de recursos
    SDL_DestroyTexture(button1.texture);
    SDL_DestroyTexture(button2.texture);
    SDL_DestroyTexture(button3.texture);
    SDL_DestroyTexture(button4.texture);
    SDL_DestroyTexture(button5.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    // Libera a mem�ria dos bot�es din�micos
    free(dynamicButtons);

    return 0;
}
