#include "window.h"
#include "menus.h"
#include "resource.h"

// Declarar o nome da classe da janela
const char g_szClassName[] = "MainWindowClass";

HWND hMainWindow;
HWND hButton;

// Registrar a classe da janela principal
BOOL RegisterMainWindowClass(HINSTANCE hInstance) {
    WNDCLASSEX wc;
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));

    return RegisterClassEx(&wc);
}

// Criar a janela principal
HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Programa",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1360, 768,
        NULL, NULL,
        hInstance, NULL);

    if (hwnd != NULL) {
        ShowWindow(hwnd, nCmdShow);
        UpdateWindow(hwnd);
    }

    return hwnd;
}

// Função de callback para processar mensagens da janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
        case WM_CREATE:
            // Inicializa o menu e o botão
            InitializeMenu(hwnd);
            InitializeButton(hwnd);
            hMainWindow = hwnd;
            break;

        case WM_COMMAND:
            ProcessMenuCommands(hwnd, wParam);
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}
