#include "Scene_SDL.h"


using namespace std;
Scene_SDL::Scene_SDL()
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


	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		//return -1;
	}



	// Version d'OpenGL

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	// Double Buffer

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	mWindow = NULL;
	mEvent = NULL;

	/* Création de la fenêtre */
	//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
	mWindow = SDL_CreateWindow("Ma premiere application SDL2", 300,
		50,
		1600,
		900,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (mWindow)
	{
		mEvent = new SDL_Event();
	}
	else
	{
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
	}



	mGLContext = (SDL_GL_CreateContext(mWindow));

	glewExperimental = GL_TRUE;


	GLenum initialisationGLEW(glewInit());
	glEnable(GL_DEPTH_TEST);
	SDL_SetRelativeMouseMode(SDL_TRUE);


	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



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
	
	//delete m_p_Event;
	SDL_GL_DeleteContext(mGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	//system("PAUSE");
}
