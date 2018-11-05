#pragma once

// ��ũ��

#define PI				3.141592
#define PI2				PI*2
#define COLOR_M			RGB(255,0,255)

#define CAMERA_SPEED	7 // �ΰ��� ȭ�鿡�� ���콺 Ŀ���� Ŭ���̾�Ʈ �����ڸ��� ������,, ī�޶� �����̴� �ӵ�

#define TANK_SIZE		40	// ��ũ ������ ( �̹��� ũ�Ⱑ �ȸ¾Ƽ� ���� ���������� )
#define TANK_MOVESPEED	1	// ��ũ �̵��ӵ�
#define TANK_GRAVITY	7	// ��ũ�� �޴� �߷�
#define BULLET_GRAVITY	3	// �Ѿ��� �޴� �߷�

#define COMPASS_CENTER_X	139
#define COMPASS_CENTER_Y	680

#define TURN_COUNT		15	// �� �������� ����


// ============== �ΰ��� ���ڼ��� �����ϰ� ������? ( �����ڵ�, ��Ƽ������ ) =======================
#if defined(_UNICODE)
	typedef std::wstring	tstring;	//std::basic_string<wchar>
#else
	typedef std::string		tstring;	//std::basic_string<char>
#endif // #if defined(_UNICODE)




// �޸� ���� ��ũ��
// Backbuffer
#define SAFE_DELETE(p)	{if(p) {delete(p);(p) = NULL;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->Release(); (p) = NULL;}}

// ������ ������ ���� ��ũ��
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define WINSIZEX	1200
#define WINSIZEY	800
#define WINSTARTX	0
#define WINSTARTY	0

// �̱��� ��ü ��ũ��
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