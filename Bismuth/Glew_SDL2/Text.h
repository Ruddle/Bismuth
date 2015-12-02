#pragma once
#include <vector>
#include "Letter.h"
#include <string>
#include "Font.h"
class Text
{
public:
	Text(EntityManager * em, ResourcesManager * rm,Font * font , std::string text, glm::vec2 position, glm::vec2 resolution);
	~Text();

	void flush(EntityManager * em);

private :
	std::vector<Letter*> mLetters;



};

