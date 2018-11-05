#include "stdafx.h"
#include "SoundManager.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

bool SoundManager::Init()
{
	System_Create(&_system);

	if (ErrCheck(_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL)))
		return false;

	unsigned int nVersion;
	if (ErrCheck(_system->getVersion(&nVersion)))
	{
		if (nVersion != FMOD_VERSION)
			return false;
	}
	else
		return false;

	return true;
}

void SoundManager::Release()			// 작동할지 미상
{
	it = totalSound.begin();
	for (;it != totalSound.end(); it++)
	{
		if((it->second)->channel)
			(it->second)->channel->stop();
		if ((it->second)->sound)
			(it->second)->sound->release();

		SAFE_DELETE((it->second));
	}

	totalSound.clear();

	if (_system)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::Update()			// 작동할지 미상
{
	_system->update();
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
		return;

	SoundInfo* info = new SoundInfo;
	FMOD_RESULT result;

	if (loop)
	{
		if (bgm)																	// bgm     true = 긴음악 ,,,,, false = 짧은 음악
		{
			result = _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL,			// Stream == 1분이상 긴 음원 재생 ,,,, 업데이트 필요한거 같음.
				NULL, &info->sound);
		}
		else
		{
			result = _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL,			// Sound == 1분이하의 짧은 음원 재생
				NULL, &info->sound);
		}
	}
	else
	{
		if (bgm)
		{
			result = _system->createStream(soundName.c_str(), FMOD_DEFAULT,
				NULL, &info->sound);
		}
		else
		{
			result = _system->createSound(soundName.c_str(), FMOD_DEFAULT,
				NULL, &info->sound);
		}
	}

	if (!ErrCheck(result))
		return;

	totalSound.insert(make_pair(keyName, info));
}

void SoundManager::Play(string keyName, float volume) // 볼륨은 0.1 ~ 1.0    1/255씩 올라감,,,, 0.004 정도씩 컨트롤 한다.
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		_system->playSound(FMOD_CHANNEL_FREE, (it->second)->sound, false, &(it->second)->channel);
		(it->second)->channel->setVolume(volume);
	}
}

void SoundManager::Stop(string keyName)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->stop();
	}
}

void SoundManager::Pause(string keyName)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(true);
	}
}

void SoundManager::Resume(string keyName)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(false);
	}
}

bool SoundManager::isPlaySound(string keyName)				// 플레이 중인지 확인하고,,, void SoundManager::Stop(string keyName)에서 스톱해줘야됨.
{
	bool isPlay = false;

	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->getPaused(&isPlay);
	}

	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPause = false;

	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->getPaused(&isPause);
	}

	return isPause;
}

bool SoundManager::ErrCheck(FMOD_RESULT result)
{
	if(result != FMOD_OK)
		return false;

	return true;
}