#pragma once
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
#include "Entity.h"
#include "Entity2D.h"
#include <vector>
#include "ResourcesManager.h"
#include "Texture_Cube.h"
#include <random>

class RenderSystem
{
public:
	RenderSystem(Config * cfg, ResourcesManager* rm);
	~RenderSystem();

	void draw(std::vector<Entity*> entities, Camera const& cam, float time, Input &input,float fps);
	void draw2D(std::vector<Entity2D*> entities);


private: 

	void doStepGeometry(Camera const &cam, std::vector<Entity*> entities);
	void doStepLight(Camera const &cam, std::vector<Entity*> entities);
	void doStepAo(Camera const &cam);
	void doStepBlurAo();
	void doStepBloom();
	void doStepLensFlare();
	void doStepMotionBlur(float fps);
	void doStepToneMapping(Camera const& cam);
	void doStepShading(Camera const& cam, Camera const &camLight, Input const& input);
	void doStepFXAA(float time);

	Config* mCfg;
	Fbo mFboGeometry;
	Fbo mFboAo;
	Fbo mFboBloom_2_h;
	Fbo mFboBloom_2_v;
	Fbo mFboBloom_8_h;
	Fbo mFboBloom_8_v;
	Fbo mFboBloom_16_h;
	Fbo mFboBloom_16_v;
	Fbo mFboBloom_32_h;
	Fbo mFboBloom_32_v;
	Fbo mFboLensFlare_2_h;
	Fbo mFboLensFlare_2_v;
	Fbo mFboBlurH;
	Fbo mFboBlurV;
	Fbo mFboShading;
	Fbo mFboShading2;
	Fbo mFboLight;

	Shader mShaderGeometry;
	Shader mShaderAo;
	Shader mShaderLight;
	Shader mShaderBlurDir;
	Shader mShaderBlur;
	Shader mShaderLensFlare;
	Shader mShaderBlurBilateral;
	Shader mShaderDeferredFinal;
	Shader mShaderTone;
	Shader mShaderFXAA;
	Shader mShader2D;

	GLuint mTextureNoiseId;
	std::vector<glm::vec3> mKernel;

	Texture_Cube *mCubemapSkybox;
	Texture* mLensStar;
	Texture* mLensDirt;

	Vao2D mSupportFbo;
	ResourcesManager* mRm;
	glm::mat4 mLastViewProjection;
	GLuint mAttach[4];
};

