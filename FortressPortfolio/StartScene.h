#pragma once

// 실행시켯을때 젤 먼저 나오는 씬.

class Button;

class StartScene : public GameNode
{
//	RECT	selectButton;
	Image*	startBackImg;
	Button*	pButton;

	int		nCount;
	int		colorTurnIndex;
	int		indexBlend;

public:
	StartScene();
	~StartScene();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void cbSceneChange();
};