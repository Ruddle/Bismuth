#pragma once

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "Updatable.h"
#include "DetectionComponent.h"


class Forcefield : public Updatable
{
    public:
        Forcefield(DetectionComponent *mDetectionComponent);
        ~Forcefield();
        DetectionComponent* getDetectionComponent() { return mDetectionComponent; }
        virtual glm::vec3 force(glm::vec3 pos) const = 0;


    protected:
        DetectionComponent *mDetectionComponent;


};
