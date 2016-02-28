#include "Hat.h"

using namespace glm;


Hat::Hat(EntityManager* em, ResourcesManager* rm,Entity* parent) : Mesh()
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

	

	this->setGraphicComponent(gc1);
	this->setPhysicComponent(pc1);

	em->add(parent,this);
}

Hat::~Hat()
{



}

void Hat::update(float time_s)
{

	
}
