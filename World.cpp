#pragma once
#include "base/Shader.h"
#include "Texture.h"
#include "Player.h"
#include "Background.h"
#include "Block.h"
#include "CollisionDetector.h"

#include <ft2build.h>
#include FT_FREETYPE_H  


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

	if (detectCollisionRight() > 1e-5) {
		ended = true;
	}
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
	startTime = glutGet(GLUT_ELAPSED_TIME);
	ended = false;
	loadShaders();
	loadTextures();
	createObjects();
	loadBlocks();
	initCollisionDetector();
}

void World::showEndScreen() {
	glClear(GL_COLOR_BUFFER_BIT);

	std::string scoreString = "Score: " + std::to_string(score);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0.0f, 0.2f);

	glUseProgram(0);
	glDisable(GL_TEXTURE_2D);

	std::string msg = "Game over";
	for (int i = 0; i < msg.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i]);
	}
	glRasterPos2f(0.0f, 0.0f);

	for (int i = 0; i < scoreString.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreString[i]);
	}

}



void World::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (instance->ended == false) {
		instance->update(); 
		instance->background->render();
		instance->player->render(); 
		instance->renderBlocks(); 
		instance->score = glutGet(GLUT_ELAPSED_TIME) - instance->startTime;
	}
	else {

		glColor3f(1.0f, 1.0f, 1.0f); 
		instance->showEndScreen(); 
	}

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
float World::detectCollisionRight() {
	return collisionDetector->detectRight();
}

World* World::instance = nullptr;