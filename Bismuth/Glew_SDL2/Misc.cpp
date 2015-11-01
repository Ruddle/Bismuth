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


Entity* createSphere(ResourcesManager* rm) {
	GraphicComponent* gc1 = new GraphicComponent(rm->loadTexture("Texture/checker.png", GL_RGB8, GL_NEAREST, GL_REPEAT), 0, 0, rm->loadVao("Mesh/sphere.obj"));
	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(vec3(0, 0, 0.5));
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	Entity* entity = new Entity(gc1, pc1);
	return entity;
}

Entity* createPlane(ResourcesManager* rm) {
	GraphicComponent* gc1 = new GraphicComponent(rm->loadTexture("Texture/checker2.png", GL_RGB8, GL_LINEAR, GL_REPEAT), 0, 0, rm->loadVao("Mesh/plane.obj"));
	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	Entity* entity = new Entity(gc1, pc1);
	return entity;
}


Entity* createThing(ResourcesManager* rm) {
	GraphicComponent* gc1 = new GraphicComponent(rm->loadTexture("Texture/checker2.png", GL_RGB8, GL_LINEAR, GL_REPEAT), 0, 0, rm->loadVao("Mesh/thing.obj"));
	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(vec3(0, 0, 0.8));
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	Entity* entity = new Entity(gc1, pc1);
	return entity;
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