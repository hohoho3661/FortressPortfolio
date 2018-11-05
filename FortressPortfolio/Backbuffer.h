#pragma once
class Backbuffer
{
	typedef struct tagBackbufferInfo
	{
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOldBit;
		float		x, y;
		int			width;
		int			height;

		tagBackbufferInfo()
		{
			hMemDC	= NULL;
			hBit	= NULL;
			hOldBit = NULL;
			x		= 0.f;
			y		= 0.f;
			width	= 0;
			height	= 0;
		}
	}BackbufferInfo, *LPBackbufferInfo;
private:
	LPBackbufferInfo _backBufferInfo;

public:
	Backbuffer();
	virtual ~Backbuffer();

	bool Init(int width, int height);
	void Release();
	void Render(HDC hdc, int destX, int destY);

	inline HDC GetMemDC() { return _backBufferInfo->hMemDC; }
};

