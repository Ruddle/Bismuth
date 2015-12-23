#include "Misc.h"



using namespace std;
using namespace glm;

Config* readConfig(void) {

	Config* cfg = new Config();

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
			cfg->ResolutionX = stoi(word2);

		if (word1 == "ResolutionY")
			cfg->ResolutionY = stoi(word2);

		if (word1 == "HalfAO")
			cfg->HalfAO = stoi(word2);

		if (word1 == "FullScreen")
			cfg->FullScreen = stoi(word2);

		if (word1 == "AO")
			cfg->AO = stoi(word2);

		if (word1 == "CookTorrance")
			cfg->CookTorrance = stoi(word2);

		if (word1 == "Reflection")
			cfg->Reflection = stoi(word2);
		

	}
	return cfg;
}




Entity* createSphere(ResourcesManager* rm) {
	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/checker2.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLUE.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/checker2C.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/band.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadVao("Mesh/sphere.obj"));
	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(vec3(0, 0, 0.8));
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	Entity* entity = new Entity(gc1, pc1);
	return entity;
}

Entity* createPlane(ResourcesManager* rm) {
	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/wood.jpg", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/wood_N.jpg", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/WHITE.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
	/*	rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock_N.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),*/
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/GRAY60.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadVao("Mesh/plane.obj"));
	PlaneDetectionComponent* dc1 = new PlaneDetectionComponent(1000,1000);
	StateComponent* sc1 = new StateComponent();
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	sc1->setMass(1.0E15f);
	sc1->setInertia(1E15f);
	//sc1->setRotation(vec3(0.0, 0, 0));
	Entity* entity = new Entity(gc1, pc1);

	return entity;
}


Entity* createThing(ResourcesManager* rm,vec3 position) {
	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/checker2.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLUE.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/checker2C.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadVao("Mesh/cube.obj"));
	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(position);
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	Entity* entity = new Entity(gc1, pc1);
	return entity;
}

Entity2D* createUI(ResourcesManager* rm) {

	GraphicComponent2D* gc1 = new GraphicComponent2D(
		rm->loadTexture("Texture/bismuthSquare.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		vec2(0),vec2(1));

	PhysicComponent2D* pc1 = new PhysicComponent2D(vec2(0.15,0.25), vec2(-0.995, 0.48));
	Entity2D* entity = new Entity2D(gc1, pc1);
	return entity;

}

std::vector<Entity2D*> getVisualCollision(ResourcesManager* rm,std::vector<Entity*> const & entities, Camera const & cam)
{
	std::vector<Entity2D*> res = std::vector<Entity2D*>();
	std::vector<vec2> a = std::vector<vec2>();

	for (auto it1 = entities.begin(); it1 != entities.end(); it1++)
	{
		if (*it1 != nullptr)
		{
			set<Contact*> contacts = (*it1)->getPhysicComponent()->getContact();
			for (auto it = contacts.begin(); it != contacts.end(); it++)
			{
				if (*it != nullptr)
				{
					vec4 worldSpace = vec4((*it)->position, 1);
					vec4 screenSpace = cam.getProjection() * cam.getView() * worldSpace;
					screenSpace /= screenSpace.w;
					a.push_back(vec2(screenSpace));

					for (int i = 0; i < 10; i++)
					{
						vec4 worldSpace = vec4((*it)->position + i*10.0f*(*it)->normal, 1);
						vec4 screenSpace = cam.getProjection() * cam.getView() * worldSpace;
						screenSpace /= screenSpace.w;
						a.push_back(vec2(screenSpace));

					}
				}

			}
		}

	}
	vec2 size = vec2(9, 16)*0.001f;

	for (int i = 0; i < a.size(); i++) 
	{
		res.push_back(new Entity2D(
			new GraphicComponent2D(
				rm->loadTexture("Texture/dot.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
				vec2(0, 0), vec2(1.0 / 1.0f)),
			new PhysicComponent2D(size*2.0f, a[i]-size/1.0f   )));
	}




	return res;
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