#include "Entity.h"

Entity::Entity(GraphicComponent* graphicComponent, PhysicComponent* physicComponent) :
    mGraphicComponent(graphicComponent), mPhysicComponent(physicComponent)
{}

Entity::~Entity()
{

    delete mGraphicComponent;
    delete mPhysicComponent;

}
