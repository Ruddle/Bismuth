#pragma once

#include <iostream>
#include <glew.h>

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


private:

	GLuint mVertexID;
	GLuint mFragmentID;
	GLuint mProgramID;

	std::string mVertexSource;
	std::string mFragmentSource;
};

