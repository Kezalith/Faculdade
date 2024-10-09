#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // Inclui SDL_image

// Estrutura para armazenar os dados do bot�o
typedef struct {
    int x, y, w, h;
    SDL_Texture* texture; // Adiciona um campo para armazenar a textura
} Button;

// Fun��o para verificar se o mouse est� sobre o bot�o
bool IsIn(Button* button, int mouseX, int mouseY) {
    return (mouseX > button->x && mouseX < (button->x + button->w) &&
            mouseY > button->y && mouseY < (button->y + button->h));
}

// Fun��o para lidar com o clique do bot�o esquerdo do mouse
bool handle_mouse_leftClick(int mouseX, int mouseY, Button* button1, Button* button2, Button* button3) {
    if (IsIn(button1, mouseX, mouseY)) {
        printf("Bot�o 1 foi clicado!\n");
        return true;
    }
    else if (IsIn(button2, mouseX, mouseY)) {
        printf("Bot�o 2 foi clicado!\n");
        return true;
    }
    else if (IsIn(button3, mouseX, mouseY)) {
        printf("Bot�o 3 foi clicado!\n");
        return true;
    }
    return false;
}

// Fun��o para renderizar um bot�o
void RenderButton(SDL_Renderer* renderer, Button* button) {
    SDL_Rect buttonRect = { button->x, button->y, button->w, button->h };
    SDL_RenderCopy(renderer, button->texture, NULL, &buttonRect); // Renderiza a textura
}

int main(int argc, char** argv) {
    // Inicializa a SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n�o p�de ser inicializada! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Inicializa a SDL_image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("SDL_image n�o p�de ser inicializada! IMG_Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Cria uma janela
    SDL_Window* window = SDL_CreateWindow("Projeto Faculdade",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1360, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);

    if (window == NULL) {
        printf("A janela n�o p�de ser criada! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* icon = SDL_LoadBMP("icone.bmp");
    if (icon == NULL) {
        printf("N�o foi poss�vel carregar o �cone! SDL_Error: %s\n", SDL_GetError());
    } else {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    // Cria um renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("O renderer n�o p�de ser criado! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);

    const int buttonWidth = 205;   // Largura dos bot�es
    const int buttonHeight = 30;    // Altura dos bot�es
    const int spacing = 50;          // Espa�amento entre os bot�es

    // C�lculo da posi��o inicial do primeiro bot�o
    int startX = (screenWidth - (3 * buttonWidth + 2 * spacing)) / 2;


    // Cria��o dos bot�es com imagens
    Button button1 = { startX, 25, buttonWidth, buttonHeight, NULL };
    Button button2 = { startX + buttonWidth + spacing, 25, buttonWidth, buttonHeight, NULL };
    Button button3 = { startX + 2 * (buttonWidth + spacing), 25, buttonWidth, buttonHeight, NULL };

    // Carregar imagens para os bot�es
    SDL_Surface* buttonImage1 = IMG_Load("bnt_categoria.png");
    SDL_Surface* buttonImage2 = IMG_Load("bnt_add_categoria.png");
    SDL_Surface* buttonImage3 = IMG_Load("bnt_add_card.png");

    if (buttonImage1 == NULL || buttonImage2 == NULL || buttonImage3 == NULL) {
        printf("N�o foi poss�vel carregar as imagens! IMG_Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Criar texturas a partir das superf�cies
    button1.texture = SDL_CreateTextureFromSurface(renderer, buttonImage1);
    button2.texture = SDL_CreateTextureFromSurface(renderer, buttonImage2);
    button3.texture = SDL_CreateTextureFromSurface(renderer, buttonImage3);

    // Liberar as superf�cies, j� que agora temos as texturas
    SDL_FreeSurface(buttonImage1);
    SDL_FreeSurface(buttonImage2);
    SDL_FreeSurface(buttonImage3);

    // Loop principal
    bool running = true;
    SDL_Event event;
    while (running) {
        // Processa os eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (handle_mouse_leftClick(mouseX, mouseY, &button1, &button2, &button3)) {
                    printf("Um dos bot�es foi clicado.\n");
                } else {
                    printf("Nenhum bot�o foi clicado.\n");
                }
            }
        }

        // Cor de fundo (branco)
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
        SDL_RenderClear(renderer);

        // Renderiza os bot�es
        RenderButton(renderer, &button1);
        RenderButton(renderer, &button2);
        RenderButton(renderer, &button3);

        // Apresenta o que foi desenhado
        SDL_RenderPresent(renderer);
    }

    // Limpeza
    SDL_DestroyTexture(button1.texture); // Libera a textura do bot�o 1
    SDL_DestroyTexture(button2.texture); // Libera a textura do bot�o 2
    SDL_DestroyTexture(button3.texture); // Libera a textura do bot�o 3
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
