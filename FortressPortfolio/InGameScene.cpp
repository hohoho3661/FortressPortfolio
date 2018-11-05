#include "stdafx.h"
#include "InGameScene.h"
#include "Secwind.h"
#include "MissileTank.h"
#include "UI.h"
#include "MissileTankBullet.h"
#include "SecwindBullet.h"
#include "Wind.h"


InGameScene::InGameScene()
{
	//missileTankTurn = false;
	secwindTurn = false;

	missileTankTurn = true;
}


InGameScene::~InGameScene()
{
}

bool InGameScene::Init()
{	
	// 이미지 불러오기
	backGround = IMAGEMANAGER->findImage(TEXT("BackGround"));
	collisionMap = IMAGEMANAGER->findImage(TEXT("CollisionMap"));


	// 카메라
	CameraInit();

	// 탱크
	secwind = new Secwind;
	secwind->Init();
	missileTank = new MissileTank;
	missileTank->Init();

	// 인터페이스
	userInterface = new UI;

	// 총알
	missileTankBullet = missileTank->GetBulletInfo();
	secwindBullet = secwind->GetBulletInfo();

	// 바람
	wind = new Wind;
	inGameWindPower = 0;

	turnCount = 0;
	

	//
	SOUNDMANAGER->Stop(TEXT("StartSound"));
	SOUNDMANAGER->Play(TEXT("InGameSound"), 0.2f);


	return true;
}

void InGameScene::Release()
{
	//SAFE_DELETE(backGround);
	//SAFE_DELETE(collisionMap);
	//SAFE_DELETE(secwind);
	//SAFE_DELETE(missileTank);
	//SAFE_DELETE(userInterface);
	//SAFE_DELETE(missileTankBullet);
	//SAFE_DELETE(secwindBullet);
	//SAFE_DELETE(wind);
}

void InGameScene::Update()
{
	// 카메라
	CameraMove();

	// 바람
	wind->Update();
	wind->SetWindPower(inGameWindPower);

	// 탱크 업데이트
	missileTank->Update();
	secwind->Update();

	// 턴
	TurnTimer();

	// 미사일탱크 턴
	MissileTankTurnFunc();

	// 세크윈드 턴
	SecwindTurnFunc();

	// 기본 인터페이스 창
	userInterface->Update();
	userInterface->CountFunc(turnCount);


	// 게임오버 ( 체력 0 or 낙사 )
	if ((missileTank->GetHP() < 1) || (missileTank->GetCollisionRC_CenterY() > 1150 - TANK_SIZE))
	{
		// 세크윈드 승!
		GAMEINFO->SetWhoIsWin(1);
		SCENEMANAGER->ChangeScene(TEXT("GameOver"));
	}
	else if ((secwind->GetHP() < 1) || (secwind->GetCollisionRC_CenterY() > 1150 - TANK_SIZE))
	{
		// 미사일탱크 승!
		GAMEINFO->SetWhoIsWin(2);
		SCENEMANAGER->ChangeScene(TEXT("GameOver"));
	}

	EFFECTMANAGER->Update();

	ANIMANAGER->Update();
}

void InGameScene::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y,
		WINSIZEX, WINSIZEY);

	// 바람
	wind->Render(hdc);

	collisionMap->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y,
		WINSIZEX, WINSIZEY);

	// 탱크
	secwind->Render(hdc);
	missileTank->Render(hdc);

	// 총알	
	if (missileTank->GetIsFire())
	{
		missileTankBullet->Render(hdc);
	}
	if (secwind->GetIsFire())
	{
		secwindBullet->Render(hdc);
	}
	
	// 인터페이스
	userInterface->Render(hdc);

	//// 문자로 턴시간 알려주는것.. 테스트용
	//TCHAR szTemp11[100] = { 0, };
	//_stprintf_s(szTemp11, sizeof(szTemp11), TEXT("%d"), turnCount);
	//TextOut(hdc, WINSIZEX - 100, WINSIZEY-100, TEXT(szTemp11), _tcslen(TEXT(szTemp11)));

	EFFECTMANAGER->Render(hdc);
}


//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================


bool InGameScene::CameraInit() 	// 카메라 설정
{
	// 미리 선언한 변수에 값을 넣어두고
	rcClientSize = { 0,0,WINSIZEX,WINSIZEY }; 
	rcWorldSize = { 0,0,2048,1150 };

	GetCursorPos(&ptMouse);
	ClientToScreen(_hWnd, &ptMouse);

	//pt = ptMouse;
	pt.x = WINSIZEX / 2;
	pt.y = WINSIZEY / 2;

	//CAMERA->Init(&ptMouse, rcClientSize, rcWorldSize);
	if (CAMERA->Init(&pt, rcClientSize, rcWorldSize) == false) // &pt값의 변화로 화면을 조정할 예정.
	{
		return false;
	}

	return true;
}

void InGameScene::CameraMove()
{
	GetCursorPos(&ptMouse);
	//ClientToScreen(_hWnd, &ptMouse);												// ToScreen은 실제 모니터상의 좌표
	ScreenToClient(_hWnd, &ptMouse); // ScreenToClient, ClientToScreen 함수차이,,,	// ToClient는 윈도우 객체속에 존재하는 좌표,,
	
//	pt = ptMouse;


	// ptMouse(마우스 커서위치)가 화면 가장자리일때,, pt값을 바꿔줘서 카메라를 이동시킴.
	if (ptMouse.x <= 30)
	{
		if (pt.x > 30)
		{
			CAMERA->setTargetPos(&pt);
			pt.x -= CAMERA_SPEED;
		}
	}
	if (ptMouse.x >= WINSIZEX - 30)
	{
		if (pt.x < WINSIZEX)
		{
			CAMERA->setTargetPos(&pt);

			pt.x += CAMERA_SPEED;
		}
	}
	if (ptMouse.y <= 60)
	{
		if (pt.y > 60)
		{
			CAMERA->setTargetPos(&pt);

			pt.y -= CAMERA_SPEED;
		}
	}
	if (ptMouse.y >= WINSIZEY - 30)
	{
		if (pt.y < WINSIZEY)
		{
			CAMERA->setTargetPos(&pt);

			pt.y += CAMERA_SPEED;
		}
	}

	CAMERA->Update();
}

void InGameScene::MissileTankTurnFunc()
{
	// 미사일탱크 턴
	if (missileTankTurn)
	{
		if (missileTankTurnStart) // 턴이 시작될때
		{
			inGameWindPower = RAND->getFromIntoTo(-3, 3);

			targetCenterPoint.x = missileTank->GetCollisionRC_CenterX();
			targetCenterPoint.y = missileTank->GetCollisionRC_CenterY();

			CAMERA->setTargetPos(&targetCenterPoint);

			missileTankTurnStart = false;
		}
		
		// 턴 동안에 할수있는것
		
		// 미사일탱크 조작키를 불러옴
		missileTank->TankMoveKey();
		missileTank->TankFireControlKey(inGameWindPower);

		// 카메라
		if (missileTank->GetIsTankMoving())
		{
			targetCenterPoint.x = missileTank->GetCollisionRC_CenterX();
			targetCenterPoint.y = missileTank->GetCollisionRC_CenterY();

			CAMERA->setTargetPos(&targetCenterPoint);
		}
		if (missileTank->GetIsFire())
		{
			targetCenterPoint.x = missileTankBullet->GetBulletX();
			targetCenterPoint.y = missileTankBullet->GetBulletY();

			CAMERA->setTargetPos(&targetCenterPoint);
		}


		// 상태 정보 ( 미사일 탱크 )
		userInterface->SetHPGauge(missileTank->GetHP());
		userInterface->SetPowerGauge(missileTank->GetCannonPower());
		userInterface->SetMoveGauge(missileTank->GetMove());

		userInterface->SetItem1(missileTank->GetHaveItem1());
		userInterface->SetItem2(missileTank->GetHaveItem2());
		userInterface->SetItem3(missileTank->GetHaveItem3());
		userInterface->SetItem4(missileTank->GetHaveItem4());


		// 각도기 그리기
		userInterface->AngleCompass(missileTank->GetCollisionRC_CenterX() - missileTank->GetCollisionRC_CenterX(), missileTank->GetCollisionRC_CenterY() - missileTank->GetCollisionRC_CenterY(),
			missileTank->GetFirePointX() - missileTank->GetCollisionRC_CenterX(), missileTank->GetFirePointY() - missileTank->GetCollisionRC_CenterY(), missileTank->GetAngle());

		// 충돌체크
		if (CollisionCircleAndCircle(TANK_SIZE, secwind->GetCollisionRC_CenterX(), secwind->GetCollisionRC_CenterY(),
			missileTankBullet->GetRadius(), missileTankBullet->GetBulletX(), missileTankBullet->GetBulletY()))
		{
			if (secwind->GetHP() > 0)
			{
				secwind->Damege(15);

				EFFECTMANAGER->Play(TEXT("Effect1"), missileTankBullet->GetBulletX() - CAMERA->getPosition()->x,
					missileTankBullet->GetBulletY() - CAMERA->getPosition()->y);

				missileTank->SetIsFire(false);
				missileTankBullet->SetIsCollision(true);

				SOUNDMANAGER->Play(TEXT("Crash"), 0.2f);
			}
		}
		if (missileTankBullet->GetIsCollision())
		{
			if ((missileTank->GetUseItem1() == false))
			{
				if ((missileTank->GetUseItem2() == false))
				{
					if ((missileTank->GetUseItem4() == false))
					{
						missileTankBullet->SetIsCollision(false);

						// 턴을 false로 바꿔줌.
						missileTankTurn = false;

						secwind->SetMove(100);
						secwindTurn = true;
						secwindTurnStart = true;
					}
				}
			}

			// =================== 아이템 1, 2 사용 ( 더 블 = 충돌했을때 한번더 발사 ) ====================
			if (missileTank->GetUseItem1())
			{
				missileTankBullet->Init(missileTank->GetCollisionRC_CenterX(), missileTank->GetCollisionRC_CenterY());

				missileTank->SetIsFire(true);
				missileTankBullet->BulletFire(missileTank->GetCollisionRC_CenterX(), missileTank->GetCollisionRC_CenterY(),
					missileTank->GetAngle(), missileTank->GetCannonPower());

				missileTank->SetUsItem1(false);
			}
			if (missileTank->GetUseItem2())
			{
				missileTankBullet->Init(missileTank->GetCollisionRC_CenterX(), missileTank->GetCollisionRC_CenterY());

				missileTank->SetIsFire(true);
				missileTankBullet->BulletFire(missileTank->GetCollisionRC_CenterX(), missileTank->GetCollisionRC_CenterY(),
					missileTank->GetAngle(), missileTank->GetCannonPower());

				missileTank->SetUsItem2(false);
			}
			if (missileTank->GetUseItem4())
			{
				missileTank->SetCollisionRC_CenterX(GAMEINFO->GetTankX());
				missileTank->SetCollisionRC_CenterY(GAMEINFO->GetTankY());
				
				missileTank->SetUsItem4(false);
				
				missileTankBullet->SetIsCollision(false);

				// 턴을 false로 바꿔줌.
				missileTankTurn = false;

				secwind->SetMove(100);
				secwindTurn = true;
				secwindTurnStart = true;
			}
		}
	}
}

void InGameScene::SecwindTurnFunc()
{
	// 세크윈드 턴
	if (secwindTurn)
	{
		if (secwindTurnStart)
		{
			inGameWindPower = RAND->getFromIntoTo(-3, 3);

			targetCenterPoint.x = secwind->GetCollisionRC_CenterX();
			targetCenterPoint.y = secwind->GetCollisionRC_CenterY();

			CAMERA->setTargetPos(&targetCenterPoint);

			secwindTurnStart = false;
		}

		// 미사일탱크 조작키를 불러옴
		secwind->TankMoveKey();
		secwind->TankFireControlKey(inGameWindPower);

		if (secwind->GetIsTankMoving())
		{
			targetCenterPoint.x = secwind->GetCollisionRC_CenterX();
			targetCenterPoint.y = secwind->GetCollisionRC_CenterY();

			CAMERA->setTargetPos(&targetCenterPoint);
		}
		if (secwind->GetIsFire())
		{
			targetCenterPoint.x = secwindBullet->GetBulletX();
			targetCenterPoint.y = secwindBullet->GetBulletY();

			CAMERA->setTargetPos(&targetCenterPoint);
		}


		// 상태 정보 ( 세크 윈드 )
		userInterface->SetHPGauge(secwind->GetHP());
		userInterface->SetPowerGauge(secwind->GetCannonPower());
		userInterface->SetMoveGauge(secwind->GetMove());

		userInterface->SetItem1(secwind->GetHaveItem1());
		userInterface->SetItem2(secwind->GetHaveItem2());
		userInterface->SetItem3(secwind->GetHaveItem3());
		userInterface->SetItem4(secwind->GetHaveItem4());

		// 각도기 그리기
		userInterface->AngleCompass(secwind->GetCollisionRC_CenterX() - secwind->GetCollisionRC_CenterX(), secwind->GetCollisionRC_CenterY() - secwind->GetCollisionRC_CenterY(),
			secwind->GetFirePointX() - secwind->GetCollisionRC_CenterX(), secwind->GetFirePointY() - secwind->GetCollisionRC_CenterY(), secwind->GetAngle());

		// 충돌체크
		if (CollisionCircleAndCircle(TANK_SIZE, missileTank->GetCollisionRC_CenterX(), missileTank->GetCollisionRC_CenterY(),
			secwindBullet->GetRadius(), secwindBullet->GetBulletX(), secwindBullet->GetBulletY()))
		{
			if (missileTank->GetHP() > 0)
			{
				missileTank->Damege(15);

				EFFECTMANAGER->Play(TEXT("Effect1"), secwindBullet->GetBulletX() - CAMERA->getPosition()->x,
					secwindBullet->GetBulletY() - CAMERA->getPosition()->y);

				secwind->SetIsFire(false);				
				secwindBullet->SetIsCollision(true);

				SOUNDMANAGER->Play(TEXT("Crash"),0.2f);
			}
		}
		if (secwindBullet->GetIsCollision())
		{
			if ((secwind->GetUseItem1() == false))
			{
				if ((secwind->GetUseItem2() == false))
				{
					if ((secwind->GetUseItem4() == false))
					{
						secwindBullet->SetIsCollision(false);

						// 턴을 false로 바꿔줌.
						secwindTurn = false;

						missileTank->SetMove(100);
						missileTankTurn = true;
						missileTankTurnStart = true;
					}
				}
			}

			// =================== 아이템 1, 2 사용 ( 더 블 = 충돌했을때 한번더 발사 ) ====================
			if (secwind->GetUseItem1())
			{
				secwindBullet->Init(secwind->GetCollisionRC_CenterX(), secwind->GetCollisionRC_CenterY());

				secwind->SetIsFire(true);
				secwindBullet->BulletFire(secwind->GetCollisionRC_CenterX(), secwind->GetCollisionRC_CenterY(),
					secwind->GetAngle(), secwind->GetCannonPower());

				secwind->SetUsItem1(false);
			}
			if (secwind->GetUseItem2())
			{
				secwindBullet->Init(secwind->GetCollisionRC_CenterX(), secwind->GetCollisionRC_CenterY());

				secwind->SetIsFire(true);
				secwindBullet->BulletFire(secwind->GetCollisionRC_CenterX(), secwind->GetCollisionRC_CenterY(),
					secwind->GetAngle(), secwind->GetCannonPower());

				secwind->SetUsItem2(false);
			}
			if (secwind->GetUseItem4())
			{
				secwind->SetCollisionRC_CenterX(GAMEINFO->GetTankX());
				secwind->SetCollisionRC_CenterY(GAMEINFO->GetTankY());

				secwind->SetUsItem4(false);

				missileTankBullet->SetIsCollision(false);

				// 턴을 false로 바꿔줌.
				secwindTurn = false;

				missileTank->SetMove(100);
				missileTankTurn = true;
				missileTankTurnStart = true;
			}
		}
	}

}

void InGameScene::TurnTimer()
{
	if (missileTankTurn)
	{
		startTickCount1 = currentTickCount2;
		currentTickCount1 = GetTickCount();
		
		turnCount = TURN_COUNT - (currentTickCount1 - startTickCount1) / 1000;

		if (currentTickCount1 - startTickCount1 >= TURN_COUNT * 1000)
		{
			missileTankTurn = false;
			
			targetCenterPoint.x = secwind->GetCollisionRC_CenterX();
			targetCenterPoint.y = secwind->GetCollisionRC_CenterY();

			CAMERA->setTargetPos(&targetCenterPoint);

			secwind->SetMove(100);
			secwindTurn = true;
		}
	}
	if(secwindTurn)
	{
		startTickCount2 = currentTickCount1;
		currentTickCount2 = GetTickCount();


		turnCount = TURN_COUNT - (currentTickCount2 - startTickCount2) / 1000;

		if (currentTickCount2 - startTickCount2 >= TURN_COUNT * 1000)
		{
			secwindTurn = false;

			targetCenterPoint.x = missileTank->GetCollisionRC_CenterX();
			targetCenterPoint.y = missileTank->GetCollisionRC_CenterY();

			CAMERA->setTargetPos(&targetCenterPoint);

			missileTank->SetMove(100);
			missileTankTurn = true;
		}
	}
}
