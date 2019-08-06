#pragma once

#include <string>

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
	bool bTransparent = false;
	bool bFakeLighting = false;
};