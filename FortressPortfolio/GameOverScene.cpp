#include "stdafx.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}

bool GameOverScene::Init()
{
	background = IMAGEMANAGER->findImage(TEXT("세크윈드 전체화면"));
	SOUNDMANAGER->Stop(TEXT("InGameSound"));
	SOUNDMANAGER->Play(TEXT("GameOverSound"), 0.2f);

	continueImg = IMAGEMANAGER->findImage(TEXT("ToContinue"));

	//
	indexBlend = 150;
	nCount = 200;
	colorTurnIndex = 1;


	return true;
}

void GameOverScene::Update()
{
	if (GAMEINFO->GetWhoIsWin() == 1)
	{
		background = IMAGEMANAGER->findImage(TEXT("세크윈드 전체화면"));
	}
	if (GAMEINFO->GetWhoIsWin() == 2)
	{
		background = IMAGEMANAGER->findImage(TEXT("미사일탱크 전체화면"));
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->Stop(TEXT("GameOverSound"));
		SCENEMANAGER->ChangeScene(TEXT("Start"));
	}


	// 점점나왔다가 점점사라지기
	if (nCount >= 254 || nCount <= 60) // 최대, 최소값
		colorTurnIndex *= -1;

	if (colorTurnIndex == 1)
		nCount += 2;
	if (colorTurnIndex == -1)
		nCount -= 2;

	indexBlend = nCount;
}

void GameOverScene::Render(HDC hdc)
{
	background->Render(hdc);

	continueImg->AlphaRender(hdc, WINSIZEX / 2 - continueImg->GetWidth() / 2, WINSIZEY / 2 - continueImg->GetHeight() / 2, indexBlend);

	//SetBkMode(hdc, TRANSPARENT); // 글자 배경색 없애기
	//SetTextColor(hdc, RGB(20, 180, 10)); // 글자 색깔 정하기
	//SetTextCharacterExtra(hdc, 4);
	//TCHAR szTemp[100] = { 0, };
	//_stprintf_s(szTemp, sizeof(szTemp), TEXT("Press [Enter] to continue..."));
	//TextOut(hdc, COMPASS_CENTER_X - 20, COMPASS_CENTER_Y + 33, TEXT(szTemp), _tcslen(TEXT(szTemp)));
}
