#include "Menu Handler.h"

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			EndDialog(hwnd, IDOK);
			break;
		}
		else
			return FALSE;
	default:
		return FALSE;
	}
	return TRUE;
}
BOOL CALLBACK EXIT(HWND hwnd) {
	if (PostMessage(hwnd, WM_CLOSE, 0, 0))
		return TRUE;
	else {
		MessageBox(NULL, L"Exit failed", L"ERROR!", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
}
BOOL CALLBACK AlwaysOnTop(HWND hwnd) {
	HMENU hMenu= GetMenu(hwnd);
	MENUITEMINFO menuItem = { 0 };
	menuItem.cbSize = sizeof(MENUITEMINFO);
	menuItem.fMask = MIIM_STATE;
	GetMenuItemInfo(hMenu, ID_OPTIONS_ALWAYSONTOP, FALSE, &menuItem);

	if (menuItem.fState == MFS_UNCHECKED) {
		if (SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE))
			menuItem.fState = MFS_CHECKED;
		else {
			MessageBox(NULL, L"Always On Top failed!", L"ERROR!", MB_ICONEXCLAMATION | MB_OK);
			return FALSE;
		}
	}
	else {
		if (SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE))
			menuItem.fState = MFS_UNCHECKED;
		else {
			MessageBox(NULL, L"Always On Top failed!", L"ERROR!", MB_ICONEXCLAMATION | MB_OK);
			return FALSE;
		}
	}
	SetMenuItemInfo(hMenu, ID_OPTIONS_ALWAYSONTOP, FALSE, &menuItem);
	return TRUE;
}
BOOL CALLBACK RunTask(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return FALSE;
}



LRESULT CALLBACK RunWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hwndParent = GetParent(hwnd);  // hwnd for parent (Main)

	switch (msg) {
	case WM_CREATE:
		// communicate with parent, so that the parent window is disabled
		EnableWindow(hwndParent, FALSE);
		return 0;
	
	// Make case for drop file
	

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		// communicate with parent, so that the parent window is enabled.
		EnableWindow(hwndParent, TRUE);
		PostQuitMessage(0);
		break;



		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}