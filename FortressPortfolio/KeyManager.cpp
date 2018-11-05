#include "stdafx.h"
#include "KeyManager.h"



KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}

bool KeyManager::Init()
{
	this->getKeyUp().reset();
	this->getKeyDown().reset();

	return true;
}

void KeyManager::Release()
{
	getSingleton()->releaseSingleton();
}

bool KeyManager::isOnceKeyDown(int _key)	// 현재 키가 눌렷는지만 알고싶을떄. (이전상태는 관심사가 아님)
{
	if (GetAsyncKeyState(_key) & 0x8000)
	{
		if (!this->getKeyDown()[_key])
		{
			this->setKeyDown(_key, true);
			return true;
		}
	}
	else
		this->setKeyDown(_key, false);

	return false;
}

bool KeyManager::isOnceKeyUp(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		this->setKeyUp(_key, true);
	else
	{
		if (this->getKeyUp()[_key])
		{
			this->setKeyUp(_key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::isStayKeyDown(int _key) // 현재 계속 눌러져있는경우 true, 아니면 false
{
	if (GetAsyncKeyState(_key) & 0x8000)
		return true;

	return false;
}

bool KeyManager::isToggleKey(int _key) // 한번 누르면 on, 다시누르면 false     ex) Caps Lock같은경우.
{
	if (GetKeyState(_key) & 0x0001)
		return true;

	return false;
}
