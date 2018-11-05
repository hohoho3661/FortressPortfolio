#include "stdafx.h"

#include "CustomDefine.h"
#include "MacroDefine.h"

#include "MainGame.h"

//=======================================================================================================================================================
MainGame _mg; // 메인게임 객체를만들고

HINSTANCE	_hInst;
HWND		_hWnd;
POINT		_ptMouse;

LPCTSTR		_lpszClass = TEXT("Win32API");
//========================================================================================================================================================

void setWindowsSize(int x, int y, int width, int height);



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lPszCmdParam, int cmdShow)
{
	MSG							message;
	WNDCLASS					wndClass;

	_hInst = hInstance;


	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	if (!_hWnd)
		return 0;

	setWindowsSize(WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY);

	//=========================================================================================================================================
	if (!_mg.Init())												// 인잇하고
		return 0;

	ShowWindow(_hWnd, cmdShow);

	HDC hdc = GetDC(_hWnd);											// 업데이트

	while (true) // 메세지가 없더라도 true를 리턴해서 루프가 돈다.
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else    // 데드윈도우 상태에서도 돌리기 위해서
		{
			TIMEMANAGER->Update(60.f);

			_mg.Update();
			_mg.Render(hdc);										// 업데이트 & 랜더
		}
	}

	_mg.Release();													// 릴리즈
	ReleaseDC(_hWnd, hdc);
	//=========================================================================================================================================

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // 메세지, 쓰레드, 타이머 콜백
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, NULL);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left)
		, (winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}
