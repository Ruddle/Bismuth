#include "Heightmap.h"


using namespace glm;

using namespace std;

Heightmap::Heightmap(EntityManager * em, ResourcesManager * rm)
{

	createVertex();

	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/GRAY200.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLUE.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/GRAY60.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT), //mystic_e
																							  /*	rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
																							  rm->loadTexture("Texture/rock_n.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
																							  rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
																							  rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR, GL_REPEAT),*/
		rm->loadTexture("Texture/GRAY60.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadVao(mPosition,mNormal,mUv));




	CubeDetectionComponent* dc1 = new CubeDetectionComponent(2, 2, 2);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(vec3(0, 0, 0));

	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);

	mMesh = new Mesh(gc1, pc1);


	em->add(mMesh);
}

Heightmap::~Heightmap()
{
}

void Heightmap::createVertex()
{

	vector< vector< quad > > grille;

	int sizeX = 100;
	int sizeY = 100;
	float size = 0.2;

	grille.resize(sizeX);
	for (int y = 0; y < sizeY; y++)
		grille[y].resize(sizeY);



	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			float x = (float(i) - float(sizeX) / 2.0)*size;
			float y = (float(j) - float(sizeY) / 2.0)*size;

			vec3 pos1 = vec3(x, y, z(x, y));
			vec3 pos2 = vec3(x+ size, y, z(x+ size, y));
			vec3 pos3 = vec3(x + size, y + size, z(x + size, y + size));
			vec3 pos4 = vec3(x, y + size, z(x, y + size));

			vec3 nor1 = calcNormal(x,y, size);
			vec3 nor2 = calcNormal(x + size, y, size);
			vec3 nor3 = calcNormal(x + size, y + size, size);
			vec3 nor4 = calcNormal(x, y + size, size);

			vec2 uv1 = vec2(0, 0);
			vec2 uv2 = vec2(1, 0);
			vec2 uv3 = vec2(1, 1);
			vec2 uv4 = vec2(0, 1);

			triangle a;
			a.posA = pos1;
			a.posB = pos2;
			a.posC = pos4;

			a.mUvA = uv1;
			a.mUvB = uv2;
			a.mUvC = uv4;

			a.norA = nor1;
			a.norB = nor2;
			a.norC = nor4;

			triangle b;
			b.posA = pos2;
			b.posB = pos3;
			b.posC = pos4;

			b.mUvA = uv2;
			b.mUvB = uv3;
			b.mUvC = uv4;

			b.norA = nor2;
			b.norB = nor3;
			b.norC = nor4;

			quad local;
			local.a = a;
			local.b = b;

			grille[i][j] = local;
		}
	}


	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			 quad local;
			 local = grille[x][y];

			 triangle a = local.a;
			 triangle b = local.b;

			 mPosition.push_back(a.posA);
			 mPosition.push_back(a.posB);
			 mPosition.push_back(a.posC);

			 mNormal.push_back(a.norA);
			 mNormal.push_back(a.norB);
			 mNormal.push_back(a.norC);

			 mUv.push_back(a.mUvA);
			 mUv.push_back(a.mUvB);
			 mUv.push_back(a.mUvC);


			 mPosition.push_back(b.posA);
			 mPosition.push_back(b.posB);
			 mPosition.push_back(b.posC);

			 mNormal.push_back(b.norA);
			 mNormal.push_back(b.norB);
			 mNormal.push_back(b.norC);

			 mUv.push_back(b.mUvA);
			 mUv.push_back(b.mUvB);
			 mUv.push_back(b.mUvC);

		}
	}





}


float Heightmap::z(float x, float y)
{
	return sin(2*x*3.141592/10.0  + y);
}

glm::vec3 Heightmap::calcNormal(float x, float y,float epsilon)
{
	return normalize(vec3(z(x- epsilon,y) - z(x+ epsilon,y)  , z(x,y- epsilon) - z(x,y+ epsilon), 2*epsilon));
}
