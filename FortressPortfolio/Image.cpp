#include "stdafx.h"
#include "Image.h"
#include "Animation.h"

#pragma comment(lib, "msimg32.lib") // GdiTransparentBlt를 사용하기위해서는 msimg32.lib를 추가시켜야 한다.

Image::Image() 
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0,0,0))
{	
}

Image::~Image()
{
}

bool Image::Init(int width, int height)
{
	if (_imageInfo != NULL)
		Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);
	//
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	
	if (_imageInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);

	return true;
}

bool Image::Init(const TCHAR * fileName, int width, int height, bool trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//
	size_t len = strlen(fileName);
	_fileName = new TCHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	
	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);

	return true;
}

bool Image::Init(const TCHAR * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//
	size_t len = strlen(fileName);
	_fileName = new TCHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);

	return true;
}

bool Image::Init(const TCHAR * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentframeX = 0;
	_imageInfo->currentframeY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;


	//
	size_t len = strlen(fileName);
	_fileName = new TCHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	
	if (_imageInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);

	return true;
}

bool Image::Init(const TCHAR * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentframeX = 0;
	_imageInfo->currentframeY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;


	//
	size_t len = strlen(fileName);
	_fileName = new TCHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);


	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);

	return true;
}



void Image::Release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOldBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOldBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}
}


void Image::SetTransColor(bool trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void Image::Render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else
	{
		BitBlt
		(
			hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			SRCCOPY
		);
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else
	{
		BitBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			SRCCOPY
		);
	}
}

void Image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX,			// 그림을 가져올때 잘라낼 부분,,,
			sourY,
			sourWidth,		// 출력할 비트맵의 전체 가로 세로 길이.
			sourHeight,
			_transColor
		);
	}
	else
	{
		BitBlt
		(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX,
			sourY,
			SRCCOPY
		);
	}
}

void Image::LoopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (offsetX < 0)
		offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)
		offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	int sourWidth = 0;
	int sourHeight = 0;

	RECT rcDest;										// Dest와 Sour라는 렉트를 선언하고
	RECT rcSour;

	int drawAreaX = drawArea->left;						// drawArea라는건. 그림이 그려질 위치?
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	for (int y = 0; y < drawAreaH; y += sourHeight)		// y값을 반복문으로.. 점점 sour의높이    를 더해주고
	{
		rcSour.top = (y + offsetY) % _imageInfo->height;	// sour의 탑은 .. 처음값에.. 이미지의 높이만큼을 자르고 남은값
		rcSour.bottom = _imageInfo->height;					// sour의 바텀은 .. 이미지의 높이값.

		sourHeight = rcSour.bottom - rcSour.top;			// sour의 높이

		if (y + sourHeight > drawAreaH)						// sour의 높이가 그릴영역의 높이보다 크면..
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;	// sour렉트의 바텀값에서 .. sour의높이에서 그릴영역의 높이를뺸값을 ... 빼서 대입해줌.
			sourHeight = rcSour.bottom - rcSour.top;		// sour의 높이에 ... 다시 대입.
		}
		
		rcDest.top = y + drawAreaY;							// dest의 탑값에 .. 그릴영역의 탑값..을 점점 더하면서 대입시켜줌.
		rcDest.bottom = rcDest.top + sourHeight;			// dest의 바텀값을 지정.

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			Render(hdc, rcDest.left, rcDest.top,		// dest값은 그리기 시작할 위치..
				rcSour.left, rcSour.top,				// Sour값은 오려낸 그림을 그리는거..
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void Image::AniRender(HDC hdc, int destX, int destY, Animation * ani)
{
	Render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

void Image::AniRenderCenter(HDC hdc, int centerX, int centerY, Animation * ani)
{
	Render(hdc, centerX - GetFrameWidth()/2, centerY - GetFrameHeight()/2, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

void Image::FrameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentframeX * _imageInfo->frameWidth,
			_imageInfo->currentframeY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentframeX * _imageInfo->frameWidth,
			_imageInfo->currentframeY * _imageInfo->frameHeight,
			SRCCOPY
		);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, int currentframeX, int currentframeY)
{
	_imageInfo->currentframeX = currentframeX;
	_imageInfo->currentframeY = currentframeY;

	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentframeX * _imageInfo->frameWidth,
			currentframeY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentframeX * _imageInfo->frameWidth,
			currentframeY * _imageInfo->frameHeight,
			SRCCOPY
		);
	}
}

void Image::FrameRenderCenter(HDC hdc, int centerX, int centerY)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			centerX - GetFrameWidth() / 2,
			centerY - GetFrameHeight() / 2,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentframeX * _imageInfo->frameWidth,
			_imageInfo->currentframeY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt
		(
			hdc,
			centerX - GetFrameWidth() / 2,
			centerY - GetFrameHeight() / 2,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentframeX * _imageInfo->frameWidth,
			_imageInfo->currentframeY * _imageInfo->frameHeight,
			SRCCOPY
		);
	}
}

void Image::AlphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y,
			SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,					// 블랭딩이미지에 복사하고
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,		// 트랜스 처리
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY,						// 알파블랜드에 적용
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		GdiAlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
}

// 블랜딩 .. 내 이미지와 배경이미지를 섞는다.
// 설정하는 알파값에 따라 출력.