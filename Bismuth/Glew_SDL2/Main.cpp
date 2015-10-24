#include "SDL.h"
#include <iostream>
#include "glew.h"
#include "SDL_image.h"
#include "Scene_SDL.h"


FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{return _iob;}


int main(int argc, char **argv)
{
	Scene_SDL* CurrentScene = new Scene_SDL(1600,900);
	
	system("PAUSE");
	delete CurrentScene;
	return 0;
}