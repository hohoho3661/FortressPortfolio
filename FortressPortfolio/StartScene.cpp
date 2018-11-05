#include "stdafx.h"
#include "StartScene.h"
#include "Button.h"



StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	startBackImg = IMAGEMANAGER->findImage(TEXT("StartImage"));

	pButton = new Button;
	assert(pButton != NULL);

	pButton->Init(TEXT("StartButton"), WINSIZEX / 2, WINSIZEY - 100,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);
	
	//
	indexBlend = 150;
	nCount = 200;
	colorTurnIndex = 1;


	//
	SOUNDMANAGER->Play(TEXT("StartSound"), 0.5f);



	return true;
}

void StartScene::Release()
{
	SAFE_DELETE(pButton);
}

void StartScene::Update()
{
	// 점점나왔다가 점점사라지기
	if (nCount == 254 || nCount == 150) // 최대, 최소값
		colorTurnIndex *= -1;

	if (colorTurnIndex == 1)
		nCount++;
	if (colorTurnIndex == -1)
		nCount--;

	indexBlend = nCount;
	

	pButton->Update();
}

void StartScene::Render(HDC hdc)
{
	startBackImg->AlphaRender(hdc, indexBlend);
	pButton->Render(hdc);
}

void StartScene::cbSceneChange()
{
	SCENEMANAGER->ChangeScene(TEXT("InGame"));
}


// 버튼은 ,,, 실행하기위한 직접정인 정보는 x

// 함수포인터를 실행하도록만

// 여기서는 cbSceneChange()이다.