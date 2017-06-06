#include<Windows.h>


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
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	RegisterClassEx(&wc);
	hWnd = CreateWindowEx(NULL,TEXT("Simple Win Class"),TEXT("Our First Window"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hWnd,cmdShow);
	UpdateWindow(hWnd);

	while(true) {
		BOOL a = GetMessage(&msg,NULL,0,0);
		if (!a) {
			break;
		}
		TranslateMessage(&msg);
		LRESULT dm = DispatchMessage(&msg);
	}
	return 0;
} 

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(NULL);
	}
	else if (uMsg == WM_PAINT) {
		PAINTSTRUCT ps;
		HDC hdc;
		RECT rect;
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rect);
		DrawText(hdc,TEXT("Assembly is necessary for Vlad"),-1,&rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd,&ps);
	} 
	else {
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}
	return LRESULT(NULL);
}