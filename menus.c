#include <windows.h>
#include <stdio.h>
#include "menus.h"
#include "resource.h"
#include "window.h"

void InitializeMenu(HWND hwnd) {
    HMENU hMenu, hSubMenu;

    hMenu = CreateMenu();

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "Abrir");
    AppendMenu(hSubMenu, MF_STRING, ID_FILE_SAVE, "Salvar");
    AppendMenu(hSubMenu, MF_STRING, ID_FILE_CLOSE, "Fechar");
    AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "Sair");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Arquivos");

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_EDIT_CUT, "&Recortar");
    AppendMenu(hSubMenu, MF_STRING, ID_EDIT_COPY, "&Copiar");
    AppendMenu(hSubMenu, MF_STRING, ID_EDIT_PASTE, "&Colar");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Editar");

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_CONFIG_ABOUT, "&Sobre");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Configuração");

    SetMenu(hwnd, hMenu);
}

void ProcessMenuCommands(HWND hwnd, WPARAM wParam) {
    switch (LOWORD(wParam)) {
        case ID_FILE_EXIT:
            if (MessageBox(hwnd, "Tem certeza que deseja sair?", "Confirmação", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            }
            break;

        case ID_EDIT_COPY:
            MessageBox(hwnd, "Parabéns!", "Woo!", MB_OK);
            break;

        case ID_CONFIG_ABOUT:
            MessageBox(hwnd, "Feito por: Caique Moura Neves!", "Sobre!", MB_OK);
            break;
    }
}

void InitializeButton(HWND hwnd) {
    const int buttonWidth = 266;   // Largura dos botões
    const int buttonHeight = 30;    // Altura dos botões
    const int spacing = 50;          // Espaçamento entre os botões
    const int screenWidth = GetSystemMetrics(SM_CXSCREEN);

    // Cálculo da posição inicial do primeiro botão
    int startX = (screenWidth - (3 * buttonWidth + 2 * spacing)) / 2; // centraliza os botões na tela

    // Botão "Categorias"
    hButton = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "BUTTON",
        "Categorias",
        WS_VISIBLE | WS_CHILD | BS_LEFT,
        startX, 25, buttonWidth, buttonHeight,
        hwnd,
        (HMENU)ID_BUTTON_CATEGORY,
        GetModuleHandle(NULL),
        NULL);

    // Botão "Adicionar Categorias"
    hButton = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "BUTTON",
        "Adicionar Categorias",
        WS_VISIBLE | WS_CHILD | BS_LEFT,
        startX + buttonWidth + spacing, 25, buttonWidth, buttonHeight,
        hwnd,
        (HMENU)ID_BUTTON_ADD_CATEGORY,
        GetModuleHandle(NULL),
        NULL);

    // Botão "Adicionar Card"
    hButton = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "BUTTON",
        "Adicionar Card",
        WS_VISIBLE | WS_CHILD | BS_LEFT,
        startX + 2 * (buttonWidth + spacing), 25, buttonWidth, buttonHeight,
        hwnd,
        (HMENU)ID_BUTTON_CARD,
        GetModuleHandle(NULL),
        NULL);
}
