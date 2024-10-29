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

		// Check for collision in both x and y directions
		float xOverlap = -(std::abs(xPlayer - xBlock) - (playerWidth + blockWidth) / 2);
		float yOverlap = -(std::abs(yPlayer - yBlock) - (playerHeight + blockHeight) / 2);

		if (xOverlap > 0 && yOverlap > 0) {
			// Determine the collision direction based on positions
			if (yPlayer > yBlock && std::abs(yPlayer - yBlock) > std::abs(xPlayer - xBlock)) {
				//std::cout << xPlayer << ' ' << yPlayer << ' ' << xBlock << ' ' << yBlock << '\n';
				return yOverlap; // Player is above the block
			}
			//else if (yPlayer < yBlock && std::abs(yPlayer - yBlock) > std::abs(xPlayer - xBlock)) {
			//	return Up; // Player is below the block
			//}
			//else if (xPlayer > xBlock) {
			//	return Left; // Player is to the right of the block
			//}
			//else {
			//	return Right; // Player is to the left of the block
			//}
		}
	}
	return -1;
}

//float CollisionDetector::detectRight() {
//	float xPlayer = player->getXPosition();
//	float yPlayer = player->getYPosition();
//	float playerWidth = player->getWidth();
//	float playerHeight = player->getHeight();
//
//	for (const auto& block : blocks) {
//		float xBlock = block->getXPosition();
//		float yBlock = block->getYPosition();
//		float blockWidth = block->getWidth();
//		float blockHeight = block->getHeight();
//
//		// Check for collision in both x and y directions
//		bool xOverlap = std::abs(xPlayer - xBlock) < (playerWidth + blockWidth) / 2;
//		bool yOverlap = std::abs(yPlayer - yBlock) < (playerHeight + blockHeight) / 2;
//
//		if (xOverlap && yOverlap) {
//			// Determine the collision direction based on positions
//			if (yPlayer > yBlock && std::abs(yPlayer - yBlock) > std::abs(xPlayer - xBlock)) {
//				std::cout << xPlayer << ' ' << yPlayer << ' ' << xBlock << ' ' << yBlock << '\n';
//				return Down; // Player is above the block
//			}
//			//else if (yPlayer < yBlock && std::abs(yPlayer - yBlock) > std::abs(xPlayer - xBlock)) {
//			//	return Up; // Player is below the block
//			//}
//			//else if (xPlayer > xBlock) {
//			//	return Left; // Player is to the right of the block
//			//}
//			//else {
//			//	return Right; // Player is to the left of the block
//			//}
//		}
//	}
//	return None;
//}
