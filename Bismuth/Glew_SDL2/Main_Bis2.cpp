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

int main(int argc, char **argv)
{
	Config cfg = readConfig(); // Misc.cpp
	Scene_SDL* currentScene = new Scene_SDL(cfg.ResolutionX, cfg.ResolutionY);
	mat4 projection = glm::perspective(70.0*M_PI / 180.0, 16.0 / 9.0, 0.1, 100.0);
	mat4 view = glm::lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 1));
	Camera* cam = new Camera(projection,view);
	ResourcesManager* rm = new ResourcesManager();
	Entity* entityA = createThing(rm);// Misc.cpp
	Entity* entityB = createPlane(rm);// Misc.cpp
	EntityManager* entityManager = new EntityManager();
	entityManager->add(entityA);
	entityManager->add(entityB);
	RenderSystem *renderSystem = new RenderSystem(cfg, rm);
	Input input;
	int time = 0;
	while (!input.end()) {
		input.updateEvents();
		entityA->getPhysicComponent()->getStateComponent()->force(vec3(0, 0, 0.0));
		entityManager->update();
		renderSystem->draw(entityManager->getEntities(), *cam,time++,input);
		currentScene->flip();
	}

	delete cam;
	delete renderSystem;
	delete entityManager;
	delete rm;

	delete currentScene;
	return 0;
}



FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
