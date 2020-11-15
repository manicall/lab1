#undef UNICODE
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include <string>
#include <vector>
std::string VectorIntInString(std::vector<int> vect) {
	std::string str;
	for (auto i : vect)
		str += char(i + '0');
	return str;
}
std::vector<int> StringToVectorInt(std::string str) {
	std::vector<int> vect;
	for (auto i : str)
		vect.emplace_back(int(i - '0'));
	return vect;
}
std::string sum(std::vector<int> a, std::vector<int> b) {
	std::string result;
	int length = max(a.size(), b.size());
	while (a.size() < length) a.emplace(a.begin(), 0);
	while (b.size() < length) b.emplace(b.begin(), 0);
	for (int i = length - 1; i >= 0; i--)
	{
		if (b[i] + a[i] > 9) {
			b[i] += a[i];// суммируем последние разряды чисел
			if (i - 1 < 0) {
				b.emplace(b.begin(), b[i] / 10);
				b[i + 1] %= 10;
			}
			else
				b[i - 1] += (b[i] / 10); // если есть разряд для переноса, переносим его в следующий разряд
			b[i] %= 10; // если есть разряд для переноса он отсекается
		}
		else
			b[i] += a[i];
	}
	result = VectorIntInString(b);
	return result;
}
static int lx = 150, ly = 200; // координаты конца экрана	
HWND hWndDialog, hWndPanel;
HINSTANCE       ghInstance;   // Переменная для хранения хендела процесса                      
// Описание используемой оконной процедуры
BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
// Главное приложение программы
int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	MSG msg;
	ghInstance = hInstance;
	// Создание  диалогового окна
	hWndDialog = CreateDialogParam(hInstance,
		MAKEINTRESOURCE(IDD_DIALOG1),
		NULL,
		(DLGPROC)PviewDlgProc,
		(LONG)0);
	ShowWindow(hWndDialog, nCmdShow);
	UpdateWindow(hWndDialog);
	ShowWindow(hWndPanel, nCmdShow);
	UpdateWindow(hWndPanel);
	// Стандартный цикл обработки сообщений приложения
	while (GetMessage(&msg, NULL, 0, 0))
		if (!IsDialogMessage(hWndDialog, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	DestroyWindow(hWndDialog);
	return 0;
}

//Процедура обработки сообщений диалогового окна
BOOL CALLBACK   PviewDlgProc(HWND    hWnd,
	UINT    wMsg,
	WPARAM  wParam,
	LPARAM  lParam)
{
	static HWND hList;
	std::vector<int> first, second;
	std::string str;
	std::string strSum;
	char* buf = new char[200];

	switch (wMsg)
	{
		// сообщение об инициализации диалоговой формы
	case WM_INITDIALOG:
		hList = GetDlgItem(hWnd, IDC_LIST1);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			
			SendMessage(GetDlgItem(hWndDialog, IDC_EDIT1), WM_GETTEXT, 200, (LPARAM)buf);

			str = buf;
			if (!(strlen(str.data()) > 0 && !atoi(str.data()) && strcmp(str.data(), "0") || !strcmp(str.data(), ""))) {
				first = StringToVectorInt(str);
				SendMessage(GetDlgItem(hWndDialog, IDC_EDIT2), WM_GETTEXT, 200, (LPARAM)buf);
				str = buf;
				if (!(strlen(str.data()) > 0 && !atoi(str.data()) && strcmp(str.data(), "0") || !strcmp(str.data(), ""))) {
					second = StringToVectorInt(str);
					strSum = sum(first, second);

					ListBox_AddString(hList, strSum.data());
					UpdateWindow(hList);
				}
			}
			break;

		default:
			return FALSE;
		}
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

