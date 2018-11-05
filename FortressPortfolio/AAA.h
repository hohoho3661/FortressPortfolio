#pragma once
#include "SingleTon.h"

// test == AAA




class AAA : public SingletonBase<AAA>
{
public:
	AAA();
	virtual ~AAA();
};

