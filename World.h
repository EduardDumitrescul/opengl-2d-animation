#pragma once
#include "base/Shader.h"
#include "Texture.h"
#include "Background.h"
#include "Block.h"
#include "CollisionDetector.h"
#include "Player.h"

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
		".......................xxxxxxx.................................................",
		"..............xxxxxxx..........................................................",
		".......xxxxx...................................................................",
		"xxx........................................................................xxxx",
		"................................................................xxxxxxxx.......",
		"...............................................................................",
		"...........................xxxxxxxxxxxxxxxxxxxxxxxxx...........................",
		"......................xxxx.....................................................",
		"................xxxx..xxxx..x..................................................",
		"........xxxxx...xxxx..xxxx........x...........x................................",
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
		"...............................................................................",
	};

	Block* blocks[24][80];
	CollisionDetector* collisionDetector;

	float offset = 0;
	float speed = 0.01;


	Shader* playerShader;
	Shader* backgroundShader;
	Shader* blockShader;

	Texture* playerTexture;
	Texture* blockTexture;

	Player* player;
	Background* background;
	
	void loadShaders();

	void loadTextures();

	void createObjects();

	void loadBlocks();

	void renderBlocks();

	void update();

	void initCollisionDetector();

	World();
public:
	static void render();

	static void input(unsigned char key, int x, int y);

	static World* getInstance();

	float detectCollisionDown();
};