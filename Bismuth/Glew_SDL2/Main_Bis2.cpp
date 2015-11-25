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
#include "Misc.h"
#include "EntityManager.h"
#include "DetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "RenderSystem.h"
#include "Ball.h"
#include "Cube.h"


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
	//entityManager->add(entityC);

	RenderSystem *renderSystem = new RenderSystem(cfg, rm);
	Input input;
	int time = 0;


	vector<Ball*> listBall = vector<Ball*>();
	vector<Cube*> listCube = vector<Cube*>();
	
	double fps = 60;

	while (!input.end()) {
		time++;
		entityC->getPhysicComponent()->getStateComponent()->setPosition(vec3(3+ cos(time / 10.0), 0, 2 + sin(time / 10.0)));
		fps = (currentScene->waitForFps(30) + 2*fps)/3.0;
		double elapsedTime = 1000.0/ fps;
		if (time % 10 == 0)	cout << fps << endl;
		input.update();
		cam->update(input, elapsedTime);
		
		vector<vec2> a;
		float numIterPhys = 5;
		for (int i = 0; i < numIterPhys; i++)
		
		{
			if (!input.getKey(SDL_SCANCODE_F11))
			{
				entityManager->update(float(elapsedTime/ numIterPhys));

				for (int i = 0; i < listBall.size(); i++)
					listBall[i]->update(elapsedTime / numIterPhys);

				for (int i = 0; i < listCube.size(); i++)
					listCube[i]->update(elapsedTime / numIterPhys);
			}
			entityManager->collision();
			entityManager->collisionResponse(elapsedTime / numIterPhys);


			vector<Entity*> entities = entityManager->getEntities();

			entities.clear();
			entities.push_back(entityB);

		for (auto it1 = entities.begin(); it1 != entities.end(); it1++)
			{
				set<Contact*> contacts = (*it1)->getPhysicComponent()->getContact();
				for (auto it = contacts.begin(); it != contacts.end(); it++)
				{
					vec4 worldSpace = vec4((*it)->position, 1);
					vec4 screenSpace = cam->getProjection() * cam->getView() * worldSpace;
					screenSpace /= screenSpace.w;
					a.push_back(vec2(screenSpace));

					for (int i = 0; i < 10; i++)
					{
						vec4 worldSpace = vec4((*it)->position + i*10.0f*(*it)->normal, 1);
						vec4 screenSpace = cam->getProjection() * cam->getView() * worldSpace;
						screenSpace /= screenSpace.w;
						a.push_back(vec2(screenSpace));

					}

				}
			}
		}

		

		if (time % 1 == 0) {
			renderSystem->draw(entityManager->getEntities(), *cam, time, input, float(fps));
			renderSystem->draw2D(*cam,a);
			currentScene->flip();
		}

		if (input.getRisingKey(SDL_SCANCODE_K))
		listBall.push_back(  new Ball(entityManager, rm, cam->getPosition(), 0.00951f*cam->getRotation()) );

		if (input.getRisingKey(SDL_SCANCODE_L))
		listCube.push_back(new Cube(entityManager, rm, cam->getPosition(), 0.00951f*cam->getRotation()));

		
	
	}

	delete cam;
	delete renderSystem;
	delete entityManager;
	delete rm;
	delete currentScene;
	return 0;
}


