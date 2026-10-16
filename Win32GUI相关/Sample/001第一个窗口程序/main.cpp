#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")


LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main()
{
	WNDCLASSEX wc{ 0 };
	wc.cbSize = sizeof(wc);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = L"MyWindowClass";
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.lpfnWndProc = WindowProc;
	RegisterClassEx(&wc);

	// 获取显示器的分辨率.
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	DWORD screenWidth = dm.dmPelsWidth;
	DWORD screenHeight = dm.dmPelsHeight;

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	DWORD dwExStyle = NULL;
	HWND hMainWindow = CreateWindowEx(dwExStyle, L"MyWindowClass", L"MainWindow", dwStyle,
		screenWidth / 8, screenHeight / 8, screenWidth / 3, screenHeight / 3, NULL, NULL, GetModuleHandle(NULL), NULL);

	ShowWindow(hMainWindow, SW_NORMAL);
	UpdateWindow(hMainWindow);

	MSG msg;
	while (GetMessageW(&msg, hMainWindow, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}


LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			break;
	}
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}