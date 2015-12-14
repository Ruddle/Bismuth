#include "Slider_dot.h"

using namespace glm;

Slider_dot::Slider_dot(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size) 
{
	mEntity = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(0, 0.0 / 4.0f), vec2(4.0 / 4.0f)),
		new PhysicComponent2D(vec2(min(size.x, size.y))*2.50f / resolution, (leftBottom +0.0f*vec2(size.x/2.0,0.0) / resolution)*2.0f - vec2(1)));

	em->add(mEntity);
	mUI_box = new UI_box(mEntity->getPhysicComponent());
	input->addObserver(mUI_box);
	mUI_box->addObserver(this);
}


Slider_dot::~Slider_dot()
{
}

void Slider_dot::onHover(glm::vec2 mouse)
{
}

void Slider_dot::onUnHover(glm::vec2 mouse)
{
}

void Slider_dot::onClick(glm::vec2 mouse)
{
}

void Slider_dot::onUnClick(glm::vec2 mouse)
{
}

void Slider_dot::onSelect(glm::vec2 mouse)
{
}

void Slider_dot::onDeSelect(glm::vec2 mouse)
{
}

void Slider_dot::notify()
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->Action_dot();
}

void Slider_dot::Action(float x)
{
	mEntity->getPhysicComponent()->setPosition((mLeftBottom + vec2(mSize.x*x, 0.0) / mResolution)*2.0f - vec2(1));
}
