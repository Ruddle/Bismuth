#pragma once
#include "glew.h"
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Texture_Abs.h"



class Texture : public Texture_Abs
{
public:
	Texture(std::string path, TextureCfg cfg);
	Texture(int w,int h, TextureCfg cfg);
	~Texture();

	void load();
	void loadFromPath();
	void loadFromVoid();
};

