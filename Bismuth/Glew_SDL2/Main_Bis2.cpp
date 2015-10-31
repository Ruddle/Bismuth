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
#include "Misc.h"
#include "EntityManager.h"
#include "DetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "RenderSystem.h"

using namespace glm;
using namespace std;

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

int main(int argc, char **argv)
{
	Config cfg = readConfig(); // Misc.cpp
	Scene_SDL* currentScene = new Scene_SDL(cfg.ResolutionX, cfg.ResolutionY);
	
	
	mat4 projection = glm::perspective(70.0*M_PI / 180.0, 16.0 / 9.0, 0.1, 100.0);
	Camera* cam = new Camera(projection);


	ResourcesManager* rm = new ResourcesManager();
	GraphicComponent* gc1 = new GraphicComponent(rm->loadTexture("Texture/checker.png", GL_RGB8, GL_NEAREST, GL_REPEAT), 0, 0, rm->loadVao("Mesh/cube.obj"));

	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);

	Entity* entity = new Entity(gc1, pc1);

	EntityManager* entityManager = new EntityManager();

	entityManager->add(entity);


	RenderSystem *renderSystem = new RenderSystem(cfg, rm);


	Input input;

	cam->

	while (!input.end()) {
		input.updateEvents();

		renderSystem->draw(entityManager->getEntities(), *cam,0);
		currentScene->flip();
	}

	delete cam;
	delete renderSystem;
	delete entityManager;
	delete rm;

	delete currentScene;
	return 0;
}