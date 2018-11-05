#pragma once
#include "SingleTon.h"
#include <time.h>

// 클래스, 싱글턴 베이스를 상속

// 클래스끼리 상호작용할수 있을 경우가 있으니까.. 생성과 호출 시점을 바꿀수있는 작업을 해줄수 있어야한다.

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		//srand((unsigned)time(NULL));
		srand(GetTickCount());
	}
	~RandomFunction(){}

	inline int getInt(int num) { return rand() % num; }
	inline int getFromIntoTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};