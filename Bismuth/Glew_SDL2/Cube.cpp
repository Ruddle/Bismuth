#include "Cube.h"

using namespace glm;


Cube::Cube(EntityManager* em, ResourcesManager* rm, glm::vec3 position, glm::vec3 speed)
{
	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/mystic_d.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/BLUE.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/checker2C.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/mystic_e.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		/*	rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock_n.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR, GL_REPEAT),*/
		rm->loadTexture("Texture/GRAY60.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadVao("Mesh/cube.obj"));




	CubeDetectionComponent* dc1 = new CubeDetectionComponent(2,2,2);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(position+speed*1000.0f);
	sc1->setPositionDiff(vec3(0,0,-0.002));

	sc1->setRotationDiff(vec3(0.01f, 0.00100f, 0.0f));
	sc1->setRotation(quat(1,0,0,0));


	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);

	mEntity = new Entity(gc1, pc1);


	em->add(mEntity);
}

Cube::~Cube()
{
}

void Cube::update(float time_s)
{
	StateComponent* sc = mEntity->getPhysicComponent()->getStateComponent();

	sc->force(time_s,vec3(0, 0, -9.8));
	sc->friction(0.3f*time_s);


	/*if (sc->getPosition().z < 1) {
		sc->setPosition(vec3(sc->getPosition().x, sc->getPosition().y, 1));
		sc->setPositionDiff(vec3(sc->getPositionDiff().x, sc->getPositionDiff().y, -0.2*sc->getPositionDiff().z));
	}*/
}
