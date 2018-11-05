#include "stdafx.h"
#include "UI.h"



UI::UI()
{
	ui = IMAGEMANAGER->findImage(TEXT("UI"));
	assert(ui != NULL);

	// ü�� ������
	HP_frontGauge = RectMake(417, 665, 605, 33);
	HP_backGauge = RectMake(417, 665, 605, 33);
	// �Ŀ� ������
	Power_frontGauge = RectMake(417, 707, 0, 33);
	Power_backGauge = RectMake(417, 707, 605, 33);
	// ���� ������
	Move_frontGauge = RectMake(417, 749, 605, 33);
	Move_backGauge = RectMake(417, 749, 605, 33);	

	//
	compassLength = 65;

	// �� ī��Ʈ

	countImg = new Image;
	countImg = IMAGEMANAGER->findImage(TEXT("Count"));
	assert(countImg != NULL);

	countImg10 = new Image;
	countImg10 = IMAGEMANAGER->findImage(TEXT("Count"));
	assert(countImg10 != NULL);

	countIndex = 0;
	countIndex10 = 0;

	turnCountNumber = 0;

	// ������
	itemImg1 = IMAGEMANAGER->findImage(TEXT("����"));
	itemImg2 = IMAGEMANAGER->findImage(TEXT("����"));
	itemImg3 = IMAGEMANAGER->findImage(TEXT("����"));
	itemImg4 = IMAGEMANAGER->findImage(TEXT("�̵�ź"));

}


UI::~UI()
{
}

bool UI::Init()
{
	return true;
}

void UI::Update()
{
}

void UI::Render(HDC hdc)
{
	ui->Render(hdc, 0, 0);


	// ������ 3�� �׸���
	DrawObject(hdc, HP_frontGauge, 0, RGB(50, 200, 50), RGB(50, 200, 50), RECTANGLE, NULL);
	DrawObject(hdc, Power_frontGauge, 0, RGB(200, 50, 50), RGB(200, 50, 50), RECTANGLE, NULL);
	DrawObject(hdc, Move_frontGauge, 0, RGB(50, 50, 200), RGB(50, 50, 200), RECTANGLE, NULL);

	// ������ �׸���
	DrawLine(hdc, compassCenter.x + COMPASS_CENTER_X, compassCenter.y + COMPASS_CENTER_Y, 
		compassEnd.x + COMPASS_CENTER_X, compassEnd.y + COMPASS_CENTER_Y, 5, RGB(255, 0, 0));

	// ���� ���ڷ� ǥ��
	SetBkMode(hdc, TRANSPARENT); // ���� ���� ���ֱ�
	SetTextColor(hdc, RGB(20, 180, 10)); // ���� ���� ���ϱ�
	TCHAR szTemp[100] = { 0, };
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("%2.f"), compassAngle/0.0174f);
	TextOut(hdc, COMPASS_CENTER_X - 20, COMPASS_CENTER_Y + 33, TEXT(szTemp), _tcslen(TEXT(szTemp)));

	// �� ī��Ʈ
	countImg->FrameRender(hdc, WINSIZEX - 85, WINSIZEY - 120, 0, countIndex);
	countImg10->FrameRender(hdc, WINSIZEX - 120, WINSIZEY - 120, 0, countIndex10);

	// ������
	if (item1)
	{
		itemImg1->Render(hdc, 380, 602);
	}
	if (item2)
	{
		itemImg2->Render(hdc, 432, 602);
	}
	if (item3)
	{
		itemImg3->Render(hdc, 487, 602);
	}
	if (item4)
	{
		itemImg4->Render(hdc, 540, 602);
	}

}


//==============================================================================================================
//==============================================================================================================
//==============================================================================================================


void UI::SetHPGauge(int HPGauge)
{
	if (HP_frontGauge.right > HP_frontGauge.left)
	{
		HP_frontGauge.right = HP_frontGauge.left + (HPGauge * 6.05f); // �������� ���̰� 605�ε�,, Move�� 100���� �����س������� 6.05�� ���ϸ� �����̵�.
	}
}

void UI::SetPowerGauge(int PowerGauge)
{
	if (Power_frontGauge.right < Power_frontGauge.left + 605)
	{
//		Power_frontGauge.right = Power_frontGauge.left + (PowerGauge*15);
		Power_frontGauge.right = Power_frontGauge.left + (PowerGauge * 6.05f * 2.5f);
	}
}

void UI::SetMoveGauge(int MoveGauge)
{
	if (Move_frontGauge.right >= Move_frontGauge.left)
	{
		Move_frontGauge.right = Move_frontGauge.left + (MoveGauge * 6.05f); // �������� ���̰� 605�ε�,, Move�� 100���� �����س������� 6.05�� ���ϸ� �����̵�.
	}
}

void UI::SetItem1(bool item)
{
	item1 = item;
}

void UI::SetItem2(bool item)
{
	item2 = item;
}

void UI::SetItem3(bool item)
{
	item3 = item;
}

void UI::SetItem4(bool item)
{
	item4 = item;
}


void UI::AngleCompass(float _centerX, float _centerY, int _endX, int _endY, float _angle)
{
	compassCenter.x = _centerX;
	compassCenter.y = _centerY;

	//compassEnd.x = _endX;
	//compassEnd.y = _endY;

	compassEnd.x = _endX + (cosf(_angle) * compassLength);
	compassEnd.y = _endY +(-sinf(_angle) * compassLength);

	compassAngle = _angle;

}

void UI::CountFunc(int _turnCount)
{
	turnCountNumber = _turnCount;

	if (turnCountNumber <= 0)
	{
		countIndex = 0;
		countIndex10 = 0;
	}
	else if (turnCountNumber > 0 && turnCountNumber < 10)
	{
		countIndex = turnCountNumber % 10;
		countIndex10 = 0;
	}
	else if (turnCountNumber >= 10 && turnCountNumber < 100)
	{
		countIndex = turnCountNumber % 10;
		countIndex10 = (turnCountNumber % 100 - countIndex) / 10;
	}
}
