#include "GraphicComponent.h"


GraphicComponent::GraphicComponent(int textureDiffuse, int textureNormal, int textureSpec, int vao) : mTextureDiffuse(textureDiffuse),mVao(vao),mTextureNormal(textureNormal),mTextureSpec(textureSpec)
{

}

GraphicComponent::~GraphicComponent()
{

}

