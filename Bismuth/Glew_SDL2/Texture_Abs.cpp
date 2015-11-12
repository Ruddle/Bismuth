#include "Texture_Abs.h"



Texture_Abs::Texture_Abs(std::string path, TextureCfg cfg) : mPath(path), mCfg(cfg), mW(0), mH(0), mId(0)
{
}

Texture_Abs::Texture_Abs(int w, int h, TextureCfg cfg) : mW(w), mH(h), mCfg(cfg), mPath(""), mId(0)
{
}

Texture_Abs::~Texture_Abs()
{
	glDeleteTextures(1, &mId);
}


SDL_Surface* Texture_Abs::invertPixels(SDL_Surface *src) const
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