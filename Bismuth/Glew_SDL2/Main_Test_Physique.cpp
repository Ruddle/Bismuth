#include "glm.hpp"
#include "Camera.h"
#include "Contact.h"
#include "DetectionComponent.h"
#include "Entity.h"
#include "EntityManager.h" 
#include "GraphicComponent.h"
#include "PhysicComponent.h"
#include "RayDetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "StateComponent.h"
#include <iostream>
//#define _USE_MATH_DEFINES
#include <math.h>

using namespace glm;
using namespace std;


int main(int argc, char** argv)
{
	EntityManager *em = new EntityManager();

	SphereDetectionComponent* dcCam = new SphereDetectionComponent(1);
	StateComponent* scCam = new StateComponent();
	PhysicComponent* pcCam = new PhysicComponent(dcCam, scCam);
	mat4 projection = glm::perspective(70.0*M_PI / 180.0, 16.0 / 9.0, 0.1, 100.0);
	Camera* cam = new Camera(projection, pcCam);


	SphereDetectionComponent* dc1 = new SphereDetectionComponent(1);
	StateComponent* sc1 = new StateComponent();
	PhysicComponent* pc1 = new PhysicComponent(dc1, sc1);
	GraphicComponent* gc1 = new GraphicComponent();
	Entity* en1 = new Entity(gc1, pc1);
	em->add(en1);

	SphereDetectionComponent* dc2 = new SphereDetectionComponent(1);
	StateComponent* sc2 = new StateComponent();
	PhysicComponent* pc2 = new PhysicComponent(dc2, sc2);
	GraphicComponent* gc2 = new GraphicComponent();
	Entity* en2 = new Entity(gc2, pc2);
	em->add(en2);


	SphereDetectionComponent* dc3 = new SphereDetectionComponent(1);
	StateComponent* sc3 = new StateComponent();
	PhysicComponent* pc3 = new PhysicComponent(dc3, sc3);
	GraphicComponent* gc3 = new GraphicComponent();
	Entity* en3 = new Entity(gc3, pc3);
	em->add(en3);



	for (int i = 0; i < 100; i++)
	{
		en2->getPhysicComponent()->getStateComponent()->setPosition(vec3(0, 0, 5-(float)i/2.0));
		en3->getPhysicComponent()->getStateComponent()->setPosition(vec3(0, 3 - (float)i / 4.0,0));

		em->collision();
		em->update();

		std::set<Contact*> contact_en1 = en1->getPhysicComponent()->getContact();

		int j = 0;
		cout << "frame n " << i << endl;
		for (std::set<Contact*>::iterator it = contact_en1.begin(); it != contact_en1.end(); it++)
		{
			j++;
			cout << "Contact du solide 1 :" << endl;
			cout << "Contact n " << j << " Xpos = " << (*it)->position.x << " Ypos = " << (*it)->position.y << " Zpos = " << (*it)->position.z << endl;
			cout << "Contact n " << j << " Xnor = " << (*it)->normal.x << " Ynor = " << (*it)->normal.y << " Znor = " << (*it)->normal.z << endl;
		}

		cout << endl;

	}


	system("PAUSE");

}