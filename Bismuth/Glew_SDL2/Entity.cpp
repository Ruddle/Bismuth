#include "Entity.h"

Entity::Entity() : mGraphicComponent(nullptr), mPhysicComponent(nullptr)
{
}

Entity::Entity(GraphicComponent* graphicComponent, PhysicComponent* physicComponent) :
    mGraphicComponent(graphicComponent), mPhysicComponent(physicComponent)
{}

Entity::~Entity()
{

    delete mGraphicComponent;
    delete mPhysicComponent;

}





