#pragma once
#include "Block.h"
#include "Player.h"
#include "Collision.h"
#include <vector>

class Player;

class CollisionDetector {
private:
	std::vector <Block*> blocks;
	Player* player = nullptr;
public:

	CollisionDetector(Player* player, std::vector <Block*> blocks);

	float detectDown();
	float detectRight();
	//Collision detectRight();
};

