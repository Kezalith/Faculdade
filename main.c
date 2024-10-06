#include <windows.h>
#include <stdio.h>
#include "window.h"
#include "menus.h"
#include "resource.h"

// Inst�ncia principal
HINSTANCE hMainInstance;

// Fun��o principal do programa
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hMainInstance = hInstance; // Atribui a inst�ncia global

    // Registrar e criar a janela principal
    if (!RegisterMainWindowClass(hInstance)) {
        MessageBox(NULL, "Falha no registro da janela!", "Erro!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateMainWindow(hInstance, nCmdShow);
    if (hwnd == NULL) {
        DWORD error = GetLastError();
        char errorMsg[256];
        sprintf(errorMsg, "Falha na criacao da janela! Erro %lu", error);  // sprintf est� correto aqui
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
