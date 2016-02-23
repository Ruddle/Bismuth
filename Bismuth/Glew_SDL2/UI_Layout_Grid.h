#pragma once
#include "UI_layout.h"
class UI_layout_grid : public UI_layout
{
public:
	UI_layout_grid(int x, int y);
	~UI_layout_grid();

	int getX() { return mX; }
	int getY() { return mY; }
private :
	int mX;
	int mY;
};

