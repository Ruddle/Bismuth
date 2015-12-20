#pragma once
#include "Misc.h"
#include "Button.h"
#include "Pane.h"
class UI_Assembler
{
public:
	UI_Assembler(CoreBismuth & core);
	~UI_Assembler();

	Pane * createPane();

	Button* createButton();


	CoreBismuth getCore() { return mCore; }
private :
	CoreBismuth& mCore;



};

