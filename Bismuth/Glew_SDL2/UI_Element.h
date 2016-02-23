#pragma once
#include <vector>
#include "UI_link.h"
#include "UI_layout.h"
#include "Misc.h"
#include "UI_box.h"

class UI_element
{
public:
	UI_element(CoreBismuth* core, UI_layout* layout);
	~UI_element();

  	void add(UI_link* link); 
	void update();

	void setPositionSize(elementConfig ec);

protected :
	CoreBismuth* mCore;
	std::vector<UI_link*> mLinks;
	UI_layout* mLayout;

	UI_box* mBox;
	Entity2D* mEntity;
private:

};

