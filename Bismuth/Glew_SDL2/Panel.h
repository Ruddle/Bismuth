#pragma once

#include "glew.h"
#include "SDL_image.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "gtc\type_ptr.hpp"
#include "Texture.h"
#include "Entity2D.h"
#include "PhysicComponent.h"
#include "GraphicComponent.h"
#include "EntityManager.h"

class Panel
{
public:
	Panel(EntityManager* em, ResourcesManager* rm,Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Panel();

	void update();
	

private:

	Entity2D* mLeft;
	Entity2D* mRight;
	Entity2D* mUp;
	Entity2D* mDown;
	Entity2D* mCenter;
	
};

