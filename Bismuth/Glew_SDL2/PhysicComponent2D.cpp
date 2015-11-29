#include "PhysicComponent2D.h"


PhysicComponent2D::PhysicComponent2D(glm::vec2 size, glm::vec2 position) : mSize(size), mPosition(position)
{
}

PhysicComponent2D::~PhysicComponent2D()
{
}

bool PhysicComponent2D::contain(glm::vec2 mouse)
{
	return mouse.x > mPosition.x &&
		mouse.x < mPosition.x + mSize.x &&
		mouse.y > mPosition.y &&
		mouse.y < mPosition.y + mSize.y;
}
