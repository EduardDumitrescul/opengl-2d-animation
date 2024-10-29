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
		"...............................................................................",
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
		"...............................................................................",
	};
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

	void update() {
		int currentTime = glutGet(GLUT_ELAPSED_TIME); // Get current time in milliseconds
		int deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		player->update(deltaTime);
		background->update(deltaTime);
	}

	World() {
		loadShaders();
		loadTextures();
		createObjects();
	}
public:




	static void render() {
		instance->update();
		glClear(GL_COLOR_BUFFER_BIT); 

		instance->background->render();
		instance->player->render();

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