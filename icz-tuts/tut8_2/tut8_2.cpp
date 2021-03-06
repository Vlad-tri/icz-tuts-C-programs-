#include<Windows.h>
#include<Windows.h>

#define IDM_TEST 1
#define IDM_HELLO 2
#define IDM_GOODBYE 3
#define IDM_EXIT 4

LRESULT CALLBACK WndProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);

INT WinMain(HINSTANCE hInstance = GetModuleHandle(NULL), HINSTANCE hPrevInstance = NULL, LPSTR lpCmdLine = GetCommandLineA(), INT cmdShow = SW_SHOWDEFAULT) {

	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("Simple Win Class");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClassEx(&wc);
	HMENU hMenu = LoadMenu(hInstance, TEXT("FirstMenu"));
	hWnd = CreateWindowEx(NULL, TEXT("Simple Win Class"), TEXT("Our First Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, hMenu, hInstance, NULL);
	ShowWindow(hWnd, cmdShow);
	UpdateWindow(hWnd);

	while (true) {
		BOOL a = GetMessage(&msg, NULL, 0, 0);
		if (!a) {
			break;
		}
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(NULL);
	}
	else if (uMsg == WM_COMMAND) {
		if (LOWORD(wParam) == IDM_TEST) {
			MessageBox(NULL, L"This is the test", L"First Window", MB_OK);
		}
		else if (LOWORD(wParam) == IDM_HELLO) {
			MessageBox(NULL, L"Hello World", L"First Window", MB_OK);
		}
		else if (LOWORD(wParam) == IDM_GOODBYE) {
			MessageBox(NULL, L"Bye bye", L"First Window", MB_OK);
		}
		else {
			DestroyWindow(hwnd);
		}
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return LRESULT(NULL);
}