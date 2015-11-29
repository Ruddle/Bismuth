#include "Letter.h"



using namespace std;
using namespace glm;

Letter::Letter(EntityManager * em, ResourcesManager * rm, std::string path, char c , glm::vec2 position, glm::vec2 resolution, float scale)
{
	vec2 unite = vec2(64.0 / 1024.0f, 64 / 1024.0f);



	
	mEntity =  new Entity2D(
		new GraphicComponent2D(
			rm->loadTexture(path, GL_RGB8, GL_LINEAR, GL_REPEAT),
			unite*vec2(c%16,15- int(c/16) ), unite),
		new PhysicComponent2D(vec2(48)*scale / resolution, (position / resolution)*2.0f - vec2(1)));

	
	em->add(mEntity);


}

Letter::~Letter()
{
	delete mEntity;
}
