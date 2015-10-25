#include "SDL.h"
#include <iostream>
#include "glew.h"
#include "SDL_image.h"
#include "Scene_SDL.h"
#include "Vao.h"
#include "Shader.h"
#include "Input.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "gtc\type_ptr.hpp"
#include "Texture.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{return _iob;}

using namespace glm;

int main(int argc, char **argv)
{
	Scene_SDL* CurrentScene = new Scene_SDL(1600,900);

	Vao vaoA = Vao("Mesh/sphere.obj");
	vaoA.load();

	TextureCfg cfg = { GL_RGB8, GL_NEAREST, GL_REPEAT };
	Texture texA = Texture("Texture/checker.png", cfg);
	texA.load();

	Shader shaderA = Shader("Shader/test.vert", "Shader/test.frag");
	shaderA.load();

	glm::mat4 projection;
	glm::mat4 modelview;
	glm::mat4 view;

	projection = glm::perspective(70.0*M_PI/180.0, (double)16 / 9, 0.1, 100.0);
	view = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));


	Input input;

	while (!input.end()) {

		input.updateEvents();
		glViewport(0, 0, 1600, 900);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glEnable(GL_BLEND);
		modelview = rotate(view, (input.getX()-1600)/100.0f, vec3(0.0f, 0.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderA.getProgramID());
		glUniformMatrix4fv(glGetUniformLocation(shaderA.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shaderA.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniformMatrix3fv(glGetUniformLocation(shaderA.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texA.getId());
		glUniform1i(glGetUniformLocation(shaderA.getProgramID(), "texture_diffuse"), 0);

		vaoA.draw();
		CurrentScene->flip();
	}

	delete CurrentScene;
	return 0;
}