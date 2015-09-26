#include "SphereDetectionComponent.h"

using namespace glm;

SphereDetectionComponent::SphereDetectionComponent(float radius2) :mRadius2(radius2)
{

}

SphereDetectionComponent::~SphereDetectionComponent()
{

}

Contact* SphereDetectionComponent::getCollisionOnRay(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	vec3 &s = pos1;
	vec3 L1 = pos2;
	vec3 L1L2 = normalize(vec3( rotate(rot2.x, vec3(1, 0, 0)) *rotate(rot2.y, vec3(0, 1, 0))*rotate(rot2.z, vec3(0, 0, 1)) * vec4(1, 0, 0, 1)));
	vec3 sL1 = L1 - s;

	float u = dot(sL1, sL1) - mRadius2;
	float v = 2 * dot(sL1, L1L2);
	float w = dot(L1L2, L1L2);

	float discri = pow(v, 2) - 4 * u*w;
	if (0 > discri) // Pas de racine r�elle => pas d'intersection
		return nullptr;

	Contact* result = new Contact;

	float t1 = (1 / (2 * w)) * (-v + sqrt(discri));
	float t2 = (1 / (2 * w)) * (-v - sqrt(discri));

	vec3 contactPosition1 = L1 + L1L2*t1;
	vec3 contactPosition2 = L1 + L1L2*t2;

	if (glm::distance(contactPosition1, L1) < glm::distance(contactPosition1, L1))
		result->position = contactPosition1;
	else
		result->position = contactPosition2;

	result->normal = result->position - pos1;


	return result;

}

Contact* SphereDetectionComponent::getCollisionOnSphere(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	if (mRadius2 + ((SphereDetectionComponent*)detComp2)->mRadius2 <= dot(pos1-pos2,pos1-pos2))
	return nullptr;
	
	Contact* result = new Contact;

	float r1 = sqrt(mRadius2);
	float r2 = sqrt(((SphereDetectionComponent*)detComp2)->mRadius2);

	result->position = (r2*pos1 + r1*pos2) / (r1 + r2);
	result->normal = pos2 - pos1;
	
	return result;
}

Contact* SphereDetectionComponent::getCollisionOnCube(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	return nullptr;
}