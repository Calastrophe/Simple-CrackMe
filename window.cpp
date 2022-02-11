#include "window.h"
#include <iostream>
#include <tchar.h>

#define ID_BUTTON 1

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND firstTextBox;
	static HWND secondTextBox;
	bool bypass = false;
	switch (uMsg)
	{
	case WM_CREATE:
		firstTextBox = CreateWindow(TEXT("EDIT"), TEXT("REGISTER_KEY"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 300, 25, hWnd, (HMENU)NULL, NULL, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("Submit flag"), WS_VISIBLE | WS_CHILD, 40, 40, 80, 20, hWnd, (HMENU) ID_BUTTON, NULL, NULL);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON)
		{
			char String[256];
			char String2[256] = { '4', '0', '8', 'a', '6', '5', 'c', '6', '-', '6', '6', '5', 'f', '-', '4', '4', '0', '1', '-', 'a', 'e', 'b', 'a', '-', '0', '0', 'e', 'e', '2', '8', '0', '3', '6', '7', 'b', '8', '\0' };
			wchar_t key[256] = { '1', '0', '8', 'a', '6', '5', 'c', '6', '-', '4', '6', '5', 'f', '-', '6', '4', '2', '1', '-', 'a', 'e', 'b', 'a', '-', '0', '0', 'e', 'e', '2', '8', '0', '3', '6', '7', 'b', '8', '\0' };
			GetWindowTextA(firstTextBox, String, sizeof(String));
			if (strncmp(String, String2, 256) == 0)
			{
				secondTextBox = CreateWindow(TEXT("STATIC"), key, WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 80, 300, 25, hWnd, (HMENU)NULL, NULL, NULL);
			}
			else
			{
				MessageBox(hWnd, L"Incorrect flag!", L"Incorrect input, please try again.", MB_ICONINFORMATION);
			}
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);	
	}

	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

Window::Window()
	: m_hInstance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"CrackMeClass";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 640;
	int height = 480;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		CLASS_NAME,
		L"CrackMe",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"CrackMe for BlueSec";

	UnregisterClass(CLASS_NAME, m_hInstance); // We need to clean-up the class registeration
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}
