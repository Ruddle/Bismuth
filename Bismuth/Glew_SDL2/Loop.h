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
class Loop
{
public:
	Loop();
	~Loop();

	void insertInLoop(std::vector<Updatable*> &toUpdate);
	bool doContinue() { return mContinue; }
	CoreBismuth getCore() {	return{ mResourcesManager,mEntityManager,mInput,mCfg,mScene,mCamera,mRenderSystem };}
	double getFps() { return mFps; }
	void setTimeStep(float timeStep);
	float getTimeStep() { return mTimeStep; }

private :
	float mTimeStep;
	float mPhysicsDelay;
	ResourcesManager* mResourcesManager;
	EntityManager* mEntityManager;
	Input* mInput;
	Config* mCfg;
	Scene_SDL* mScene;
	Camera* mCamera;
	RenderSystem* mRenderSystem;
	int mFrame;
	double mFps;
	bool mContinue;



};

