#pragma once


class UI
{
	Image*	ui;


	// ü�� ������
	RECT	HP_frontGauge;
	RECT	HP_backGauge;
	// �Ŀ� ������
	RECT	Power_frontGauge;
	RECT	Power_backGauge;
	// ���� ������
	RECT	Move_frontGauge;
	RECT	Move_backGauge;

	// ������ �׸���
	POINT	compassCenter;
	POINT	compassEnd;
	float	compassAngle;
	int		compassLength;

	// �� ī��Ʈ ǥ��

	Image*	countImg;
	Image*	countImg10;

	int		countIndex;
	int		countIndex10;

	int		turnCountNumber;

	// ������
	Image*	itemImg1;
	Image*	itemImg2;
	Image*	itemImg3;
	Image*	itemImg4;

	bool	item1;
	bool	item2;
	bool	item3;
	bool	item4;

public:
	UI();
	~UI();

	bool Init();
	void Update();
	void Render(HDC hdc);

	void SetHPGauge(int HPGauge);
	void SetPowerGauge(int PowerGauge);
	void SetMoveGauge(int MoveGauge);

	void SetItem1(bool item);
	void SetItem2(bool item);
	void SetItem3(bool item);
	void SetItem4(bool item);


	void AngleCompass(float _centerX, float _centerY, int _endX, int _endY, float _angle);

	void CountFunc(int _turnCount);
};

