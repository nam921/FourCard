#include "Main.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass="SilenceStory Server";

FourCardServer* game_server;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	game_server = new FourCardServer();
	game_server->start(5807);

	
	while(GetMessage(&Message,0,0,0)) {
      if (!IsDialogMessage(hWnd,&Message)) { 
         TranslateMessage(&Message); 
         DispatchMessage(&Message); 
      } 
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc, hMemDC;
	HBITMAP hBit, hOldBit;
	PAINTSTRUCT ps;

	static RECT rtClient;

	static HWND hButton_start, hButton_end;

	switch(iMessage) {
	case WM_CREATE:
		// 클라이언트의 작업 영역을 720*480 으로 고정합니다.
		SetRect(&rtClient, 0, 0, 230, 50);
		AdjustWindowRect(&rtClient, GetWindowLong(hWnd, GWL_STYLE), FALSE);
		SetRect(&rtClient, 0, 0, rtClient.right - rtClient.left, rtClient.bottom - rtClient.top);
		SetWindowPos(hWnd, NULL, GetSystemMetrics(SM_CXSCREEN) / 2 - rtClient.right / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - rtClient.bottom / 2, rtClient.right, rtClient.bottom, SWP_NOZORDER);
		// 50 FPS로 동작하도록 20ms마다 WM_PAINT를 호출 합니다.
		SetTimer(hWnd, TM_PAINT, 20, NULL);

		hButton_start = CreateWindow("button", "Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_DISABLED, 10, 10, 100, 30, hWnd, (HMENU) 1, g_hInst, NULL);
		hButton_end = CreateWindow("button", "End", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 10, 100, 30, hWnd, (HMENU) 2, g_hInst, NULL);

		return 0;
	case WM_TIMER:
		switch(wParam)
		{
		case TM_PAINT:
			InvalidateRect(hWnd, NULL, false);
			break;
		}
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case 1:
			{
			game_server->start(5807);
			EnableWindow(hButton_start, FALSE);
			EnableWindow(hButton_end, TRUE);
			}
			break;
		case 2:

			game_server->end();
			EnableWindow(hButton_start, TRUE);
			EnableWindow(hButton_end, FALSE);
			break;
		}
		return 0;
	case WM_PAINT:
		// 더블 버퍼링 (hMemDC에 출력)
		hdc=BeginPaint(hWnd, &ps);
		hMemDC=CreateCompatibleDC(hdc);
		hBit = CreateCompatibleBitmap(hdc, rtClient.right, rtClient.bottom);
		hOldBit = (HBITMAP) SelectObject(hMemDC, hBit);
		FillRect(hMemDC, &rtClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

		// 이 코드 블럭 안에 그리기 코드를 추가합니다 :
		{
		}

		BitBlt(hdc, 0, 0, rtClient.right, rtClient.bottom, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hOldBit);
		DeleteObject(hBit);
		DeleteDC(hMemDC);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DestroyWindow(hButton_start);
		DestroyWindow(hButton_end);
		if(game_server->is_running())
			game_server->end();
		delete game_server;
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}