#pragma once
#include "Block.h"
#include "Player.h"
#include "Collision.h"
#include <vector>

#include <iostream>

CollisionDetector::CollisionDetector(Player* player, std::vector <Block*> blocks) {
	this->player = player;
	this->blocks = blocks;
}


float CollisionDetector::detectDown() {
	float xPlayer = player->getXPosition();
	float yPlayer = player->getYPosition();
	float playerWidth = player->getWidth();
	float playerHeight = player->getHeight();

	for (const auto& block : blocks) {
		float xBlock = block->getXPosition();
		float yBlock = block->getYPosition();
		float blockWidth = block->getWidth();
		float blockHeight = block->getHeight();

		float xOverlap = -(std::abs(xPlayer - xBlock) - (playerWidth + blockWidth) / 2);
		float yOverlap = -(std::abs(yPlayer - yBlock) - (playerHeight + blockHeight) / 2);

		if (xOverlap > 0 && yOverlap > 0) {
			if (yPlayer > yBlock && std::abs(yPlayer - yBlock) > std::abs(xPlayer - xBlock)) {
				
				return yOverlap; 
			}

		}
	}
	return -1;
}

float CollisionDetector::detectRight() {
	float xPlayer = player->getXPosition();
	float yPlayer = player->getYPosition();
	float playerWidth = player->getWidth();
	float playerHeight = player->getHeight();

	for (const auto& block : blocks) {
		float xBlock = block->getXPosition();
		float yBlock = block->getYPosition();
		float blockWidth = block->getWidth();
		float blockHeight = block->getHeight();

		float xOverlap = -(std::abs(xPlayer - xBlock) - (playerWidth + blockWidth) / 2);
		float yOverlap = -(std::abs(yPlayer - yBlock) - (playerHeight + blockHeight) / 2);

		if (xOverlap > 0 && yOverlap > 0) {
			if (xPlayer > xBlock && std::abs(yPlayer - yBlock) < std::abs(xPlayer - xBlock)) {

				return yOverlap;
			}

		}
	}
	return -1;
}

