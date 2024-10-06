#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

extern HWND hMainWindow;
extern HWND hButton;

BOOL RegisterMainWindowClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

#endif
