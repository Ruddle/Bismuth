#include "Slider_dot.h"

using namespace glm;

Slider_dot::Slider_dot(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size) 
	: mIsDragged(0), mResolution(resolution), mSize(size), mLeftBottom(leftBottom)
{

	vec2 dotSize = vec2(min(size.x, size.y))*2.0f;
	mEntity = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(0, 0.0 / 4.0f), vec2(4.0 / 4.0f)),
		new PhysicComponent2D(dotSize*2.0f / resolution, (( leftBottom + 0.50f*vec2(size.x,0)  -0.5f*dotSize + vec2(0,size.y/2.0)) / resolution)*2.0f - vec2(1)));

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

void Slider_dot::onDrag(glm::vec2 mouse)
{
	if (mouse.x > mEntity->getPhysicComponent()->getPosition().x + mEntity->getPhysicComponent()->getSize().x/1.0f)
		notify(1);
	else if (mouse.x < mEntity->getPhysicComponent()->getPosition().x + 0*mEntity->getPhysicComponent()->getSize().x / 2.0f)
		notify(-1);

}

void Slider_dot::notify(int direction)
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->Action_dot(direction);
}

void Slider_dot::Action(float value, float min, float max, float step)
{
	float x = -min + value / (max - min);
	std::cout << x << std::endl;
	vec2 dotSize = vec2(glm::min(mSize.x, mSize.y))*2.0f;
	mEntity->getPhysicComponent()->setPosition(((mLeftBottom + x*vec2(mSize.x, 0) - 0.5f*dotSize + vec2(0, mSize.y / 2.0)) / mResolution)*2.0f - vec2(1));
}
