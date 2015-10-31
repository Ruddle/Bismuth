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
#include "Fbo.h"
#include "Vao2D.h"
#include "Misc.h"


using namespace glm;
using namespace std;

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

int main(int argc, char **argv)
{
	

	Config cfg = readConfig(); // Misc.cpp
	Scene_SDL* CurrentScene = new Scene_SDL(cfg.ResolutionX,cfg.ResolutionY);

	vec2 resolution = vec2(cfg.ResolutionX, cfg.ResolutionY);

	Vao vaoA = Vao("Mesh/sphere.obj");
	vaoA.load(vec4(0,0,0,0));

	Vao vaoB = Vao("Mesh/plane.obj");
	vaoB.load(vec4(0, 0, 0, 0));

	TextureCfg texCfgA = { GL_RGB8, GL_NEAREST, GL_REPEAT };
	Texture texA = Texture("Texture/checker.png", texCfgA);
	texA.load();

	Shader shaderForward = Shader("Shader/test.vert", "Shader/test.frag");
	shaderForward.load();

	Shader shaderGeometry = Shader("Shader/defPass1.vert", "Shader/defPass1.frag");
	shaderGeometry.load();

	Shader shaderDeferred = Shader("Shader/defPassN.vert", "Shader/defPassN.frag");
	shaderDeferred.load();

	Shader shaderAO = Shader("Shader/defPassN.vert", "Shader/AO.frag");
	shaderAO.load();

	Fbo* fboGeometry = createFboGeometry(cfg); // Misc.cpp

	Vao2D supportFbo = Vao2D();
	supportFbo.load();

	glm::mat4 projection;
	glm::mat4 modelview;
	glm::mat4 view;

	projection = glm::perspective(70.0*M_PI/180.0, (double)cfg.ResolutionX / (double)cfg.ResolutionY, 0.01, 100.0);
	view = glm::lookAt(glm::vec3(2,2,2), glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 1));


	Input input;

	int frame = 0;
	while (!input.end()) {
		frame++;
		if (true) {
			GLuint attachments[3] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 ,GL_COLOR_ATTACHMENT2};
			
			input.updateEvents();

			modelview = rotate(view, (input.getX() - cfg.ResolutionX) / 200.0f, vec3(0.0f, 0.0f, 1.0f));
			modelview = translate(modelview, vec3(0, 0, 0.8));


			glViewport(0, 0, cfg.ResolutionX, cfg.ResolutionY);
			glBindFramebuffer(GL_FRAMEBUFFER, fboGeometry->getId());
			glDrawBuffers(3, attachments);
			glDisable(GL_BLEND);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shaderGeometry.getProgramID());
			glUniformMatrix4fv(glGetUniformLocation(shaderGeometry.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(shaderGeometry.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniformMatrix3fv(glGetUniformLocation(shaderGeometry.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));
			glUniform2fv(glGetUniformLocation(shaderGeometry.getProgramID(),"resolution") ,1, value_ptr(resolution));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texA.getId());
			glUniform1i(glGetUniformLocation(shaderGeometry.getProgramID(), "texture_diffuse"), 0);
			vaoA.draw();

			modelview = view;
			glUniformMatrix4fv(glGetUniformLocation(shaderGeometry.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(shaderGeometry.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniformMatrix3fv(glGetUniformLocation(shaderGeometry.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));
			vaoB.draw();
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);


			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glEnable(GL_BLEND);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shaderDeferred.getProgramID());

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, fboGeometry->getColorBufferId(0));
			glUniform1i(glGetUniformLocation(shaderDeferred.getProgramID(), "gNormal"), 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, fboGeometry->getColorBufferId(1));
			glUniform1i(glGetUniformLocation(shaderDeferred.getProgramID(), "gDiffuse"), 1);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, fboGeometry->getColorBufferId(2));
			glUniform1i(glGetUniformLocation(shaderDeferred.getProgramID(), "gPosition"), 2);

			glUniformMatrix4fv(glGetUniformLocation(shaderDeferred.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

			glUniform1f(glGetUniformLocation(shaderDeferred.getProgramID(), "varA"), input.getY() / resolution.y);
			glUniform1i(glGetUniformLocation(shaderDeferred.getProgramID(), "time"), frame);
			glUniform2fv(glGetUniformLocation(shaderDeferred.getProgramID(), "resolution"), 1, value_ptr(resolution));

			supportFbo.draw();
			
			CurrentScene->flip();

		}
		else {
			input.updateEvents();
			glViewport(0, 0, cfg.ResolutionX, cfg.ResolutionY);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glEnable(GL_BLEND);
			modelview = rotate(view, (input.getX() - cfg.ResolutionX) / 100.0f, vec3(0.0f, 0.0f, 1.0f));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shaderForward.getProgramID());
			glUniformMatrix4fv(glGetUniformLocation(shaderForward.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(shaderForward.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniformMatrix3fv(glGetUniformLocation(shaderForward.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texA.getId());
			glUniform1i(glGetUniformLocation(shaderForward.getProgramID(), "texture_diffuse"), 0);

			vaoA.draw();
			CurrentScene->flip();
		}
	}

	delete CurrentScene;
	return 0;
}

