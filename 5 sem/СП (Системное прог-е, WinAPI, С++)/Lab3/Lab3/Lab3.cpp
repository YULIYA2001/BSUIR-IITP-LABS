// Lab3.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab3.h"

#define MAX_LOADSTRING 100
#define START_BUTTON 1200
#define STOP_BUTTON 1201

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// создание переменных для 4 потоков
HANDLE thread1, thread2, thread3, thread4;

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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
      CW_USEDEFAULT, 0, 700, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


// параметры передающиеся в функцию потока
struct Data
{
    HWND hWnd;
    int rnd;            // для генерации реально случайных чисел
    int threadNum;
};
Data data1, data2, data3, data4;

// функция, которую выполняют потоки
DWORD WINAPI ThreadFunc(void *data)
{
    Data* d = (Data*)data;
    HWND hWnd = (HWND)d->hWnd;
    int num = d->threadNum;
    
    HDC hDC = GetDC(hWnd);
    RECT rect;
    GetClientRect(hWnd, &rect);

    int l = rect.left;
    int t = rect.top;
    int r = rect.right;
    int b = rect.bottom-50;
    int red, green, blue;

    srand(d->rnd);        // для генерации реально случайных чисел
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    while (true)
    {
        red = rand() % 256;
        green = rand() % 256;
        blue = rand() % 256;
        SetDCBrushColor(hDC, RGB(red, green, blue));
        switch (num)
        {
        case 1:
            Rectangle(hDC, l, t, l + (r - l) / 2, t + (b - t) / 2);
            break;
        case 2:
            Rectangle(hDC, l + (r - l) / 2, t, r, t + (b - t) / 2);
            break;
        case 3:
            Rectangle(hDC, l, t + (b - t) / 2, l + (r - l) / 2, b);
            break;
        case 4:
            Rectangle(hDC, l + (r - l) / 2, t + (b - t) / 2, r, b);
            break;
        }        
        Sleep(1000);
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
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // определение размеров окна
        RECT rect;
        GetClientRect(hWnd, &rect);

        // создание кнопок START и STOP на всю ширину окна и высоту 50 (в функции потока они не будут задеты)
        CreateWindow(_T("Button"), _T("START"), WS_CHILD | WS_VISIBLE,
            0, rect.bottom-50, rect.right/2, 50, hWnd, (HMENU)START_BUTTON, hInst, NULL);
        CreateWindow(_T("Button"), _T("STOP"), WS_CHILD | WS_VISIBLE,
           rect.right/2, rect.bottom - 50, rect.right/2, 50, hWnd, (HMENU)STOP_BUTTON, hInst, NULL);

        // заполнение структур с параметрами для функции потоков и создание потоков
        data1.hWnd = hWnd;
        data1.rnd = 1111;
        data1.threadNum = 1;
        thread1 = CreateThread(NULL, 0, ThreadFunc, &data1, 0, 0);
        if (NULL == thread1) {
            MessageBox(hWnd, L"Failed to create thread1.", L"Error", MB_OK);
        }

        data2.hWnd = hWnd;
        data2.rnd = 2222;
        data2.threadNum = 2;
        thread2 = CreateThread(NULL, 0, &ThreadFunc, &data2, 0, 0);
        if (NULL == thread2) {
            MessageBox(hWnd, L"Failed to create thread2.", L"Error", MB_OK);
        }

        data3.hWnd = hWnd;
        data3.rnd = 3333;
        data3.threadNum = 3;
        thread3 = CreateThread(NULL, 0, &ThreadFunc, &data3, 0, 0);
        if (NULL == thread3) {
            MessageBox(hWnd, L"Failed to create thread3.", L"Error", MB_OK);
        }
        
        data4.hWnd = hWnd;
        data4.rnd = 4444;
        data4.threadNum = 4;
        thread4 = CreateThread(NULL, 0, &ThreadFunc, &data4, 0, 0);
        if (NULL == thread4) {
            MessageBox(hWnd, L"Failed to create thread4.", L"Error", MB_OK);
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
            case START_BUTTON:
                ResumeThread(thread1);
                ResumeThread(thread2);
                ResumeThread(thread3);
                ResumeThread(thread4);
                break;
            case STOP_BUTTON:
                SuspendThread(thread1);
                SuspendThread(thread2);
                SuspendThread(thread3);
                SuspendThread(thread4);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
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
        CloseHandle(thread1);
        CloseHandle(thread2);
        CloseHandle(thread3);
        CloseHandle(thread4);
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
