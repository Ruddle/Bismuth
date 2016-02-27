#include "Mesh.h"

Mesh::Mesh(): mGraphicComponent(nullptr), mPhysicComponent(nullptr)
{

}

Mesh::Mesh(GraphicComponent* graphicComponent, PhysicComponent* physicComponent) : mGraphicComponent(graphicComponent) , mPhysicComponent(physicComponent)
{}

Mesh::~Mesh()
{
    delete mGraphicComponent;
    delete mPhysicComponent;
}
