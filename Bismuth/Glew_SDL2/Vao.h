#pragma once
#include <string>
#include <vector>
#include "glew.h"
#include "glm.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif


class Vao
{


public:
	Vao(std::string path);
	~Vao();

	void draw();
	void Vao::loadFile();
	void Vao::load();
	GLuint getVAO() { return mVaoID; }

private:

	GLuint mVboVertexID;
	GLuint mVaoID;

	std::string mPath;

	//Vertex
	std::vector<glm::vec3> mPosition;
	std::vector<glm::vec3> mNormal;
	std::vector<glm::vec2> mUv;
};

