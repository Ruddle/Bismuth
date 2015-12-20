#pragma once
#include "UI_Layout.h"

struct Option_Absolute
{
	int x;
	int y;
};


class UI_Layout_Absolute : public UI_Layout
{
public:
	UI_Layout_Absolute();
	~UI_Layout_Absolute();
};

