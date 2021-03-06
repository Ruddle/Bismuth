#include "Texture.h"

Texture::Texture(std::string path, TextureCfg cfg) : Texture_Abs(path,cfg)
{
}

Texture::Texture(int w,int h, TextureCfg cfg) : Texture_Abs(w,h,cfg)
{
}

Texture::~Texture()
{
}


void Texture::load() {

	if (mPath.length() == 0)
		loadFromVoid();
	else 
		loadFromPath();

}

void Texture::loadFromPath()
{

	// Chargement de l'image dans une surface SDL

	SDL_Surface *imageSDL = IMG_Load(mPath.c_str());

	if (imageSDL == 0)
	std::cout << "Erreur : " << SDL_GetError() << std::endl;


	// Inversion de l'image
	SDL_Surface *invertedSDL = invertPixels(imageSDL);
	SDL_FreeSurface(imageSDL);


	// G�n�ration de l'ID
	glGenTextures(1, &mId);


	// Verrouillage
	glBindTexture(GL_TEXTURE_2D, mId);

	// Format de l'image

	GLenum internFormat(0);
	GLenum format(0);


	
	// D�termination du format et du format interne pour les images � 3 composantes
	if (invertedSDL->format->BytesPerPixel == 3)
	{
		// Format interne
		internFormat = GL_RGB;
		// Format
		if (invertedSDL->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;
	}

	// D�termination du format et du format interne pour les images � 4 composantes
	else if (invertedSDL->format->BytesPerPixel == 4)
	{
		// Format interne
		internFormat = GL_RGBA;


		// Format

		if (invertedSDL->format->Rmask == 0xff)
			format = GL_RGBA;

		else
			format = GL_BGRA;
	}


	// Dans les autres cas, on arr�te le chargement

	else
	{
		std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
		SDL_FreeSurface(invertedSDL);
	}


	// Copie des pixels

	mW = invertedSDL->w;
	mH = invertedSDL->h;
	glTexImage2D(GL_TEXTURE_2D, 0, internFormat, invertedSDL->w, invertedSDL->h, 0, format, GL_UNSIGNED_BYTE, invertedSDL->pixels);


	// Application des filtres
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mCfg.wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mCfg.wrap);

	float aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	// D�verrouillage

	glBindTexture(GL_TEXTURE_2D, 0);

	// Fin de la m�thode
	SDL_FreeSurface(invertedSDL);
}

void Texture::loadFromVoid()
{
	// Destruction d'une �ventuelle ancienne texture
	if (glIsTexture(mId) == GL_TRUE)
		glDeleteTextures(1, &mId);

	// G�n�ration de l'ID
	glGenTextures(1, &mId);

	// Verrouillage
	glBindTexture(GL_TEXTURE_2D, mId);

	// D�finition des caract�ristiques de la texture
	glTexImage2D(GL_TEXTURE_2D, 0, mCfg.format, mW, mH, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Application des filtres
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mCfg.wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mCfg.wrap);

	// D�verrouillage
	glBindTexture(GL_TEXTURE_2D, 0);
}
