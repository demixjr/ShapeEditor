#include "framework.h"
#include "Lab_4.h"
#include "My_Editor.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

HWND hwndToolBar = NULL;

#define MAX_LOADSTRING 100

class Toolbar
{
public:
    void OnCreate(HWND);
    void OnSize(HWND);
    void OnNotify(HWND, WPARAM, LPARAM);
};

MyEditor object;
Toolbar toolbar;

HWND hWnd;

PAINTSTRUCT ps;
HDC hdc;

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)

{

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    InitCommonControls();


    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB4);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
    LPARAM lParam)
{
    int wmId, wmEvent;
    switch (message)
    {
    case WM_CREATE:
        toolbar.OnCreate(hWnd);
        break;
    case WM_SIZE:
        toolbar.OnSize(hWnd);
        break;
    case WM_NOTIFY:
        toolbar.OnNotify(hWnd, wParam, lParam);
        break;
     case WM_LBUTTONDOWN: //натиснуто ліву кнопку миші
        object.OnLBdown(hWnd);
        break;
    case WM_LBUTTONUP: //відпущено ліву кнопку миші
        object.OnLBup(hWnd);
        break;
    case WM_MOUSEMOVE: //пересунуто мишу у клієнтській частині вікна
        object.OnMouseMove(hWnd);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        object.OnPaint(hWnd, hdc);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_TOOL_POINT:
            object.Start(new PointShape);
            SetWindowText(hWnd, TEXT("Режим вводу крапок"));
            break;
        case ID_TOOL_LINE:
            object.Start(new LineShape);
            SetWindowText(hWnd, TEXT("Режим вводу ліній"));
            break;
        case ID_TOOL_RECT:
            object.Start(new RectShape);
            SetWindowText(hWnd, TEXT("Режим вводу прямокутників"));
            break;
        case ID_TOOL_ELLIPSE:
            object.Start(new EllipseShape);
            SetWindowText(hWnd, TEXT("Режим вводу еліпсів"));
            break;
        case ID_TOOL_LINE_OO:
            object.Start(new LineOOShape);
            SetWindowText(hWnd, TEXT("Режим вводу ліній з двома кружечками"));
            break;
        case ID_TOOL_CUBE:
            object.Start(new CubeShape);
            SetWindowText(hWnd, TEXT("Режим вводу кубів"));
            break;
        case IDM_POINT:
            object.Start(new PointShape);
            SetWindowText(hWnd, TEXT("Режим вводу крапок"));
            break;
        case IDM_LINE:
            object.Start(new LineShape);
            SetWindowText(hWnd, TEXT("Режим вводу ліній"));
            break;
        case IDM_RECT:
            object.Start(new RectShape);
            SetWindowText(hWnd, TEXT("Режим вводу прямокутників"));
            break;
        case IDM_ELLIPSE:
            object.Start(new EllipseShape);
            SetWindowText(hWnd, TEXT("Режим вводу еліпсів"));
            break;
        case IDM_LINE_OO:
            object.Start(new LineOOShape);
            SetWindowText(hWnd, TEXT("Режим вводу ліній з двома кружечками"));
            break;
        case IDM_CUBE:
            object.Start(new CubeShape);
            SetWindowText(hWnd, TEXT("Режим вводу кубів"));
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
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

void Toolbar::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_POINT:
            lstrcpy(lpttt->szText, L"Крапка");
            break;
        case ID_TOOL_LINE:
            lstrcpy(lpttt->szText, L"Лінія");
            break;
        case ID_TOOL_RECT:
            lstrcpy(lpttt->szText, L"Прямокутник");
            break;
        case ID_TOOL_ELLIPSE:
            lstrcpy(lpttt->szText, L"Еліпс");
            break;
        case ID_TOOL_LINE_OO:
            lstrcpy(lpttt->szText, L"Лінія з кружечками на кінцях");
            break;
        case ID_TOOL_CUBE:
            lstrcpy(lpttt->szText, L"Куб");
            break;
        default:
            lstrcpy(lpttt->szText, L"Щось невідоме");
        }

    }
}

void Toolbar::OnCreate(HWND hWnd) {
    TBBUTTON tbb[6]; //масив опису кнопок вікна Toolbar
    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0; //стандартне зображення
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_TOOL_POINT;

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;

    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_BUTTON;
    tbb[4].idCommand = ID_TOOL_LINE_OO;

    tbb[5].iBitmap = 5;
    tbb[5].fsState = TBSTATE_ENABLED;
    tbb[5].fsStyle = TBSTYLE_BUTTON;
    tbb[5].idCommand = ID_TOOL_CUBE;

    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | TTS_ALWAYSTIP |
        WS_CLIPSIBLINGS | CCS_TOP |
        TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        5,
        hInst,
        IDB_BITMAP1,
        tbb,
        6,
        24, 24, 24, 24,
        sizeof(TBBUTTON));
}

void Toolbar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); //нові розміри головного вікна
        GetWindowRect(hwndToolBar, &rw); //потрібно знати висоту Toolbar
        MoveWindow(hwndToolBar, 0, 0,
            rc.right - rc.left, //ширина Toolbar як у головного вікна
            rw.bottom - rw.top, FALSE);
    }
}
