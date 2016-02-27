#pragma once
#include "glew.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class Vao2D
{
public:
	Vao2D();
	~Vao2D();

	void load();
	void draw();

private:

	GLuint mVboId;
	GLuint mVaoId;
};

