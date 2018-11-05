#pragma once
#include "SingleTon.h"

//미리 사용할 이미지를 관리, 싱글턴으로, 객체를 미리 만들어둠.



class Image;

class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, Image*>				mapImageList;
	typedef map<string, Image*>::iterator	mapImageIter;
	
private:
	mapImageList	_mImageList;


public:
	ImageManager();
	~ImageManager();

	bool Init();
	void Release();

	Image*	AddImage(string strKey, int width, int height);
	Image*	AddImage(string strKey, const TCHAR* fileName, int width, int height, bool trans, COLORREF transColor); // 스트링이 두가지니까 비슷하게 미리 만들어놓으면 좋음.
	Image*	AddImage(string strKey, const TCHAR* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor); // 스트링이 두가지니까 비슷하게 미리 만들어놓으면 좋음.
	
	Image*	AddFrameImage(string strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor); // 스트링이 두가지니까 비슷하게 미리 만들어놓으면 좋음.
	Image*	AddFrameImage(string strKey, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY ,bool trans, COLORREF transColor); // 스트링이 두가지니까 비슷하게 미리 만들어놓으면 좋음.

	Image*	findImage(string strKey);
	HDC		findImageDC(string strKey);


	bool	DeleteImage(string strKey);
	bool	DeleteAll();

	void	Render(string strKey, HDC hdc);
	void	Render(string strKey, HDC hdc, int destX, int destY);
	void	Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void	FrameRender(string strKey, HDC hdc, int destX, int destY);
	void	FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void	LoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
};

