#pragma once
#include "glew.h"
#include <string>
#include <iostream>
#include "SDL.h"
#include "Texture.h"
#include <vector>


class Fbo
{
public:
	Fbo();
	Fbo(std::vector<Texture*> colorBufferTexture, bool depthBuffer, bool stencilBuffer);
	Fbo(int w,int h, bool depthBuffer, bool stencilBuffer);
	~Fbo();

	void load();

	GLuint getId() { return mId; }
	GLuint getRenderBufferId() { return mRenderBufferId; }
	GLuint getColorBufferId(int n) { return mColorBufferTexture[n]->getId(); }

private:

	int mW;
	int mH;
	GLuint mId;
	std::vector<Texture*> mColorBufferTexture;

	bool mDepthBuffer;
	bool mStencilBuffer;
	
	GLuint mRenderBufferId;
};

