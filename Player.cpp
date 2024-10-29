#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"
#include "Player.h"
#include "World.h"

# define M_PI  3.14159265358979323846


float Player::closestValue(float value, std::vector<float> set)
{
	float minDiff = 1e10;
	float closestValue = value;
	for (float s : set) {
		float diff = std::abs(s - value);
		if (minDiff > diff) {
			minDiff = diff;
			closestValue = s;
		}
	}
	return closestValue;
}

Player::Player(World* world, Shader* shader, Texture* texture) {
	this->world = world;
	this->shader = shader;
	this->texture = texture;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Player::render() {
	shader->use();
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 1.0));
	shader->setMat4(scaleMatrixTag,scaleMatrix);
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1), glm::vec3(xPosition, yPosition, 0));
	shader->setMat4(translateMatrixTag, translateMatrix);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), rotationAngle, glm::vec3(0, 0, 1));
	shader->setMat4(rotationMatrixTag, rotationMatrix);

	texture->use();
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Player::freeResources() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Player::update(int deltaTime)
{
	// Check for collision below the player
	float collision = world->detectCollisionDown();
	//std::cout << collision << '\n';

	// If a block is detected beneath the player
	if (collision > 1e-7) {
		std::cout << "down\n";
		// Wrap rotation angle to stay within [0, 2π)
		while (rotationAngle >= 2 * M_PI) {
			rotationAngle -= 2 * M_PI;
		}
		while (rotationAngle < 0) {
			rotationAngle += 2 * M_PI;
		}

		// Adjust position to the top of the block
		yPosition += collision;

		// Snap rotation angle to nearest right angle
		rotationAngle = closestValue(rotationAngle, { 0, M_PI / 2, M_PI, 3 * M_PI / 2, 2 * M_PI });

		// Reset velocity as the player has landed
		yVelocity = 0;
		isInAir = false;
	}
	else if(isInAir){
		std::cout << "jump" << " " << yVelocity << '\n';
		// No block detected beneath the player; apply gravity
		rotationAngle += rotationSpeed * deltaTime / 1000.0;

		// Apply vertical movement and gravity
		yPosition += yVelocity * deltaTime / 1000.0;
		yVelocity -= gravitationalAcceleration * deltaTime / 1000.0;
	}
	else if (collision < 0) {
		isInAir = true;
	}
}


void Player::jump()
{
	if (!isInAir) {
		yVelocity = 2;
		rotationSpeed = -0.98 * M_PI / (2 * yVelocity / gravitationalAcceleration);
		isInAir = true;
	}
}

float Player::getWidth() const
{
	return width;
}

float Player::getHeight() const
{
	return height;
}

float Player::getXPosition() const
{
	return xPosition;
}

float Player::getYPosition() const
{
	return yPosition;
}
