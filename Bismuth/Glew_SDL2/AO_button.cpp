#include "AO_button.h"



AO_button::AO_button(Button* button, Config* cfg) : ButtonController(button), mCfg(cfg)
{
}


AO_button::~AO_button()
{
}

void AO_button::Action()
{
	mCfg->AO = mButton->isChecked();
}
