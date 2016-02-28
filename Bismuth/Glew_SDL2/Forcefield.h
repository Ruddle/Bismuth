#pragma once

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "Updatable.h"
#include "DetectionComponent.h"
#include "PhysicComponent.h"
#include "Entity.h"

class Forcefield : public Entity
{
    public:
        Forcefield(PhysicComponent *mPhysicComponent);
        ~Forcefield();
        PhysicComponent* getPhysicComponentComponent() { return mPhysicComponent; }
        virtual glm::vec3 force(glm::vec3 pos) const = 0;


		Type getType() const { return Entity::FORCEFIELD; }

    protected:
        PhysicComponent *mPhysicComponent;


};
