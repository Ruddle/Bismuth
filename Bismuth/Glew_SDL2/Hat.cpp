#include "Hat.h"

using namespace glm;


Hat::Hat(EntityManager* em, ResourcesManager* rm,Entity* parent)
{
	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/GRAY60.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/BLUE.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/GRAY200.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT), //mystic_e
																							  /*	rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
																							  rm->loadTexture("Texture/rock_n.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
																							  rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
																							  rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR, GL_REPEAT),*/
		rm->loadTexture("Texture/GRAY60.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadVao("Mesh/hat.obj"));


	SphereDetectionComponent* dc1 = new SphereDetectionComponent(0);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(vec3(0,0,2));

	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);

	

	mMesh = new Mesh(gc1, pc1);


	em->add(parent,mMesh);
}

Hat::~Hat()
{



}

void Hat::update(float time_s)
{

	/*if (sc->getPosition().z < 1) {
	sc->setPosition(vec3(sc->getPosition().x, sc->getPosition().y, 1));
	sc->setPositionDiff(vec3(sc->getPositionDiff().x, sc->getPositionDiff().y, -0.2*sc->getPositionDiff().z));
	}*/
}
