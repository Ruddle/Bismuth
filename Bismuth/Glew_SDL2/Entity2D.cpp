#include "Entity2D.h"



Entity2D::Entity2D()
{
}

Entity2D::Entity2D(GraphicComponent * graphicComponent, PhysicComponent2D * physicComponent) : mPhysicComponent(physicComponent), mGraphicComponent(graphicComponent)
{
}


Entity2D::~Entity2D()
{
}
