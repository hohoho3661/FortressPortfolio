#include "stdafx.h"
#include "Backbuffer.h"


Backbuffer::Backbuffer() : _backBufferInfo(NULL)
{
}


Backbuffer::~Backbuffer()
{
}

bool Backbuffer::Init(int width, int height)
{
	if (_backBufferInfo != NULL)
		Release();

	HDC hdc = GetDC(_hWnd);
	_backBufferInfo = new BackbufferInfo;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);			// 그려줌... 전환은 화면마다 한번씩만
	_backBufferInfo->hOldBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = width;
	_backBufferInfo->height = height;

	if (_backBufferInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);
	return false;
}

void Backbuffer::Release()
{
	if (_backBufferInfo)
	{
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hOldBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		SAFE_DELETE(_backBufferInfo);
	}
}



//  목적지에 대한 좌표,,,, 소스에 대한 좌표
void Backbuffer::Render(HDC hdc, int destX, int destY)
{
	// 백버퍼에 출력된 내용들을 화면으로 고속복사
	BitBlt(hdc,									// 복사가 되는 DC
		destX,									// 복사가 되는 위치
		destY,
		_backBufferInfo->width,					// 복사가 되는 크기
		_backBufferInfo->height,
		_backBufferInfo->hMemDC,				// 복사할 소스가 있는 DC
		0,										// 복사할 소스의 시작 위치
		0,
		SRCCOPY);
}
