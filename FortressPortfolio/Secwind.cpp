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
	secwind = IMAGEMANAGER->findImage(TEXT("��ũ����"));
	assert(secwind != NULL);

	secwindAni = ANIMANAGER->FindAni(TEXT("SecwindR"));


	collisionRC_CenterX = WINSIZEX / 2 - 100;
	collisionRC_CenterY = 100;

	collisionRC = RectMakeCenter(collisionRC_CenterX, collisionRC_CenterY,
		TANK_SIZE, TANK_SIZE);

	// Ž����Y��( �̵��� ������ �ȼ��� üũ�ϸ鼭 ��ġ�� �������ִ� �� ) ����
	probY = collisionRC_CenterY + TANK_SIZE / 2;

	// ĳ�� ����
	angle = PI / 3;
	length = TANK_SIZE / 2;

	//
	nomalBullet = new SecwindBullet;
	nomalBullet->Init(collisionRC_CenterX, collisionRC_CenterY);

	fire = false;

	// ��������
	HP = 100;
	cannonPower = 0;
	move = 100;

	// ü�¹�
	hpBar = new ProgressBar;
	hpBar->Init(collisionRC_CenterX - TANK_SIZE / 2, collisionRC_CenterY - TANK_SIZE / 2 + 40, TANK_SIZE, 10);
	hpBar->SetGauge(HP, 100);

	//
	isTankMoving = false;
	
	//========================= 1,2�� ����  //  3�� ����  //  4�� �̵�ź ========================
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
	//// �̵����� Ű
	//TankMoveKey();
	//// �߻���� Ű
	//TankFireControlKey();

	if (fire == false)
	{
		nomalBullet->Init(collisionRC_CenterX, collisionRC_CenterY);
	}

	// ü�¹�
	hpBar->SetX(collisionRC_CenterX - TANK_SIZE / 2);
	hpBar->SetY(collisionRC_CenterY - TANK_SIZE / 2 + 40);
	hpBar->SetGauge(HP, 100);
	hpBar->Update();

	// ��ũ�� ����Ǵ� �߷�
	collisionRC_CenterY += TANK_GRAVITY;
	// ��ũ �̵� �ȼ��浹
	pixelCheck();	
}

void Secwind::Render(HDC hdc)
{
	//
	secwind->AniRenderCenter(hdc, collisionRC_CenterX - CAMERA->getPosition()->x, collisionRC_CenterY - CAMERA->getPosition()->y + 20, secwindAni);



	////
	//EllipseMakeCenter(hdc, collisionRC_CenterX - CAMERA->getPosition()->x, collisionRC_CenterY - CAMERA->getPosition()->y, 
	//	TANK_SIZE, TANK_SIZE);
	//// ���� �׸��� ( �Ѿ��� �߻����� )
	//lineMake(hdc, collisionRC_CenterX - CAMERA->getPosition()->x, collisionRC_CenterY - CAMERA->getPosition()->y,
	//	firePoint.x - CAMERA->getPosition()->x, firePoint.y - CAMERA->getPosition()->y);

	if (fire)
	{
		nomalBullet->Render(hdc);
	}

	// ü�¹�
	hpBar->Render(hdc, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
}



//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================


#define POWERDECRESE 0.1


void Secwind::TankMoveKey()
{
	// ���� ����Ű �Է�
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) // Once �ѹ��������� �ִϸ��̼� ���� & ��ŸƮ
	{
		dirPosY = collisionRC_CenterY;								// Ű�� ������������ Y���� ����

		isTankMoving = true;

		secwindAni = ANIMANAGER->FindAni(TEXT("SecwindL"));
		secwindAni->start();

		if (angle > 0 && angle < PI / 2)
		{
			angle += PI / 2;
			dir = -1;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && move > 0) // Stay ������ ���ȿ��� �̵�
	{
		collisionRC_CenterX -= TANK_MOVESPEED;
		move--;

		if (dirPosY < collisionRC_CenterY)							// dirPosY���� ���ؼ� ���� Y���� �� ũ�� ,, �������°�
		{
			secwindAni = ANIMANAGER->FindAni(TEXT("SecwindL_DOWN"));
			secwindAni->resume();
		}
		if (dirPosY > collisionRC_CenterY)							// �ö󰡴°�
		{
			secwindAni = ANIMANAGER->FindAni(TEXT("SecwindL_UP"));
			secwindAni->resume();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		isTankMoving = false;
	}

	// ������ ����Ű �Է�
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) // Once �ѹ��������� �ִϸ��̼� ���� & ��ŸƮ
	{
		dirPosY = collisionRC_CenterY;								// Ű�� ������������ Y���� ����

		isTankMoving = true;

		secwindAni = ANIMANAGER->FindAni(TEXT("SecwindR"));
		secwindAni->start();

		if (angle > PI / 2 && angle < PI)
		{
			angle -= PI / 2;
			dir = 1;
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && move > 0) // Stay ������ ���ȿ��� �̵�
	{
		collisionRC_CenterX += TANK_MOVESPEED;
		move--;

		if (dirPosY < collisionRC_CenterY)							// dirPosY���� ���ؼ� ���� Y���� �� ũ�� ,, �������°�
		{
			secwindAni = ANIMANAGER->FindAni(TEXT("SecwindR_DOWN"));
			secwindAni->resume();
		}
		if (dirPosY > collisionRC_CenterY)							// �ö󰡴°�
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
	// UP Ű
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (angle > 0.04f) // ++��ũ�� ���⸦ ���߿� �߰�
		{
			angle -= 0.04f; // ������ �ð��������
		}
	}

	// DOWN Ű
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (angle < PI - 0.04f)
		{
			angle += 0.04f; // ������ �ݽð��������
		}
	}
	firePoint.x = collisionRC_CenterX + (cosf(angle) * length);
	firePoint.y = collisionRC_CenterY + (-sinf(angle) * length);


	// �߻��ư ( �����̽� �� )	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && fire == false)
	{
		// �Ѿ� ���� �ʱ�ȭ
		nomalBullet->Init(collisionRC_CenterX, collisionRC_CenterY);

		cannonPower = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && fire == false)
	{
		// �Ŀ������� ++
		if (cannonPower <= 10);
		{
			cannonPower += 0.2f;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) && fire == false)
	{
		// �Ѿ� �߻�
		fire = true;
		nomalBullet->BulletFire(collisionRC_CenterX, collisionRC_CenterY, angle, cannonPower);
		
		SOUNDMANAGER->Play(TEXT("Fire"), 0.2f);
	}

	if (fire)
	{
		nomalBullet->BulletMove(_wind, dir);
	}


	//
	if (nomalBullet->GetIsCollision()) // �Ѿ��� �浹�ߴ��� Ȯ���ϰ�
	{
		fire = false; // �浹�ϸ� �߻縦 false�� �ٲ���.
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

	for (int i = probY - 50; i < probY; ++i) // �˻��� ���� ����
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), collisionRC_CenterX, i); // �̹��� DC���� �����ͼ� �ȼ� �˻�

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