#pragma once
#include "Contact.h"
#include "PhysicComponent.h"
#include "RayDetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "PlaneDetectionComponent.h"
#include "CubeDetectionComponent.h"

#include "glm.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\norm.hpp"

class DetectionProcessor
{
public:
	DetectionProcessor();
	~DetectionProcessor();

	static Contact* detection(PhysicComponent * phyA, PhysicComponent * phyB);

	template <typename A,typename B>
	static Contact* contactFrom( Contact*(*func ) (A * a, B * b,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2)   , PhysicComponent * phyA, PhysicComponent * phyB );

	static Contact* cubeToRay(CubeDetectionComponent * cube, RayDetectionComponent * ray,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);//TODO

	static Contact* cubeToSphere(CubeDetectionComponent * cube, SphereDetectionComponent * sphere,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2); 
	static Contact* cubeToPlane(CubeDetectionComponent * cube, PlaneDetectionComponent * plane,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);
	static Contact* cubeToCube(CubeDetectionComponent * cube, CubeDetectionComponent * cube2,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2) ;//TODO

	static Contact* planeToRay(PlaneDetectionComponent * plane, RayDetectionComponent * ray,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);//TODO
	static Contact* planeToSphere(PlaneDetectionComponent * plane, SphereDetectionComponent * sphere,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);//TOCHECK
	static Contact* planeToPlane(PlaneDetectionComponent * plane, PlaneDetectionComponent * plane2,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);//TODO

	static Contact* sphereToRay(SphereDetectionComponent * sphere, RayDetectionComponent * ray,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);
	static Contact* sphereToSphere(SphereDetectionComponent * sphere, SphereDetectionComponent * sphere2,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);//TOCHECK

	static Contact* rayToRay(RayDetectionComponent * ray, RayDetectionComponent * ray2,
		glm::vec3 const&pos1, glm::quat const&rot1,
		glm::vec3 const&pos2, glm::quat const&rot2);

private :

	static Contact* reverse(Contact* c);

};

