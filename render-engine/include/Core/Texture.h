#pragma once
#include <string>
#include <iostream>
using namespace std;
class Texture
{
public:
	Texture(const char* path, int textureUnit, int colorMode);
	void use();
protected:
	unsigned int textureId;
	int textureUnit;
private:
};