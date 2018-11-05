#pragma once

class Image;

class Animation
{
public:
	typedef std::vector<POINT>		vFrameList;
	typedef std::vector<int>		vPlayList;

private:
	vFrameList						_frameList;
	vPlayList						_playList;

	int _frameNum;
	int _frameWidth;
	int _frameHeight;

	bool _loop;
	bool _play;

	float _frameUpdateSec;
	float _elapsedSec;

	DWORD _nowPlayIndex;

public:
	Animation();
	virtual ~Animation();

	bool Init(int totlaW, int totalH, int frameW, int frameH);
	bool Init(Image* image);

	void Release();

	void setDefPlayFrame(bool reverse = false, bool loop = false);    // 리버스, 루프     순서대로 처음부터 끝까지
	void setPlayFrame(int *playArr, int arLen, bool loop = false);		//				 특정배열에 프레임순서를 넣어놓고 그 순서대로 플레이
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false); //	 연속적이긴하지만 처음부터 끝까지는 아닌경우. 시작과 끝을 지정해주고 사용

	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline bool isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }
};

