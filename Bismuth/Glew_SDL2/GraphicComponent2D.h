#pragma once
#include "glm.hpp"
class GraphicComponent2D
{
public:
	GraphicComponent2D(int textureDiffuse,glm::vec2 leftBottom, glm::vec2 size );
	~GraphicComponent2D();

	int getTextureDiffuseId() const { return mTextureDiffuse; }
	glm::vec2 getLeftBottom() { return mLeftBottom; }
	glm::vec2 getSize() { return mSize; }

	void setLeftBottom(glm::vec2 leftBottom) {	mLeftBottom = leftBottom;}

private:

	int mTextureDiffuse;
	glm::vec2 mLeftBottom;
	glm::vec2 mSize;

};

