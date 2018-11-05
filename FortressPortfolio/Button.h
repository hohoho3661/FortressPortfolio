#pragma once

enum BUTTONDIR
{
	BUTTONDIR_NONE,
	BUTTONDIR_UP,
	BUTTONDIR_DOWN,
};

typedef void(*FUNC)();


class Button
{
	BUTTONDIR		_direction;

	string			_imageName;
	Image*			_image;
	RECT			_rc;
	float			_x, _y;
	POINT			_btnDownFramePoint;
	POINT			_btnUpFramePoint;

	FUNC			_callBackFunc;

public:
	Button();
	~Button();

	bool Init(const string imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, FUNC pFunc);

	void Release();
	void Update();
	void Render(HDC hdc);

};

// 콜백함수에 들어가는 매게변수는 함수포인터,,,

// 함수 포인터
// 함수 이름으로 찾는게아니라, 함수가 저장되는 위치를 보고 호출.

// 반환형(*함수명)(매개변수 리스트);
// typedef void(*Func)(int);  // 괄호의 중요성!
// 							   ex) typedef void* Func (int); ----> 괄호가 없으면 보이드 포인터를 반환형으로하는 일반함수가 되어버림

// Func pFunc		=	Function; // 함수이름을 대입해주는식으로 이 함수를 쓸수있다.
// 함수포인터형 변수	=	함수명 (괄호가 빠진 함수명)
// 선언되어있는 함수포인터형의 정보 ( 반환형, 매게변수 자료형 )이 완전 일치해야 된다. ***************


// 선언된 함수포인터는 함수 형태로 사용 가능.
// (*Func)(10); => pFunc(10); 후자와 같은 호출도 허용해준다.


// 함수포인터형 간에는 캐스팅이 가능 (잘안씀)
// int(*Func1)(int), float(*Func2)(float);
// Func1 = (int(*)(int))Func2;

// 

// 클래스 변수를 사용하는 함수를 쓰려면 사용범위가 제한됨.
// 객체를 생성해야되는데,,, 그래서 범용적으로 사용하기가 힘듬.

//
//

// 결국에 필요한곳에는 스태틱선언이 필수라서
// 바람직한 코딩은 아니다.



// C++에서의 함수포인터
// std::function<void(*)()> pFunc;



//
//// 함수 객체
//class AAA
//{
//public:
//	bool operator()(int n)
//	{
//		return 10 < n;
//	}
//};
//
//AAA a;
//bool n = a(1);
////
//



//int Func1(int n)		// 함수를 만들고
//{
//	return (n + 10);
//}
//
//std::function<int(int)> pFunc = Func1;	// 함수를 객체처럼 넘기고
//
//int n = pFunc(10);				// 적용해서 사용가능.