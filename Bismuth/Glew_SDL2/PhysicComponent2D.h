#pragma once
#include "glm.hpp"
#include "Observer_Input.h"
class PhysicComponent2D : public Observer_Input
{
public:
	PhysicComponent2D(glm::vec2 size,glm::vec2 position);
	~PhysicComponent2D();

	glm::vec2 getSize() { return mSize; }
	glm::vec2 getPosition() { return mPosition; }


	void move(glm::vec2 mouse, glm::vec2 mouseRelative) ;
	void select(glm::vec2 mouse) ;
	void deselect(glm::vec2 mouse) ;

	bool contain(glm::vec2 mouse);

	bool isSelected() { return mIsSelected; }
	bool isHovered() { return mIsSelected; }

private:

	glm::vec2 mSize;
	glm::vec2 mPosition; //left bottom 

	bool mIsSelected;
	bool mIsHovered;
	

};

