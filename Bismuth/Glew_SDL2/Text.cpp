#include "Text.h"

using namespace std;
using namespace glm;

Text::Text(EntityManager * em, ResourcesManager * rm, std::string path, std::string text, glm::vec2 position, glm::vec2 resolution)
{

	for (int i = 0; i < text.size(); i++)
	{
		mLetters.push_back( new Letter(em,rm,path,text[i],position + vec2(i*70,0),resolution));
	}


}

Text::~Text()
{
}
