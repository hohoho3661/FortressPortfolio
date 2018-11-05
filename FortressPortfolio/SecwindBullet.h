#pragma once



class SecwindBullet
{
	Image*		bulletImg;
	Animation*	bulletAni;

	float	x, y;	// �Ѿ��� x,y ��ǥ
	float	speedX; // �Ѿ��� x������ �̵��ϴ� �ӵ�
	float	speedY; // �Ѿ��� y������ �̵��ϴ� �ӵ�.

	float	angle;
	float	radius; // ������
	float	gravity;

	float	cannonPower;

	bool	isCollision; // �Ѿ��� �浹���� Ȯ��
	int		wind;
public:
	SecwindBullet();
	~SecwindBullet();

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