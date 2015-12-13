#include "GraphicComponent.h"


GraphicComponent::GraphicComponent(int textureDiffuse, int textureNormal, int textureSpec,int textureEmit,int textureReflection, int vao) : 
	mTextureDiffuse(textureDiffuse),mVao(vao),mTextureNormal(textureNormal),mTextureSpec(textureSpec),
	mTextureEmit(textureEmit),mTextureReflection(textureReflection)
{

}

GraphicComponent::~GraphicComponent()
{

}

