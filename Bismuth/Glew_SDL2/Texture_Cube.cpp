#include "Texture_Cube.h"

using namespace std;

Texture_Cube::Texture_Cube(std::string path, TextureCfg cfg) : Texture_Abs(path,cfg)
{
}


Texture_Cube::~Texture_Cube()
{
}


void Texture_Cube::load()
{
	// Génération de l'ID
	glGenTextures(1, &mId);

	// Verrouillage
	glBindTexture(GL_TEXTURE_2D, mId);

	for (int i = 0; i < 6; i++)
	{
		// Chargement de l'image dans une surface SDL

		string sub = mPath.substr(0, mPath.size() - 4);
		SDL_Surface *imageSDL = IMG_Load((sub + (char)(i + '0') + mPath.substr(mPath.size()-4, mPath.size())   ).c_str());

		if (imageSDL == 0)
			std::cout << "Erreur : " << SDL_GetError() << std::endl;


		// Inversion de l'image
		SDL_Surface *invertedSDL = invertPixels(imageSDL);
		SDL_FreeSurface(imageSDL);


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
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internFormat, invertedSDL->w, invertedSDL->h, 0, format, GL_UNSIGNED_BYTE, invertedSDL->pixels);

		SDL_FreeSurface(invertedSDL);
	}
	


	// Application des filtres

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, mCfg.wrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, mCfg.wrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, mCfg.wrap);

	float aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	// Déverrouillage

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}