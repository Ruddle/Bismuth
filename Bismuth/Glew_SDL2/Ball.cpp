#include "Ball.h"

using namespace glm;


Ball::Ball(EntityManager* em,ResourcesManager* rm,glm::vec3 position, glm::vec3 speed)
{
	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/checker.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		0,
		0,
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

void Ball::update()
{
	StateComponent* sc = mEntity->getPhysicComponent()->getStateComponent();

	sc->force(vec3(0, 0, -0.00051));
	sc->friction(0.01f);


	if (sc->getPosition().z < 1) {
		sc->setPosition(vec3(sc->getPosition().x, sc->getPosition().y, 1));
		sc->setPositionDiff(vec3(sc->getPositionDiff().x, sc->getPositionDiff().y, -0.5*sc->getPositionDiff().z));
	}


	std::set<Contact*> contact = mEntity->getPhysicComponent()->getContact();

	for (std::set<Contact*>::iterator it = contact.begin(); it != contact.end(); it++)
	{
		
		sc->force( -(*it)->normal *0.01f);
		sc->setPosition(sc->getPosition() - (*it)->normal/2.0f);


	}


	
		





}
