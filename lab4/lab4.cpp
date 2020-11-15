// l4.cpp : Определяет точку входа для приложения.
//
#undef UNICODE
#include "framework.h"
#include <windowsx.h>
#include "lab4.h"
#include <stack>
#include <string>


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    dialog(HWND, UINT, WPARAM, LPARAM);
HWND hWnd;
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
    LoadStringW(hInstance, IDC_L4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_L4));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_L4));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_L4);
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

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void PrintStack(std::stack<int> st) {
    HDC hdc = GetDC(hWnd);
    int x = 0, y = 0;
    InvalidateRect(hWnd, 0, 0);
    std::string buf;
    while (!st.empty()) {
        buf = st.top();
        TextOut(hdc, x, y, buf.data(), buf.size());
        st.pop();
        y += 18;
    }
    InvalidateRect(hWnd, 0, 0);
}
std::stack<int>st;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDD_L4_DIALOG:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG), hWnd, dialog);
            break;
        case ID_LIST_INSERT:
            st.push(std::to_string(rand() % 10)[0]);
            break;
        case ID_LIST_DELETE:
            st.pop();
            break;
        case ID_LIST_SHOW:
            PrintStack(st);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
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

HWND hList, hEdit;

void PrintStackInListBox(HWND& hList, std::stack<int> st) {
    while (ListBox_GetCount(hList) > 0) {
        ListBox_DeleteString(hList, 0);
    }
    std::string buf;
    while (!st.empty()) {
        buf = std::to_string(st.top());
        ListBox_AddString(hList, buf.data());
        st.pop();
    }
}

INT_PTR CALLBACK dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::string buf;
    switch (message)
    {
    case WM_INITDIALOG:
        hEdit = GetDlgItem(hDlg, IDC_EDIT1);
        hList = GetDlgItem(hDlg, IDC_LIST1);
        PrintStackInListBox(hList, st);
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_LIST1:
            if (HIWORD(wParam) == LBN_DBLCLK) {
                if (!ListBox_GetCurSel(hList)) {
                    st.pop();
                    ListBox_DeleteString(hList, 0);
                }
            }
            break;
        case IDOK:
            SendMessage(hEdit, WM_GETTEXT, 50, (LPARAM)buf.c_str());
            if (strlen(buf.data()) > 0 && !atoi(buf.data()) && strcmp(buf.data(), "0") || !strcmp(buf.data(), ""))
                MessageBoxA(0, "стек принимает данные типа int", 0, 0);
            else {
                st.push(atoi(buf.data()));
                PrintStackInListBox(hList, st);
            }
            break;
        case IDCLOSE:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
