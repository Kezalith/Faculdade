#include <windows.h>
#include <stdio.h>
#include "window.h"
#include "menus.h"
#include "resource.h"

// Instância principal
HINSTANCE hMainInstance;

// Função principal do programa
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hMainInstance = hInstance; // Atribui a instância global

    // Registrar e criar a janela principal
    if (!RegisterMainWindowClass(hInstance)) {
        MessageBox(NULL, "Falha no registro da janela!", "Erro!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateMainWindow(hInstance, nCmdShow);
    if (hwnd == NULL) {
        DWORD error = GetLastError();
        char errorMsg[256];
        sprintf(errorMsg, "Falha na criacao da janela! Erro", error);
        MessageBox(NULL, errorMsg, "Erro!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Loop de mensagens
    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}
