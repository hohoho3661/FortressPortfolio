#include "stdafx.h"
#include "Util.h"


namespace UTIL
{
	//float getDistance(float startX, float startY, float endX, float endY)
	//{
	//	float x = endX - startX;
	//	float y = endY - startY;


	//	return sqrtf(x * x + y * y);
	//}

	float getDistance(const float startX, const float startY, const float endX, const float endY)
	{
		float x = endX - startX;
		float y = endY - startY;


		return sqrtf(x * x + y * y);
	}

	float getAngle(const float x1, const float y1, const float x2, const float y2) // 두개의 x,y값으로 .. 앵글(각)을 구하는 함수.
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);
		
		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2)
			{
				angle -= PI2;
			}
		}

		return angle;
	}
}