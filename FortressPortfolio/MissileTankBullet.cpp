#include "stdafx.h"
#include "MissileTankBullet.h"

MissileTankBullet::MissileTankBullet()
{
}


MissileTankBullet::~MissileTankBullet()
{
}

bool MissileTankBullet::Init(float _x, float _y)
{
	bulletImg = IMAGEMANAGER->findImage(TEXT("MissileTankBullet"));
	bulletAni = ANIMANAGER->FindAni(TEXT("M_Bullet"));
	bulletAni->start();

	x = _x;
	y = _y;
	speedX = speedY = 5.f;

	radius = 15;
	gravity = 0.5f;


	cannonPower = 2;

	isCollision = false;

	return true;
}

void MissileTankBullet::Render(HDC hdc)
{
	// �Ѿ� �׸���
	EllipseMakeCenter(hdc, x - CAMERA->getPosition()->x, y - CAMERA->getPosition()->y,
		radius * 2, radius * 2);
	
	// �̹���
	bulletImg->AniRenderCenter(hdc, x - CAMERA->getPosition()->x, y - CAMERA->getPosition()->y, bulletAni);
		
	// �浹 üũ
	if (GAMEINFO->GetUseMovingBullet() == false)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), x, y); // �̹��� DC���� �����ͼ� �ȼ� �˻�


		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255)) // CollisionMap�̹������� ����Ÿ ���� �ƴ� �κ� ( ������ ǥ���Ǵºκ� )�� �浹�Ǹ�
		{
			if (y - CAMERA->getPosition()->y > 0)
			{
				// �浹�Ǵ� �̹����� �� �׸���
				HPEN hPen, hOldPen;
				HBRUSH hBrush, hOldBrush;

				hPen = CreatePen(PS_SOLID, 1, COLOR_M);
				hOldPen = (HPEN)SelectObject(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), hPen);

				hBrush = CreateSolidBrush(COLOR_M);
				hOldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), hBrush);

				// ���� ���̴� ���� = ���� �����̴ϱ� ��ź���ٴ� ũ���ؾ� �ڿ�������
				EllipseMakeCenter(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), x, y,
					radius * 4, radius * 4);

				SelectObject(hdc, hOldPen);
				SelectObject(hdc, hOldBrush);

				DeleteObject(hPen);
				DeleteObject(hBrush);
				
				if ((x - CAMERA->getPosition()->x > 0) && (x - CAMERA->getPosition()->x < WINSIZEX))
				{
					if (y - CAMERA->getPosition()->y < WINSIZEY)
					{
						SOUNDMANAGER->Play(TEXT("Crash"), 0.2f);
					}
				}


				isCollision = true;
				x = 0;
				y = 0;

			}
		}
	}

	if (GAMEINFO->GetUseMovingBullet())
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), x, y); // �̹��� DC���� �����ͼ� �ȼ� �˻�


		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255)) // CollisionMap�̹������� ����Ÿ ���� �ƴ� �κ� ( ������ ǥ���Ǵºκ� )�� �浹�Ǹ�
		{
			if (y - CAMERA->getPosition()->y > 0)
			{				
				GAMEINFO->SetTankX(x);
				GAMEINFO->SetTankY(y);

				//if ((x - CAMERA->getPosition()->x > 0) && (x - CAMERA->getPosition()->x < WINSIZEX))
				//{
				//	if (y - CAMERA->getPosition()->y < WINSIZEY)
				//	{
				//		SOUNDMANAGER->Play(TEXT("Crash"), 0.2f);
				//	}
				//}

				isCollision = true;
				x = 0;
				y = 0;

				GAMEINFO->SetUseMovingBullet(false);
			}
		}
	}
}

void MissileTankBullet::Release()
{
}

void MissileTankBullet::BulletFire(float tankCenterX, float tankCenterY, float tankAngle, float _cannonPower)
{
	// �� ����
	speedX += _cannonPower;
	speedY += _cannonPower;

	angle = tankAngle;
}

void MissileTankBullet::BulletMove(int _wind, int _dir)
{
	gravity = 0.5f;

	wind = _wind * _dir;

	speedX += wind * 0.1;
	speedY -= gravity; // �߷� ���� �ް�

	//�Ѿ��� x,y��ġ ����
	x += (cosf(angle) * speedX);
	y += (-sinf(angle) * speedY) + BULLET_GRAVITY;		
}