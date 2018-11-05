#include "stdafx.h"
#include "MainGame.h"

#include "StartScene.h"
#include "InGameScene.h"
#include "GameOverScene.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}



bool MainGame::Init() // 초기화
{
	GameNode::Init(true);
	
	//===================================

	// 여기서 이미지 메니저를 초기화 하자.
	IMAGEMANAGER->Init();

	// 씬매니저를 초기화 하고 ... Scene을 추가
	SCENEMANAGER->Init();

	//
	EFFECTMANAGER->Init();

	// 게임 정보
	GAMEINFO->getSingleton();

	// StartScene
	IMAGEMANAGER->AddImage(TEXT("StartImage"), TEXT("Image/Fortress/StartBackGround.bmp"), 1200, 800, true, COLOR_M);

	// Map
	IMAGEMANAGER->AddImage(TEXT("BackGround"), TEXT("Image/Fortress/BackGround.bmp"), 2048, 1150, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("CollisionMap"), TEXT("Image/Fortress/CollisionMap.bmp"), 2048, 1150, true, COLOR_M);

	// Player ( 탱크 )
	// 미사일탱크
	IMAGEMANAGER->AddFrameImage(TEXT("미사일탱크"), TEXT("Image/Fortress/MissileTank.bmp"), 1050, 6300, 5, 30, true, COLOR_M);
	
	ANIMANAGER->AddCoordAni(TEXT("MissileTankR"), TEXT("미사일탱크"), 0, 20, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankL"), TEXT("미사일탱크"), 26, 49, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankR_DOWN"), TEXT("미사일탱크"), 51, 70, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankL_UP"), TEXT("미사일탱크"), 76, 99, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankR_UP"), TEXT("미사일탱크"), 101, 120, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankL_DOWN"), TEXT("미사일탱크"), 126, 149, 10, true);

	// 세크윈드
	IMAGEMANAGER->AddFrameImage(TEXT("세크윈드"), TEXT("Image/Fortress/Secwind.bmp"), 1280, 16896, 5, 66, true, COLOR_M);
	
	ANIMANAGER->AddCoordAni(TEXT("SecwindR"), TEXT("세크윈드"), 0, 55, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindL"), TEXT("세크윈드"), 56, 110, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindR_DOWN"), TEXT("세크윈드"), 111, 165, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindL_UP"), TEXT("세크윈드"), 166, 220, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindR_UP"), TEXT("세크윈드"), 221, 275, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindL_DOWN"), TEXT("세크윈드"), 276, 330, 10, true);

	// Bullet
	IMAGEMANAGER->AddFrameImage(TEXT("MissileTankBullet"), TEXT("Image/Fortress/미사일탱크탄환.bmp"), 120, 43, 4, 1, true, RGB(128, 0, 0));
	IMAGEMANAGER->AddFrameImage(TEXT("SecwindBullet"), TEXT("Image/Fortress/세크윈드탄환.bmp"), 60, 30, 2, 1, true, RGB(248, 0, 248));

	ANIMANAGER->AddCoordAni(TEXT("M_Bullet"), TEXT("MissileTankBullet"), 0, 4, 20, true);
	ANIMANAGER->AddCoordAni(TEXT("S_Bullet"), TEXT("SecwindBullet"), 0, 2, 10, true);
	
	// UI
	IMAGEMANAGER->AddImage(TEXT("UI"), TEXT("Image/Fortress/UI.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Count"), TEXT("Image/Fortress/Count.bmp"), 47, 470, 1, 10, true, RGB(255, 40, 255));

	IMAGEMANAGER->AddFrameImage(TEXT("StartButton"), TEXT("Image/Fortress/시작버튼.bmp"),0,0, 231, 222, 1, 2, true, COLOR_M);


	// Wind
	IMAGEMANAGER->AddFrameImage(TEXT("Wind"), TEXT("Image/Fortress/Wind.bmp"), 750, 150, 5, 1, true, COLOR_M);

	// GameOverScene
	IMAGEMANAGER->AddImage(TEXT("미사일탱크 전체화면"), TEXT("Image/Fortress/미사일탱크 전체화면.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("세크윈드 전체화면"), TEXT("Image/Fortress/세크윈드 전체화면.bmp"), 1200, 800, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("ToContinue"), TEXT("Image/Fortress/게임오버씬에 글자.bmp"), 785, 96, true, RGB(255,255,255));

	
	// effect
	EFFECTMANAGER->AddEffect(TEXT("Effect1"), TEXT("Image/Fortress/Effect.bmp"), 1462, 98, 97.4f, 98, 10, 0.05f, 10, RGB(255, 255, 255));

	// Sound
	SOUNDMANAGER->Init();
	SOUNDMANAGER->AddSound(TEXT("StartSound"), TEXT("Sound/시작화면 배경음.wav"), true, false);
	SOUNDMANAGER->AddSound(TEXT("InGameSound"), TEXT("Sound/포트리스 인게임 배경음.wav"), true, true);
	SOUNDMANAGER->AddSound(TEXT("GameOverSound"), TEXT("Sound/결과화면 배경음.wav"), true, true);

	SOUNDMANAGER->AddSound(TEXT("Fire"), TEXT("Sound/BulletFire.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Crash"), TEXT("Sound/Crash.wav"), false, false);


	// 아이템
	IMAGEMANAGER->AddImage(TEXT("더블"), TEXT("Image/Fortress/더블.bmp"), 50, 50, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("수리"), TEXT("Image/Fortress/수리.bmp"), 50, 50, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("이동탄"), TEXT("Image/Fortress/이동탄.bmp"), 50, 50, true, COLOR_M);

	



	// 씬 추가
	SCENEMANAGER->AddScene(TEXT("Start"), new StartScene);
	SCENEMANAGER->AddScene(TEXT("InGame"), new InGameScene);
	SCENEMANAGER->AddScene(TEXT("GameOver"), new GameOverScene);
	

	// 첫 씬 설정
	SCENEMANAGER->ChangeScene(TEXT("Start"));





	//===================================

	return true;
}

void MainGame::Release() // 해제
{
	GameNode::Release();
	//==================================
	
	//IMAGEMANAGER->Release();
	//SCENEMANAGER->Release();

	//==================================
}

void MainGame::Update() // 변동
{
	GameNode::Update();
	//==================================

	CursorCase(); // 마우스커서를 클라이언트 영역에 가두는 함수.


	SCENEMANAGER->Update();
	//==================================

}

void MainGame::Render(HDC hdc) // 그리기 ( 화면 출력 ) // 랜더링작업을 백버퍼에 프래임단위로 1/10초마다 한번씩 화면에 뿌려줌
{
	//GameNode::Render(hdc);

	HDC	backDC = (this->GetBackBuffer())->GetMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============================
	// 모든작업은 여기 안에서 작업.

	SCENEMANAGER->Render(backDC);


	//============================
	this->GetBackBuffer()->Render(hdc, 0, 0);
	
}






// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================


void MainGame::CursorCase()
{
	// 클라이언트 크기를 가져오고
	GetClientRect(_hWnd, &clientRect);

	// 클라이언트 좌표를 미리만들어둔 pt1, pt2값에 저장
	p1.x = clientRect.left;
	p1.y = clientRect.top - 20; // 20은 작업표시줄까지 여유를 둔 값.
	p2.x = clientRect.right;
	p2.y = clientRect.bottom;

	// 클라이언트 크기를 스크린 크기로 변환
	ClientToScreen(_hWnd, &p1);
	ClientToScreen(_hWnd, &p2);

	clientRect.left = p1.x;
	clientRect.top = p1.y;
	clientRect.right = p2.x;
	clientRect.bottom = p2.y;

	// 그 좌표를 기준으로 커서를 고정시킴
	ClipCursor(&clientRect);
}
