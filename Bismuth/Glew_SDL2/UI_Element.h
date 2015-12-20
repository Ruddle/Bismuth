#pragma once
#include "UI_Layout_Grid.h"
#include "UI_Layout_Absolute.h"

class UI_Element
{
public:
	UI_Element();
	~UI_Element();

	void setOptionGrid(int x, int y) { mOG.x = x; mOG.y = y; }
	void setOptionAbsolute(int x, int y) {mOA.x = x; mOA.y = y; }
	Option_Grid getOptionGrid() { return mOG; }
	Option_Absolute getOptionAbsolute() { return mOA; }


private:
	Option_Grid mOG;
	Option_Absolute mOA;
};

