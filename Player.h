#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"
#include "Texture.h"
#include <string>

class Player {
private:
	const std::string scaleMatrixTag = "scaleMatrix";

	Shader* shader = nullptr;
	Texture* texture = nullptr;

	float height = 2.0/24, width = 2.0/40;

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
};

