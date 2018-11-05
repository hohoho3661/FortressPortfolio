#include "stdafx.h"
#include "Timer.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib") // 링크드 애러


Timer::Timer()
{
}


Timer::~Timer()
{
}

bool Timer::Init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency)) // QueryPerformanceFrequency = cpu가 돌아가는 속도..?   // 요즘껀 동작
	{
		_isHardWare = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else																													// 옛날꺼
	{
		_isHardWare = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSframeCount = 0;
	_FPSTimeElapsed = 0.f;
	_worldTime = 0.f;

	return true;
}



// 고정 fps방식 : 1초에 xx프레임.. 일정시간간격으로만 돌게      0.01666초마다 호출 ..   
//				 1초에 60번만 호출되게 할거임
//				 타이머랑 연계해서 프레임을 맞춘다.

// 가변 fps방식 : 들어오는 델타타임을 가지고 임의로 작업..      상태가 좋으면 빠르고,, 랜더링할게 많아지면 느려짐

void Timer::Tick(float lockFPS)    // 업데이트에서 계속 호출
{
	if (_isHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale; // 타임스케일을 곱해줘서 시간을 맞춰줌. ex)60을 곱하면 1초

	if (lockFPS > 0.0f)				// lockFPS가 설정되있다면.. 이 값이 프레임 값이됨.
	{
		while (_timeElapsed < 1.0f / lockFPS) // 1.0 .. 크면 느리고    작으면 빠름
		{
			if (_isHardWare)
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else
				_curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime)* _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSframeCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long Timer::getFrameRate(TCHAR * str)
{
	if (str != NULL)
	{
		//_stprintf(str, TEXT("FPS : %d"), _frameRate);
	}

	return _frameRate;
}
