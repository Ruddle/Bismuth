#include "Texture.h"

Texture::Texture(std::string path, TextureCfg cfg) : mPath(path), mCfg(cfg), mW(0), mH(0)
{
}

Texture::Texture(int w,int h, TextureCfg cfg) : mW(w), mH(h), mCfg(cfg) , mPath("")
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &mId);
}


void Texture::load() {

	if (mPath.length == 0)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mCfg.wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mCfg.wrap);

	// Déverrouillage

	glBindTexture(GL_TEXTURE_2D, 0);

	// Fin de la méthode
	SDL_FreeSurface(invertedSDL);
}

void Texture::loadFromVoid()
{
	// Destruction d'une éventuelle ancienne texture
	if (glIsTexture(mId) == GL_TRUE)
		glDeleteTextures(1, &mId);

	// Génération de l'ID
	glGenTextures(1, &mId);

	// Verrouillage
	glBindTexture(GL_TEXTURE_2D, mId);

	// Définition des caractéristiques de la texture
	glTexImage2D(GL_TEXTURE_2D, 0, mCfg.format, mW, mH, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Application des filtres
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mCfg.filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mCfg.wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mCfg.wrap);

	// Déverrouillage
	glBindTexture(GL_TEXTURE_2D, 0);
}

SDL_Surface* Texture::invertPixels(SDL_Surface *src) const
{
	// Copie conforme de l'image source sans les pixels
	SDL_Surface *res = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask,
		src->format->Gmask, src->format->Bmask, src->format->Amask);

	// Tableau intermédiaires permettant de manipuler les pixels
	unsigned char* srcPixels = (unsigned char*)src->pixels;
	unsigned char* resPixels = (unsigned char*)res->pixels;

	// Inversion des pixels
	for (int i = 0; i < src->h; i++)
	{
		for (int j = 0; j < src->w * src->format->BytesPerPixel; j++)
			resPixels[(src->w * src->format->BytesPerPixel * (src->h - 1 - i)) + j] = srcPixels[(src->w * src->format->BytesPerPixel * i) + j];
	}

	// Retour de l'image inversée
	return res;
}