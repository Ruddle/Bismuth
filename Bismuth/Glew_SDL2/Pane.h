#pragma once
#include "UI_Element.h"
class Pane
{
public:
	Pane();
	~Pane();


private :

	CoreBismuth& mCore;
	std::vector<UI_Element*> mElements;



};

