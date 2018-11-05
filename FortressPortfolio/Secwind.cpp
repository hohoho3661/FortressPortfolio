#include "stdafx.h"
#include "Secwind.h"
#include "SecwindBullet.h"
#include "ProgressBar.h"

Secwind::Secwind()
{
}

Secwind::~Secwind()
{
}

bool Secwind::Init()
{
	secwind = IMAGEMANAGER->findImage(TEXT("세크윈드"));
	assert(secwind != NULL);

	secwindAni = ANIMANAGER->FindAni(TEXT("SecwindR"));


	collisionRC_CenterX = WINSIZEX / 2 - 100;
	collisionRC_CenterY = 100;

	collisionRC = RectMakeCenter(collisionRC_CenterX, collisionRC_CenterY,
		TANK_SIZE, TANK_SIZE);

	// 탐사축Y값( 이동시 지형의 픽셀을 체크하면서 위치를 조정해주는 점 ) 설정
	probY = collisionRC_CenterY + TANK_SIZE / 2;

	// 캐논 설정
	angle = PI / 3;
	length = TANK_SIZE / 2;

	//
	nomalBullet = new SecwindBullet;
	nomalBullet->Init(collisionRC_CenterX, collisionRC_CenterY);

	fire = false;

	// 상태정보
	HP = 100;
	cannonPower = 0;
	move = 100;

	// 체력바
	hpBar = new ProgressBar;
	hpBar->Init(collisionRC_CenterX - TANK_SIZE / 2, collisionRC_CenterY - TANK_SIZE / 2 + 40, TANK_SIZE, 10);
	hpBar->SetGauge(HP, 100);

	//
	isTankMoving = false;
	
	//========================= 1,2는 더블  //  3은 수리  //  4는 이동탄 ========================
	useItem1 = false;
	useItem2 = false;
	useItem3 = false;
	useItem4 = false;

	haveItem1 = true;
	haveItem2 = true;
	haveItem3 = true;
	haveItem4 = true;

	return true;
}

void Secwind::Update()
{
	//// 이동관련 키
	//TankMoveKey();
	//// 발사관련 키
	//TankFireControlKey();

	if (fire == false)
	{
		nomalBullet->Init(collisionRC_CenterX, collisionRC_CenterY);
	}

	// 체력바
	hpBar->SetX(collisionRC_CenterX - TANK_SIZE / 2);
	hpBar->SetY(collisionRC_CenterY - TANK_SIZE / 2 + 40);
	hpBar->SetGauge(HP, 100);
	hpBar->Update();

	// 탱크에 적용되는 중력
	collisionRC_CenterY += TANK_GRAVITY;
	// 탱크 이동 픽셀충돌
	pixelCheck();	
}

void Secwind::Render(HDC hdc)
{
	//
	secwind->AniRenderCenter(hdc, collisionRC_CenterX - CAMERA->getPosition()->x, collisionRC_CenterY - CAMERA->getPosition()->y + 20, secwindAni);



	////
	//EllipseMakeCenter(hdc, collisionRC_CenterX - CAMERA->getPosition()->x, collisionRC_CenterY - CAMERA->getPosition()->y, 
	//	TANK_SIZE, TANK_SIZE);
	//// 포신 그리기 ( 총알의 발사지점 )
	//lineMake(hdc, collisionRC_CenterX - CAMERA->getPosition()->x, collisionRC_CenterY - CAMERA->getPosition()->y,
	//	firePoint.x - CAMERA->getPosition()->x, firePoint.y - CAMERA->getPosition()->y);

	if (fire)
	{
		nomalBullet->Render(hdc);
	}

	// 체력바
	hpBar->Render(hdc, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
}



//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================


#define POWERDECRESE 0.1


void Secwind::TankMoveKey()
{
	// 왼쪽 방향키 입력
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) // Once 한번눌렀을때 애니메이션 선택 & 스타트
	{
		dirPosY = collisionRC_CenterY;								// 키를 눌렀을시점에 Y값을 저장

		isTankMoving = true;

		secwindAni = ANIMANAGER->FindAni(TEXT("SecwindL"));
		secwindAni->start();

		if (angle > 0 && angle < PI / 2)
		{
			angle += PI / 2;
			dir = -1;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && move > 0) // Stay 누르는 동안에는 이동
	{
		collisionRC_CenterX -= TANK_MOVESPEED;
		move--;

		if (dirPosY < collisionRC_CenterY)							// dirPosY값과 비교해서 지금 Y값이 더 크면 ,, 내려가는것
		{
			secwindAni = ANIMANAGER->FindAni(TEXT("SecwindL_DOWN"));
			secwindAni->resume();
		}
		if (dirPosY > collisionRC_CenterY)							// 올라가는것
		{
			secwindAni = ANIMANAGER->FindAni(TEXT("SecwindL_UP"));
			secwindAni->resume();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		isTankMoving = false;
	}

	// 오른쪽 방향키 입력
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) // Once 한번눌렀을때 애니메이션 선택 & 스타트
	{
		dirPosY = collisionRC_CenterY;								// 키를 눌렀을시점에 Y값을 저장

		isTankMoving = true;

		secwindAni = ANIMANAGER->FindAni(TEXT("SecwindR"));
		secwindAni->start();

		if (angle > PI / 2 && angle < PI)
		{
			angle -= PI / 2;
			dir = 1;
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && move > 0) // Stay 누르는 동안에는 이동
	{
		collisionRC_CenterX += TANK_MOVESPEED;
		move--;

		if (dirPosY < collisionRC_CenterY)							// dirPosY값과 비교해서 지금 Y값이 더 크면 ,, 내려가는것
		{
			secwindAni = ANIMANAGER->FindAni(TEXT("SecwindR_DOWN"));
			secwindAni->resume();
		}
		if (dirPosY > collisionRC_CenterY)							// 올라가는것
		{
			secwindAni = ANIMANAGER->FindAni(TEXT("SecwindR_UP"));
			secwindAni->resume();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		isTankMoving = false;
	}
}

void Secwind::TankFireControlKey(int _wind)
{
	// UP 키
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (angle > 0.04f) // ++탱크의 기울기를 나중에 추가
		{
			angle -= 0.04f; // 각도가 시계방향으로
		}
	}

	// DOWN 키
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (angle < PI - 0.04f)
		{
			angle += 0.04f; // 각도가 반시계방향으로
		}
	}
	firePoint.x = collisionRC_CenterX + (cosf(angle) * length);
	firePoint.y = collisionRC_CenterY + (-sinf(angle) * length);


	// 발사버튼 ( 스페이스 바 )	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && fire == false)
	{
		// 총알 설정 초기화
		nomalBullet->Init(collisionRC_CenterX, collisionRC_CenterY);

		cannonPower = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && fire == false)
	{
		// 파워게이지 ++
		if (cannonPower <= 10);
		{
			cannonPower += 0.2f;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) && fire == false)
	{
		// 총알 발사
		fire = true;
		nomalBullet->BulletFire(collisionRC_CenterX, collisionRC_CenterY, angle, cannonPower);
		
		SOUNDMANAGER->Play(TEXT("Fire"), 0.2f);
	}

	if (fire)
	{
		nomalBullet->BulletMove(_wind, dir);
	}


	//
	if (nomalBullet->GetIsCollision()) // 총알이 충돌했는지 확인하고
	{
		fire = false; // 충돌하면 발사를 false로 바꿔줌.
	}
	

	//
	if (KEYMANAGER->isOnceKeyDown('1') && haveItem1 == true)
	{
		useItem1 = true;
		haveItem1 = false;
	}
	if (KEYMANAGER->isOnceKeyDown('2') && haveItem2 == true)
	{
		useItem2 = true;
		haveItem2 = false;
	}
	if (KEYMANAGER->isOnceKeyDown('3') && haveItem3 == true)
	{
		useItem3 = true;
		
		HP += 50;
		if (HP >= 100)
		{
			HP = 100;
		}

		haveItem3 = false;
	}
	if (KEYMANAGER->isOnceKeyDown('4') && haveItem4 == true)
	{
		useItem4 = true;

		GAMEINFO->SetUseMovingBullet(true);

		haveItem4 = false;
	}
}

void Secwind::pixelCheck()
{
	probY = collisionRC_CenterY + TANK_SIZE / 2;

	for (int i = probY - 50; i < probY; ++i) // 검사할 범위 지정
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), collisionRC_CenterX, i); // 이미지 DC값을 가져와서 픽셀 검사

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			collisionRC_CenterY = (i - TANK_SIZE / 2);
			break;
		}
	}
}