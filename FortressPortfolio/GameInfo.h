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

	// 결과창에서 누가이겼는지 정보
	int GetWhoIsWin() { return whoIsWin; }
	void SetWhoIsWin(int _whoIsWin) { whoIsWin = _whoIsWin; }

	// 무빙탄을 쐇는지 여부
	int GetUseMovingBullet() { return useItem4; }
	void SetUseMovingBullet(int _useItem4) { useItem4 = _useItem4; }

	// 탱크의 좌표
	int GetTankX() { return tankX; }
	void SetTankX(int _tankX) { tankX = _tankX; }

	int GetTankY() { return tankY; }
	void SetTankY(int _tankY) { tankY = _tankY; }
};

