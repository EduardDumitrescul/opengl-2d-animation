#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "SOIL.h"
#include <string>

class Texture {

private:
	unsigned int id;

public:
	Texture(std::string path);
	void use();
	void freeResources();
};