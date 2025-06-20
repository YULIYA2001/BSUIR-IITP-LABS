// Lab5_client.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab5_client.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// My Global Variables:
#define RBUTTON1_ID 1
#define RBUTTON2_ID 2
#define RBUTTON3_ID 3
#define RBUTTON4_ID 4
#define RBUTTON5_ID 5
#define RBUTTON6_ID 6
#define RBUTTON7_ID 7
#define RBUTTON8_ID 8

#define COLOR_MESSAGE L"ColorMessage"

HWND hWnd_server;   // handle of server
UINT WM_COLOR;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB5CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5CLIENT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 235, 188, nullptr, nullptr, hInstance, nullptr);

   	CreateWindow(L"button", L"Белый",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		0, 0, 110, 40, hWnd, (HMENU)RBUTTON1_ID, hInstance, NULL);
	CreateWindow(L"button", L"Красный",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		0, 30, 110, 40, hWnd, (HMENU)RBUTTON2_ID, hInstance, NULL);
	CreateWindow(L"button", L"Оранжевый",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		0, 60, 110, 40, hWnd, (HMENU)RBUTTON3_ID, hInstance, NULL);
    CreateWindow(L"button", L"Желтый",
        WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 90, 110, 40, hWnd, (HMENU)RBUTTON4_ID, hInstance, NULL);
    CreateWindow(L"button", L"Зеленый",
        WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        110, 0, 110, 40, hWnd, (HMENU)RBUTTON5_ID, hInstance, NULL);
    CreateWindow(L"button", L"Голубой",
        WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        110, 30, 110, 40, hWnd, (HMENU)RBUTTON6_ID, hInstance, NULL);
    CreateWindow(L"button", L"Синий",
        WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        110, 60, 110, 40, hWnd, (HMENU)RBUTTON7_ID, hInstance, NULL);
    CreateWindow(L"button", L"Фиолетовый",
        WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        110, 90, 110, 40, hWnd, (HMENU)RBUTTON8_ID, hInstance, NULL);
    // 1 - выбрана изначально
    // BOOL CheckRadioButton(HWND hDlg, int  nIDFirstButton, int  nIDLastButton, int  nIDCheckButton)        );
    CheckRadioButton(hWnd, RBUTTON1_ID, RBUTTON8_ID, RBUTTON1_ID);

    // UINT RegisterWindowMessageA(LPCSTR lpString)
    WM_COLOR = RegisterWindowMessageA((LPCSTR)COLOR_MESSAGE);
    // HWND FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName)
    hWnd_server = FindWindowA(NULL, (LPCSTR)"Lab5_server");

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            // Parse the menu selections:
            if (wmId >= RBUTTON1_ID && wmId <= RBUTTON8_ID)
		    {
                if (hWnd_server == NULL)
                {
                    MessageBox(hWnd, L"Окно сервера не найдено. Приложение-сервер не запущено",
                        L"Ошибка", MB_OK);
                    break;
                }
                //LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
			    SendMessage(hWnd_server, WM_COLOR, 0, wmId - RBUTTON1_ID);
                // выбрать нажатый цвет
			    CheckRadioButton(hWnd, RBUTTON1_ID, RBUTTON8_ID, wmId);
		    }
            else
            {
                switch (wmId)
                {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

