#include "Menu Handler.h"

#define MAX_LOADSTRING 100;

// Global variables:
HINSTANCE hInst;
WCHAR szTitle[] = L"Process Explorer"; // title bar text

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HWND hwndRun;
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	// For Menu files
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_HELP_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, AboutDlgProc);
			break;
		case ID_FILE_EXIT:
			EXIT(hwnd);
			break;
		case ID_OPTIONS_ALWAYSONTOP:
			AlwaysOnTop(hwnd);
			break;
		case ID_FILE_RUNNEWTASKS:
			HINSTANCE hInstance = GetModuleHandle(szTitle);
			RECT Rect;
			GetWindowRect(hwnd, &Rect);

			HWND Run_New_Task = CreateWindowEx(
				0,
				(LPCWSTR)szTitle,
				L"Run new task",
				WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
				50, 50, Rect.right - Rect.left - 500, Rect.bottom - Rect.top - 200,
				hwnd,
				NULL,
				hInstance,
				NULL
			);
			
		}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	// Registering Window class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROCESSEXPLORER));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = (LPCWSTR)szTitle;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hInst = hInstance;

	wc.lpfnWndProc = RunWndProc;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RUNTASK));
	RegisterClassEx(&wc);


	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(LPCWSTR)szTitle,
		L"Process Explorer",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"ERROR!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
