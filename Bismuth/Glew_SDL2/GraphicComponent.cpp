#include "GraphicComponent.h"


GraphicComponent::GraphicComponent(bool is3D,int textureDiffuse, int textureNormal, int textureSpec,int textureEmit, int vao) : 
	mTextureDiffuse(textureDiffuse),mVao(vao),mTextureNormal(textureNormal),mTextureSpec(textureSpec),
	mTextureEmit(textureEmit),mIs3D(is3D)
{

}

GraphicComponent::~GraphicComponent()
{

}

