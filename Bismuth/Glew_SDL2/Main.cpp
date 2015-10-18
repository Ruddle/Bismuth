#include "SDL.h"
#include <iostream>
#include "glew.h"
#include "SDL_image.h"
#include "Scene_SDL.h"


#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{return _iob;}

int main(int argc, char **argv)
{
	Scene_SDL* CurrentScene = new Scene_SDL();
	

	system("PAUSE");
	delete CurrentScene;
	return 0;
}