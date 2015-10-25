#pragma once
#include "glew.h"
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

struct TextureCfg
{
	GLenum format;
	GLenum filter;
	GLenum wrap;
};


class Texture
{
public:
	Texture(std::string path, TextureCfg cfg);
	Texture(int w,int h, TextureCfg cfg);
	~Texture();

	void load();
	void loadFromPath();
	void loadFromVoid();

	GLuint getID() { return mId; }

	SDL_Surface* invertPixels(SDL_Surface *src) const;

private:

	GLuint mId;
	std::string mPath;
	TextureCfg mCfg;
	int mW;
	int mH;
};

