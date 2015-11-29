#include "Scene_SDL.h"


using namespace std;
Scene_SDL::Scene_SDL(int w, int h, int fullscreen) : mLastTime(0)
{
	cout << "Creation    : Scene_SDL" << endl;
	
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	m_rmask = 0xff000000;
	m_gmask = 0x00ff0000;
	m_bmask = 0x0000ff00;
	m_amask = 0x000000ff;
#else
	m_rmask = 0x000000ff;
	m_gmask = 0x0000ff00;
	m_bmask = 0x00ff0000;
	m_amask = 0xff000000;
#endif

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	cout << "Echec : " << endl << SDL_GetError() << endl;
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mWindow = NULL;
	mEvent = NULL;

	//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

	if(fullscreen)
	mWindow = SDL_CreateWindow(
		"Bismuth Engine",
		10,
		30,
		w,
		h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	else
		mWindow = SDL_CreateWindow(
			"Bismuth Engine",
			10,
			30,
			w,
			h,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);


	if (mWindow)
	mEvent = new SDL_Event();
	else
	cout << "Echec : " << endl << SDL_GetError() << endl;
	

	mGLContext = (SDL_GL_CreateContext(mWindow));

	glewExperimental = GL_TRUE;
	GLenum initialisationGLEW(glewInit());
	glEnable(GL_DEPTH_TEST);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);



	//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	//	glEnable(GL_LINE_SMOOTH);
	//	glEnable(GL_POLYGON_SMOOTH);
}


Scene_SDL::~Scene_SDL()
{

	cout << "Destruction : Scene_SDL" << endl;
	
	delete mEvent;
	SDL_GL_DeleteContext(mGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}


double Scene_SDL::waitForFps(double fpsTarget)
{
		Uint64 diff = (SDL_GetPerformanceCounter() - mLastTime);
		
		double diffDouble = double(diff);
		double freqDouble = double(SDL_GetPerformanceFrequency());

		double ecart = diffDouble / freqDouble;
	
		double fps = 1.0 / ecart;
		double TimetoWait = 1000.0 / fpsTarget - 1000.0*ecart;

	//	cout << 1000*ecart << endl;

		mLastTime = SDL_GetPerformanceCounter();
	//	if(TimetoWait >0)
	//	Sleep(TimetoWait);
		
		
		return fps>1.0? fps:1;
}

void Scene_SDL::flip() {
	SDL_GL_SwapWindow(mWindow);
}