#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"

class Background {
private:
	Shader* shader = nullptr;
	float offset = 0;
	float speed = 0.001;

	float vertices[36] = {
		-1, -1, 0,
		1, -1, 0,
		-1, 1, 0,
		1, 1, 0,

		1, -1, 0,
		3, -1, 0,
		1, 1, 0,
		3, 1, 0,

		3, -1, 0,
		5, -1, 0,
		3, 1, 0,
		5, 1, 0
	};

	float colors[48] = {
		0.1, 0.4, 0.9, 1,
		0.6, 0.2, 0.9, 1,
		0.1, 0.4, 0.9, 1,
		0.6, 0.2, 0.9, 1,
		0.6, 0.2, 0.9, 1,
		0.1, 0.4, 0.9, 1,
		0.6, 0.2, 0.9, 1,
		0.1, 0.4, 0.9, 1,
		0.1, 0.4, 0.9, 1,
		0.6, 0.2, 0.9, 1,
		0.1, 0.4, 0.9, 1,
		0.6, 0.2, 0.9, 1,
	};

	unsigned int VBO_coords;
	unsigned int VBO_color;
	unsigned int VAO;

public:
	Background(Shader* shader);

	void update(int deltaTime);
	void render();
	void freeResources();
};