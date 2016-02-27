#include "BisObject.h"


using namespace std;
using namespace glm;

BisObject::BisObject(EntityManager* em, ResourcesManager* rm, glm::vec3 position, glm::vec3 speed, string path)
{


	BisObjectConfig boc;

	boc.mesh = "";
	boc.texture = "";
	boc.texture_d = "";
	boc.texture_n = "";
	boc.texture_r = "";
	boc.texture_e = "";
	boc.texture_s = "";


	ifstream flux(path);

	if (!flux)
		cout << "ERROR : Loading of " << path << " failed !" << endl;

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


		if (word1 == "Mesh")
			boc.mesh = word2;

		if (word1 == "Texture")
			boc.texture = word2;

		if (word1 == "Texture_Diffuse")
			boc.texture_d = word2;

		if (word1 == "Texture_Normal")
			boc.texture_n = word2;

		if (word1 == "Texture_Specular")
			boc.texture_s = word2;

		if (word1 == "Texture_Emit")
			boc.texture_e = word2;

		if (word1 == "Texture_Reflection")
			boc.texture_r = word2;
	}


	if (boc.texture != "")
	{
		ifstream* flux;

		flux =new ifstream("Texture/" + boc.texture + "/d.png");
		if (flux->good())
		boc.texture_d = boc.texture + "/d.png";

		flux = new ifstream("Texture/" + boc.texture + "/n.png");
		if (flux->good())
			boc.texture_n = boc.texture + "/n.png";
		
		flux = new ifstream("Texture/" + boc.texture + "/e.png");
		if (flux->good())
			boc.texture_e = boc.texture + "/e.png";

		flux = new ifstream("Texture/" + boc.texture + "/r.png");
		if (flux->good())
			boc.texture_r = boc.texture + "/r.png";

		flux = new ifstream("Texture/" + boc.texture + "/s.png");
		if (flux->good())
			boc.texture_s = boc.texture + "/s.png";
	}

	if (boc.mesh == "")
		boc.mesh = "Default/o.obj";

	if (boc.texture_d == "")
		boc.texture_d = "Default/d.png";

	if (boc.texture_e == "")
		boc.texture_e = "Default/e.png";

	if (boc.texture_r == "")
		boc.texture_r = "Default/r.png";

	if (boc.texture_s == "")
		boc.texture_s = "Default/s.png";

	if (boc.texture_n == "")
		boc.texture_n = "Default/n.png";



	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/" + boc.texture_d, GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/" + boc.texture_n, GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/" + boc.texture_s, GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/" + boc.texture_e, GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/" + boc.texture_r, GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadVao("Mesh/" + boc.mesh));




	CubeDetectionComponent* dc1 = new CubeDetectionComponent(2, 2, 2);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(position + speed*1000.0f);
	sc1->setPositionDiff(vec3(0, 0, 0.0));

	sc1->setRotationDiff(vec3(10.0f, 0.00000f, 0.0f));
	sc1->setRotation(quat(1, 0, 0, 0));


	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);

	mMesh = new Mesh(gc1, pc1);


	em->add(mMesh);
}


BisObject::~BisObject()
{
}

void BisObject::update(float time_s)
{
}
