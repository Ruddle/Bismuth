#pragma once
#include "Texture.h"
#include "Vao.h"
#include <string>

class ResourcesManager
{
public:
	ResourcesManager();
	~ResourcesManager();
	int loadTexture(std::string path, GLenum format, GLenum filter, GLenum wrap);
	int loadVAO(std::string path);

	Texture* getTexture(unsigned int id);
	Vao* getVao(unsigned int id);

private:
	int getTexture(std::string path, TextureCfg cfg);
	int getVAO(std::string path);

	std::vector<Texture*> mTextures;
	std::vector<Vao*> mVaos;
};

