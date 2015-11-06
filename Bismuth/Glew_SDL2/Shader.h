#pragma once

#include <iostream>
#include <glew.h>
#include <map>

class Shader
{
public:

	Shader();
	Shader(Shader const &refShader);
	Shader(std::string vertexSource, std::string fragmentSource);
	~Shader();

	Shader& operator=(Shader const &refShader);

	bool load();
	bool compileShader(GLuint &shader, GLenum type, std::string const &sourceFile);
	GLuint getProgramID() const;

	GLuint getLocation(std::string name);


private:

	GLuint mVertexID;
	GLuint mFragmentID;
	GLuint mProgramID;

	std::map<std::string, GLuint> mLocation;

	std::string mVertexSource;
	std::string mFragmentSource;
};

