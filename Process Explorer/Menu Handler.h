#pragma once
#include "framework.h"

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EXIT(HWND hwnd);
BOOL CALLBACK AlwaysOnTop(HWND hwnd);
BOOL CALLBACK RunTask(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK RunWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);