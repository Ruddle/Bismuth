#include "Slider.h"



using namespace glm;

Slider::Slider(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size)
{
	mValue = 0.5;

	mBar = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(2.0 / 4.0f), vec2(1.0 / 4.0f)),
		new PhysicComponent2D(size*2.0f / resolution, (leftBottom / resolution)*2.0f - vec2(1)));

	mDot = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(1.0 / 4.0f), vec2(1.0 / 4.0f)),
		new PhysicComponent2D( vec2(min(size.x,size.y))*2.50f / resolution, (leftBottom / resolution)*2.0f - vec2(1)));


	em->add(mBar);
	em->add(mDot);


	mUIBar = new UI_box(mBar->getPhysicComponent());
	mUIDot = new UI_box(mDot->getPhysicComponent());

	input->addObserver(mUIBar);
	input->addObserver(mUIDot);
}

Slider::~Slider()
{
}
