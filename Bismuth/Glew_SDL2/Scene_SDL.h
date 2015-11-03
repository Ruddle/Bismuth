#pragma once
#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include "glew.h"

#include <chrono>
#include <thread>

#include <windows.h>

class Scene_SDL
{
public:
	Scene_SDL(int w,int h);
	~Scene_SDL();

	double waitForFps(double fpsTarget);
	void flip();

private :
	SDL_GLContext mGLContext;
	SDL_Window* mWindow;
	SDL_Event * mEvent;
	Uint32 m_rmask, m_gmask, m_bmask, m_amask;
	Uint64 mLastTime;
};

