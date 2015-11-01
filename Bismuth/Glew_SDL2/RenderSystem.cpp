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
	TextureCfg texCfgPosition = { GL_R32F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texPosition = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgPosition);
	texPosition->load();
	vector<Texture*> textureArray = vector<Texture*>();
	textureArray.push_back(texNormal);
	textureArray.push_back(texDiffuse);
	textureArray.push_back(texPosition);
	mFboGeometry= Fbo(textureArray, 1, 0);
	mFboGeometry.load();

	TextureCfg texCfgAo = { GL_R8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texAo = new Texture(cfg.ResolutionX/(cfg.HalfAO ? 2.0:1.0) , cfg.ResolutionY/ (cfg.HalfAO ? 2.0 : 1.0), texCfgAo);
	texAo->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texAo);
	mFboAo = Fbo(textureArray, 0, 0);
	mFboAo.load();

	TextureCfg texCfgBlurH = { GL_R8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBlurH = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgBlurH);
	texBlurH->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBlurH);
	mFboBlurH = Fbo(textureArray, 0, 0);
	mFboBlurH.load();

	TextureCfg texCfgBlurV = { GL_R8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBlurV = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgBlurV);
	texBlurV->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBlurV);
	mFboBlurV = Fbo(textureArray, 0, 0);
	mFboBlurV.load();

	mShaderGeometry = Shader("Shader/defPass1.vert", "Shader/defPass1.frag") ;
	mShaderGeometry.load();

	mShaderAo       = Shader("Shader/defPassN.vert", "Shader/AO.frag");
	mShaderAo.load();

	mShaderBlurH = Shader("Shader/defPassN.vert", "Shader/blurH_1ch.frag");
	mShaderBlurH.load();

	mShaderBlurV = Shader("Shader/defPassN.vert", "Shader/blurV_1ch.frag");
	mShaderBlurV.load();

	mShaderDeferredFinal = Shader("Shader/defPassN.vert", "Shader/defPassN.frag");
	mShaderDeferredFinal.load();

	mShaderDeferredFinalDebug = Shader("Shader/defPassN.vert", "Shader/defPassN.frag");
	mShaderDeferredFinalDebug.load();

	mSupportFbo = Vao2D();
	mSupportFbo.load();
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::draw(std::vector<Entity*> entities,Camera const& cam, float time,Input &input) {
	time = 0;
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
		modelview = view*entity->getPhysicComponent()->getStateComponent()->getModel();
		glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniformMatrix3fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));
		mRm->getVao( entity->getGraphicComponent()->getVaoId() )->draw();
	}




	//Dessin intermédiaire (effect : AO ,SHADOW, MOTION BLUR, BLUR )
	
	//AO
	glBindFramebuffer(GL_FRAMEBUFFER, mFboAo.getId());
	if(mCfg.HalfAO==1 )
	glViewport(0, 0, mCfg.ResolutionX/2.0, mCfg.ResolutionY/2.0);
	glDrawBuffers(1, attachments);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderAo.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(glGetUniformLocation(mShaderAo.getProgramID(), "gPosition"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderAo.getProgramID(), "gNormal"), 1);
	glUniform1f(glGetUniformLocation(mShaderAo.getProgramID(), "time"), time);
	glUniformMatrix4fv(glGetUniformLocation(mShaderAo.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform1f(glGetUniformLocation(mShaderAo.getProgramID(), "aspect"), cam.getAspect());
	glUniform1f(glGetUniformLocation(mShaderAo.getProgramID(), "tanHalfFov"), cam.getTanHalfFov());
	glUniform1f(glGetUniformLocation(mShaderAo.getProgramID(), "near"), cam.getNear());
	glUniform1f(glGetUniformLocation(mShaderAo.getProgramID(), "far"), cam.getFar());
	mSupportFbo.draw();

	//Blur AO Horizontal
	glViewport(0, 0, mCfg.ResolutionX, mCfg.ResolutionY);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurH.getId());
	glDrawBuffers(1, attachments);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlurH.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboAo.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderBlurH.getProgramID(), "image"), 0);
	glUniform1f(glGetUniformLocation(mShaderBlurH.getProgramID(), "size"), 0);
	glUniform2fv(glGetUniformLocation(mShaderBlurH.getProgramID(), "resolution"), 1, value_ptr(resolution));
	mSupportFbo.draw();

	//Blur AO Vertical
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurV.getId());
	glDrawBuffers(1, attachments);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlurV.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBlurH.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderBlurV.getProgramID(), "image"), 0);
	glUniform1f(glGetUniformLocation(mShaderBlurV.getProgramID(), "size"), 0);
	glUniform2fv(glGetUniformLocation(mShaderBlurV.getProgramID(), "resolution"), 1, value_ptr(resolution));
	mSupportFbo.draw();

	int nombreDePasseBlur = 10;
	for (int i = 1; i < nombreDePasseBlur; i++) {
		//Blur AO Horizontal
		glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurH.getId());
		glDrawBuffers(1, attachments);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlurH.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBlurV.getColorBufferId(0));
		glUniform1i(glGetUniformLocation(mShaderBlurH.getProgramID(), "image"), 0);
		glUniform1f(glGetUniformLocation(mShaderBlurH.getProgramID(), "size"),3.0* (float) i/ (float)nombreDePasseBlur );
		mSupportFbo.draw();

		//Blur AO Vertical
		glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurV.getId());
		glDrawBuffers(1, attachments);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlurV.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBlurH.getColorBufferId(0));
		glUniform1i(glGetUniformLocation(mShaderBlurV.getProgramID(), "image"), 0);
		glUniform1f(glGetUniformLocation(mShaderBlurV.getProgramID(), "size"),3.0* (float)i / (float)nombreDePasseBlur );
		mSupportFbo.draw();
	}


	//Dessin final, sur l'écran
	GLuint selectedFinalShader = input.getKey(SDL_SCANCODE_F3) ? mShaderDeferredFinalDebug.getProgramID() : mShaderDeferredFinal.getProgramID();
	
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

	glUniform1f(glGetUniformLocation(selectedFinalShader, "aspect"), cam.getAspect());
	glUniform1f(glGetUniformLocation(selectedFinalShader, "tanHalfFov"), cam.getTanHalfFov());
	glUniform1f(glGetUniformLocation(selectedFinalShader, "near"), cam.getNear());
	glUniform1f(glGetUniformLocation(selectedFinalShader, "far"), cam.getFar());


	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, !input.getKey(SDL_SCANCODE_F6) ? mFboBlurV.getColorBufferId(0) : mFboAo.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "aoSampler"), 3);

	glUniformMatrix4fv(glGetUniformLocation(selectedFinalShader, "projection"), 1, GL_FALSE, value_ptr(projection));

	
	glUniformMatrix4fv(glGetUniformLocation(selectedFinalShader, "view"), 1, GL_FALSE, value_ptr(view));


	glUniform1f(glGetUniformLocation(selectedFinalShader, "time"), time);
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF1"), input.getKey(SDL_SCANCODE_F1));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF2"), input.getKey(SDL_SCANCODE_F2));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF3"), input.getKey(SDL_SCANCODE_F3));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF4"), input.getKey(SDL_SCANCODE_F4));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF5"), input.getKey(SDL_SCANCODE_F5));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF6"), input.getKey(SDL_SCANCODE_F6));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF7"), input.getKey(SDL_SCANCODE_F7));
	glUniform1i(glGetUniformLocation(selectedFinalShader, "keyF8"), input.getKey(SDL_SCANCODE_F8));

	glUniform2fv(glGetUniformLocation(selectedFinalShader, "resolution"), 1, value_ptr(resolution));

	mSupportFbo.draw();
}