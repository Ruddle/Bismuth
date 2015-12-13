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
#include "UserCamera.h"
#include "Button.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

using namespace std;
using namespace glm;

int main(int argc, char **argv)
{
	Loop currentLoop= Loop();// CODE MOTEUR MINIMAL
	CoreBismuth core = currentLoop.getCore(); 
	vector<Updatable*> listUpdate = vector<Updatable*>();

	core.entityManager->add(createPlane(core.resourcesManager));
	Panel panel = Panel(core.entityManager, core.resourcesManager,core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(0, 0), vec2(250, core.cfg->ResolutionY));
	
	core.entityManager->add(createUI(core.resourcesManager));
	Font * font = new Font("Font/Calibri64.png", 1.0f);
	Text text1 = Text(core.entityManager, core.resourcesManager, font, "Fps:", vec2(0, 0), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	Text text2 = Text(core.entityManager, core.resourcesManager, font, "x:", vec2(0, 64*0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	Text text3 = Text(core.entityManager, core.resourcesManager, font, "nbStep:", vec2(0,2* 64 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	Text text4 = Text(core.entityManager, core.resourcesManager, font, "timeFac:", vec2(0, 3 * 64 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	

	
	Button button = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 200), vec2(120, 50));
	Text label =  Text(core.entityManager, core.resourcesManager, font, "AO", vec2(10, 210), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));


	Button button2 = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 260), vec2(120, 50));
	Text label2 =  Text(core.entityManager, core.resourcesManager, font, "Shading", vec2(10, 260), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));



	UserCamera cam = UserCamera(core.camera);
	while (currentLoop.doContinue())// CODE MOTEUR MINIMAL
	{
		Text textFps2 =  Text(core.entityManager, core.resourcesManager, font, to_string(currentLoop.getFps()).substr(0,4), vec2(32*4*0.5, 0), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
		Text textX2 = Text(core.entityManager, core.resourcesManager, font, to_string(listUpdate.size()), vec2(32 * 2 * 0.5, 64*0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
		Text textPos = Text(core.entityManager, core.resourcesManager, font, to_string(currentLoop.getNbStep()), vec2(32 * 7 * 0.5, 128 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
		Text textTime = Text(core.entityManager, core.resourcesManager, font, to_string(currentLoop.getTimeFactor()).substr(0,7), vec2(32 * 8 * 0.5, 192 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));

		currentLoop.insertInLoop(listUpdate); // CODE MOTEUR MINIMAL
		cam.update(*core.input, currentLoop.getElapsedTime());
		if (core.input->getKey(SDL_SCANCODE_K))
			listUpdate.push_back(new Ball(core.entityManager, core.resourcesManager, core.camera->getPosition(), core.input->getKey(SDL_SCANCODE_I)*10.51f*normalize(core.camera->getRotation())));
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

		double x = currentLoop.getTimeFactor();
		int sign_x = (x > 0) - (x < 0);

		if (core.input->getKey(SDL_SCANCODE_Q))
			currentLoop.setTimeFactor(x*(1-0.03*sign_x) - 0.01);
		if (core.input->getKey(SDL_SCANCODE_E))
			currentLoop.setTimeFactor(x*(1 + 0.03*sign_x) + 0.01);

		if (core.input->getRisingKey(SDL_SCANCODE_T))
			currentLoop.setTimeFactor( -x );
	
		if (core.input->getRisingKey(SDL_SCANCODE_Y))
			currentLoop.setTimeFactor(1.0);

		if (core.input->getRisingKey(SDL_SCANCODE_U))
			currentLoop.setTimeFactor(0.0);
	
		panel.update();
		button.update();
		button2.update();

		if (button.isChecked()) core.cfg->AO = 1;
		else  core.cfg->AO = 0;

		textTime.flush(core.entityManager);
		textFps2.flush(core.entityManager);
		textX2.flush(core.entityManager);
		textPos.flush(core.entityManager);

	}

	return 0;
}