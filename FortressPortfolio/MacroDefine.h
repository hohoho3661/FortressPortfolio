#pragma once

// 매크로

#define PI				3.141592
#define PI2				PI*2
#define COLOR_M			RGB(255,0,255)

#define CAMERA_SPEED	7 // 인게임 화면에서 마우스 커서가 클라이언트 가장자리로 갔을때,, 카메라가 움직이는 속도

#define TANK_SIZE		40	// 탱크 사이즈 ( 이미지 크기가 안맞아서 따로 지정해주자 )
#define TANK_MOVESPEED	1	// 탱크 이동속도
#define TANK_GRAVITY	7	// 탱크가 받는 중력
#define BULLET_GRAVITY	3	// 총알이 받는 중력

#define COMPASS_CENTER_X	139
#define COMPASS_CENTER_Y	680

#define TURN_COUNT		15	// 턴 몇초인지 설정


// ============== 두가지 문자셋을 안전하게 디파인? ( 유니코드, 멀티바이팅 ) =======================
#if defined(_UNICODE)
	typedef std::wstring	tstring;	//std::basic_string<wchar>
#else
	typedef std::string		tstring;	//std::basic_string<char>
#endif // #if defined(_UNICODE)




// 메모리 해제 매크로
// Backbuffer
#define SAFE_DELETE(p)	{if(p) {delete(p);(p) = NULL;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->Release(); (p) = NULL;}}

// 윈도우 사이즈 관련 매크로
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define WINSIZEX	1200
#define WINSIZEY	800
#define WINSTARTX	0
#define WINSTARTY	0

// 싱글턴 객체 매크로
#define RAND			RandomFunction::getSingleton()
#define CAMERA			Camera::getSingleton()

#define IMAGEMANAGER	ImageManager::getSingleton()
#define KEYMANAGER		KeyManager::getSingleton()
#define TIMEMANAGER		TimeManager::getSingleton()
#define EFFECTMANAGER	EffectManager::getSingleton()
#define SCENEMANAGER	SceneManager::getSingleton()
#define SOUNDMANAGER	SoundManager::getSingleton()
#define TXTDATA			TextData::getSingleton()
#define ANIMANAGER		AniManager::getSingleton()

//
#define GAMEINFO		GameInfo::getSingleton()