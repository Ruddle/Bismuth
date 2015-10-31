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
#include "Entity.h"
#include <vector>
#include "ResourcesManager.h"

class RenderSystem
{
public:
	RenderSystem(Config cfg, ResourcesManager* rm);
	~RenderSystem();

	void draw(std::vector<Entity*> entities, Camera const& cam, float time);



private: 
	Config mCfg;
	Fbo mFboGeometry;
	Fbo mFboAo;
	Shader mShaderGeometry;
	Shader mShaderAo;
	Shader mShaderDeferredFinal;
	Vao2D mSupportFbo;
	ResourcesManager* mRm;
	


};

