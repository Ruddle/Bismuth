#include "SDL.h"
#include <iostream>
#include "glew.h"
#include "SDL_image.h"
#include "Scene_SDL.h"
#include "Vao.h"
#include "Shader.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "gtc\type_ptr.hpp"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{return _iob;}


int main(int argc, char **argv)
{
	Scene_SDL* CurrentScene = new Scene_SDL(1600,900);

	

	Vao vaoA = Vao("Mesh/cube.obj");
	vaoA.load();
	

	Shader shaderA = Shader("Shader/test.vert", "Shader/test.frag");
	shaderA.load();

	glm::mat4 projection;
	glm::mat4 modelview;
	glm::mat4 view;

	projection = glm::perspective(70.0*M_PI/180.0, (double)16 / 9, 0.1, 100.0);
	view = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));


	while (true) {
		glViewport(0, 0, 1600, 900);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glEnable(GL_BLEND);
		modelview = view;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderA.getProgramID());
		glUniformMatrix4fv(glGetUniformLocation(shaderA.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shaderA.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniformMatrix3fv(glGetUniformLocation(shaderA.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));
		vaoA.draw();
		CurrentScene->flip();
	}


	system("PAUSE");
	delete CurrentScene;
	return 0;
}