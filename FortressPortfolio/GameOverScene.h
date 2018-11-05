#pragma once
class GameOverScene : public GameNode
{
	Image*		background;
	Image*		continueImg;

	int		nCount;
	int		colorTurnIndex;
	int		indexBlend;

public:
	GameOverScene();
	~GameOverScene();

	bool Init();
	void Update();
	void Render(HDC hdc);
};

