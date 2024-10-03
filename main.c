#include <windows.h>  // Biblioteca necessária para criar a interface do Windows

// Definição de identificadores para os itens de menu
#define ID_FILE_OPEN 9001
#define ID_FILE_SAVE 9002
#define ID_FILE_CLOSE 9003
#define ID_FILE_EXIT 9004
#define ID_EDIT_CUT 9005
#define ID_EDIT_COPY 9006
#define ID_EDIT_PASTE 9007
#define ID_CONFIG_ABOUT 9008

// Nome da classe da janela, usado para registrar a janela
const char g_szClassName[] = "myWindowClass";

// Função de callback para processar mensagens da janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    // Processa diferentes mensagens enviadas para a janela
	switch(Message)
	{
        // Mensagem enviada quando a janela é criada
		case WM_CREATE:
		{
			HMENU hMenu, hSubMenu;  // Variáveis para os menus
			HICON hIcon, hIconSm;   // Variáveis para ícones grandes e pequenos

            // Criação do menu principal da janela
			hMenu = CreateMenu();

            // Criação do submenu "Arquivos" com seus itens
			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "Abrir");
			AppendMenu(hSubMenu, MF_STRING, ID_FILE_SAVE, "Salvar");
			AppendMenu(hSubMenu, MF_STRING, ID_FILE_CLOSE, "Fechar");
			AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "Sair");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Arquivos");

            // Criação do submenu "Editar" com seus itens
			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, ID_EDIT_CUT, "&Recortar");
			AppendMenu(hSubMenu, MF_STRING, ID_EDIT_COPY, "&Copiar");
			AppendMenu(hSubMenu, MF_STRING, ID_EDIT_PASTE, "&Colar");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Editar");

            // Criação do submenu "Configuração" com o item "Sobre"
			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, ID_CONFIG_ABOUT, "&Sobre");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Configuracao");

            // Define o menu criado como o menu da janela
			SetMenu(hwnd, hMenu);

            // Carrega e define ícones grandes e pequenos para a janela
			hIcon = (HICON)LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
			if(hIcon) {
				SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);  // Define ícone grande
			} else {
				MessageBox(hwnd, "Nao foi possivel carregar o icone grande! Ele esta no diretorio de trabalho atual?", "Erro", MB_OK | MB_ICONERROR);
			}

			hIconSm = (HICON)LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
			if(hIconSm) {
				SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);  // Define ícone pequeno
			} else {
				MessageBox(hwnd, "Nao foi possivel carregar o icone pequeno! Ele esta no diretorio de trabalho atual?", "Erro", MB_OK | MB_ICONERROR);
			}
		}
		break;

        // Mensagem enviada quando um item do menu é selecionado
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				// Ação ao selecionar "Sair" do menu Arquivos
				case ID_FILE_EXIT:
				    if (MessageBox(hwnd, "Tem certeza que deseja sair?", "Confirmação", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                        PostMessage(hwnd, WM_CLOSE, 0, 0);  // Envia mensagem para fechar a janela
                    }
                break;

				// Ação ao selecionar "Copiar" no menu Editar
				case ID_EDIT_COPY:
					MessageBox(hwnd, "Parabens!", "Woo!", MB_OK);  // Exibe uma mensagem
				break;

				// Ação ao selecionar "Sobre" no menu Configuração
				case ID_CONFIG_ABOUT:
					MessageBox(hwnd, "Feito por: Caique Moura Neves!", "Sobre!", MB_OK);  // Mostra informações sobre o programa
				break;
			}
		break;

        // Mensagem enviada quando a janela é fechada
		case WM_CLOSE:
			DestroyWindow(hwnd);  // Destrói a janela
		break;

        // Mensagem enviada quando a janela é destruída (fechamento completo)
		case WM_DESTROY:
			PostQuitMessage(0);  // Envia uma mensagem para encerrar o loop de mensagens
		break;

        // Processa todas as outras mensagens não tratadas
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

// Função principal do programa
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;  // Estrutura para definir as propriedades da janela
	HWND hwnd;      // Handle (identificador) da janela
	MSG Msg;        // Estrutura para mensagens da janela

    // Configuração da classe da janela
	wc.cbSize		 = sizeof(WNDCLASSEX);  // Tamanho da estrutura
	wc.style		 = 0;                   // Estilo da janela
	wc.lpfnWndProc	 = WndProc;             // Função de processamento de mensagens
	wc.cbClsExtra	 = 0;                   // Extra para a classe
	wc.cbWndExtra	 = 0;                   // Extra para a janela
	wc.hInstance	 = hInstance;           // Instância do programa
	wc.hIcon		 = NULL;                // Ícone grande (pode ser definido aqui)
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);  // Define o cursor padrão (seta)
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);     // Cor de fundo da janela
	wc.lpszMenuName  = NULL;                // Sem menu na classe (definido depois)
	wc.lpszClassName = g_szClassName;       // Nome da classe da janela
	wc.hIconSm		 = NULL;                // Ícone pequeno (pode ser definido aqui)

    // Registra a classe da janela no sistema
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Falha no registro da janela!", "Erro!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

    // Criação da janela principal
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,             // Estilo estendido da janela
		g_szClassName,                // Nome da classe da janela
		"Programa",                   // Título da janela
		WS_OVERLAPPEDWINDOW,          // Estilo da janela (barras, bordas)
		CW_USEDEFAULT, CW_USEDEFAULT, // Posição inicial da janela
		1360, 768,                    // Tamanho da janela (largura x altura)
		NULL, NULL,                   // Sem janelas parentes e menus
		hInstance, NULL);             // Instância do programa

    // Verifica se a criação da janela foi bem-sucedida
	if(hwnd == NULL)
	{
        // Em caso de erro, obtém o código do erro e exibe uma mensagem
	    DWORD error = GetLastError();
	    char errorMsg[256];
	    sprintf(errorMsg, "Falha na criacao da janela! Erro %lu", error);
	    MessageBox(NULL, errorMsg, "Erro!", MB_ICONEXCLAMATION | MB_OK);
	    return 0;
	}

    // Exibe a janela e atualiza seu conteúdo
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

    // Loop de mensagens da janela
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);   // Traduz mensagens de teclado
		DispatchMessage(&Msg);    // Envia as mensagens para a função de callback (WndProc)
	}

	return Msg.wParam;  // Retorna quando o programa termina
}
