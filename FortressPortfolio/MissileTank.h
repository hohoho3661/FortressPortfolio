#pragma once

class Image;
class MissileTankBullet;
class ProgressBar;

class MissileTank
{
	Image*		missileTank;
	Animation*	missileTankAni;

	RECT		collisionRC; // �浹ó���� �ϴ� ����

	float		collisionRC_CenterX, // ���� X
				collisionRC_CenterY; // ���� Y

	float		probY; // �ȼ��浹�� ���� Ž����

	// ��ź�� �߻�Ǵ� ���� �����
	POINT		firePoint; // �Ѿ��� ������ ����.
	float		angle;
	int			length;	// ������ ����

	// �Ѿ�
	MissileTankBullet*	nomalBullet;
	bool		fire;

	// ��������
	int			HP;				// ü��
	float		cannonPower;	// �Ѿ��Ŀ� ( VK_SPACE�� ��Ʈ���ϴ� ���� )
	int			move;			// �̵���

	// ü�¹�
	ProgressBar*	hpBar;

	// �����̴� ������ Ȯ���� bool�� ���� ( �����̴� ���߿��� ī�޶� �����ǰ� �� ���� )
	bool		isTankMoving;

	// ��ũ�� ������� �����ִ��� �˻�
	int			dir;

	// ���⿡ ���� �񱳰�Y
	float	dirPosY;

	// ������
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

	// ���� ����
	int GetHP() { return HP; }
	void SetHP(int _HP) { HP = _HP; }
	void Damege(int damaga) { HP -= damaga; }

	int GetCannonPower() { return cannonPower; }
		
	int GetMove() { return move; }
	void SetMove(int _move) { move = _move; }

	// ������ �׸���
	float GetCollisionRC_CenterX() { return collisionRC_CenterX; }
	float GetCollisionRC_CenterY() { return collisionRC_CenterY; }
	void SetCollisionRC_CenterX(float _tankX) { collisionRC_CenterX = _tankX; }
	void SetCollisionRC_CenterY(float _tankY) { collisionRC_CenterY = _tankY; }
	
	int GetFirePointX() { return firePoint.x; }
	int GetFirePointY() { return firePoint.y; }
	float GetAngle() { return angle; }

	//
	MissileTankBullet* GetBulletInfo() { return nomalBullet; }

	// �����̴� ������ Ȯ���� �Լ� ( ī�޶� ������ �� ��� )
	bool	GetIsTankMoving() { return isTankMoving; }
	void	SetIsTankMoving(bool _isTankMoving) { isTankMoving = _isTankMoving; }

	//
	bool	GetIsFire() { return fire; }
	void	SetIsFire(bool _fire) { fire = _fire; }


	// ������
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