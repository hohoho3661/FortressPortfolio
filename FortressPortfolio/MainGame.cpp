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



bool MainGame::Init() // �ʱ�ȭ
{
	GameNode::Init(true);
	
	//===================================

	// ���⼭ �̹��� �޴����� �ʱ�ȭ ����.
	IMAGEMANAGER->Init();

	// ���Ŵ����� �ʱ�ȭ �ϰ� ... Scene�� �߰�
	SCENEMANAGER->Init();

	//
	EFFECTMANAGER->Init();

	// ���� ����
	GAMEINFO->getSingleton();

	// StartScene
	IMAGEMANAGER->AddImage(TEXT("StartImage"), TEXT("Image/Fortress/StartBackGround.bmp"), 1200, 800, true, COLOR_M);

	// Map
	IMAGEMANAGER->AddImage(TEXT("BackGround"), TEXT("Image/Fortress/BackGround.bmp"), 2048, 1150, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("CollisionMap"), TEXT("Image/Fortress/CollisionMap.bmp"), 2048, 1150, true, COLOR_M);

	// Player ( ��ũ )
	// �̻�����ũ
	IMAGEMANAGER->AddFrameImage(TEXT("�̻�����ũ"), TEXT("Image/Fortress/MissileTank.bmp"), 1050, 6300, 5, 30, true, COLOR_M);
	
	ANIMANAGER->AddCoordAni(TEXT("MissileTankR"), TEXT("�̻�����ũ"), 0, 20, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankL"), TEXT("�̻�����ũ"), 26, 49, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankR_DOWN"), TEXT("�̻�����ũ"), 51, 70, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankL_UP"), TEXT("�̻�����ũ"), 76, 99, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankR_UP"), TEXT("�̻�����ũ"), 101, 120, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("MissileTankL_DOWN"), TEXT("�̻�����ũ"), 126, 149, 10, true);

	// ��ũ����
	IMAGEMANAGER->AddFrameImage(TEXT("��ũ����"), TEXT("Image/Fortress/Secwind.bmp"), 1280, 16896, 5, 66, true, COLOR_M);
	
	ANIMANAGER->AddCoordAni(TEXT("SecwindR"), TEXT("��ũ����"), 0, 55, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindL"), TEXT("��ũ����"), 56, 110, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindR_DOWN"), TEXT("��ũ����"), 111, 165, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindL_UP"), TEXT("��ũ����"), 166, 220, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindR_UP"), TEXT("��ũ����"), 221, 275, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("SecwindL_DOWN"), TEXT("��ũ����"), 276, 330, 10, true);

	// Bullet
	IMAGEMANAGER->AddFrameImage(TEXT("MissileTankBullet"), TEXT("Image/Fortress/�̻�����ũźȯ.bmp"), 120, 43, 4, 1, true, RGB(128, 0, 0));
	IMAGEMANAGER->AddFrameImage(TEXT("SecwindBullet"), TEXT("Image/Fortress/��ũ����źȯ.bmp"), 60, 30, 2, 1, true, RGB(248, 0, 248));

	ANIMANAGER->AddCoordAni(TEXT("M_Bullet"), TEXT("MissileTankBullet"), 0, 4, 20, true);
	ANIMANAGER->AddCoordAni(TEXT("S_Bullet"), TEXT("SecwindBullet"), 0, 2, 10, true);
	
	// UI
	IMAGEMANAGER->AddImage(TEXT("UI"), TEXT("Image/Fortress/UI.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Count"), TEXT("Image/Fortress/Count.bmp"), 47, 470, 1, 10, true, RGB(255, 40, 255));

	IMAGEMANAGER->AddFrameImage(TEXT("StartButton"), TEXT("Image/Fortress/���۹�ư.bmp"),0,0, 231, 222, 1, 2, true, COLOR_M);


	// Wind
	IMAGEMANAGER->AddFrameImage(TEXT("Wind"), TEXT("Image/Fortress/Wind.bmp"), 750, 150, 5, 1, true, COLOR_M);

	// GameOverScene
	IMAGEMANAGER->AddImage(TEXT("�̻�����ũ ��üȭ��"), TEXT("Image/Fortress/�̻�����ũ ��üȭ��.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("��ũ���� ��üȭ��"), TEXT("Image/Fortress/��ũ���� ��üȭ��.bmp"), 1200, 800, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("ToContinue"), TEXT("Image/Fortress/���ӿ������� ����.bmp"), 785, 96, true, RGB(255,255,255));

	
	// effect
	EFFECTMANAGER->AddEffect(TEXT("Effect1"), TEXT("Image/Fortress/Effect.bmp"), 1462, 98, 97.4f, 98, 10, 0.05f, 10, RGB(255, 255, 255));

	// Sound
	SOUNDMANAGER->Init();
	SOUNDMANAGER->AddSound(TEXT("StartSound"), TEXT("Sound/����ȭ�� �����.wav"), true, false);
	SOUNDMANAGER->AddSound(TEXT("InGameSound"), TEXT("Sound/��Ʈ���� �ΰ��� �����.wav"), true, true);
	SOUNDMANAGER->AddSound(TEXT("GameOverSound"), TEXT("Sound/���ȭ�� �����.wav"), true, true);

	SOUNDMANAGER->AddSound(TEXT("Fire"), TEXT("Sound/BulletFire.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Crash"), TEXT("Sound/Crash.wav"), false, false);


	// ������
	IMAGEMANAGER->AddImage(TEXT("����"), TEXT("Image/Fortress/����.bmp"), 50, 50, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("����"), TEXT("Image/Fortress/����.bmp"), 50, 50, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("�̵�ź"), TEXT("Image/Fortress/�̵�ź.bmp"), 50, 50, true, COLOR_M);

	



	// �� �߰�
	SCENEMANAGER->AddScene(TEXT("Start"), new StartScene);
	SCENEMANAGER->AddScene(TEXT("InGame"), new InGameScene);
	SCENEMANAGER->AddScene(TEXT("GameOver"), new GameOverScene);
	

	// ù �� ����
	SCENEMANAGER->ChangeScene(TEXT("Start"));





	//===================================

	return true;
}

void MainGame::Release() // ����
{
	GameNode::Release();
	//==================================
	
	//IMAGEMANAGER->Release();
	//SCENEMANAGER->Release();

	//==================================
}

void MainGame::Update() // ����
{
	GameNode::Update();
	//==================================

	CursorCase(); // ���콺Ŀ���� Ŭ���̾�Ʈ ������ ���δ� �Լ�.


	SCENEMANAGER->Update();
	//==================================

}

void MainGame::Render(HDC hdc) // �׸��� ( ȭ�� ��� ) // �������۾��� ����ۿ� �����Ӵ����� 1/10�ʸ��� �ѹ��� ȭ�鿡 �ѷ���
{
	//GameNode::Render(hdc);

	HDC	backDC = (this->GetBackBuffer())->GetMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============================
	// ����۾��� ���� �ȿ��� �۾�.

	SCENEMANAGER->Render(backDC);


	//============================
	this->GetBackBuffer()->Render(hdc, 0, 0);
	
}






// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================


void MainGame::CursorCase()
{
	// Ŭ���̾�Ʈ ũ�⸦ ��������
	GetClientRect(_hWnd, &clientRect);

	// Ŭ���̾�Ʈ ��ǥ�� �̸������� pt1, pt2���� ����
	p1.x = clientRect.left;
	p1.y = clientRect.top - 20; // 20�� �۾�ǥ���ٱ��� ������ �� ��.
	p2.x = clientRect.right;
	p2.y = clientRect.bottom;

	// Ŭ���̾�Ʈ ũ�⸦ ��ũ�� ũ��� ��ȯ
	ClientToScreen(_hWnd, &p1);
	ClientToScreen(_hWnd, &p2);

	clientRect.left = p1.x;
	clientRect.top = p1.y;
	clientRect.right = p2.x;
	clientRect.bottom = p2.y;

	// �� ��ǥ�� �������� Ŀ���� ������Ŵ
	ClipCursor(&clientRect);
}
