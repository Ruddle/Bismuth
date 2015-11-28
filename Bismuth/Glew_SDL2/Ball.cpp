#include "Ball.h"

using namespace glm;


Ball::Ball(EntityManager* em,ResourcesManager* rm,glm::vec3 position, glm::vec3 speed)
{
	GraphicComponent* gc1 = new GraphicComponent(1,
		rm->loadTexture("Texture/circleColor.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/BLUE.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/checker2C.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/circle.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
	/*	rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock_n.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR, GL_REPEAT),*/
		rm->loadVao("Mesh/sphere.obj"));


		

	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(position);
	sc1->setPositionDiff(speed);
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);

	mEntity = new Entity(gc1, pc1);


	em->add(mEntity);
}

Ball::~Ball()
{
}

void Ball::update(float elapsedTime)
{
	StateComponent* sc = mEntity->getPhysicComponent()->getStateComponent();

    sc->force(elapsedTime,vec3(0, 0, -0.000021*elapsedTime));
	sc->friction(0.001f*elapsedTime);


	/*if (sc->getPosition().z < 1) {
		sc->setPosition(vec3(sc->getPosition().x, sc->getPosition().y, 1));
		sc->setPositionDiff(vec3(sc->getPositionDiff().x, sc->getPositionDiff().y, -0.2*sc->getPositionDiff().z));
	}*/
}
