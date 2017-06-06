#include<Windows.h>
#include<Windows.h>

#define ButtonID 1
#define EditID 2
#define IDM_HELLO 1
#define IDM_CLEAR 2
#define IDM_GETTEXT 3
#define IDM_EXIT 4

LRESULT CALLBACK WndProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);

HINSTANCE hInstance = GetModuleHandle(NULL);
HWND hWndEdit;
HWND hWndButton;
CHAR buffer[512];

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
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszMenuName = TEXT("FirstMenu");
	wc.lpszClassName = TEXT("Simple Win Class");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClassEx(&wc);
	hWnd = CreateWindowEx(NULL, TEXT("Simple Win Class"), TEXT("Our First Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	while (true) {
		BOOL a = GetMessage(&msg, NULL, 0, 0);
		if (!a) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(NULL);
	}
	else if (uMsg == WM_CREATE) {
		hWndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 50, 35, 200, 25, hwnd, (HMENU)8, hInstance, NULL);
		SetFocus(hWndEdit);
		hWndButton = CreateWindowEx(NULL, TEXT("button"), TEXT("My First Button"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 75, 70, 140, 25, hwnd, HMENU(ButtonID), hInstance, NULL);
	}
	else if (uMsg == WM_COMMAND) {
		if (lParam == 0) {
			if (LOWORD(wParam) == IDM_HELLO) {
				SetWindowText(hWndEdit, TEXT("This is the test string"));
			}
			else if (LOWORD(wParam) == IDM_CLEAR) {
				SetWindowText(hWndEdit, NULL);
			}
			else if (LOWORD(wParam) == IDM_GETTEXT) {
				GetWindowText(hWndEdit, buffer, 512);
				MessageBox(NULL, buffer, TEXT("Window Text"), MB_OK);
			}
			else {
				DestroyWindow(hwnd);
			}
		}
		else {
			if (LOWORD(wParam) == ButtonID) {
				WPARAM wp = wParam;
				wp = wp << 16;
				if (LOWORD(wp) == BN_CLICKED) {
					SendMessage(hwnd, WM_COMMAND, IDM_GETTEXT, 0);
				}
			}
		}
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return LRESULT(NULL);
}