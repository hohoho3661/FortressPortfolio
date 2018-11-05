#pragma once

class Image;
class MissileTankBullet;
class ProgressBar;

class MissileTank
{
	Image*		missileTank;
	Animation*	missileTankAni;

	RECT		collisionRC; // 충돌처리를 하는 도형

	float		collisionRC_CenterX, // 센터 X
				collisionRC_CenterY; // 센터 Y

	float		probY; // 픽셀충돌을 해줄 탐사축

	// 포탄이 발사되는 지점 만들기
	POINT		firePoint; // 총알이 나가는 지점.
	float		angle;
	int			length;	// 포신의 길이

	// 총알
	MissileTankBullet*	nomalBullet;
	bool		fire;

	// 상태정보
	int			HP;				// 체력
	float		cannonPower;	// 총알파워 ( VK_SPACE로 컨트롤하는 변수 )
	int			move;			// 이동량

	// 체력바
	ProgressBar*	hpBar;

	// 움직이는 중인지 확인할 bool형 변수 ( 움직이는 도중에는 카메라가 고정되게 할 예정 )
	bool		isTankMoving;

	// 탱크가 어느쪽을 보고있는지 검사
	int			dir;

	// 기울기에 쓰일 비교값Y
	float	dirPosY;

	// 아이템
	bool	useItem1;
	bool	useItem2;
	bool	useItem3;
	bool	useItem4;

	bool	haveItem1;
	bool	haveItem2;
	bool	haveItem3;
	bool	haveItem4;

public:
	MissileTank();
	~MissileTank();

	bool Init();
	void Update();
	void Render(HDC hdc);

	void TankMoveKey();
	void TankFireControlKey(int _wind);
	void pixelCheck();

	// 상태 정보
	int GetHP() { return HP; }
	void SetHP(int _HP) { HP = _HP; }
	void Damege(int damaga) { HP -= damaga; }

	int GetCannonPower() { return cannonPower; }
		
	int GetMove() { return move; }
	void SetMove(int _move) { move = _move; }

	// 각도기 그리기
	float GetCollisionRC_CenterX() { return collisionRC_CenterX; }
	float GetCollisionRC_CenterY() { return collisionRC_CenterY; }
	void SetCollisionRC_CenterX(float _tankX) { collisionRC_CenterX = _tankX; }
	void SetCollisionRC_CenterY(float _tankY) { collisionRC_CenterY = _tankY; }
	
	int GetFirePointX() { return firePoint.x; }
	int GetFirePointY() { return firePoint.y; }
	float GetAngle() { return angle; }

	//
	MissileTankBullet* GetBulletInfo() { return nomalBullet; }

	// 움직이는 중인지 확인할 함수 ( 카메라 고정할 때 사용 )
	bool	GetIsTankMoving() { return isTankMoving; }
	void	SetIsTankMoving(bool _isTankMoving) { isTankMoving = _isTankMoving; }

	//
	bool	GetIsFire() { return fire; }
	void	SetIsFire(bool _fire) { fire = _fire; }


	// 아이템
	bool	GetUseItem1() { return useItem1; }
	void	SetUsItem1(bool _useItem1) { useItem1 = _useItem1; }

	bool	GetUseItem2() { return useItem2; }
	void	SetUsItem2(bool _useItem2) { useItem2 = _useItem2; }

	bool	GetUseItem3() { return useItem3; }
	void	SetUsItem3(bool _useItem3) { useItem3 = _useItem3; }

	bool	GetUseItem4() { return useItem4; }
	void	SetUsItem4(bool _useItem4) { useItem4 = _useItem4; }

	bool	GetHaveItem1() { return haveItem1; }
	bool	GetHaveItem2() { return haveItem2; }
	bool	GetHaveItem3() { return haveItem3; }
	bool	GetHaveItem4() { return haveItem4; }
};