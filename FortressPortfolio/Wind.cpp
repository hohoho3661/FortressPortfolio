#include "stdafx.h"
#include "Wind.h"

Wind::Wind()
{
	windIMG1 = IMAGEMANAGER->findImage(TEXT("Wind"));
	assert(windIMG1 != NULL);

	windIMG2 = IMAGEMANAGER->findImage(TEXT("Wind"));
	assert(windIMG2 != NULL);

	windIMG3 = IMAGEMANAGER->findImage(TEXT("Wind"));
	assert(windIMG3 != NULL);



	ANIMANAGER->AddCoordAni(TEXT("WindAni"), TEXT("Wind"), 0, 4, 5, true);
	
	windAni = ANIMANAGER->FindAni(TEXT("WindAni"));

	windAni->start();



	imgX1 = 300;
	imgY1 = 0;

	imgX2 = 1000;
	imgY2 = 0;

	imgX3 = 1700;
	imgY3 = 0;

	windPower = 0;

	windIMG1->SetX(imgX1);
	windIMG1->SetY(imgY1);

	windIMG2->SetX(imgX2);
	windIMG2->SetY(imgY2);

	windIMG3->SetX(imgX3);
	windIMG3->SetY(imgY3);
}

Wind::~Wind()
{
}

bool Wind::Init()
{
	return true;
}

void Wind::Update()
{
	windIMG1->SetX(imgX1);
	windIMG1->SetY(imgY1);

	windIMG2->SetX(imgX2);
	windIMG2->SetY(imgY2);

	windIMG3->SetX(imgX3);
	windIMG3->SetY(imgY3);

	imgX1 += windPower;
	imgY1 += 3;

	imgX2 += windPower;
	imgY2 += 3;

	imgX3 += windPower;
	imgY3 += 3;


	if (imgY1 > WINSIZEY || imgX1 > 2000 || imgX1 < 0)
	{
		imgX1 = 300;
		imgY1 = 0;
	}

	if (imgY2 > WINSIZEY || imgX2 > 2000 || imgX2 < 0)
	{
		imgX2 = 800;
		imgY2 = 0;
	}

	if (imgY3 > WINSIZEY || imgX3 > 2000 || imgX3 < 0)
	{
		imgX3 = 1300;
		imgY3 = 0;
	}
}

void Wind::Render(HDC hdc)
{
	windIMG1->AniRender(hdc, imgX1 - CAMERA->getPosition()->x, imgY1 - CAMERA->getPosition()->y, windAni);

	windIMG2->AniRender(hdc, imgX2 - CAMERA->getPosition()->x, imgY2 - CAMERA->getPosition()->y, windAni);
	
	windIMG3->AniRender(hdc, imgX3 - CAMERA->getPosition()->x, imgY3 - CAMERA->getPosition()->y, windAni);
}
