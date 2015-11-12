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


class Texture_Abs
{
public:	
	Texture_Abs(std::string path, TextureCfg cfg);
	Texture_Abs(int w, int h, TextureCfg cfg);
	~Texture_Abs();

	virtual void load() = 0;

	GLuint getId() { return mId; }
	int getW() { return mW; }
	int getH() { return mH; }
	std::string getPath() const { return mPath; }
	TextureCfg getCfg() const { return mCfg; }

	SDL_Surface* invertPixels(SDL_Surface *src) const;

protected :
	GLuint mId;
	std::string mPath;
	TextureCfg mCfg;
	int mW;
	int mH;
};

