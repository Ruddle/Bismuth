#include "RenderSystem.h"

using namespace std;
using namespace glm;

RenderSystem::RenderSystem(Config cfg, ResourcesManager* rm) : mCfg(cfg), mRm(rm)
{
	TextureCfg texCfgNormal = { GL_RG16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texNormal = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgNormal);
	texNormal->load();
	TextureCfg texCfgDiffuse = { GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texDiffuse = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgDiffuse);
	texDiffuse->load();
	TextureCfg texCfgPosition = { GL_RGBA32F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texPosition = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgPosition);
	texPosition->load();
	vector<Texture*> textureArray = vector<Texture*>();
	textureArray.push_back(texNormal);
	textureArray.push_back(texDiffuse);
	textureArray.push_back(texPosition);
	mFboGeometry= Fbo(textureArray, 1, 0);
	mFboGeometry.load();

	TextureCfg texCfg_1ch = { GL_R8, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* tex_1ch = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfg_1ch);
	tex_1ch->load();
	vector<Texture*> textureArray2 = vector<Texture*>();
	textureArray2.push_back(tex_1ch);
	mFboAo = Fbo(textureArray2, 0, 0);
	mFboAo.load();

	mShaderGeometry = Shader("Shader/defPass1.vert", "Shader/defPass1.frag") ;
	mShaderGeometry.load();

	mShaderAo       = Shader("Shader/defPassN.vert", "Shader/AO.frag");
	mShaderAo.load();

	mShaderDeferredFinal = Shader("Shader/defPassN.vert", "Shader/defPassN.frag");
	mShaderDeferredFinal.load();

	mShaderDeferredFinalDebug = Shader("Shader/defPassN.vert", "Shader/defPassNDebug.frag");
	mShaderDeferredFinalDebug.load();

	mSupportFbo = Vao2D();
	mSupportFbo.load();
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::draw(std::vector<Entity*> entities,Camera const& cam, float time,Input &input) {

	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 ,GL_COLOR_ATTACHMENT2 };

	vec2 resolution = vec2(mCfg.ResolutionX, mCfg.ResolutionY);
	mat4 projection = cam.getProjection();
	mat4 view = cam.getView();
	mat4 modelview;

	glViewport(0, 0, mCfg.ResolutionX, mCfg.ResolutionY);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboGeometry.getId());
	glDrawBuffers(3, attachments);
	glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderGeometry.getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform2fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "resolution"), 1, value_ptr(resolution));
	
	for (int i = 0; i < entities.size(); i++) {

		Entity* entity = entities[i];
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ( mRm->getTexture(       entity->getGraphicComponent()->getTextureDiffuseId()    )->getId()  )   );
		glUniform1i(glGetUniformLocation(mShaderGeometry.getProgramID(), "texture_diffuse"), 0);
		modelview = entity->getPhysicComponent()->getStateComponent()->getModel()*view;
		glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniformMatrix3fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));
		mRm->getVao( entity->getGraphicComponent()->getVaoId() )->draw();
	}




	//Dessin intermédiaire (effect : AO ,SHADOW, MOTION BLUR, BLUR )
	glBindFramebuffer(GL_FRAMEBUFFER, mFboAo.getId());
	glDrawBuffers(1, attachments);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderAo.getProgramID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(glGetUniformLocation(mShaderAo.getProgramID(), "gPosition"), 0);

	glUniform1f(glGetUniformLocation(mShaderAo.getProgramID(), "time"), time);
	glUniformMatrix4fv(glGetUniformLocation(mShaderAo.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

	mSupportFbo.draw();

	GLuint selectedFinalShader = input.getKey(SDL_SCANCODE_F3) ? mShaderDeferredFinalDebug.getProgramID() : mShaderDeferredFinal.getProgramID();

	//Dessin final, sur l'écran
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(selectedFinalShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "gNormal"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(1));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "gDiffuse"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "gPosition"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, mFboAo.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "aoSampler"), 3);

	glUniformMatrix4fv(glGetUniformLocation(selectedFinalShader, "projection"), 1, GL_FALSE, value_ptr(projection));

	glUniform1f(glGetUniformLocation(selectedFinalShader, "time"), time);
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF2"), input.getKey(SDL_SCANCODE_F2));
	glUniform2fv(glGetUniformLocation(selectedFinalShader, "resolution"), 1, value_ptr(resolution));

	mSupportFbo.draw();
}