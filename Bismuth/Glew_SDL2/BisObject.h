#pragma once
#include "Cube.h"
#include <string>

struct BisObjectConfig
{
	std::string mesh;
	std::string texture;
	std::string texture_d;
	std::string texture_s;
	std::string texture_n;
	std::string texture_r;
	std::string texture_e;
};

class BisObject : public Updatable, public Mesh
{
public:
	BisObject(EntityManager* em, ResourcesManager* rm, glm::vec3 position, glm::vec3 speed,std::string path);
	~BisObject();

	void update(float time_s);


};

