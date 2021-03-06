#include "Ball.h"

using namespace glm;


Ball::Ball(EntityManager* em,ResourcesManager* rm,glm::vec3 position, glm::vec3 speed) : Mesh()
{
	GraphicComponent* gc1 = new GraphicComponent(
		rm->loadTexture("Texture/circleColor2.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/BLUE.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/checker2C.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
		rm->loadTexture("Texture/circle.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
	/*	rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock_n.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/rock.png", GL_RGB8, GL_LINEAR, GL_REPEAT),
		rm->loadTexture("Texture/BLACK.png", GL_RGB8, GL_LINEAR, GL_REPEAT),*/

		rm->loadTexture("Texture/GRAY60.png", GL_RGB8, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT),
		rm->loadVao("Mesh/sphere.obj"));



	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	sc1->setPosition(position);
	sc1->setPositionDiff(speed);
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);

	this->setGraphicComponent(gc1);
	this->setPhysicComponent(pc1);

	em->add(this);
}



Ball::~Ball()
{
}


void Ball::update(float time_s)
{
	StateComponent* sc = getPhysicComponent()->getStateComponent();

  //  sc->force(time_s,vec3(0, 0, -9.8));
	sc->friction(0.3f*time_s);


	/*if (sc->getPosition().z < 1) {
		sc->setPosition(vec3(sc->getPosition().x, sc->getPosition().y, 1));
		sc->setPositionDiff(vec3(sc->getPositionDiff().x, sc->getPositionDiff().y, -0.2*sc->getPositionDiff().z));
	}*/
}
