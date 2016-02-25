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
	int loadTexture(std::string path, TextureCfg cfg);
	int loadVao(std::string path);
	int loadVao(std::vector<glm::vec3> position, std::vector<glm::vec3> normal, std::vector<glm::vec2> uv);

	Texture* getTexture(unsigned int id);
	Vao* getVao(unsigned int id);

private:
	int getTexture(std::string path, TextureCfg cfg);
	int getVao(std::string path);

	std::vector<Texture*> mTextures;
	std::vector<Vao*> mVaos;
};

