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
	// 총알 그리기
	EllipseMakeCenter(hdc, x - CAMERA->getPosition()->x, y - CAMERA->getPosition()->y,
		radius * 2, radius * 2);
	
	// 이미지
	bulletImg->AniRenderCenter(hdc, x - CAMERA->getPosition()->x, y - CAMERA->getPosition()->y, bulletAni);
		
	// 충돌 체크
	if (GAMEINFO->GetUseMovingBullet() == false)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), x, y); // 이미지 DC값을 가져와서 픽셀 검사


		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255)) // CollisionMap이미지에서 마젠타 값이 아닌 부분 ( 맵으로 표현되는부분 )과 충돌되면
		{
			if (y - CAMERA->getPosition()->y > 0)
			{
				// 충돌되는 이미지에 원 그리기
				HPEN hPen, hOldPen;
				HBRUSH hBrush, hOldBrush;

				hPen = CreatePen(PS_SOLID, 1, COLOR_M);
				hOldPen = (HPEN)SelectObject(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), hPen);

				hBrush = CreateSolidBrush(COLOR_M);
				hOldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), hBrush);

				// 맵이 파이는 영역 = 폭발 영역이니까 포탄보다는 크게해야 자연스럽다
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImageDC(TEXT("CollisionMap")), x, y); // 이미지 DC값을 가져와서 픽셀 검사


		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255)) // CollisionMap이미지에서 마젠타 값이 아닌 부분 ( 맵으로 표현되는부분 )과 충돌되면
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
	// 힘 전달
	speedX += _cannonPower;
	speedY += _cannonPower;

	angle = tankAngle;
}

void MissileTankBullet::BulletMove(int _wind, int _dir)
{
	gravity = 0.5f;

	wind = _wind * _dir;

	speedX += wind * 0.1;
	speedY -= gravity; // 중력 영향 받게

	//총알의 x,y위치 설정
	x += (cosf(angle) * speedX);
	y += (-sinf(angle) * speedY) + BULLET_GRAVITY;		
}