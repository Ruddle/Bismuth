#include "PhysicComponent2D.h"


PhysicComponent2D::PhysicComponent2D(glm::vec2 size, glm::vec2 position) : mSize(size), mPosition(position) , mIsSelected(false), mIsHovered(false)
{
}

PhysicComponent2D::~PhysicComponent2D()
{
}

void PhysicComponent2D::move(glm::vec2 mouse, glm::vec2 mouseRelative)
{
	mIsHovered = contain(mouse);
}

void PhysicComponent2D::select(glm::vec2 mouse)
{
	mIsSelected = contain(mouse);
}

void PhysicComponent2D::deselect(glm::vec2 mouse)
{
	mIsSelected = false;
}

bool PhysicComponent2D::contain(glm::vec2 mouse)
{
	return mouse.x > mPosition.x &&
		mouse.x < mPosition.x + mSize.x &&
		mouse.y > mPosition.y &&
		mouse.y < mPosition.y + mSize.y;
}
