#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "Updatable.h"
#include "DetectionComponent.h"


class Forcefield : public Entity
{
    public:
        Forcefield(PhysicComponent *mPhysicComponent;
        ~Forcefield();
        PhysicComponent* getPhysicComponentComponent() { return mPhysicComponent; }
        virtual glm::vec3 force(glm::vec3 pos) const = 0;


    protected:
        PhysicComponent *mPhysicComponent;


};

#endif // FORCEFIELD_H
