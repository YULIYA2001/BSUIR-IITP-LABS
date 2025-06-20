// Lab2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int currentX = 0, currentY = 0;     // текущие координаты
int destX = 0, destY = 0;           // координаты назначения
int TIMER_ID = 1;
HPEN pen, redPen;
HBRUSH brush;


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
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
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
      CW_USEDEFAULT, 0, 600, 400, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



void Save()
{
    HANDLE hFile = CreateFile(L"AppliedContext.txt", GENERIC_WRITE, 0,
        NULL, CREATE_ALWAYS, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, (LPCWSTR)L"Faild to open/create file", (LPCWSTR)L"Error", MB_OK);
        return;
    }

    CHAR DataBuffer[255] = { 0 };
    sprintf_s(DataBuffer, "%d %d", currentX, currentY);
    DWORD bytesWritten;
    WriteFile(hFile, DataBuffer, strlen(DataBuffer), &bytesWritten, nullptr);
    
    CloseHandle(hFile);
}

// создание дочернего процесса
void CreateChildWindow()
{
    Save();
    CHAR szFilePath[MAX_PATH];
    GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    // Start the child process. 
    if (!CreateProcessA(szFilePath, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi))
    {
        MessageBox(NULL, (LPCWSTR)L"CreateProcess failed", (LPCWSTR)L"Error", MB_OK);
        return;
    }
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//  WM_CLOSE - Отправляется как сигнал о том, что окно или приложение должны закрыться
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));       // зеленый контур курсора
        brush = CreateSolidBrush(RGB(255, 255, 100));       // желтая заливка
        redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // красная кисть для места назначения
        SetTimer(hWnd, TIMER_ID, 5, NULL);

        HANDLE hFile = CreateFile(L"AppliedContext.txt", GENERIC_READ, 0, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        
        if (hFile == INVALID_HANDLE_VALUE)
        {
            MessageBox(hWnd, (LPCWSTR)L"Open file failed", (LPCWSTR)L"Error", MB_OK);
        }
        CHAR DataBuffer[255] = { 0 };
        DWORD bytesReaded;
        if (FALSE == ReadFile(hFile, DataBuffer, 255, &bytesReaded, NULL))
        {
            MessageBox(hWnd, (LPCWSTR)L"Open file failed", (LPCWSTR)L"Error", MB_OK);
        }
        CloseHandle(hFile);
        // прочитанную из файла строку разбить по пробелу на 2 числа - координаты х и у
        char *next_tocken = NULL;
        char *tocken = strtok_s(DataBuffer, " ", &next_tocken);
        currentX = destX = atoi(tocken);
        currentY = destY = atoi(strtok_s(NULL, " ", &next_tocken));
    }
        break;
    case WM_TIMER:
    {
        int wmId = LOWORD(wParam);

        if (wmId == TIMER_ID)
        {
            int redraw = 0;
            RECT rect;
            GetClientRect(hWnd, &rect);

            if (currentX > destX && currentX > rect.left) {
                currentX--;
                redraw = 1;
            }

            if (currentX < destX && currentX < rect.right - 16) {
                currentX++;
                redraw = 1;
            }

            if (currentY > destY && currentY > rect.top) {
                currentY--;
                redraw = 1;
            }

            if (currentY < destY && currentY < rect.bottom - 16) {
                currentY++;
                redraw = 1;
            }

            if (redraw) {
                InvalidateRect(hWnd, NULL, TRUE);       // перерисока окна (с перерисовкой фона)
            }
        }
        else
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
        break;
    case WM_LBUTTONDOWN:
    {
        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);

        RECT rect;
        GetClientRect(hWnd, &rect);

        if (xPos > rect.left + 8 && xPos < rect.right - 16 && yPos < rect.bottom - 16) {
            destX = xPos - 8;
            destY = yPos;
        }
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            HPEN oldPen = (HPEN)SelectObject(hdc, pen);
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

            // отрисовка шарика
            Ellipse(hdc, currentX, currentY, currentX + 16, currentY + 16);

            // отрисовка крестика на месте назначения
            if (currentX != destX || currentY != destY) {
                SelectObject(hdc, redPen);
                MoveToEx(hdc, destX + 8 - 4, destY + 8 - 4, NULL);
                LineTo(hdc, destX + 8 + 4, destY + 8 + 4);
                MoveToEx(hdc, destX + 8 + 4, destY + 8 - 4, NULL);
                LineTo(hdc, destX + 8 - 4, destY + 8 + 4);
            }

            SelectObject(hdc, oldPen);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CLOSE:
        CreateChildWindow();
        DestroyWindow(hWnd);            
        break;
    case WM_DESTROY:
        KillTimer(hWnd, TIMER_ID);
        DeleteObject(pen);
        DeleteObject(redPen);
        DeleteObject(brush);
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
