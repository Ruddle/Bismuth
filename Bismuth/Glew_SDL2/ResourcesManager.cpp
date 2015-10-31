#include "ResourcesManager.h"



ResourcesManager::ResourcesManager()
{
}


ResourcesManager::~ResourcesManager()
{
	for (int i = 0; i < mTextures.size(); i++)
		delete mTextures[i];

	for (int i = 0; i < mVaos.size(); i++)
		delete mVaos[i];
}

Texture* ResourcesManager::getTexture(unsigned int id)
{
	if (id < mTextures.size())
		return mTextures[id];
	else
		return NULL;
}

Vao* ResourcesManager::getVao(unsigned int id)
{
	if (id < mVaos.size())
		return mVaos[id];
	else
		return NULL;
}

int ResourcesManager::loadTexture(std::string path, TextureCfg cfg)
{
	return loadTexture(path, cfg.format, cfg.filter, cfg.wrap);
}

int ResourcesManager::loadTexture(std::string path, GLenum format, GLenum filter, GLenum wrap)
{
	TextureCfg cfg = { format , filter, wrap };

	int id = getTexture(path, cfg); // On cherche si une texture a déjà été chargée avec les mêmes paramètres

	if (id != -1) // La texture a déjà été chargée avant
	{
		return id;
	}
	else // La texture n'a pas encore été chargée
	{
		Texture *newTexture = new Texture(path, cfg);
		mTextures.push_back(newTexture);
		newTexture->load();
		return mTextures.size() - 1;
	}
}

int ResourcesManager::loadVao(std::string path)
{
	int id = getVao(path); // On cherche si un VAO a déjà été chargé avec les mêmes paramètres

	if (id != -1) // Le VAO a déjà été chargé avant
	{
		return id;
	}
	else // Le VAO n'a pas encore été chargé
	{
		Vao *newVao = new Vao(path);
		mVaos.push_back(newVao);
		newVao->load();
		return mVaos.size() - 1;
	}
}

int ResourcesManager::getTexture(std::string path, TextureCfg cfg)
{
	for (int i = 0; i < mTextures.size(); i++)
	{
		TextureCfg currCfg = mTextures[i]->getCfg();

		if (mTextures[i]->getPath() == path && currCfg.filter == cfg.filter && currCfg.format == cfg.format && currCfg.wrap == cfg.wrap)
			return i;
	}

	return -1;
}

int ResourcesManager::getVao(std::string path)
{
	for (int i = 0; i < mVaos.size(); i++)
	{
		if (mVaos[i]->getPath() == path)
			return i;
	}

	return -1;
}