#pragma once
#include "Backbuffer.h"

class Backbuffer;

class GameNode
{
	Backbuffer *	_backBuffer;

	bool			_managerInit;

	void	SetBackBuffer();
private:
	
public:
	GameNode();
	virtual ~GameNode();

	virtual bool Init();
	virtual bool Init(bool mInit);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Backbuffer * GetBackBuffer() { return _backBuffer; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

