#include "GraphicComponent.h"


GraphicComponent::GraphicComponent(int textureDiffuse, int textureNormal, int textureSpec,int textureEmit, int vao) : 
	mTextureDiffuse(textureDiffuse),mVao(vao),mTextureNormal(textureNormal),mTextureSpec(textureSpec),
	mTextureEmit(textureEmit)
{

}

GraphicComponent::~GraphicComponent()
{

}

