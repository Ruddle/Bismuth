#include "UI_element.h"

using namespace glm;

UI_element::UI_element(CoreBismuth* core,UI_layout* layout) : mLayout(layout), mCore(core)
{
	mEntity = new Entity2D(
		new GraphicComponent2D(
			core->resourcesManager->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(0, 0), vec2(1.0 / 4.0f)),
		new PhysicComponent2D(vec2(0.5), vec2(0)));

	core->entityManager->add(mEntity);

	mBox = new UI_box(mEntity->getPhysicComponent());
	core->input->addObserver(mBox);
}


UI_element::~UI_element()
{
}

void UI_element::add(UI_link* link)
{
	mLinks.push_back(link);
}

void UI_element::update()
{
	for (int i = 0; i < mLinks.size(); i++)
	{
		UI_link* link = mLinks[i];
		UI_element* son = link->getSon();
		elementConfig relative = link->getPositionSize(mLayout, this);/*Relative*/
		elementConfig absolute = { 
			relative.position + mEntity->getPhysicComponent()->getPosition()*2.0f ,
			relative.size / mEntity->getPhysicComponent()->getSize()*2.0f
		};

		son->setPositionSize(absolute);
		son->update();
	}
}

void UI_element::setPositionSize(elementConfig ec /*Absolute*/) 
{
	mEntity->getPhysicComponent()->setPosition(ec.position);
	mEntity->getPhysicComponent()->setSize(ec.size);
}


