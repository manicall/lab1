// lab3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab3.h"
#include <vector>
#include <string>

#define MAX_LOADSTRING 100

using namespace std;

class Menu {
public:
	vector<vector<string> > points_of_second_menu = {
		{"Белый гриб", "Козляк", "Опёнок осенний"},
		{"Мухомор красный", "Строфария говняная", "Сатанинский гриб"}
	};
	vector<vector<string> > descriptions = {
	{
		"Различные разновидности белого гриба произрастают в лиственных, хвойных и смешанных лесах с начала лета до октября (с перерывами), образуя микоризу с различными видами деревьев.",
		"Козляк похож на моховик, только шляпка его очень выпуклая, сверху покрыта словно коричневой кожей, слегка клейкая.",
        "Шляпка диаметром 2 - 9, очень вариабельная, выпуклая, затем плоско - распростертая с загнутыми краями, с плоской депрессией в центре, затем края шляпки могут выгибаться и вверх."
	},
	{
		"Мухомор красный (лат. Amanita muscaria) — ядовитый психоактивный гриб рода Мухомор, или Аманита (лат. Amanita) порядка агариковых (лат. Agaricales), относится к базидиомицетам.",
		"Небольшой пластинчатый гриб с размером шляпки до 2,5 сантиметров. Растёт с середины августа, встречаются как по отдельности, так и массово.",
		"Сатанинский гриб(лат.Rubroboletus satanas) — ядовитый(по некоторым данным, условно съедобный) гриб из рода Rubrobolet семейства Болетовые(лат.Boletaceae)."
	}
	};
};

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Menu menu;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case ID_32771: MessageBoxA(0, menu.descriptions[0][0].data(), menu.points_of_second_menu[0][0].data(), 0); break;
            case ID_32772: MessageBoxA(0, menu.descriptions[0][1].data(), menu.points_of_second_menu[0][1].data(), 0); break;
            case ID_32773: MessageBoxA(0, menu.descriptions[0][2].data(), menu.points_of_second_menu[0][2].data(), 0); break;
            case ID_32774: MessageBoxA(0, menu.descriptions[1][0].data(), menu.points_of_second_menu[1][0].data(), 0); break;
            case ID_32775: MessageBoxA(0, menu.descriptions[1][1].data(), menu.points_of_second_menu[1][1].data(), 0); break;
            case ID_32776: MessageBoxA(0, menu.descriptions[1][2].data(), menu.points_of_second_menu[1][2].data(), 0); break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
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
