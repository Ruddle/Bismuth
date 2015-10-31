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

	GraphicComponent();
	~GraphicComponent();


private:


	int mTextureDiffuse;
	int mTextureNormal;
	int mTextureSpec;
	int mVao;







};