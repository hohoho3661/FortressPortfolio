#pragma once

class Secwind;
class MissileTank;
class UI;
class MissileTankBullet;
class SecwindBullet;
class Wind;


class InGameScene : public GameNode
{
	Image*			backGround; // 화면 배경
	Image*			collisionMap; // 충돌 번위가 되어줄 맵 이미지

	RECT			rcWorldSize;	// 전체 크기
	RECT			rcClientSize;	// 클라이언트 크기

	POINT			ptMouse;	// 화면에 마우스 위치를 확인용
	POINT			pt;			// 이 값을 기준으로 카메라 이동

	//

	Secwind*		secwind;
	MissileTank*	missileTank;

	UI*				userInterface;

	MissileTankBullet*	missileTankBullet;
	SecwindBullet*		secwindBullet;

	// 턴 카운트
	DWORD startTickCount1;
	DWORD currentTickCount1;

	DWORD startTickCount2;
	DWORD currentTickCount2;

	int				turnCount;

	bool			missileTankTurn;
	bool			secwindTurn;

	bool			missileTankTurnStart;
	bool			secwindTurnStart;

	// 카메라 설정 ( 타겟 )
	POINT			targetCenterPoint;

	// 바람
	Wind*			wind;
	int				inGameWindPower;
		
public:
	InGameScene();
	~InGameScene();

	virtual bool	Init();
	virtual void	Release();
	virtual void	Update();
	virtual void	Render(HDC hdc);

	// 카메라 리펙토링
	bool			CameraInit(); 
	void			CameraMove(); 

	// 턴
	void MissileTankTurnFunc();
	void SecwindTurnFunc();

	void TurnTimer();

};