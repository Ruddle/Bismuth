#pragma once
#include <vector>
#include "Letter.h"
#include <string>
class Text
{
public:
	Text(EntityManager * em, ResourcesManager * rm, std::string path, std::string text, glm::vec2 position, glm::vec2 resolution);
	~Text();



private :
	std::vector<Letter*> mLetters;



};

