#include "Mesh.h"

Mesh::Mesh():mPhysicComponent(nullptr), mGraphicComponent(nullptr)
{

}

Mesh::Mesh(GraphicComponent* graphicComponent, PhysicComponent* physicComponent) : mGraphicComponent(graphicComponent) , mPhysicComponent(physicComponent)
{}

Mesh::~Mesh()
{
    delete mGraphicComponent;
    delete mPhysicComponent;
}
