#pragma once

bool CollisionRectAndRect(const RECT& r1, const RECT& r2);
bool CollisionCircleAndCircle(const float r1, const float x1, const float y1, const float r2, const float x2, const float y2); // 첫번째원( 스타트 )의 r,x,y ... 두번째 원 ( end )의 r,x,y