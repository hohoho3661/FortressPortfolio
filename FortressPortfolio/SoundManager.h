#pragma once
#include "SingleTon.h"


// FMOD는 전부 WAV 파일을 써야됨.


#include "inc/fmod.hpp"							// FMOD 사용을 위한 라이브러리 헤더,,, dll
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;   // fmod는 오픈소스이긴한데, 이윤추구 게임에 사용하면 사용료를 내야됨.

#define TOTALSOUNDBUFFER 15 // 동시에 재생할수 있는 사운드 채널 수 ,, 높일수록 메모리를 많이먹으니까 ,, 게임을 만들때 적당한 값을 정하자.

struct SoundInfo
{
	Sound*		sound;			// 로드한 음원 정보
	Channel*	channel;		// 음원의 상태
};

class SoundManager : public SingletonBase<SoundManager>
{
private:
	System * _system;

	map<string, SoundInfo*>				totalSound;		// 음원들을 저장하는 맵
	map<string, SoundInfo*>::iterator	it;
public:
	SoundManager();
	~SoundManager();

	bool		Init();
	void		Release();
	void		Update();


	void		AddSound(string keyName, string soundName, bool bgm, bool loop);

	void		Play(string keyName, float volume);
	void		Stop(string keyName);
	void		Pause(string keyName);
	void		Resume(string keyName);

	bool		isPlaySound(string keyName);
	bool		isPauseSound(string keyName);

	bool		ErrCheck(FMOD_RESULT result);
};

