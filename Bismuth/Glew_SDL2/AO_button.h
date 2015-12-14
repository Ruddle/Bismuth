#pragma once
#include "ButtonController.h"
#include "Misc.h"
class AO_button : public ButtonController
{
public:
	AO_button(Button* button, Config* cfg);
	~AO_button();

	void Action();

private : 
	Config* mCfg;
};

