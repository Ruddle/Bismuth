#include "Fbo.h"

using namespace std;


Fbo::Fbo() {

}


Fbo::Fbo(std::vector<Texture*> colorBufferTexture, bool depthBuffer, bool stencilBuffer) : mColorBufferTexture(colorBufferTexture),
mDepthBuffer(depthBuffer), mStencilBuffer(stencilBuffer) ,mId(0)
{
	if (mColorBufferTexture.size() == 0)
		cout << "Erreur : appel du constructeur de FBO avec un vector de taille nulle !" << endl;
}

Fbo::Fbo(int w, int h, bool depthBuffer, bool stencilBuffer) : mW(w),mH(h),
mDepthBuffer(depthBuffer), mStencilBuffer(stencilBuffer), mId(0)
{
}

Fbo::~Fbo()
{
	glDeleteFramebuffers(1, &mId);
	glDeleteRenderbuffers(1, &mRenderBufferId);
}

void Fbo::load()
{
	if (mColorBufferTexture.size() > 0) {
		 mW = mColorBufferTexture[0]->getW();
		 mH = mColorBufferTexture[0]->getH();
	}
	

	// Génération d'un id
	glGenFramebuffers(1, &mId);

	// Verrouillage du Frame Buffer
	glBindFramebuffer(GL_FRAMEBUFFER, mId);


	// Création du Depth et du Stencil Buffer
	if (mDepthBuffer == 1 || mStencilBuffer == 1)
	{
		// Destruction d'un éventuel ancien Render Buffer

		if (glIsRenderbuffer(mRenderBufferId) == GL_TRUE)
			glDeleteRenderbuffers(1, &mRenderBufferId);

		// Génération de l'identifiant
		glGenRenderbuffers(1, &mRenderBufferId);

		// Verrouillage
		glBindRenderbuffer(GL_RENDERBUFFER, mRenderBufferId);

		// Configuration du Render Buffer
		GLuint format;
		if (mDepthBuffer == 1)
		{
			if (mStencilBuffer == 1)
				format = GL_DEPTH24_STENCIL8;
			else
				format = GL_DEPTH_COMPONENT32;
		}
		else
		{
			format = GL_STENCIL_INDEX8;
		}

		glRenderbufferStorage(GL_RENDERBUFFER, format, mW, mH);

		// Déverrouillage
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	for (int i = 0; i < mColorBufferTexture.size(); i++)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mColorBufferTexture[i]->getId(), 0);
	}

	// Association du Depth et du Stencil Buffer
	if (mDepthBuffer == 1 || mStencilBuffer == 1)
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferId);


	if (mColorBufferTexture.size() == 0)
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	// Vérification de l'intégrité du FBO
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		// Libération des buffers
		glDeleteFramebuffers(1, &mId);
		glDeleteRenderbuffers(1, &mRenderBufferId);
		std::cout << "Erreur : le FBO est mal construit" << std::endl;
	}

	// Déverrouillage du Frame Buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
