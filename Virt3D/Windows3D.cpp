// Virt3D.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Windows3D.h"
#include "Render3D.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int CurrentModel = 0;
int OutputList[100] = { 1 };
RECT WindowRect;
Render3D render;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK Add(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Rend(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Transform(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.
	//AllocConsole();
	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_VIRT3D, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VIRT3D));

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
	wcex.hIcon = LoadIcon(hInstance, NULL);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_VIRT3D);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);

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

	HWND hWnd = CreateWindowW(szWindowClass, L"Windows3D", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
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
	GetWindowRect(hWnd, &WindowRect);
	render.width = WindowRect.right - WindowRect.left;
	render.height = WindowRect.bottom - WindowRect.top;
	OPENFILENAME ofn = { 0 };
	HMENU hm = GetMenu(hWnd);
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case IDM_ROTATE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ROTATE), hWnd, Transform);
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case IDM_ADD:
			wchar_t szDirect[260];
			wchar_t szFileName[260];
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szDirect;
			*(ofn.lpstrFile) = 0;
			ofn.nMaxFile = sizeof(szDirect);
			ofn.lpstrFilter = NULL;
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = szFileName;
			*(ofn.lpstrFileTitle) = 0;
			ofn.nMaxFileTitle = sizeof(szFileName);
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_EXPLORER;
			GetOpenFileName(&ofn);
			if (szDirect[0] != L'\0') {
				render.addModel(ModelLoader::Load(szDirect));
				OutputList[render.numberOfModels()] = render.numberOfModels();
			}
			//MessageBox(hWnd, L"d", L"f", NULL);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_REND:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_REND), hWnd, Rend);
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		MoveToEx(hdc, (int)render.width, (int)render.height, NULL);
		LineTo(hdc, (int)render.width + 10, (int)render.height + 10);
		render.action(hdc, CurrentModel);
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

INT_PTR CALLBACK Add(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Rend(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hEditCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < 100; i++) {
			if (OutputList[i] != 0) SendMessage(hEditCombo1, CB_ADDSTRING, NULL, (LPARAM)std::to_string(i).c_str());
		}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			CurrentModel = SendMessage(hEditCombo1, CB_GETCURSEL, NULL, NULL);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

	INT_PTR CALLBACK Transform(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hEditCombo1 = GetDlgItem(hDlg, IDC_EDIT1);
	HWND hEditCombo2 = GetDlgItem(hDlg, IDC_EDIT2);
	HWND hEditCombo3 = GetDlgItem(hDlg, IDC_EDIT3);
	HWND checkBox = GetDlgItem(hDlg, IDC_CHECK1);
	HWND hWnd = GetParent(hDlg);
	HWND hEdit1 = GetDlgItem(hDlg, IDC_COMBO1);
	HWND hEdit2 = GetDlgItem(hDlg, IDC_COMBO2);
	HWND hEdit3 = GetDlgItem(hDlg, IDC_COMBO3);
	int num = render.verticesNumber(CurrentModel);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < num; i++) {
			SendMessage(hEdit1, CB_ADDSTRING, NULL, (LPARAM)std::to_wstring(i).c_str());
			SendMessage(hEdit2, CB_ADDSTRING, NULL, (LPARAM)std::to_wstring(i).c_str());
		}
		SendMessage(hEdit3, CB_ADDSTRING, NULL, (LPARAM)L"Поворот");
		SendMessage(hEdit3, CB_ADDSTRING, NULL, (LPARAM)L"Отражение");
		SendMessage(hEdit3, CB_ADDSTRING, NULL, (LPARAM)L"Масштабирование");
		SendMessage(hEdit3, CB_ADDSTRING, NULL, (LPARAM)L"Перемещение");
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			wchar_t x[100];
			wchar_t y[100];
			wchar_t z[100];
			GetWindowText(hEditCombo1, x, 100);
			GetWindowText(hEditCombo2, y, 100);
			GetWindowText(hEditCombo3, z, 100);
			double xx = std::stod(std::wstring(x));
			double yy = std::stod(std::wstring(y));
			double zz = std::stod(std::wstring(z));
			int Vert1;
			int Vert2;
			int axis;
			Vert1 = SendMessage(hEdit1, CB_GETCURSEL, NULL, NULL);
				Vert2 = SendMessage(hEdit2, CB_GETCURSEL, NULL, NULL);
				axis = SendMessage(hEdit3, CB_GETCURSEL, NULL, NULL);
				render.act(xx, yy, zz, CurrentModel, render.verticeCoordiante(CurrentModel, Vert1), render.verticeCoordiante(CurrentModel, Vert2), axis);
			InvalidateRgn(hWnd, NULL, TRUE);
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
