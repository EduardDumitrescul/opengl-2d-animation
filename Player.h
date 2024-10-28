#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"
#include "Texture.h"

class Player {
private:
	Shader* shader = nullptr;
	Texture* texture = nullptr;

	float vertices[20] = {
		0, 0, 0, 0, 1,
		0.1, 0, 0, 1, 1,
		0.1, 0.1, 0, 1, 0,
		0, 0.1, 0, 0, 0,
	};

	unsigned int VBO;
	unsigned int VAO;

public:

	Player(Shader* shader, Texture* texture);

	void render();
	void freeResources();
};

