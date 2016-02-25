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
	Vao(std::vector<glm::vec3> mPosition,std::vector<glm::vec3> mNormal,std::vector<glm::vec2> mUv);
	~Vao();

	void draw();
	void loadFile();
	void loadData();
	void load();
	void load(glm::vec4 color);
	void calcTangentBitangent();

	GLuint getVAO() { return mVaoID; }
	std::string getPath() const { return mPath; }

private:

	GLuint mVboInstanceID;
	GLuint mVboVertexID;
	GLuint mVaoID;

	std::string mPath;

	//Vertex
	std::vector<glm::vec3> mPosition;
	std::vector<glm::vec3> mNormal;
	std::vector<glm::vec3> mTangent;
	std::vector<glm::vec3> mBitangent;
	std::vector<glm::vec2> mUv;
};

