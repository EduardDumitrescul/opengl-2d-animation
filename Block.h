#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"
#include "Texture.h"

class Block {
private:
	const std::string scaleMatrixTag = "scaleMatrix";
	const std::string translateMatrixTag = "translateMatrix";

	Shader* shader = nullptr;
	Texture* texture = nullptr;
	float speed = 0.001;

	float vertices[36] = {
		-0.5, -0.5, 0, 0, 1,
		0.5, -0.5, 0, 1, 1,
		0.5, 0.5, 0, 1, 0,
		-0.5, 0.5, 0, 0, 0,
	};

	float xPosition = 0, yPosition = 0;
	float height = 2.0 / 24, width = 2.0 / 40;

	unsigned int VBO;
	unsigned int VAO;

public:
	Block(Shader* shader, Texture* texture);

	void setPosition(float x, float y);
	void render();
	void freeResources();
};