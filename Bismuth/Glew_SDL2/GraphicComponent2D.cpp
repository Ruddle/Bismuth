#include "GraphicComponent2D.h"





GraphicComponent2D::GraphicComponent2D(int textureDiffuse, glm::vec2 leftBottom, glm::vec2 size):
	mSize(size), mLeftBottom(leftBottom),mTextureDiffuse(textureDiffuse)
{
}

GraphicComponent2D::~GraphicComponent2D()
{
}
