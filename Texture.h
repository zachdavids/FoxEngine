#pragma once

#include <string>

class Texture
{
public:
	unsigned int id_;
	std::string type_;
	std::string path_;
	bool GetTransparent() { return transparent_; }
	bool GetFakeLighting() { return fake_lighting_; }
private:

	bool transparent_ = false;
	bool fake_lighting_ = false;
};