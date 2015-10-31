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

int ResourcesManager::loadTexture(std::string path, GLenum format, GLenum filter, GLenum wrap)
{
	TextureCfg cfg = { format , filter, wrap };

	int id = getTexture(path, cfg); // On cherche si une texture a d�j� �t� charg�e avec les m�mes param�tres

	if (id != -1) // La texture a d�j� �t� charg�e avant
	{
		return id;
	}
	else // La texture n'a pas encore �t� charg�e
	{
		mTextures.push_back(new Texture(path, cfg));
		return mTextures.size() - 1;
	}
}

int ResourcesManager::loadVao(std::string path)
{
	int id = getVao(path); // On cherche si un VAO a d�j� �t� charg� avec les m�mes param�tres

	if (id != -1) // Le VAO a d�j� �t� charg� avant
	{
		return id;
	}
	else // Le VAO n'a pas encore �t� charg�
	{
		mVaos.push_back(new Vao(path));
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