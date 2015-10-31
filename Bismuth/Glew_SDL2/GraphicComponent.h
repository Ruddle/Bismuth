#pragma once
#include "ResourcesManager.h"
#include "Camera.h"
#include "Texture.h"
#include "VAO.h"
#include "Shader.h"
#include "Fbo.h"

class Camera;


class GraphicComponent
{

public:

	GraphicComponent(int textureDiffuse, int textureNormal, int textureSpec, int vao);
	int getTextureDiffuseId() const { return mTextureDiffuse; }
	int getTextureNormalId() const { return mTextureNormal; }
	int getTextureSpecId() const { return mTextureSpec; }
	int getVaoId() const { return mVao; }
	~GraphicComponent();


private:


	int mTextureDiffuse;
	int mTextureNormal;
	int mTextureSpec;
	int mVao;







};