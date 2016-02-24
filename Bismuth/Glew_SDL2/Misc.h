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
#include "Entity2D.h"
#include "PhysicComponent.h"
#include "GraphicComponent.h"
#include "SphereDetectionComponent.h"
#include "CubeDetectionComponent.h"
#include "PlaneDetectionComponent.h"
#include "InteractionManager.h"


#define CONFIGPATH  "config.ini"



struct Config
{
	int FullScreen;
	int ResolutionX;
	int ResolutionY;
	int AO;
	int HalfAO;
	int CookTorrance;
	int Reflection;
	int LensFlare_Undersampling;
};

class ResourcesManager;
class EntityManager;
class Input;
class Scene_SDL;
class RenderSystem;

struct CoreBismuth
{
	ResourcesManager* resourcesManager;
	EntityManager* entityManager;
	Input* input;
	Config* cfg;
	Scene_SDL* scene;
	Camera* camera;
	RenderSystem* renderSystem;
};

Config* readConfig(void);

// Utile pour Main_Bis2
Entity* createSphere(ResourcesManager* rm);
Entity* createThing(ResourcesManager* rm,glm::vec3 position);
Entity* createPlane(ResourcesManager* rm);
Entity2D* createUI(ResourcesManager* rm);

std::vector<Entity2D*> getVisualCollision(ResourcesManager* rm, InteractionManager * im, Camera const & cam);


// Utile pour Main_Bis1
Fbo* createFboGeometry(Config cfg);
Fbo* createFbo_1ch(Config cfg); // AO, blur, shadow 