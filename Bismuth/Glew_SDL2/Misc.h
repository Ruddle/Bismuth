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

#define CONFIGPATH  "config.ini"



struct Config
{
	int ResolutionX;
	int ResolutionY;
};

Config readConfig(void);


Fbo* createFboGeometry(Config cfg);
Fbo* createFbo_1ch(Config cfg); // AO, blur, shadow 