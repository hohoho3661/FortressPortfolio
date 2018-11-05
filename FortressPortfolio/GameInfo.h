#pragma once
#include "SingleTon.h"

class GameInfo : public SingletonBase<GameInfo>
{
	int whoIsWin;
	bool useItem4 = false;

	float tankX;
	float tankY;

public:
	GameInfo();
	~GameInfo();

	// ���â���� �����̰���� ����
	int GetWhoIsWin() { return whoIsWin; }
	void SetWhoIsWin(int _whoIsWin) { whoIsWin = _whoIsWin; }

	// ����ź�� �i���� ����
	int GetUseMovingBullet() { return useItem4; }
	void SetUseMovingBullet(int _useItem4) { useItem4 = _useItem4; }

	// ��ũ�� ��ǥ
	int GetTankX() { return tankX; }
	void SetTankX(int _tankX) { tankX = _tankX; }

	int GetTankY() { return tankY; }
	void SetTankY(int _tankY) { tankY = _tankY; }
};

