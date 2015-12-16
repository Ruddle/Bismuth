#include "Slider_bar.h"

using namespace glm;

Slider_bar::Slider_bar(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size) 
{
	mEntity = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(1.0 / 4.0f,2/4.0f), vec2(2.0 / 4.0f,1)),
		new PhysicComponent2D(size*2.0f / resolution, (leftBottom / resolution)*2.0f - vec2(1)));

	em->add(mEntity);
	mUI_box = new UI_box(mEntity->getPhysicComponent());
	input->addObserver(mUI_box);
	mUI_box->addObserver(this);

}


Slider_bar::~Slider_bar()
{
}

void Slider_bar::onHover(glm::vec2 mouse)
{
}

void Slider_bar::onUnHover(glm::vec2 mouse)
{
}

void Slider_bar::onClick(glm::vec2 mouse)
{
}

void Slider_bar::onUnClick(glm::vec2 mouse)
{
}

void Slider_bar::onSelect(glm::vec2 mouse)
{
}

void Slider_bar::onDeSelect(glm::vec2 mouse)
{
}

void Slider_bar::onDrag(glm::vec2 mouse)
{
}

void Slider_bar::notify()
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->Action_bar();
}
