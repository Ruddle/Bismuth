#pragma once
#include "glew.h"
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Texture_Abs.h"
class Texture_Cube : public Texture_Abs
{
public:
	Texture_Cube();
	Texture_Cube(std::string path, TextureCfg cfg);
	~Texture_Cube();

	void load(); // TODO 
};

