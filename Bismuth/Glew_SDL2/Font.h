#pragma once
#include <string>

class Font
{
public:
	Font(std::string path, float scale);
	~Font();

	std::string getPath() { return mPath; }
	float getScale() { return mScale; }

private:
	std::string mPath;
	float mScale;
};

