#include "Panel.h"

using namespace glm;

Panel::Panel(EntityManager* em, ResourcesManager* rm, glm::vec2 resolution,glm::vec2 leftBottom,glm::vec2 size)
{
	mCenter = new Entity2D(
		new GraphicComponent2D( 
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(0, 0), vec2(1.0/4.0f)),
		new PhysicComponent2D(size /resolution, (leftBottom/resolution)*2.0f - vec2(1) ));

	mRight = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(0, 1.0 / 4.0f), vec2(2.0 / 4.0f, 1.0 / 4.0f)),
		new PhysicComponent2D(  vec2(2.0f,size.y) / resolution  , ((leftBottom+vec2( size.x-2.0f,0)) / resolution)*2.0f - vec2(1)));

	mLeft = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(2.0 / 4.0f, 1.0 / 4.0f), vec2(2.0 / 4.0f, 1.0 / 4.0f)),
		new PhysicComponent2D(vec2(2.0f, size.y) / resolution, ((leftBottom + vec2(   0, 0)) / resolution)*2.0f - vec2(1)));

	mUp = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(1.0 / 4.0f, 0.0 / 4.0f), vec2(1.0 / 4.0f, 2.0 / 4.0f)),
		new PhysicComponent2D(vec2(size.x, 2.0f) / resolution, ((leftBottom + vec2(0, size.y-2.0)) / resolution)*2.0f - vec2(1)));

	mDown = new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture("Texture/ui.png", GL_RGB8, GL_NEAREST, GL_REPEAT),
			vec2(1.0 / 4.0f, 2.0 / 4.0f), vec2(1.0 / 4.0f, 2.0 / 4.0f)),
		new PhysicComponent2D(vec2(size.x, 2.0f) / resolution, ((leftBottom + vec2(0, 0)) / resolution)*2.0f - vec2(1)));
	
	em->add(mCenter);
	em->add(mRight);
	em->add(mLeft);
	em->add(mDown);
	em->add(mUp);
	
}



Panel::~Panel()
{



}

void Panel::update(Input & input)
{




}
