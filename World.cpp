#pragma once
#include "base/Shader.h"
#include "Texture.h"
#include "Player.h"
#include "Background.h"
#include "Block.h"
#include "CollisionDetector.h"


void World::loadShaders() {
	playerShader = new Shader("player.vert", "player.frag");
	backgroundShader = new Shader("background.vert", "background.frag");
	blockShader = new Shader("block.vert", "block.frag");
}

void World::loadTextures() {
	playerTexture = new Texture("player.jpg");
	blockTexture = new Texture("block.png");
}

void World::createObjects() {
	player = new Player((World*)this, playerShader, playerTexture);
	background = new  Background(backgroundShader);
}

void World::loadBlocks() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j] == 'x') {
				blocks[i][j] = new Block(blockShader, blockTexture);
			}
		}
	}
}

void World::renderBlocks() {
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

void World::update() {
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

void World::initCollisionDetector() {
	std::vector <Block*> blockArray;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j] == 'x') {
				blockArray.push_back(blocks[i][j]);
			}
		}
	}
	collisionDetector = new CollisionDetector(player, blockArray);
}

World::World() {
	loadShaders();
	loadTextures();
	createObjects();
	loadBlocks();
	initCollisionDetector();
}

void World::render() {
	instance->update();
	glClear(GL_COLOR_BUFFER_BIT);

	instance->background->render();
	instance->player->render();
	instance->renderBlocks();

	glutSwapBuffers();
}

void World::input(unsigned char key, int x, int y) {
	switch (key) {
	case ' ': {
		instance->player->jump();
		break;
	}
	}
}

World* World::getInstance() {
	if (instance == nullptr) {
		instance = new World();
	}
	return instance;
}

float World::detectCollisionDown() {
	return collisionDetector->detectDown();
}

World* World::instance = nullptr;