#pragma once
#include "Panel.h"
#include "Text.h"
class Button : public Panel
{
public:
	Button(EntityManager* em, ResourcesManager* rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Button();

	void update();
	bool isChecked() { return mIsChecked; }

private: 
	bool mLastSelected; 
	bool mIsChecked;
	Text* mLabel;

};

