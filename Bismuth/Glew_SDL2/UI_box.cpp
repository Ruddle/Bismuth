#include "UI_box.h"



UI_box::UI_box(PhysicComponent2D* physicComponent) : mPhysicComponent(physicComponent),
mIsClicked(0),mIsSelected(0),mIsHovered(0)
{
}


UI_box::~UI_box()
{
}

void UI_box::move(glm::vec2 mouse, glm::vec2 mouseRelative)
{
	bool lastHover = mIsHovered;

	mIsHovered =mPhysicComponent->contain(mouse);
	if (mIsHovered)
		notifyHover(mouse);

	if (!mIsHovered && lastHover)
		notifyUnHover(mouse);

}

void UI_box::click(glm::vec2 mouse)
{
	mIsClicked = mIsHovered;

	if (mIsClicked)
	{
		

		mIsSelected = !mIsSelected;
		if (mIsSelected)
			notifySelected(mouse);
		else
			notifyUnSelected(mouse);

		notifyClick(mouse);
	}
}

void UI_box::unclick(glm::vec2 mouse)
{
	mIsClicked = false;
}


void UI_box::notifyHover(glm::vec2 mouse)
{
	/*std::cout << "hover on : " << this << std::endl;*/
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->onHover(mouse);
}

void UI_box::notifyClick(glm::vec2 mouse)
{
	/*std::cout << "click on : "<< this << std::endl;*/
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->onClick(mouse);
}

void UI_box::notifySelected(glm::vec2 mouse)
{
	/*std::cout << "select on : " << this << std::endl;*/
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->onSelect(mouse);
}

void UI_box::notifyUnSelected(glm::vec2 mouse)
{
	/*std::cout << "deselect on : " << this << std::endl;*/
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->onDeSelect(mouse);
}

void UI_box::notifyUnHover(glm::vec2 mouse)
{
	/*std::cout << "unhover on : " << this << std::endl;*/
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->onUnHover(mouse);
}
