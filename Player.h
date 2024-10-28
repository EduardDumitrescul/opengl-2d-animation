#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"

class Player {
private:
	Shader* shader = nullptr;

	float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	unsigned int VAO;

public:

	Player(Shader* shader);
	void draw();
};

