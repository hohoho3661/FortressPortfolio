#pragma once

class Image;

class Wind
{
	Image*		windIMG1;
	Image*		windIMG2;
	Image*		windIMG3;

	Animation*	windAni;

	float		imgX1, imgY1;
	float		imgX2, imgY2;
	float		imgX3, imgY3;


	int			windPower;
public:
	Wind();
	~Wind();

	bool Init();
	void Update();
	void Render(HDC hdc);

	int GetWindPower() { return windPower; }
	void SetWindPower(int _windPower) { windPower = _windPower; }

};

