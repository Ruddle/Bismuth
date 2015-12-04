#include "Text.h"

using namespace std;
using namespace glm;

Text::Text(EntityManager * em, ResourcesManager * rm,Font * font , std::string text, glm::vec2 position, glm::vec2 resolution)
{

	for (int i = 0; i < text.size(); i++)
	{
		mLetters.push_back( new Letter(em,rm,font->getPath(),text[i],position + vec2(i*16* font->getScale(),0),resolution,font->getScale()) );
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
