#pragma once
#include "SDL.h"
#include <iostream>
#include "glew.h"
#include "SDL_image.h"
#include "Scene_SDL.h"
#include "Vao.h"
#include "Shader.h"
#include "Input.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "gtc\type_ptr.hpp"
#include "Texture.h"
#include "Fbo.h"
#include "Vao2D.h"
#include "Entity.h"
#include "PhysicComponent.h"
#include "GraphicComponent.h"
#include "SphereDetectionComponent.h"

#define CONFIGPATH  "config.ini"



struct Config
{
	int FullScreen;
	int ResolutionX;
	int ResolutionY;
	int AO;
	int HalfAO;
};

Config readConfig(void);

// Utile pour Main_Bis2
Entity* createSphere(ResourcesManager* rm);
Entity* createThing(ResourcesManager* rm,glm::vec3 position);
Entity* createPlane(ResourcesManager* rm);

// Utile pour Main_Bis1
Fbo* createFboGeometry(Config cfg);
Fbo* createFbo_1ch(Config cfg); // AO, blur, shadow 