#include "RenderSystem.h"

using namespace std;
using namespace glm;

RenderSystem::RenderSystem(Config cfg, ResourcesManager* rm) : mCfg(cfg), mRm(rm)
{


	TextureCfg texCfgNormal = { GL_RGB16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texNormal = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgNormal);
	texNormal->load();
	TextureCfg texCfgDiffuse = { GL_RGB16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
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
	mFboAo = Fbo(textureArray, 0, 0);
	mFboAo.load();


	mShaderGeometry = Shader("Shader/defPass1.vert", "Shader/defPass1.frag") ;
	mShaderGeometry.load();

	mShaderAo       = Shader("Shader/defPassN.vert", "Shader/AO.frag");
	mShaderAo.load();

	mShaderDeferredFinal = Shader("Shader/defPassN.vert", "Shader/defPassNDebug.frag");
	mShaderDeferredFinal.load();

	mSupportFbo = Vao2D();
	mSupportFbo.load();
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::draw(std::vector<Entity*> entities,Camera const& cam, float time) {

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




	// DRAW EACH VAO

	for (int i = 0; i < entities.size(); i++) {


		Entity* entity = entities[i];

		

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ( mRm->getTexture(       entity->getGraphicComponent()->getTextureDiffuseId()    )->getId()  )   );
		glUniform1i(glGetUniformLocation(mShaderGeometry.getProgramID(), "texture_diffuse"), 0);


		//modelview = rotate(view,  entity->getPhysicComponent()->getStateComponent()->getRotation()   );
		modelview = translate(view, entity->getPhysicComponent()->getStateComponent()->getPosition());
		glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniformMatrix3fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));

		mRm->getVao( entity->getGraphicComponent()->getVaoId() )->draw();

	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);


	// END OF EACH VAO

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderDeferredFinal.getProgramID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "gNormal"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(1));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "gDiffuse"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "gPosition"), 2);

	glUniformMatrix4fv(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

	glUniform1f(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "time"), time);
	glUniform2fv(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "resolution"), 1, value_ptr(resolution));

	mSupportFbo.draw();



}