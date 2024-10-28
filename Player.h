#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"
#include "Texture.h"
#include <string>

class Player {
private:
	const std::string scaleMatrixTag = "scaleMatrix";
	const std::string translateMatrixTag = "translateMatrix";

	Shader* shader = nullptr;
	Texture* texture = nullptr;

	float xPosition = 0, yPosition = 0;
	float height = 2.0/24, width = 2.0/40;

	bool isInAir = false;
	float gravitationalAcceleration = 10, yVelocity = 0;

	float vertices[20] = {
		-0.5, -0.5, 0, 0, 1,
		0.5, -0.5, 0, 1, 1,
		0.5, 0.5, 0, 1, 0,
		-0.5, 0.5, 0, 0, 0,
	};

	unsigned int VBO;
	unsigned int VAO;

public:

	Player(Shader* shader, Texture* texture);

	void render();
	void freeResources();
	void update(int deltaTime);
	void jump();
};



