#pragma once
#include "glm.hpp"
#include "Entity.h"

class Light : public Entity
{
public:
	Light();
	~Light();

	void setIntensity(glm::vec3 intensity) { mIntensity = intensity; }
	void setAttenuation(float a) { mAttenuation = a; }
	void setCastShadow(bool b) { mCastShadows = b; }

	glm::vec3  getIntensity() { return mIntensity; }
	float getAttenuation() { return mAttenuation; }
	bool getCastShadow() { return mCastShadows; }

	Type getType() { return LIGHT };

private:
	glm::vec3 mIntensity;
	float mAttenuation;
	bool mCastShadows;


};

