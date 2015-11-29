#include "Text.h"

using namespace std;
using namespace glm;

Text::Text(EntityManager * em, ResourcesManager * rm, std::string path, std::string text, glm::vec2 position, glm::vec2 resolution, float scale)
{

	for (int i = 0; i < text.size(); i++)
	{
		mLetters.push_back( new Letter(em,rm,path,text[i],position + vec2(i*48*scale,0),resolution,scale) );
	}


}

Text::~Text()
{
}

void Text::flush(EntityManager * em)
{
	for (auto it = mLetters.begin(); it != mLetters.end(); it++)
	{
		em->suppr2D((*it)->getEntity()->getId());
		//delete (*it);
	}


}
