#pragma once
#include "Panel.h"
#include "Text.h"
#include "Observer_button.h"
class Button : public Panel, public Observer_UI_box
{
public:
	Button(EntityManager* em, ResourcesManager* rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Button();


	bool isChecked() { return mBox->isSelected(); }

	void onHover(glm::vec2 mouse);
	void onUnHover(glm::vec2 mouse);
	void onUnClick(glm::vec2 mouse) ;
	void onClick(glm::vec2 mouse);
	void onSelect(glm::vec2 mouse);
	void onDeSelect(glm::vec2 mouse);


	void notifyAction();

	void addObserver(Observer_button* observer) { mObservers.insert(observer); }

private: 

	Text* mLabel;
	std::unordered_set<Observer_button*> mObservers;
};

