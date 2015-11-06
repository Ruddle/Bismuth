#include "RenderSystem.h"

using namespace std;
using namespace glm;

RenderSystem::RenderSystem(Config cfg, ResourcesManager* rm) : mCfg(cfg), mRm(rm), mLastViewProjection(0)
{
	for (int i = 0; i < 4; i++)
		mAttach[i] = GL_COLOR_ATTACHMENT0 + i;  

	TextureCfg texCfgNormal = { GL_RGB16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
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


	TextureCfg texCfgShading = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texShading = new Texture(cfg.ResolutionX , cfg.ResolutionY, texCfgShading);
	texShading->load();
	TextureCfg texCfgShadingBloom = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texShadingBloom = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgShadingBloom);
	texShadingBloom->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texShading);
	textureArray.push_back(texShadingBloom);
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

	TextureCfg texCfgBloom1 = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom1 = new Texture(cfg.ResolutionX / 2.0, cfg.ResolutionY /  2.0, texCfgBloom1);
	texBloom1->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom1);
	mFboBloom1 = Fbo(textureArray, 0, 0);
	mFboBloom1.load();

	TextureCfg texCfgBloom2 = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom2 = new Texture(cfg.ResolutionX / 2.0, cfg.ResolutionY / 2.0, texCfgBloom2);
	texBloom2->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom2);
	mFboBloom2 = Fbo(textureArray, 0, 0);
	mFboBloom2.load();

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

	mShaderAo       = Shader("Shader/defPassN.vert", "Shader/AO2.frag");
	mShaderAo.load();

	mShaderBlurDir = Shader("Shader/defPassN.vert", "Shader/blurDir_3ch.frag");
	mShaderBlurDir.load();

	mShaderBlur = Shader("Shader/defPassN.vert", "Shader/blur_3ch.frag");
	mShaderBlur.load();

	mShaderBlurBilateral = Shader("Shader/defPassN.vert", "Shader/blurBilateral_1ch.frag");
	mShaderBlurBilateral.load();

	mShaderDeferredFinal = Shader("Shader/defPassN.vert", "Shader/defPassN.frag");
	mShaderDeferredFinal.load();

	mShaderTone = Shader("Shader/defPassN.vert", "Shader/tone.frag");
	mShaderTone.load();

	mSupportFbo = Vao2D();
	mSupportFbo.load();


	//Texture de bruit pour l'occlusion ambiante

	std::uniform_real_distribution<GLfloat> randomFloats(-1.0, 1.0);
	std::default_random_engine generator;
	std::vector<glm::vec4> noiseKernel;
	for (GLuint i = 0; i < cfg.ResolutionX*cfg.ResolutionY/16.0 ;  ++i)
	{
		glm::vec4 sample(
			randomFloats(generator) ,
			randomFloats(generator) ,
			randomFloats(generator) / 2.0 + 0.5,
			randomFloats(generator)
			);
		noiseKernel.push_back(sample);
	}

	glGenTextures(1, &mTextureNoiseId);
	glBindTexture(GL_TEXTURE_2D, mTextureNoiseId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, cfg.ResolutionX/4.0, cfg.ResolutionY / 4.0, 0, GL_RGBA, GL_FLOAT, &noiseKernel[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	
	for (GLuint i = 0; i < 64; ++i)
	{
		glm::vec3 sample(
			randomFloats(generator),
			randomFloats(generator),
			randomFloats(generator)
			);
		mKernel.push_back(sample);
	}

}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::draw(std::vector<Entity*> entities,Camera const& cam, float time,Input &input,float fps) {
	time = 0.0f;

	doStepGeometry(cam,entities);
	doStepAo(cam);
	doStepBlurAo();
	doStepShading(cam,input);
	doStepBloom();
	doStepToneMapping();
	doStepMotionBlur(fps);

	mLastViewProjection = cam.getProjection()*cam.getView();
}

void RenderSystem::doStepAo(Camera const &cam)
{
	vec2 resolution = vec2(mCfg.ResolutionX, mCfg.ResolutionY);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboAo.getId());
	if (mCfg.HalfAO == 1)
		glViewport(0, 0, mCfg.ResolutionX / 2.0, mCfg.ResolutionY / 2.0);
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderAo.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(mShaderAo.getLocation( "gPosition"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(0));
	glUniform1i(mShaderAo.getLocation( "gNormal"), 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mTextureNoiseId);
	glUniform1i(mShaderAo.getLocation("noiseSampler"), 2);
	glUniform2fv(mShaderAo.getLocation("resolution"), 1, value_ptr(resolution));

	for (GLuint i = 0; i < 64; ++i)
		glUniform3fv(mShaderAo.getLocation("samples[" + std::to_string(i) + "]"), 1, &mKernel[i][0]);


	

	glUniform1f(mShaderAo.getLocation( "time"), 0);
	glUniformMatrix4fv(mShaderAo.getLocation( "projection"), 1, GL_FALSE, value_ptr(cam.getProjection()));
	glUniform1f(mShaderAo.getLocation( "aspect"), cam.getAspect());
	glUniform1f(mShaderAo.getLocation( "tanHalfFov"), cam.getTanHalfFov());
	glUniform1f(mShaderAo.getLocation( "near"), cam.getNear());
	glUniform1f(mShaderAo.getLocation( "far"), cam.getFar());
	mSupportFbo.draw();
	glViewport(0, 0, mCfg.ResolutionX, mCfg.ResolutionY);
}

void RenderSystem::doStepBlurAo()
{
	vec2 resolution = vec2(mCfg.ResolutionX, mCfg.ResolutionY);
	//Blur AO Horizontal
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurH.getId());
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlurBilateral.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(mShaderBlurBilateral.getLocation( "gPosition"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(0));
	glUniform1i(mShaderBlurBilateral.getLocation( "gNormal"), 1);
	glUniform2fv(mShaderBlurBilateral.getLocation( "resolution"), 1, value_ptr(resolution));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboAo.getColorBufferId(0));
	glUniform1i(mShaderBlurBilateral.getLocation( "image"), 0);
	glUniform1i(mShaderBlurBilateral.getLocation( "h"), 1);
	glUniform1f(mShaderBlurBilateral.getLocation( "size"), 0);
	mSupportFbo.draw();

	//Blur AO Vertical
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurV.getId());
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBlurH.getColorBufferId(0));
	glUniform1i(mShaderBlurBilateral.getLocation( "image"), 0);
	glUniform1i(mShaderBlurBilateral.getLocation( "h"), 0);
	glUniform1f(mShaderBlurBilateral.getLocation( "size"), 0);
	mSupportFbo.draw();

	int nombreDePasseBlurAo = 4;
	for (int i = 1; i < nombreDePasseBlurAo; i++) {
		//Blur AO Horizontal
		glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurH.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBlurV.getColorBufferId(0));
		glUniform1i(mShaderBlurBilateral.getLocation( "h"), 1);
		glUniform1i(mShaderBlurBilateral.getLocation( "image"), 0);
		glUniform1f(mShaderBlurBilateral.getLocation( "size"), 3.0* (float)i / (float)nombreDePasseBlurAo);
		mSupportFbo.draw();

		//Blur AO Vertical
		glBindFramebuffer(GL_FRAMEBUFFER, mFboBlurV.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBlurH.getColorBufferId(0));
		glUniform1i(mShaderBlurBilateral.getLocation( "h"), 0);
		glUniform1i(mShaderBlurBilateral.getLocation( "image"), 0);
		glUniform1f(mShaderBlurBilateral.getLocation( "size"), 3.0* (float)i / (float)nombreDePasseBlurAo);
		mSupportFbo.draw();
	}
}

void RenderSystem::doStepBloom()
{
	vec2 resolution_2 = vec2(mCfg.ResolutionX / 2.0f, mCfg.ResolutionY / 2.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom1.getId());
	glViewport(0, 0, mCfg.ResolutionX / 2.0, mCfg.ResolutionY / 2.0);
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(1));
	glUniform1i(mShaderBlur.getLocation("image"), 0);

	glUniform1i(mShaderBlur.getLocation( "h"), 1);
	glUniform1f(mShaderBlur.getLocation( "size"), 0);
	glUniform2fv(mShaderBlur.getLocation( "resolution"), 1,
		value_ptr(resolution_2));
	mSupportFbo.draw();

	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom2.getId());
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBloom1.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation( "image"), 0);

	glUniform1i(mShaderBlur.getLocation( "h"), 0);
	glUniform1f(mShaderBlur.getLocation( "size"), 0);
	glUniform2fv(mShaderBlur.getLocation( "resolution"), 1,
		value_ptr(resolution_2));
	mSupportFbo.draw();

	int nombreDePasseBlurBloom = 5;
	for (int i = 1; i < nombreDePasseBlurBloom; i++) {
		float size = 0 * float(i) / nombreDePasseBlurBloom;

		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom1.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom2.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation( "image"), 0);

		glUniform1i(mShaderBlur.getLocation( "h"), 1);
		glUniform1f(mShaderBlur.getLocation( "size"), size);
		glUniform2fv(mShaderBlur.getLocation( "resolution"), 1,
			value_ptr(resolution_2));
		mSupportFbo.draw();


		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom2.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom1.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation( "image"), 0);

		glUniform1i(mShaderBlur.getLocation( "h"), 0);
		glUniform1f(mShaderBlur.getLocation( "size"), size);
		glUniform2fv(mShaderBlur.getLocation( "resolution"), 1,
			value_ptr(resolution_2));
		mSupportFbo.draw();
	}
	glViewport(0, 0, mCfg.ResolutionX, mCfg.ResolutionY);

}

void RenderSystem::doStepMotionBlur(float fps)
{
	vec2 resolution = vec2(mCfg.ResolutionX, mCfg.ResolutionY);

	//Motion Blur 1
	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading.getId());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlurDir.getProgramID());
	glUniform1f(mShaderBlurDir.getLocation("factor"), (fps / 60.0) * 300 );

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading2.getColorBufferId(0));
	glUniform1i(mShaderBlurDir.getLocation("image"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(3));
	glUniform1i(mShaderBlurDir.getLocation("speed"), 1);

	glUniform2fv(mShaderBlurDir.getLocation("resolution"), 1, value_ptr(resolution));
	glUniform1f(mShaderBlurDir.getLocation("size"), 0.0);
	mSupportFbo.draw();


	//Motion Blur 2
	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading2.getId());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlurDir.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(0));
	glUniform1f(mShaderBlurDir.getLocation("size"), 0.0);
	mSupportFbo.draw();


	//Motion Blur 3
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderBlurDir.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading2.getColorBufferId(0));
	glUniform1f(mShaderBlurDir.getLocation("size"), 0.0);
	mSupportFbo.draw();
}

void RenderSystem::doStepToneMapping()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading2.getId());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderTone.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(0));
	glUniform1i(mShaderTone.getLocation("imageSampler"),0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboBloom2.getColorBufferId(0));
	glUniform1i(mShaderTone.getLocation("bloomSampler"), 1);
	mSupportFbo.draw();
}

void RenderSystem::doStepShading(Camera const& cam,Input const& input)
{

	vec2 resolution = vec2(mCfg.ResolutionX, mCfg.ResolutionY);
	vec2 resolution_2 = vec2(mCfg.ResolutionX / 2.0f, mCfg.ResolutionY / 2.0f);
	mat4 projection = cam.getProjection();
	mat4 view = cam.getView();

	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading.getId());
	glDrawBuffers(2, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderDeferredFinal.getProgramID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(0));
	glUniform1i(mShaderDeferredFinal.getLocation("gNormal"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(1));
	glUniform1i(mShaderDeferredFinal.getLocation("gDiffuse"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mFboGeometry.getColorBufferId(2));
	glUniform1i(mShaderDeferredFinal.getLocation("gPosition"), 2);

	glUniform1f(mShaderDeferredFinal.getLocation("aspect"), cam.getAspect());
	glUniform1f(mShaderDeferredFinal.getLocation("tanHalfFov"), cam.getTanHalfFov());
	glUniform1f(mShaderDeferredFinal.getLocation("near"), cam.getNear());
	glUniform1f(mShaderDeferredFinal.getLocation("far"), cam.getFar());

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, !input.getKey(SDL_SCANCODE_F5) ? mFboBlurV.getColorBufferId(0) : mFboAo.getColorBufferId(0));
	glUniform1i(mShaderDeferredFinal.getLocation("aoSampler"), 3);

	glUniformMatrix4fv(mShaderDeferredFinal.getLocation("projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(mShaderDeferredFinal.getLocation("view"), 1, GL_FALSE, value_ptr(view));
	glUniform1f(mShaderDeferredFinal.getLocation("time"), 0);
	glUniform1i(mShaderDeferredFinal.getLocation("keyF1"), input.getKey(SDL_SCANCODE_F1));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF2"), input.getKey(SDL_SCANCODE_F2));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF3"), input.getKey(SDL_SCANCODE_F3));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF4"), input.getKey(SDL_SCANCODE_F4));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF5"), input.getKey(SDL_SCANCODE_F5));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF6"), input.getKey(SDL_SCANCODE_F6));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF7"), input.getKey(SDL_SCANCODE_F7));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF8"), input.getKey(SDL_SCANCODE_F8));
	glUniform1i(mShaderDeferredFinal.getLocation("keyF9"), input.getKey(SDL_SCANCODE_F9));
	glUniform2fv(mShaderDeferredFinal.getLocation("resolution"), 1, value_ptr(resolution));
	mSupportFbo.draw();
}

void RenderSystem::doStepGeometry(Camera const &cam, std::vector<Entity*> entities)
{
	vec2 resolution = vec2(mCfg.ResolutionX, mCfg.ResolutionY);
	vec2 resolution_2 = vec2(mCfg.ResolutionX / 2.0f, mCfg.ResolutionY / 2.0f);
	mat4 projection = cam.getProjection();
	mat4 view = cam.getView();
	mat4 modelview;
	mat4 lastModel;

	glViewport(0, 0, mCfg.ResolutionX, mCfg.ResolutionY);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboGeometry.getId());
	glDrawBuffers(4, mAttach);
	glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderGeometry.getProgramID());

	glUniformMatrix4fv(mShaderGeometry.getLocation("projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(mShaderGeometry.getLocation("lastViewProjection"), 1, GL_FALSE, value_ptr(mLastViewProjection));
	glUniform2fv(mShaderGeometry.getLocation("resolution"), 1, value_ptr(resolution));

	for (int i = 0; i < entities.size(); i++) {

		Entity* entity = entities[i];
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (mRm->getTexture(entity->getGraphicComponent()->getTextureDiffuseId())->getId()));
		glUniform1i(mShaderGeometry.getLocation("texture_diffuse"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, (mRm->getTexture(entity->getGraphicComponent()->getTextureNormalId())->getId()));
		glUniform1i(mShaderGeometry.getLocation("texture_normal"), 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, (mRm->getTexture(entity->getGraphicComponent()->getTextureSpecId())->getId()));
		glUniform1i(mShaderGeometry.getLocation("texture_spec"), 2);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, (mRm->getTexture(entity->getGraphicComponent()->getTextureEmitId())->getId()));
		glUniform1i(mShaderGeometry.getLocation("texture_emit"), 3);

		modelview = view*entity->getPhysicComponent()->getStateComponent()->getModel();
		lastModel = entity->getPhysicComponent()->getStateComponent()->getLastModel();
		glUniformMatrix4fv(mShaderGeometry.getLocation("modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniformMatrix4fv(mShaderGeometry.getLocation("lastModel"), 1, GL_FALSE, value_ptr(lastModel));
		glUniformMatrix3fv(mShaderGeometry.getLocation("normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));
		mRm->getVao(entity->getGraphicComponent()->getVaoId())->draw();
	}

}
