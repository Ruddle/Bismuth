#include "Misc.h"



using namespace std;
using namespace glm;

Config readConfig(void) {

	Config cfg;

	ifstream flux(CONFIGPATH);

	if (!flux)
		cout << "ERROR : Loading of " << CONFIGPATH << " failed !" << endl;

	bool loading = true;

	while (loading)
	{
		string line;
		if (!getline(flux, line)) //On lit une ligne complète
			loading = false;

		istringstream lineStream(line);

		string word1;
		lineStream >> word1;

		string word2;
		lineStream >> word2;
		lineStream >> word2;

		if (word1 == "ResolutionX")
			cfg.ResolutionX = stoi(word2);

		if (word1 == "ResolutionY")
			cfg.ResolutionY = stoi(word2);
	}
	return cfg;
}

Fbo* createFboGeometry(Config cfg) {

	TextureCfg texCfgNormal = { GL_RGB16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texNormal =new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgNormal);
	texNormal->load();

	TextureCfg texCfgDiffuse = { GL_RGB16F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texDiffuse = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgDiffuse);
	texDiffuse->load();

	TextureCfg texCfgPosition = { GL_RGBA32F, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* texPosition = new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfgPosition);
	texPosition->load();

	vector<Texture*> textureArray = vector<Texture*>();
	textureArray.push_back(texNormal);
	textureArray.push_back(texDiffuse);
	textureArray.push_back(texPosition);

	Fbo* fbo =new Fbo(textureArray, 1, 0);
	fbo->load();

	return fbo;
}

Fbo* createFbo_1ch(Config cfg) { // AO, blur, shadow 

	TextureCfg texCfg = { GL_R8, GL_NEAREST, GL_CLAMP_TO_EDGE };
	Texture* tex =new Texture(cfg.ResolutionX, cfg.ResolutionY, texCfg);
	tex->load();
	vector<Texture*> textureArray = vector<Texture*>();
	textureArray.push_back(tex);

	Fbo* fbo =new Fbo(textureArray, 0, 0);
	fbo->load();

	return fbo;
}