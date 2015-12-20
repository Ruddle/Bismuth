#include "RenderSystem.h"

using namespace std;
using namespace glm;

RenderSystem::RenderSystem(Config* cfg, ResourcesManager* rm) : mCfg(cfg), mRm(rm), mLastViewProjection(0)
{
	for (int i = 0; i < 4; i++)
		mAttach[i] = GL_COLOR_ATTACHMENT0 + i;  

	TextureCfg texCfgNormal = { GL_RGB16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texNormal = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgNormal);
	texNormal->load();
	TextureCfg texCfgDiffuse = { GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texDiffuse = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgDiffuse);
	texDiffuse->load();
	TextureCfg texCfgPosition = { GL_R32F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texPosition = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgPosition);
	texPosition->load();
	TextureCfg texCfgSpeed = { GL_RG16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texSpeed = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgSpeed);
	texSpeed->load();
	vector<Texture*> textureArray = vector<Texture*>();
	textureArray.push_back(texNormal);
	textureArray.push_back(texDiffuse);
	textureArray.push_back(texPosition);
	textureArray.push_back(texSpeed);
	mFboGeometry= Fbo(textureArray, 1, 0);
	mFboGeometry.load();


	TextureCfg texCfgShading = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texShading = new Texture(cfg->ResolutionX , cfg->ResolutionY, texCfgShading);
	texShading->load();
	TextureCfg texCfgShadingBloom = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texShadingBloom = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgShadingBloom);
	texShadingBloom->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texShading);
	textureArray.push_back(texShadingBloom);
	mFboShading = Fbo(textureArray, 0, 0);
	mFboShading.load();


	TextureCfg texCfgShading2 = { GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texShading2 = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgShading2);
	texShading2->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texShading2);
	mFboShading2 = Fbo(textureArray, 0, 0);
	mFboShading2.load();


	TextureCfg texCfgAo = { GL_R8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texAo = new Texture(cfg->ResolutionX/(cfg->HalfAO ? 2.0:1.0) , cfg->ResolutionY/ (cfg->HalfAO ? 2.0 : 1.0), texCfgAo);
	texAo->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texAo);
	mFboAo = Fbo(textureArray, 0, 0);
	mFboAo.load();


	TextureCfg texCfgLight = { GL_R32F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texLight = new Texture(1024*4, 1024*4, texCfgLight);
	texLight->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texLight);
	mFboLight = Fbo(textureArray, 1, 0);
	mFboLight.load();

	TextureCfg texCfgSkybox = { GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	mCubemapSkybox = new Texture_Cube("Texture/Skybox/purple-nebula/n.png", texCfgSkybox);
	mCubemapSkybox->load();

	//BLOOM 
	TextureCfg texCfgBloom_2_h = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_2_h = new Texture(cfg->ResolutionX / 2.0, cfg->ResolutionY /  2.0, texCfgBloom_2_h);
	texBloom_2_h->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_2_h);
	mFboBloom_2_h = Fbo(textureArray, 0, 0);
	mFboBloom_2_h.load();

	TextureCfg texCfgBloom_2_v = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_2_v = new Texture(cfg->ResolutionX / 2.0, cfg->ResolutionY / 2.0, texCfgBloom_2_v);
	texBloom_2_v->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_2_v);
	mFboBloom_2_v = Fbo(textureArray, 0, 0);
	mFboBloom_2_v.load();

	TextureCfg texCfgBloom_8_h = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_8_h = new Texture(cfg->ResolutionX / 8.0, cfg->ResolutionY / 8.0, texCfgBloom_8_h);
	texBloom_8_h->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_8_h);
	mFboBloom_8_h = Fbo(textureArray, 0, 0);
	mFboBloom_8_h.load();

	TextureCfg texCfgBloom_8_v = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_8_v = new Texture(cfg->ResolutionX / 8.0, cfg->ResolutionY / 8.0, texCfgBloom_8_v);
	texBloom_8_v->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_8_v);
	mFboBloom_8_v = Fbo(textureArray, 0, 0);
	mFboBloom_8_v.load();

	TextureCfg texCfgBloom_16_h = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_16_h = new Texture(cfg->ResolutionX / 16.0, cfg->ResolutionY / 16.0, texCfgBloom_16_h);
	texBloom_16_h->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_16_h);
	mFboBloom_16_h = Fbo(textureArray, 0, 0);
	mFboBloom_16_h.load();

	TextureCfg texCfgBloom_16_v = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_16_v = new Texture(cfg->ResolutionX / 16.0, cfg->ResolutionY / 16.0, texCfgBloom_16_v);
	texBloom_16_v->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_16_v);
	mFboBloom_16_v = Fbo(textureArray, 0, 0);
	mFboBloom_16_v.load();

	TextureCfg texCfgBloom_32_h = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_32_h = new Texture(cfg->ResolutionX / 32.0, cfg->ResolutionY / 32.0, texCfgBloom_32_h);
	texBloom_32_h->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_32_h);
	mFboBloom_32_h = Fbo(textureArray, 0, 0);
	mFboBloom_32_h.load();

	TextureCfg texCfgBloom_32_v = { GL_RGB16F, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBloom_32_v = new Texture(cfg->ResolutionX / 32.0, cfg->ResolutionY / 32.0, texCfgBloom_32_v);
	texBloom_32_v->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBloom_32_v);
	mFboBloom_32_v = Fbo(textureArray, 0, 0);
	mFboBloom_32_v.load();




	//AO BLUR or any 1 channel stuff
	TextureCfg texCfgBlurH = { GL_R8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBlurH = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgBlurH);
	texBlurH->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBlurH);
	mFboBlurH = Fbo(textureArray, 0, 0);
	mFboBlurH.load();

	TextureCfg texCfgBlurV = { GL_R8, GL_LINEAR, GL_CLAMP_TO_EDGE };
	Texture* texBlurV = new Texture(cfg->ResolutionX, cfg->ResolutionY, texCfgBlurV);
	texBlurV->load();
	textureArray = vector<Texture*>();
	textureArray.push_back(texBlurV);
	mFboBlurV = Fbo(textureArray, 0, 0);
	mFboBlurV.load();

	mShaderGeometry = Shader("Shader/defPass1.vert", "Shader/defPass1.frag") ;
	mShaderGeometry.load();

	mShaderAo       = Shader("Shader/defPassN.vert", "Shader/AO2.frag");
	mShaderAo.load();

	mShaderLight = Shader("Shader/light.vert", "Shader/light.frag");
	mShaderLight.load();

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

	mShaderFXAA = Shader("Shader/defPassN.vert", "Shader/FXAA.frag");
	mShaderFXAA.load();

	mShader2D = Shader("Shader/2D.vert", "Shader/2D.frag");
	mShader2D.load();

	mSupportFbo = Vao2D();
	mSupportFbo.load();




	//Texture de bruit pour l'occlusion ambiante

	std::uniform_real_distribution<GLfloat> randomFloats(-1.0, 1.0);
	std::default_random_engine generator;
	std::vector<glm::vec4> noiseKernel;
	for (GLuint i = 0; i < cfg->ResolutionX*cfg->ResolutionY/16.0 ;  ++i)
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, cfg->ResolutionX/4.0, cfg->ResolutionY / 4.0, 0, GL_RGBA, GL_FLOAT, &noiseKernel[0]);
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
	delete mCubemapSkybox;
}


void RenderSystem::draw(std::vector<Entity*> entities,Camera const& cam, float time,Input &input,float fps) {


	Camera cam2 = Camera(70, 1.0, 100, 300);
	cam2.setPosition(vec3(-100, -40, 100));
	cam2.setRotation(-cam2.getPosition());


	doStepGeometry(cam,entities);
	doStepLight(cam2, entities);
	if (mCfg->AO == 1) 
	{
		doStepAo(cam);
		doStepBlurAo();
	}

	doStepShading(cam,cam2,input);
	doStepBloom();
	doStepToneMapping();
	doStepMotionBlur(fps);
	doStepFXAA(time);

	mLastViewProjection = cam.getProjection()*cam.getView();
}


void RenderSystem::draw2D(std::vector<Entity2D*> entities)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(mShader2D.getProgramID());
	glEnable(GL_BLEND);
	for (int i = 0; i < entities.size(); i++) {

		Entity2D* entity = entities[i];

		if (entity != nullptr)
		{
			mat4 view = translate(
							vec3(entity->getPhysicComponent()->getPosition()+ 
								vec2(entity->getPhysicComponent()->getSize()/2.0f)        ,0)) 
						*
						scale(vec3(entity->getPhysicComponent()->getSize()/2.0f,1));

		
		

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, (mRm->getTexture(entity->getGraphicComponent()->getTextureDiffuseId())->getId()));
			glUniform1i(mShaderGeometry.getLocation("texture_diffuse"), 0);

			glUniformMatrix4fv(mShader2D.getLocation("view"), 1, GL_FALSE, value_ptr(view));
		
			mat4 toUV = translate(vec3(entity->getGraphicComponent()->getLeftBottom(), 0)) * scale(vec3(entity->getGraphicComponent()->getSize(), 1));
			glUniformMatrix4fv(mShader2D.getLocation("toUV"), 1, GL_FALSE, value_ptr(toUV));
			
			mSupportFbo.draw();
		}
	}
	glEnable(GL_DEPTH_TEST);
}

void RenderSystem::doStepAo(Camera const &cam)
{
	vec2 resolution = vec2(mCfg->ResolutionX, mCfg->ResolutionY);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboAo.getId());
	if (mCfg->HalfAO == 1)
		glViewport(0, 0, mCfg->ResolutionX / 2.0, mCfg->ResolutionY / 2.0);
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
	glViewport(0, 0, mCfg->ResolutionX, mCfg->ResolutionY);
}

void RenderSystem::doStepBlurAo()
{
	vec2 resolution = vec2(mCfg->ResolutionX, mCfg->ResolutionY);
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

	int nombreDePasseBlurAo = 7;
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
	int nombreDePasseBlurBloom = 4;
	int nombreDePasseBlurBloom8 = 4;
	int nombreDePasseBlurBloom16 = 4;
	int nombreDePasseBlurBloom32 = 4;
	vec2 resolution_2 = vec2(mCfg->ResolutionX / 2.0f, mCfg->ResolutionY / 2.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_2_h.getId());
	glViewport(0, 0, mCfg->ResolutionX / 2.0, mCfg->ResolutionY / 2.0);
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

	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_2_v.getId());
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBloom_2_h.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation( "image"), 0);

	glUniform1i(mShaderBlur.getLocation( "h"), 0);
	glUniform1f(mShaderBlur.getLocation( "size"), 0);
	glUniform2fv(mShaderBlur.getLocation( "resolution"), 1,
		value_ptr(resolution_2));
	mSupportFbo.draw();

	
	for (int i = 1; i < nombreDePasseBlurBloom; i++) {
		float size = 0 * float(i) / nombreDePasseBlurBloom;

		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_2_h.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_2_v.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation( "image"), 0);

		glUniform1i(mShaderBlur.getLocation( "h"), 1);
		glUniform1f(mShaderBlur.getLocation( "size"), size);
		glUniform2fv(mShaderBlur.getLocation( "resolution"), 1,
			value_ptr(resolution_2));
		mSupportFbo.draw();


		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_2_v.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_2_h.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation( "image"), 0);

		glUniform1i(mShaderBlur.getLocation( "h"), 0);
		glUniform1f(mShaderBlur.getLocation( "size"), size);
		glUniform2fv(mShaderBlur.getLocation( "resolution"), 1,
			value_ptr(resolution_2));
		mSupportFbo.draw();
	}




	// HUITEME DE RESOLUTION

	vec2 resolution_8 = vec2(mCfg->ResolutionX / 8.0f, mCfg->ResolutionY / 8.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_8_h.getId());
	glViewport(0, 0, mCfg->ResolutionX / 8.0, mCfg->ResolutionY / 8.0);
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(1));
	glBindTexture(GL_TEXTURE_2D, mFboBloom_2_v.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation("image"), 0);

	glUniform1i(mShaderBlur.getLocation("h"), 1);
	glUniform1f(mShaderBlur.getLocation("size"), 0);
	glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
		value_ptr(resolution_8));
	mSupportFbo.draw();

	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_8_v.getId());
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBloom_8_h.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation("image"), 0);

	glUniform1i(mShaderBlur.getLocation("h"), 0);
	glUniform1f(mShaderBlur.getLocation("size"), 0);
	glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
		value_ptr(resolution_8));
	mSupportFbo.draw();


	for (int i = 1; i < nombreDePasseBlurBloom8; i++) {
		float size = 0 * float(i) / nombreDePasseBlurBloom8;

		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_8_h.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_8_v.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation("image"), 0);

		glUniform1i(mShaderBlur.getLocation("h"), 1);
		glUniform1f(mShaderBlur.getLocation("size"), size);
		glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
			value_ptr(resolution_8));
		mSupportFbo.draw();


		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_8_v.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_8_h.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation("image"), 0);

		glUniform1i(mShaderBlur.getLocation("h"), 0);
		glUniform1f(mShaderBlur.getLocation("size"), size);
		glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
			value_ptr(resolution_8));
		mSupportFbo.draw();
	}


	// 16 DE RESOLUTION

	vec2 resolution_16 = vec2(mCfg->ResolutionX / 16.0f, mCfg->ResolutionY / 16.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_16_h.getId());
	glViewport(0, 0, mCfg->ResolutionX / 16.0, mCfg->ResolutionY / 16.0);
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(1));
	glBindTexture(GL_TEXTURE_2D, mFboBloom_8_v.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation("image"), 0);

	glUniform1i(mShaderBlur.getLocation("h"), 1);
	glUniform1f(mShaderBlur.getLocation("size"), 0);
	glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
		value_ptr(resolution_16));
	mSupportFbo.draw();

	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_16_v.getId());
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBloom_16_h.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation("image"), 0);

	glUniform1i(mShaderBlur.getLocation("h"), 0);
	glUniform1f(mShaderBlur.getLocation("size"), 0);
	glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
		value_ptr(resolution_16));
	mSupportFbo.draw();

	
	for (int i = 1; i < nombreDePasseBlurBloom16; i++) {
		float size = 0 * float(i) / nombreDePasseBlurBloom16;

		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_16_h.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_16_v.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation("image"), 0);

		glUniform1i(mShaderBlur.getLocation("h"), 1);
		glUniform1f(mShaderBlur.getLocation("size"), size);
		glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
			value_ptr(resolution_16));
		mSupportFbo.draw();


		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_16_v.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_16_h.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation("image"), 0);

		glUniform1i(mShaderBlur.getLocation("h"), 0);
		glUniform1f(mShaderBlur.getLocation("size"), size);
		glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
			value_ptr(resolution_16));
		mSupportFbo.draw();
	}

	// 32 DE RESOLUTION

	vec2 resolution_32 = vec2(mCfg->ResolutionX / 32.0f, mCfg->ResolutionY / 32.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_32_h.getId());
	glViewport(0, 0, mCfg->ResolutionX / 32.0, mCfg->ResolutionY / 32.0);
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(1));
	glBindTexture(GL_TEXTURE_2D, mFboBloom_16_v.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation("image"), 0);

	glUniform1i(mShaderBlur.getLocation("h"), 1);
	glUniform1f(mShaderBlur.getLocation("size"), 0);
	glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
		value_ptr(resolution_32));
	mSupportFbo.draw();

	glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_32_v.getId());
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(mShaderBlur.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboBloom_32_h.getColorBufferId(0));
	glUniform1i(mShaderBlur.getLocation("image"), 0);

	glUniform1i(mShaderBlur.getLocation("h"), 0);
	glUniform1f(mShaderBlur.getLocation("size"), 0);
	glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
		value_ptr(resolution_32));
	mSupportFbo.draw();


	for (int i = 1; i < nombreDePasseBlurBloom32; i++) {
		float size = 0 * float(i) / nombreDePasseBlurBloom32;

		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_32_h.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_32_v.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation("image"), 0);

		glUniform1i(mShaderBlur.getLocation("h"), 1);
		glUniform1f(mShaderBlur.getLocation("size"), size);
		glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
			value_ptr(resolution_32));
		mSupportFbo.draw();


		glBindFramebuffer(GL_FRAMEBUFFER, mFboBloom_32_v.getId());
		glDrawBuffers(1, mAttach);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mShaderBlur.getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mFboBloom_32_h.getColorBufferId(0));
		glUniform1i(mShaderBlur.getLocation("image"), 0);

		glUniform1i(mShaderBlur.getLocation("h"), 0);
		glUniform1f(mShaderBlur.getLocation("size"), size);
		glUniform2fv(mShaderBlur.getLocation("resolution"), 1,
			value_ptr(resolution_32));
		mSupportFbo.draw();
	}







	glViewport(0, 0, mCfg->ResolutionX, mCfg->ResolutionY);

}

void RenderSystem::doStepMotionBlur(float fps)
{
	vec2 resolution = vec2(mCfg->ResolutionX, mCfg->ResolutionY);

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
	glBindFramebuffer(GL_FRAMEBUFFER, mFboShading.getId());
	glClear(GL_COLOR_BUFFER_BIT );
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
	glBindTexture(GL_TEXTURE_2D, mFboBloom_2_v.getColorBufferId(0));
	glUniform1i(mShaderTone.getLocation("bloomSampler1"), 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mFboBloom_8_v.getColorBufferId(0));
	glUniform1i(mShaderTone.getLocation("bloomSampler2"), 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, mFboBloom_16_v.getColorBufferId(0));
	glUniform1i(mShaderTone.getLocation("bloomSampler3"), 3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, mFboBloom_32_v.getColorBufferId(0));
	glUniform1i(mShaderTone.getLocation("bloomSampler4"), 4);
	mSupportFbo.draw();
}

void RenderSystem::doStepShading(Camera const& cam, Camera const &camLight,Input const& input)
{

	vec2 resolution = vec2(mCfg->ResolutionX, mCfg->ResolutionY);
	vec2 resolution_2 = vec2(mCfg->ResolutionX / 2.0f, mCfg->ResolutionY / 2.0f);
	mat4 projection = cam.getProjection();
	mat4 view = cam.getView();
	mat4 invView = inverse(view);
	mat4 viewLight= (camLight.getView());

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

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, mFboLight.getColorBufferId(0));
	glUniform1i(mShaderDeferredFinal.getLocation("shadowSampler"), 4);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemapSkybox->getId());
	glUniform1i(mShaderDeferredFinal.getLocation("skyboxSampler"), 5);

	glUniformMatrix4fv(mShaderDeferredFinal.getLocation("projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(mShaderDeferredFinal.getLocation("projectionLight"), 1, GL_FALSE, value_ptr(camLight.getProjection()));
	glUniformMatrix4fv(mShaderDeferredFinal.getLocation("viewLight"), 1, GL_FALSE, value_ptr(viewLight));
	glUniformMatrix4fv(mShaderDeferredFinal.getLocation("invView"), 1, GL_FALSE, value_ptr(invView));
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
	glUniform1i(mShaderDeferredFinal.getLocation("keyF10"), input.getKey(SDL_SCANCODE_F10));
	glUniform1i(mShaderDeferredFinal.getLocation("CookTorrance"), mCfg->CookTorrance);
	glUniform1i(mShaderDeferredFinal.getLocation("Reflection"), mCfg->Reflection);
	glUniform1i(mShaderDeferredFinal.getLocation("AO"), mCfg->AO);
	glUniform2fv(mShaderDeferredFinal.getLocation("resolution"), 1, value_ptr(resolution));
	mSupportFbo.draw();
}

void RenderSystem::doStepGeometry(Camera const &cam, std::vector<Entity*> entities)
{
	vec2 resolution = vec2(mCfg->ResolutionX, mCfg->ResolutionY);
	vec2 resolution_2 = vec2(mCfg->ResolutionX / 2.0f, mCfg->ResolutionY / 2.0f);
	mat4 projection = cam.getProjection();
	mat4 view = cam.getView();
	mat4 modelview;
	mat4 lastModel;

	glViewport(0, 0, mCfg->ResolutionX, mCfg->ResolutionY);
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

		if (entity != nullptr)
		{
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

			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, (mRm->getTexture(entity->getGraphicComponent()->getTextureReflectionId())->getId()));
			glUniform1i(mShaderGeometry.getLocation("texture_reflection"), 4);

			modelview = view*entity->getPhysicComponent()->getStateComponent()->getModel();
			lastModel = entity->getPhysicComponent()->getStateComponent()->getLastModel();
			glUniformMatrix4fv(mShaderGeometry.getLocation("modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniformMatrix4fv(mShaderGeometry.getLocation("lastModel"), 1, GL_FALSE, value_ptr(lastModel));
			glUniformMatrix3fv(mShaderGeometry.getLocation("normal"), 1, GL_FALSE, value_ptr(transpose(inverse(glm::mat3(modelview)))));
			mRm->getVao(entity->getGraphicComponent()->getVaoId())->draw();
		}
	}

}

void RenderSystem::doStepLight(Camera const &cam, std::vector<Entity*> entities)
{

	glBindFramebuffer(GL_FRAMEBUFFER, mFboLight.getId());
	glViewport(0, 0, 1024*4, 1024*4);
	glDrawBuffers(1, mAttach);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderLight.getProgramID());
	glDisable(GL_BLEND);
	
	glUniformMatrix4fv(mShaderLight.getLocation("projection"), 1, GL_FALSE, value_ptr(cam.getProjection()));

	mat4 view = cam.getView();
	mat4 modelview;
	for (int i = 0; i < entities.size(); i++) {
		Entity* entity = entities[i];
		if (entity != nullptr)
		{
			modelview = view*entity->getPhysicComponent()->getStateComponent()->getModel();
			glUniformMatrix4fv(mShaderLight.getLocation("modelview"), 1, GL_FALSE, value_ptr(modelview));
			mRm->getVao(entity->getGraphicComponent()->getVaoId())->draw();
		}
		
	}

	
	glViewport(0, 0, mCfg->ResolutionX, mCfg->ResolutionY);
}

void RenderSystem::doStepFXAA(float time) {

	vec2 resolution = vec2(mCfg->ResolutionX, mCfg->ResolutionY);

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderFXAA.getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mFboShading.getColorBufferId(0));
	glUniform1i(mShaderFXAA.getLocation("image"), 0);
	glUniform1f(mShaderFXAA.getLocation("time"), time);
	glUniform2fv(mShaderFXAA.getLocation("resolution"), 1, value_ptr(resolution));
	mSupportFbo.draw();


}