#pragma once

class Secwind;
class MissileTank;
class UI;
class MissileTankBullet;
class SecwindBullet;
class Wind;


class InGameScene : public GameNode
{
	Image*			backGround; // ȭ�� ���
	Image*			collisionMap; // �浹 ������ �Ǿ��� �� �̹���

	RECT			rcWorldSize;	// ��ü ũ��
	RECT			rcClientSize;	// Ŭ���̾�Ʈ ũ��

	POINT			ptMouse;	// ȭ�鿡 ���콺 ��ġ�� Ȯ�ο�
	POINT			pt;			// �� ���� �������� ī�޶� �̵�

	//

	Secwind*		secwind;
	MissileTank*	missileTank;

	UI*				userInterface;

	MissileTankBullet*	missileTankBullet;
	SecwindBullet*		secwindBullet;

	// �� ī��Ʈ
	DWORD startTickCount1;
	DWORD currentTickCount1;

	DWORD startTickCount2;
	DWORD currentTickCount2;

	int				turnCount;

	bool			missileTankTurn;
	bool			secwindTurn;

	bool			missileTankTurnStart;
	bool			secwindTurnStart;

	// ī�޶� ���� ( Ÿ�� )
	POINT			targetCenterPoint;

	// �ٶ�
	Wind*			wind;
	int				inGameWindPower;
		
public:
	InGameScene();
	~InGameScene();

	virtual bool	Init();
	virtual void	Release();
	virtual void	Update();
	virtual void	Render(HDC hdc);

	// ī�޶� �����丵
	bool			CameraInit(); 
	void			CameraMove(); 

	// ��
	void MissileTankTurnFunc();
	void SecwindTurnFunc();

	void TurnTimer();

};