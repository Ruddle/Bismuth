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
#include "Loop.h"
#include "UserCamera.h"
#include "Button.h"
#include "AO_button.h"
#include "Slider.h"
#include "Test_Slider.h"
#include "ButtonController_int.h"
#include "BisObject.h"
#include "Heightmap.h"
//#include "UI_layout_grid.h"
//#include "UI_link_grid.h"
//#include "UI_button.h"
#include "Hat.h"
#include "Gravity.h"
#include "PhysicBoom.h"


#if defined(WIN32) || defined(_WIN32)
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#endif

using namespace std;
using namespace glm;

int main(int argc, char **argv)
{
	Loop currentLoop= Loop();// CODE MOTEUR MINIMAL
	CoreBismuth core = currentLoop.getCore();
	vector<Updatable*> listUpdate = vector<Updatable*>();
	vector<Entity*> listUpdateEntity = vector<Entity*>();

	core.entityManager->add(createPlane(core.resourcesManager));
	
	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1000);
	StateComponent* sc1 = new StateComponent();
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	Gravity* g = new Gravity(pc1);
	core.entityManager->add(g);

	Panel panel = Panel(core.entityManager, core.resourcesManager,core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(0, 0), vec2(250, core.cfg->ResolutionY));

	core.entityManager->add(createUI(core.resourcesManager));
	Font * font = new Font("Font/Calibri64.png", 1.0f);
	Text text1 = Text(core.entityManager, core.resourcesManager, font, "Fps:", vec2(0, 0), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	Text text2 = Text(core.entityManager, core.resourcesManager, font, "x:", vec2(0, 64*0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	Text text3 = Text(core.entityManager, core.resourcesManager, font, "nbStep:", vec2(0,2* 64 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	Text text4 = Text(core.entityManager, core.resourcesManager, font, "timeFac:", vec2(0, 3 * 64 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	Slider slider = Slider(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(15, 4 * 64 * 0.5),vec2(100,12));


	Text info = Text(core.entityManager, core.resourcesManager, font, "keys : F = free mouse, I/K = throw/drop Ball, L = drop Box", vec2(250, 0), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));

	Button button = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 200), vec2(150, 50));
	Text label =  Text(core.entityManager, core.resourcesManager, font, "AO", vec2(10, 210), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));

	AO_button aoControl(&button, core.cfg); // Listener/Controller pour le bouton AO
	float test = 0.5;
	Test_Slider sliderControl(&slider,&test);

	Button button2 = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 260), vec2(150, 50));
	Text label2 =  Text(core.entityManager, core.resourcesManager, font, "Shading", vec2(10, 260), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	ButtonController_int b2c(&button2, &(core.cfg->CookTorrance));

	Button buttonR = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 320), vec2(150, 50));
	Text labelR = Text(core.entityManager, core.resourcesManager, font, "Reflect", vec2(10, 320), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	ButtonController_int bcR(&buttonR, &(core.cfg->Reflection));

	Button buttonB = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 380), vec2(150, 50));
	Text labelB = Text(core.entityManager, core.resourcesManager, font, "Bloom", vec2(10, 380), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	ButtonController_int bcB(&buttonB, &(core.cfg->Bloom));

	Button buttonSM = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 440), vec2(150, 50));
	Text labelSM = Text(core.entityManager, core.resourcesManager, font, "Shadow", vec2(10, 440), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	ButtonController_int bcSM(&buttonSM, &(core.cfg->ShadowMap));

	Button buttonMB = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 500), vec2(150, 50));
	Text labelMB = Text(core.entityManager, core.resourcesManager, font, "M-blur", vec2(10, 500), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	ButtonController_int bcMB(&buttonMB, &(core.cfg->MotionBlur));

	Button buttonCO = Button(core.entityManager, core.resourcesManager, core.input, vec2(core.cfg->ResolutionX, core.cfg->ResolutionY), vec2(10, 560), vec2(150, 50));
	Text labelCO = Text(core.entityManager, core.resourcesManager, font, "Collision", vec2(10, 560), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
	ButtonController_int bcCO(&buttonCO, &(core.cfg->DrawCollision));


	//UI_layout_grid* layout = new UI_layout_grid(3, 4);
	//UI_button* ui_buttonA = new UI_button(&core, layout);
	//ui_buttonA->setPositionSize({ vec2(-1),vec2(2) });

	//UI_layout_grid* layout1 = new UI_layout_grid(2,2);
	//UI_button* ui_button1 = new UI_button(&core, layout1);

	//UI_link_grid* ui_link1 = new UI_link_grid(ui_button1, 0, 0);
	//UI_link_grid* ui_link2 = new UI_link_grid(ui_button1, 1, 1);
	//UI_link_grid* ui_link3 = new UI_link_grid(ui_button1, 2, 3);

	//ui_buttonA->add(ui_link1);
	//ui_buttonA->add(ui_link2);
	//ui_buttonA->add(ui_link3);

	//ui_buttonA->update();

	//Heightmap hm = Heightmap(core.entityManager, core.resourcesManager);

	UserCamera cam = UserCamera(core.camera);
	while (currentLoop.doContinue())// CODE MOTEUR MINIMAL
	{

		/*core.camera->setFov(179 - test * 178);*/
		Text textFps2 =  Text(core.entityManager, core.resourcesManager, font, to_string(currentLoop.getFps()).substr(0,4), vec2(32*4*0.5, 0), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
		Text textX2 = Text(core.entityManager, core.resourcesManager, font, to_string(listUpdate.size()), vec2(32 * 2 * 0.5, 64*0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
		Text textPos = Text(core.entityManager, core.resourcesManager, font, to_string(currentLoop.getNbStep()), vec2(32 * 7 * 0.5, 128 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
		Text textTime = Text(core.entityManager, core.resourcesManager, font, to_string(currentLoop.getTimeFactor()).substr(0,7), vec2(32 * 8 * 0.5, 192 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));
		Text textTestSlider = Text(core.entityManager, core.resourcesManager, font, to_string(test).substr(0, 5), vec2(32 * 8 * 0.5, 256 * 0.5), vec2(core.cfg->ResolutionX, core.cfg->ResolutionY));


		currentLoop.insertInLoop(listUpdate); // CODE MOTEUR MINIMAL
		cam.update(*core.input, currentLoop.getElapsedTime());

		if (core.input->getRisingKey(SDL_SCANCODE_K)) {
			Ball* e = new Ball(core.entityManager, core.resourcesManager, core.camera->getPosition(), 0 * 10.51f*normalize(core.camera->getRotation()));
			listUpdate.push_back(e);
			listUpdateEntity.push_back(e);
		}

		if (core.input->getKey(SDL_SCANCODE_I))
		{
			Ball* e = new Ball(core.entityManager, core.resourcesManager, core.camera->getPosition(), 1 * 10.51f*normalize(core.camera->getRotation()));
			listUpdate.push_back(e);
			listUpdateEntity.push_back(e);
		}
		if (core.input->getRisingKey(SDL_SCANCODE_L))
		{
			Cube* e =new Cube(core.entityManager, core.resourcesManager, core.camera->getPosition(), 0.00951f*core.camera->getRotation());
			listUpdate.push_back(e);
			listUpdateEntity.push_back(e);
		}
			


		if (core.input->getRisingKey(SDL_SCANCODE_V))
		{
			BisObject* e =new BisObject(core.entityManager, core.resourcesManager, core.camera->getPosition(), 0.00951f*core.camera->getRotation(), "BisObject/saber.txt");
			listUpdate.push_back(e);
			listUpdateEntity.push_back(e);
		}

		if (core.input->getRisingKey(SDL_SCANCODE_O))
		{
			SphereDetectionComponent* dc = new SphereDetectionComponent(100);
			StateComponent* sc = new StateComponent();
			PhysicComponent* pc = new PhysicComponent(dc, sc);
			PhysicBoom* s = new PhysicBoom(pc1);
			sc->setPosition(core.camera->getPosition());
			s->setModel(glm::translate(core.camera->getPosition()));
			core.entityManager->add(s);
			core.entityManager->setTimeOfDeath(s->getId(), 0.1);
			
		}




		if (core.input->getRisingKey(SDL_SCANCODE_N))
			new Hat (core.entityManager, core.resourcesManager, listUpdateEntity[listUpdateEntity.size()-1 ] );

		if (core.input->getRisingKey(SDL_SCANCODE_R))
		{
			for (int i = 0; i < listUpdateEntity.size();i++)
			{
				core.entityManager->suppr(  listUpdateEntity[i]->getId());
			}
			listUpdate.clear();
			listUpdateEntity.clear();
		}

		double x = currentLoop.getTimeFactor();
		int sign_x = (x > 0) - (x < 0);

		if (core.input->getKey(SDL_SCANCODE_X))
			currentLoop.setTimeFactor(x*(1-0.03*sign_x) - 0.01);
		if (core.input->getKey(SDL_SCANCODE_C))
			currentLoop.setTimeFactor(x*(1 + 0.03*sign_x) + 0.01);

		if (core.input->getRisingKey(SDL_SCANCODE_T))
			currentLoop.setTimeFactor( -x );

		if (core.input->getRisingKey(SDL_SCANCODE_Y))
			currentLoop.setTimeFactor(1.0);

		if (core.input->getRisingKey(SDL_SCANCODE_U))
			currentLoop.setTimeFactor(0.0);

		textTestSlider.flush(core.entityManager);
		textTime.flush(core.entityManager);
		textFps2.flush(core.entityManager);
		textX2.flush(core.entityManager);
		textPos.flush(core.entityManager);

	}

	return 0;
}
