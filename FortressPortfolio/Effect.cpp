#include "stdafx.h"
#include "Effect.h"
#include "Animation.h"


Effect::Effect()
	: _effectImage(NULL),
	_effectAnimaion(NULL),
	_isRunning(false), _x(0), _y(0)
{
}


Effect::~Effect()
{
}

bool Effect::Init(Image * effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if (!effectImage)
		return false;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnimaion)
		_effectAnimaion = new Animation;

	_effectAnimaion->Init(_effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH);
	_effectAnimaion->setDefPlayFrame(false,false);
	_effectAnimaion->setFPS(fps);
	_effectAnimaion->stop();

	return true;
}

void Effect::Release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimaion);
}

void Effect::Update()
{
	if (!_isRunning)
		return;

	_effectAnimaion->frameUpdate(_elapsedTime);

	if (!_effectAnimaion->isPlay())
		KillEffect();
}

void Effect::Render(HDC hdc)
{
	if (!_isRunning)
		return;

	_effectImage->AniRender(hdc, _x, _y, _effectAnimaion);
}

void Effect::KillEffect()
{
	_isRunning = false;
}

void Effect::StartEffect(int x, int y)
{
	if (!_effectImage || !_effectAnimaion)
		return;

	_x = x - (_effectAnimaion->getFrameWidth() / 2);
	_y = y - (_effectAnimaion->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimaion->start();
}
