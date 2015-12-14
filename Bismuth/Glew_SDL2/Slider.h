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
#include "UI_box.h"

class Slider
{
public:
	Slider(EntityManager* em, ResourcesManager* rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Slider();

protected:
	UI_box* mUIBar;
	UI_box* mUIDot;
private:
	Entity2D* mBar;
	Entity2D* mDot;
	double mValue;
};

