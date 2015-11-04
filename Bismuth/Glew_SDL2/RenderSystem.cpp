#include "RenderSystem.h"

using namespace std;
using namespace glm;

RenderSystem::RenderSystem(Config cfg, ResourcesManager* rm) : mCfg(cfg), mRm(rm), mLastViewProjection(0)
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
	TextureCfg texCfgSpeed = { GL_RG16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texSpeed = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgSpeed);
	texSpeed->load();
	vector<Texture*> textureArray = vector<Texture*>();
	textureArray.push_back(texNormal);
	textureArray.push_back(texDiffuse);
	textureArray.push_back(texPosition);
	textureArray.push_back(texSpeed);
	mFboGeometry= Fbo(textureArray, 1, 0);
	mFboGeometry.load();


	TextureCfg texCfgShading = { GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texShading = new Texture(cfg.ResolutionX , cfg.ResolutionY, texCfgShading);
	texShading->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texShading);
	mFboShading = Fbo(textureArray, 0, 0);
	mFboShading.load();


	TextureCfg texCfgShading2 = { GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texShading2 = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgShading2);
	texShading2->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texShading2);
	mFboShading2 = Fbo(textureArray, 0, 0);
	mFboShading2.load();



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

	mShaderBlur = Shader("Shader/defPassN.vert", "Shader/blurDir_3ch.frag");
	mShaderBlur.load();

	mShaderBlurBilateral = Shader("Shader/defPassN.vert", "Shader/blurBilateral_1ch.frag");
	mShaderBlurBilateral.load();

	mShaderDeferredFinal = Shader("Shader/defPassN.vert", "Shader/defPassN.frag");
	mShaderDeferredFinal.load();

	mSupportFbo = Vao2D();
	mSupportFbo.load();
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::draw(std::vector<Entity*> entities,Camera const& cam, float time,Input &input,float fps) {
	time = 0.0f;
	GLuint attachments[4] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 ,GL_COLOR_ATTACHMENT2 ,GL_COLOR_ATTACHMENT3 };

	vec2 resolution = vec2(mCfg.ResolutionX, mCfg.ResolutionY);
	mat4 projection = cam.getProjection();
	mat4 view = cam.getView();
	mat4 modelview;
	mat4 lastModel;

	glViewport(0, 0, mCfg.ResolutionX, mCfg.ResolutionY);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboGeometry.getId());
	glDrawBuffers(4, attachments);
	glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderGeometry.getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "lastViewProjection"), 1, GL_FALSE, value_ptr(mLastViewProjection));
	glUniform2fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "resolution"), 1, value_ptr(resolution));
	
	for (int i = 0; i < entities.size(); i++) {

		Entity* entity = entities[i];
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ( mRm->getTexture(       entity->getGraphicComponent()->getTextureDiffuseId()    )->getId()  )   );
		glUniform1i(glGetUniformLocation(mShaderGeometry.getProgramID(), "texture_diffuse"), 0);
		modelview = view*entity->getPhysicComponent()->getStateComponent()->getModel();
		lastModel = entity->getPhysicComponent()->getStateComponent()->getLastModel();
		glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniformMatrix4fv(glGetUniformLocation(mShaderGeometry.getProgramID(), "lastModel"), 1, GL_FALSE, value_ptr(lastModel));
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
	glUseProgram(mShaderBlurBilateral.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "gPosition"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "gNormal"), 1);
	glUniform2fv(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "resolution"), 1, value_ptr(resolution));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboAo.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "image"), 0);
	glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "h"), 1);
	glUniform1f(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "size"), 0);
	mSupportFbo.draw();

	//Blur AO Vertical
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurV.getId());
	glDrawBuffers(1, attachments);
	glClear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBlurH.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "image"), 0);
	glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "h"), 0);
	glUniform1f(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "size"), 0);
	mSupportFbo.draw();

	int nombreDePasseBlur = 7;
	for (int i = 1; i < nombreDePasseBlur; i++) {
		//Blur AO Horizontal
		glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurH.getId());
		glDrawBuffers(1, attachments);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBlurV.getColorBufferId(0));
		glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "h"), 1);
		glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "image"), 0);
		glUniform1f(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "size"),3.0* (float) i/ (float)nombreDePasseBlur );
		mSupportFbo.draw();

		//Blur AO Vertical
		glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurV.getId());
		glDrawBuffers(1, attachments);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBlurH.getColorBufferId(0));
		glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "h"), 0);
		glUniform1i(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "image"), 0);
		glUniform1f(glGetUniformLocation(mShaderBlurBilateral.getProgramID(), "size"),3.0* (float)i / (float)nombreDePasseBlur );
		mSupportFbo.draw();
	}

	//Shading
	
	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading.getId());
	glDrawBuffers(1, attachments);
	glClear(GL_COLOR_BUFFER_BIT);
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

	glUniform1f(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "aspect"), cam.getAspect());
	glUniform1f(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "tanHalfFov"), cam.getTanHalfFov());
	glUniform1f(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "near"), cam.getNear());
	glUniform1f(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "far"), cam.getFar());


	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, !input.getKey(SDL_SCANCODE_F5) ? mFboBlurV.getColorBufferId(0) : mFboAo.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "aoSampler"), 3);

	glUniformMatrix4fv(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniform1f(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "time"), time);
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF1"), input.getKey(SDL_SCANCODE_F1));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF2"), input.getKey(SDL_SCANCODE_F2));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF3"), input.getKey(SDL_SCANCODE_F3));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF4"), input.getKey(SDL_SCANCODE_F4));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF5"), input.getKey(SDL_SCANCODE_F5));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF6"), input.getKey(SDL_SCANCODE_F6));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF7"), input.getKey(SDL_SCANCODE_F7));
	glUniform1i(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "keyF8"), input.getKey(SDL_SCANCODE_F8));
	glUniform2fv(glGetUniformLocation(mShaderDeferredFinal.getProgramID(), "resolution"), 1, value_ptr(resolution));

	mSupportFbo.draw();



	//Motion Blur 1
	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading2.getId());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glUniform1f(glGetUniformLocation(mShaderBlur.getProgramID(), "factor"), (fps/60.0)*300*(float)(!input.getKey(SDL_SCANCODE_F6)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(0));
	glUniform1i(glGetUniformLocation(mShaderBlur.getProgramID(), "image"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(3));
	glUniform1i(glGetUniformLocation(mShaderBlur.getProgramID(), "speed"), 1);

	glUniform2fv(glGetUniformLocation(mShaderBlur.getProgramID(), "resolution"), 1, value_ptr(resolution));
	glUniform1f(glGetUniformLocation(mShaderBlur.getProgramID(), "size"), 0.0);
	mSupportFbo.draw();


	//Motion Blur 2
	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading.getId());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading2.getColorBufferId(0));
	glUniform1f(glGetUniformLocation(mShaderBlur.getProgramID(), "size"), 0.0);
	mSupportFbo.draw();


	//Motion Blur 3
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(0));
	glUniform1f(glGetUniformLocation(mShaderBlur.getProgramID(), "size"), 0.0);
	mSupportFbo.draw();




	mLastViewProjection = projection*view  ;
}