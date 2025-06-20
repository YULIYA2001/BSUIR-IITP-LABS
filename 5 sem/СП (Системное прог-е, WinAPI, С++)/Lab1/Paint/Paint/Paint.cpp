// Paint.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Paint.h"

#define MAX_LOADSTRING 100
#define IDM_CLEARBUTTON 10001
#define IDM_CLICKBUTTON 10016
#define RED_BUTTON 1200
#define YELLOW_BUTTON 1201
#define GREEN_BUTTON 1202
#define BLUE_BUTTON 1203
#define THIN 1301
#define MEDIUM 1302
#define THICK 1303
#define _PEN 1401
#define _ERASER 1402
#define _FILL 1403
#define _RECTANGLE 1404
#define _ELLIPSE 1405


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

BOOL fDraw = FALSE;
POINT ptPrevious = { 0 };               // начальные координаты (левая кнопка мышки)
HPEN hPen;                              // карандаш
COLORREF penColor = RGB(255, 0, 0);     // цвет по умолчанию - красный
int thickness = 2;                      // толщина линии по умолчанию - 2(тонкая)

enum Tools
{
    PEN,
    ERASER,
    FILL,
    RECTANGLE,
    ELLIPSE
};
Tools tool = Tools::PEN;                       // инструмент по умолчанию - ручка 


// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;   // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

bool click = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    RECT text;          // прямоугольник, в котором выводится надпись "цвет" (его координаты)
    text.left = 40;
    text.top = 10;
    text.right = 100;
    text.bottom = 25;

    switch (message)
    {
    case WM_CREATE:
        {
            // кнопка очистки листа
            CreateWindow(_T("BUTTON"), _T("Clear"), WS_CHILD | WS_VISIBLE,
                20, 365, 100, 25, hWnd, (HMENU)IDM_CLEARBUTTON, hInst, NULL);   // цифры - коорд. и размеры
            // кнопки-цвета
            CreateWindow(_T("Button"), _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                20, 25, 50, 50, hWnd, (HMENU)RED_BUTTON, hInst, NULL);
            CreateWindow(_T("Button"), _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                20, 75, 50, 50, hWnd, (HMENU)YELLOW_BUTTON, hInst, NULL);
            CreateWindow(_T("Button"), _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                70, 25, 50, 50, hWnd, (HMENU)GREEN_BUTTON, hInst, NULL);
            CreateWindow(_T("Button"), _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                70, 75, 50, 50, hWnd, (HMENU)BLUE_BUTTON, hInst, NULL);
            // GROUPBOX - толщина линий
            CreateWindow(_T("Button"), _T("Thickness"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 125, 100, 95, hWnd, 0, hInst, NULL);
            HWND button1 = CreateWindow(_T("Button"), _T("Thin"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON
                | WS_GROUP, 30, 145, 80, 20, hWnd, (HMENU)THIN, hInst, NULL);
            // установка флажка по умолчанию в первый кружок
            SendMessage(button1, BM_SETCHECK, BST_CHECKED, 1);   
            CreateWindow(_T("Button"), _T("Medium"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                30, 170, 80, 20, hWnd, (HMENU)MEDIUM, hInst, NULL);            
            CreateWindow(_T("Button"), _T("Thick"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                30, 195, 80, 20, hWnd, (HMENU)THICK, hInst, NULL);
            // GROUPBOX - инструменты
            CreateWindow(_T("Button"), _T("Tools"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 225, 100, 135, hWnd, 0, hInst, NULL);
            HWND button2 = CreateWindow(_T("Button"), _T("Pen"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON
                | WS_GROUP, 30, 245, 85, 20, hWnd, (HMENU)_PEN, hInst, NULL);
            // установка флажка по умолчанию в первый кружок
            SendMessage(button2, BM_SETCHECK, BST_CHECKED, 1);
            CreateWindow(_T("Button"), _T("Eraser"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                30, 267, 85, 20, hWnd, (HMENU)_ERASER, hInst, NULL);
            CreateWindow(_T("Button"), _T("Fill"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                30, 289, 85, 20, hWnd, (HMENU)_FILL, hInst, NULL);
            CreateWindow(_T("Button"), _T("Rectangle"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                30, 311, 85, 20, hWnd, (HMENU)_RECTANGLE, hInst, NULL);
            CreateWindow(_T("Button"), _T("Ellipse"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                30, 333, 85, 20, hWnd, (HMENU)_ELLIPSE, hInst, NULL);
            CreateWindow(_T("BUTTON"), _T("CLICK!!!"), WS_CHILD | WS_VISIBLE,
                20, 395, 100, 25, hWnd, (HMENU)IDM_CLICKBUTTON, hInst, NULL);
        }
        break;

    case WM_COMMAND:
        {
            wmId = LOWORD(wParam);
            wmEvent = HIWORD(wParam);

            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_CLEARBUTTON:
                InvalidateRect(hWnd, NULL, TRUE);
                break;                
            case IDM_CLICKBUTTON:
                click = true;
                RECT area;
                GetWindowRect(hWnd, &area);
                area.left = 0;
                area.top = 0;                
                InvalidateRect(hWnd, &area, TRUE);
                break;
            case RED_BUTTON:
                penColor = RGB(255, 0, 0);
                hdc = GetDC(hWnd);
                SetTextColor(hdc, penColor);    // устанавливаем цвет текста и рисуем текст:
                DrawText(hdc, L"Color", -1, &text, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
                ReleaseDC(hWnd, hdc);
                break;
            case YELLOW_BUTTON:
                penColor = RGB(255, 245, 0);
                hdc = GetDC(hWnd);
                SetTextColor(hdc, penColor);    // устанавливаем цвет текста и рисуем текст:
                DrawText(hdc, L"Color", -1, &text, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
                ReleaseDC(hWnd, hdc);
                break;
            case GREEN_BUTTON:
                penColor = RGB(0, 255, 0);
                hdc = GetDC(hWnd);
                SetTextColor(hdc, penColor);    // устанавливаем цвет текста и рисуем текст:
                DrawText(hdc, L"Color", -1, &text, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
                ReleaseDC(hWnd, hdc);
                break;
            case BLUE_BUTTON:
                penColor = RGB(0, 0, 255);
                hdc = GetDC(hWnd);
                SetTextColor(hdc, penColor);    // устанавливаем цвет текста и рисуем текст:
                DrawText(hdc, L"Color", -1, &text, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
                ReleaseDC(hWnd, hdc);
                break;
            case THICK:
                thickness = 24;    // толщина линии
                break;
            case MEDIUM:
                thickness = 8;
                break;
            case THIN:
                thickness = 2;
                break;
            case _PEN:
                tool = PEN;
                break;
            case _ERASER:
                tool = ERASER;
                break;
            case _FILL:
                tool = FILL;
                break;
            case _RECTANGLE:
                tool = RECTANGLE;
                break;
            case _ELLIPSE:
                tool = ELLIPSE;
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_DRAWITEM:
        {
            //отрисовка цветных кнопок
            LPDRAWITEMSTRUCT di = (LPDRAWITEMSTRUCT)lParam;
            RECT rc = di->rcItem;
            HDC hdc = di->hDC;

            int isMyButton = 0;
            HPEN itemPen, whitePen, oldPen;
            HBRUSH itemBrush, whiteBrush, oldBrush;
            COLORREF color;                      
            
            switch (di->CtlID) 
            {
                case RED_BUTTON:
                    isMyButton = 1;
                    color = RGB(255, 0, 0);
                    break;
                case YELLOW_BUTTON:
                    isMyButton = 1;
                    color = RGB(255, 245, 0);
                    break;
                case GREEN_BUTTON:
                    isMyButton = 1;
                    color = RGB(0, 255, 0);
                    break;
                case BLUE_BUTTON:
                    isMyButton = 1;
                    color = RGB(0, 0, 255);
                    break;
            }

            if (isMyButton) 
            {
                itemPen = CreatePen(PS_SOLID, 1, color);
                itemBrush = CreateSolidBrush(color);
                whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

                oldPen = (HPEN)SelectObject(hdc, whitePen);
                oldBrush = (HBRUSH)SelectObject(hdc, whiteBrush);

                Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

                SelectObject(hdc, itemPen);
                SelectObject(hdc, itemBrush);

                Rectangle(hdc, rc.left + 5, rc.top + 5, rc.right - 5, rc.bottom - 5);
               
                SelectObject(hdc, oldPen);
                SelectObject(hdc, oldBrush);
                DeleteObject(itemPen);
                DeleteObject(itemBrush);
                DeleteObject(whitePen);
                DeleteObject(whiteBrush);

                return TRUE;
            }
            else
            {
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    // Рисование (обработка нажатия и движения мышки)
    case WM_LBUTTONDOWN:
        fDraw = TRUE;
        ptPrevious.x = LOWORD(lParam);
        ptPrevious.y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        if (fDraw)
        {            
            if (tool == FILL)
            {
                hdc = GetDC(hWnd);
                // не рисовать на панели инструментов
                RECT r;
                GetWindowRect(hWnd, &r);
                ExcludeClipRect(hdc, 0, 0, 130, r.bottom);
                HBRUSH brush, whiteBrush, oldBrush;
                brush = CreateSolidBrush(penColor);                
                whiteBrush = CreateSolidBrush(RGB(255, 255, 255));                
                oldBrush = (HBRUSH)SelectObject(hdc, whiteBrush);
                SelectObject(hdc, brush);                
                ExtFloodFill(hdc, ptPrevious.x, ptPrevious.y, GetPixel(hdc, ptPrevious.x, ptPrevious.y), 
                    FLOODFILLSURFACE);      // заливка 
                SelectObject(hdc, oldBrush);
                DeleteObject(brush);                
                ReleaseDC(hWnd, hdc);
            }
            else if (tool == RECTANGLE || tool == ELLIPSE)
            {               
                int x = LOWORD(lParam);
                int y = HIWORD(lParam);
                hdc = GetDC(hWnd);
                // не рисовать на панели инструментов
                RECT r;
                GetWindowRect(hWnd, &r);
                ExcludeClipRect(hdc, 0, 0, 130, r.bottom);
                hPen = CreatePen(PS_SOLID, thickness, penColor);
                HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
                SelectObject(hdc, GetStockObject(NULL_BRUSH));
                if (tool == RECTANGLE)
                {
                    // прямоугольник (зажатие мыши определяет центр, отпускание - размер)
                    Rectangle(hdc, ptPrevious.x - (x - ptPrevious.x), ptPrevious.y - (y - ptPrevious.y),
                        x, y);
                }
                else
                {
                    Ellipse(hdc, ptPrevious.x - (x - ptPrevious.x), ptPrevious.y - (y - ptPrevious.y),
                        x, y);
                }
                SelectObject(hdc, oldPen);
                DeleteObject(hPen);
                ReleaseDC(hWnd, hdc);
            }
            else
            {
                hdc = GetDC(hWnd);
                // не рисовать на панели инструментов
                RECT r;
                GetWindowRect(hWnd, &r);
                ExcludeClipRect(hdc, 0, 0, 130, r.bottom);
                if (tool == PEN)
                {
                    hPen = CreatePen(PS_SOLID, thickness, penColor);            // ручка
                }
                if (tool == ERASER)
                {
                    hPen = CreatePen(PS_SOLID, thickness, RGB(255, 255, 255));  // карандаш белого цвета (ластик)
                }
                HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
                MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
                LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
                SelectObject(hdc, oldPen);
                DeleteObject(hPen);
                ReleaseDC(hWnd, hdc);
            }
        }
        fDraw = FALSE;
        break;
    case WM_MOUSEMOVE:
        if (fDraw && (tool == PEN || tool == ERASER))
        {           
            hdc = GetDC(hWnd);
            // не рисовать на панели инструментов
            RECT r;
            GetWindowRect(hWnd, &r);
            ExcludeClipRect(hdc, 0, 0, 130, r.bottom);
            if (tool == PEN)
            {
                hPen = CreatePen(PS_SOLID, thickness, penColor);
            }
            if (tool == ERASER)
            {
                hPen = CreatePen(PS_SOLID, thickness, RGB(255, 255, 255));  // карандаш белого цвета
            }
            HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
            SelectObject(hdc, hPen);
            MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
            LineTo(hdc, ptPrevious.x = LOWORD(lParam), ptPrevious.y = HIWORD(lParam));
            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            //надпись "цвет"
            SetTextColor(hdc, penColor); // устанавливаем цвет текста
            DrawText(hdc, L"Color", -1, &text, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // рисуем текст
            // не рисовать на панели инструментов
            RECT r;
            GetWindowRect(hWnd, &r);
            ExcludeClipRect(hdc, 0, 0, 130, r.bottom);
                      
            // рисунок по нажатию на кнопку CLICK
            if (click == true)
            {         
                click = false;
                HPEN pen, whitePen, oldPen;
                HBRUSH brush, whiteBrush, oldBrush;                                

                pen = CreatePen(PS_SOLID, 3, RGB(0, 225, 0));
                brush = CreateSolidBrush(RGB(0, 225, 0));
                whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
                oldPen = (HPEN)SelectObject(hdc, whitePen);
                oldBrush = (HBRUSH)SelectObject(hdc, whiteBrush);              
                SelectObject(hdc, pen);
                SelectObject(hdc, brush);
                // ёлка
                MoveToEx(hdc, 500, 50, NULL);
                LineTo(hdc, 450, 100);
                LineTo(hdc, 475, 100);
                LineTo(hdc, 425, 150);
                LineTo(hdc, 450, 150);
                LineTo(hdc, 400, 200);
                LineTo(hdc, 425, 200);
                LineTo(hdc, 375, 250);
                LineTo(hdc, 625, 250);
                LineTo(hdc, 575, 200);
                LineTo(hdc, 600, 200);
                LineTo(hdc, 550, 150);
                LineTo(hdc, 575, 150);
                LineTo(hdc, 525, 100);
                LineTo(hdc, 550, 100);
                LineTo(hdc, 500, 50);
                ExtFloodFill(hdc, 500, 150, GetPixel(hdc, 500, 150), FLOODFILLSURFACE);
                DeleteObject(pen);
                DeleteObject(brush);
                // ствол
                pen = CreatePen(PS_SOLID, 3, RGB(150, 75, 0));
                brush = CreateSolidBrush(RGB(150, 75, 0));
                SelectObject(hdc, pen);
                SelectObject(hdc, brush);
                MoveToEx(hdc, 525, 250, NULL);
                LineTo(hdc, 525, 275);
                LineTo(hdc, 475, 275);
                LineTo(hdc, 475, 250);
                LineTo(hdc, 525, 250);
                ExtFloodFill(hdc, 500, 260, GetPixel(hdc, 500, 260), FLOODFILLSURFACE);
                DeleteObject(pen);
                DeleteObject(brush);
                // игрушки красные
                pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
                brush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, pen);
                SelectObject(hdc, brush);
                Ellipse(hdc, 515, 90, 525, 100);
                Ellipse(hdc, 425, 225, 450, 250);
                Ellipse(hdc, 497, 152, 518, 173);
                DeleteObject(pen);
                DeleteObject(brush);
                // игрушки желтые
                pen = CreatePen(PS_SOLID, 3, RGB(255, 225, 0));
                brush = CreateSolidBrush(RGB(255, 225, 0));
                SelectObject(hdc, pen);
                SelectObject(hdc, brush);
                Ellipse(hdc, 525, 190, 550, 215);
                Ellipse(hdc, 479, 104, 496, 121);
                Ellipse(hdc, 550, 140, 565, 155);
                DeleteObject(pen);
                DeleteObject(brush);
                // игрушки синие
                pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 225));
                brush = CreateSolidBrush(RGB(0, 0, 225));
                SelectObject(hdc, pen);
                SelectObject(hdc, brush);
                Ellipse(hdc, 475, 75, 490, 90);
                Ellipse(hdc, 425, 175, 445, 195);
                Ellipse(hdc, 575, 225, 600, 250);
                DeleteObject(pen);
                DeleteObject(brush);
                // игрушки розовые
                pen = CreatePen(PS_SOLID, 3, RGB(252, 15, 192));
                brush = CreateSolidBrush(RGB(252, 15, 192));
                SelectObject(hdc, pen);
                SelectObject(hdc, brush);
                Ellipse(hdc, 475, 200, 500, 225);
                Ellipse(hdc, 445, 125, 465, 145);
                Ellipse(hdc, 494, 25, 502, 65);
                DeleteObject(brush);
                brush = CreateSolidBrush(RGB(240, 248, 255));
                SelectObject(hdc, brush);
                ExtFloodFill(hdc, 600, 10, GetPixel(hdc, 600, 10), FLOODFILLSURFACE);
                SelectObject(hdc, oldPen);
                SelectObject(hdc, oldBrush);
                DeleteObject(pen);
                DeleteObject(brush);
                DeleteObject(whitePen);
                DeleteObject(whiteBrush);
                // Надписи
                RECT t;
                t.left = 600;
                t.top = 110;
                t.right = 700;
                t.bottom = 125;
                SetTextColor(hdc, RGB(255, 0, 0));
                DrawText(hdc, L"Happy", -1, &t, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                t.left = 615;
                t.top = 130;
                t.right = 715;
                t.bottom = 140;
                SetTextColor(hdc, RGB(0, 255, 0));
                DrawText(hdc, L"New", -1, &t, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                t.left = 630;
                t.top = 145;
                t.right = 730;
                t.bottom = 155;
                SetTextColor(hdc, RGB(0, 0, 255));
                DrawText(hdc, L"Year!", -1, &t, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                t.left = 300;
                t.top = 100;
                t.right = 400;
                t.bottom = 125;
                SetTextColor(hdc, RGB(255, 225, 0));
                DrawText(hdc, L"Merry", -1, &t, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                t.left = 330;
                t.top = 120;
                t.right = 430;
                t.bottom = 145;
                SetTextColor(hdc, RGB(252, 15, 192));
                DrawText(hdc, L"Christmas!", -1, &t, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }
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

// Обработчик сообщений для окна "О программе".
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
