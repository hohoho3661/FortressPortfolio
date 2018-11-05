#pragma once
#include "Bullet.h"

class MissileTankBullet : public Bullet
{
	Image*		bulletImg;
	Animation*	bulletAni;

	float	x, y;	// 총알의 x,y 좌표
	float	speedX; // 총알의 x축으로 이동하는 속도
	float	speedY; // 총알의 y축으로 이동하는 속도.

	float	angle;
	float	radius; // 반지름
	float	gravity;
	
	float	cannonPower;

	bool	isCollision; // 총알의 충돌여부 확인
	
	int		wind;
public:
	MissileTankBullet();
	~MissileTankBullet();

	bool Init(float _x, float _y);
	void Render(HDC hdc);
	void Release();

	void BulletFire(float tankCenterX, float tankCenterY, float tankAngle, float _cannonPower);
	void BulletMove(int _wind, int _dir);
	
	void SetIsCollision(bool _isCollision) { isCollision = _isCollision; };
	bool GetIsCollision() { return isCollision; }

	int GetBulletX() { return x; }
	int GetBulletY() { return y; }
	void SetBulletX(float _x) { x = _x; }
	void SetBulletY(float _y) { y = _y; }

	float GetRadius() { return radius; }
};