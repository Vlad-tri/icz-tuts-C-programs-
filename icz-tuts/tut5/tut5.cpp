#include<Windows.h>

#pragma comment (lib,"gdiplus.lib")

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
		HFONT hfont;
		hdc = BeginPaint(hwnd,&ps);
		HGDIOBJ h = CreateFont(24,16,0,0,400,0,0,0,OEM_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SCRIPT,"script");
		HGDIOBJ hso = SelectObject(hdc,h);
		hfont = (HFONT)hso;
		COLORREF crText = 16711935;
		COLORREF bk = 10171935;
		SetTextColor(hdc,crText);
		SetBkColor(hdc,bk);
		TextOut(hdc,0,0,"Hello Vlad",sizeof("Hello Vlad"));
		SelectObject(hdc,hso);
		EndPaint(hwnd,&ps);
	} 
	else {
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}
	return LRESULT(NULL);
}