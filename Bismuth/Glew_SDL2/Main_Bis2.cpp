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
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Texture.h"
#include "Fbo.h"
#include "Vao2D.h"
#include "Misc.h"
#include "EntityManager.h"
#include "DetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "RenderSystem.h"
#include "Ball.h"
#include "Cube.h"
#include "Panel.h"
#include "Updatable.h"
#include "Text.h"

using namespace glm;
using namespace std;


FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}



int main(int argc, char **argv)
{
	Config cfg = *readConfig(); // Misc.cpp
	Scene_SDL* currentScene = new Scene_SDL(cfg.ResolutionX,cfg.ResolutionY,cfg.FullScreen);
	Camera* cam = new Camera(70.0, (float) cfg.ResolutionX/cfg.ResolutionY, 0.3, 100.0);
	ResourcesManager* rm = new ResourcesManager();
	Entity* entityA = createSphere(rm);// Misc.cpp
	Entity* entityB = createPlane(rm);// Misc.cpp
	Entity* entityC = createThing(rm, vec3(0, 0, 0.8));// Misc.cpp
	entityA->getPhysicComponent()->getStateComponent()->setRotationDiff(vec3(0, 0, 0.01));
	entityC->getPhysicComponent()->getStateComponent()->setPosition(vec3(2, 0, 1));
	EntityManager* entityManager = new EntityManager();
	//entityManager->add(entityA);
	entityManager->add(entityB);
	entityManager->add(entityC);


	Entity2D* entity2DA = createUI(rm);
	entityManager->add(entity2DA);

	Panel* panel = new Panel(entityManager, rm, vec2(cfg.ResolutionX, cfg.ResolutionY), vec2(cfg.ResolutionX-200, 0), vec2(200, cfg.ResolutionY));
	//Text* text = new Text(entityManager, rm, "Font/font1.png", "abcdefghijklmnopqrstuvwxyz", vec2(100,100) , vec2(cfg.ResolutionX, cfg.ResolutionY));


	RenderSystem *renderSystem = new RenderSystem(cfg, rm);
	Input input;
	int time = 0;

	vector<Updatable*> listUpdate =  vector<Updatable*>();

	double fps = 60;

	while (!input.end()) {
		time++;
		fps = (currentScene->waitForFps(30) + 2*fps)/3.0;
		double elapsedTime = 1000.0/ fps;
		//if (time % 10 == 0)	cout << fps << endl;

		input.update();
		cam->update(input, elapsedTime);

		float numIterPhys = 10;
		for (int i = 0; i < numIterPhys; i++)
		{
			if (!input.getKey(SDL_SCANCODE_F11))
			{
				entityManager->update(float(elapsedTime / numIterPhys));

				//ICI l'utilisateur doit pouvoir update ces entitées physiques

				// USER_CODE
				for (int i = 0; i < listUpdate.size(); i++)
					listUpdate[i]->update(elapsedTime / numIterPhys);
				// END USER_CODE
			}
			entityManager->collision();
			entityManager->collisionResponse(elapsedTime / numIterPhys);
		}

		// USER_CODE
		if (input.getRisingKey(SDL_SCANCODE_K))
			listUpdate.push_back(new Ball(entityManager, rm, cam->getPosition(), input.getKey(SDL_SCANCODE_I)*0.0951f*cam->getRotation()));

		if (input.getRisingKey(SDL_SCANCODE_L))
			listUpdate.push_back(new Cube(entityManager, rm, cam->getPosition(), 0.00951f*cam->getRotation()));

		if (input.getRisingKey(SDL_SCANCODE_R))
		{
			for (auto it = listUpdate.begin(); it != listUpdate.end(); it++)
			{
				entityManager->suppr((*it)->getEntity()->getId());
				delete (*it);
			}
			listUpdate.clear();
		}
		// END USER_CODE

		renderSystem->draw(entityManager->getEntities(), *cam, time, input, float(fps));
		renderSystem->draw2D(getVisualCollision(rm, entityManager->getEntities(), *cam));
		renderSystem->draw2D(entityManager->getEntities2D());
		currentScene->flip();
	}

	delete cam;
	delete renderSystem;
	delete entityManager;
	delete rm;
	delete currentScene;
	return 0;
}


