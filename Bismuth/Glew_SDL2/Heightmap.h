#pragma once
#include "Mesh.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"



struct triangle
{
	glm::vec3 posA;
	glm::vec3 posB;
	glm::vec3 posC;

	glm::vec2 mUvA;
	glm::vec2 mUvB;
	glm::vec2 mUvC;

	glm::vec3 norA;
	glm::vec3 norB;
	glm::vec3 norC;
};

struct quad {
	triangle a;
	triangle b;
};

class Heightmap
{
public:
	Heightmap(EntityManager* em, ResourcesManager* rm);
	Entity *getEntity() { return mMesh; }
	~Heightmap();
private:
	Mesh *mMesh;

	std::vector<glm::vec3> mPosition;
	std::vector<glm::vec3> mNormal;
	std::vector<glm::vec2> mUv;

	void createVertex();

	float z(float x, float y);
	glm::vec3 calcNormal(float x, float y,float epsilon);

};

