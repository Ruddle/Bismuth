#pragma once
#include "UI_Element.h"
#include "Misc.h"
class Pane
{
public:
	Pane(CoreBismuth & core);
	~Pane();


private :

	CoreBismuth& mCore;
	std::vector<UI_Element*> mElements;



};

