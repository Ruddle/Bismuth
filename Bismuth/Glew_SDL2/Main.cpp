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
#include "Panel.h"
#include "Updatable.h"
#include "Text.h"
#include "Loop.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

using namespace std;
using namespace glm;

int main(int argc, char **argv)
{
	Loop currentLoop= Loop();
	CoreBismuth core = currentLoop.getCore();
	vector<Updatable*> listUpdate = vector<Updatable*>();

	core.entityManager->add(createPlane(core.resourcesManager));
	Panel panel = Panel(core.entityManager, core.resourcesManager, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(0, 0), vec2(300, core.cfg->ResolutionY));
	core.entityManager->add(createUI(core.resourcesManager));
	Text textFps1 = Text(core.entityManager, core.resourcesManager, "Font/Calibri64.png", "Fps:", vec2(0, 0), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY),0.5);
	Text textX1 = Text(core.entityManager, core.resourcesManager, "Font/Calibri64.png", "x:", vec2(0, 64*0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), 0.5);

	while (currentLoop.doContinue())
	{
		Text textFps2 =  Text(core.entityManager, core.resourcesManager, "Font/Calibri64.png", to_string(currentLoop.getFps()), vec2(48*5*0.5, 0), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY),0.5);
		Text textX2 = Text(core.entityManager, core.resourcesManager, "Font/Calibri64.png", to_string(listUpdate.size()), vec2(48 * 3 * 0.5, 64*0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), 0.5);
		Text textPos = Text(core.entityManager, core.resourcesManager, "Font/Calibri64.png", (listUpdate.size()>0) ? to_string(listUpdate[0]->getEntity()->getPhysicComponent()->getStateComponent()->getPosition().z) : "", vec2(48 * 3 * 0.5, 128 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), 0.5);

		currentLoop.insertInLoop(listUpdate);

		if (core.input->getRisingKey(SDL_SCANCODE_K))
			listUpdate.push_back(new Ball(core.entityManager, core.resourcesManager, core.camera->getPosition(), core.input->getKey(SDL_SCANCODE_I)*0.0951f*core.camera->getRotation()));
		if (core.input->getRisingKey(SDL_SCANCODE_L))
			listUpdate.push_back(new Cube(core.entityManager, core.resourcesManager, core.camera->getPosition(), 0.00951f*core.camera->getRotation()));
		if (core.input->getRisingKey(SDL_SCANCODE_R))
		{
			for (auto it = listUpdate.begin(); it != listUpdate.end(); it++)
			{
				core.entityManager->suppr((*it)->getEntity()->getId());
				delete (*it);
			}
			listUpdate.clear();
		}


		textFps2.flush(core.entityManager);
		textX2.flush(core.entityManager);
		textPos.flush(core.entityManager);

	}

	return 0;
}