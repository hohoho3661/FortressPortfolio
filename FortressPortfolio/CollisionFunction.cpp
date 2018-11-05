#pragma once
#include "stdafx.h"
#include "CollisionFunction.h"

bool CollisionRectAndRect(const RECT& r1, const RECT& r2)
{
	if (r1.left <= r2.right && r1.right >= r2.left)
	{
		if (r1.top <= r2.bottom && r1.bottom >= r2.top)
		{
			return true;
		}
	}
	return false;
}

bool CollisionCircleAndCircle(const float r1, const float x1, const float y1, const float r2, const float x2, const float y2) // 첫번째원( 스타트 )의 r,x,y ... 두번째 원 ( end )의 r,x,y
{
	if (r1 + r2 >= UTIL::getDistance(x1, y1, x2, y2))
		return true;

	return false;
}
