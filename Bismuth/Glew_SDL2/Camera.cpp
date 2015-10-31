#include "Camera.h"

Camera::Camera(glm::mat4 &projection, PhysicComponent* physicComponent) : mProjection(projection), mPhysicComponent(physicComponent), mView(0)
{


}

Camera::~Camera()
{


}