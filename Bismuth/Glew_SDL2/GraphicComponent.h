#pragma once
#include "ResourcesManager.h"
#include "Camera.h"
#include "Texture.h"
#include "Vao.h"
#include "Shader.h"
#include "Fbo.h"

class Camera;


class GraphicComponent
{

public:

	GraphicComponent(int textureDiffuse, int textureNormal, int textureSpec,int textureEmit,int textureReflection, int vao);
	int getTextureDiffuseId() const { return mTextureDiffuse; }
	int getTextureNormalId() const { return mTextureNormal; }
	int getTextureSpecId() const { return mTextureSpec; }
	int getTextureEmitId() const { return mTextureEmit; }
	int getTextureReflectionId() const { return mTextureReflection; }
	int getVaoId() const { return mVao; }
	~GraphicComponent();


private:

	int mTextureDiffuse;
	int mTextureNormal;
	int mTextureSpec;
	int mTextureEmit;
	int mTextureReflection;
	int mVao;







};
