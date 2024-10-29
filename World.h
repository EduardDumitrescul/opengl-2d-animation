#pragma once
#include "base/Shader.h"
#include "Texture.h"
#include "Player.h"
#include "Background.h"
#include "Block.h"

class World {
private:
	static World* instance;

	int previousTime = 0;
	const int width = 80, height = 24;
	const float blockWidth = 2.0 / 40, blockHeight = 2.0 / 24;

	char map[24][80] = {
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"...............................................................................",
		"........x...........x..............x...........x...............................",
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
		"...............................................................................",
	};

	Block* blocks[24][80];

	float offset = 0;
	float speed = 0.01;


	Shader* playerShader;
	Shader* backgroundShader;
	Shader* blockShader;

	Texture* playerTexture;
	Texture* blockTexture;

	Player* player;
	Background* background;
	
	void loadShaders() {
		playerShader = new Shader("player.vert", "player.frag");
		backgroundShader = new Shader("background.vert", "background.frag");
		blockShader = new Shader("block.vert", "block.frag");
	}

	void loadTextures() {
		playerTexture = new Texture("player.jpg");
		blockTexture = new Texture("block.png");
	}

	void createObjects() {
		player = new Player(playerShader, playerTexture);
		background =new  Background(backgroundShader);
	}

	void loadBlocks() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (map[i][j] == 'x') {
					blocks[i][j] = new Block(blockShader, blockTexture);
				}
			}
		}
	}

	void renderBlocks() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (map[i][j] == 'x') {
					float x = (j - 20) * blockWidth + offset;
					if (x < -1) {
						x += (width - 1) * blockWidth;
					}
					float y = ((height - i) - 12) * blockHeight;
					blocks[i][j]->setPosition(x, y);
					blocks[i][j]->render();
				}
			}
		}
	}

	void update() {
		int currentTime = glutGet(GLUT_ELAPSED_TIME); // Get current time in milliseconds
		int deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		offset -= speed;
		if (offset < -width * blockWidth) {
			offset += width * blockWidth;
		}

		player->update(deltaTime);
		background->update(deltaTime);
	}

	World() {
		loadShaders();
		loadTextures();
		createObjects();
		loadBlocks();
	}
public:
	static void render() {
		instance->update();
		glClear(GL_COLOR_BUFFER_BIT); 

		instance->background->render();
		instance->player->render();
		instance->renderBlocks();

		glutSwapBuffers();
	}

	static void input(unsigned char key, int x, int y) {
		switch (key) {
			case ' ': {
				instance->player->jump();
				break;
			}
		}
	}

	static World* getInstance() {
		if (instance == nullptr) {
			instance = new World();
		}
		return instance;
	}
};

World* World::instance = nullptr;