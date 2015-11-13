#include "Texture_Cube.h"



Texture_Cube::Texture_Cube(std::string path, TextureCfg cfg) : Texture_Abs(path,cfg)
{
}


Texture_Cube::~Texture_Cube()
{
}


void Texture_Cube::load()
{
	// Chargement de l'image dans une surface SDL

	SDL_Surface *imageSDL = IMG_Load(mPath.c_str());

	if (imageSDL == 0)
		std::cout << "Erreur : " << SDL_GetError() << std::endl;


	// Inversion de l'image
	SDL_Surface *invertedSDL = invertPixels(imageSDL);
	SDL_FreeSurface(imageSDL);


	// Génération de l'ID
	glGenTextures(1, &mId);


	// Verrouillage
	glBindTexture(GL_TEXTURE_2D, mId);

	// Format de l'image

	GLenum internFormat(0);
	GLenum format(0);



	// Détermination du format et du format interne pour les images à 3 composantes
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

	// Détermination du format et du format interne pour les images à 4 composantes
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


	// Dans les autres cas, on arrête le chargement

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

	// Déverrouillage

	glBindTexture(GL_TEXTURE_2D, 0);

	// Fin de la méthode
	SDL_FreeSurface(invertedSDL);


}