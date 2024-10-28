#include <GL/glew.h>
#include <GL/freeglut.h>
#include "base/Shader.h"
#include "Player.h"


Player::Player(Shader* shader, Texture* texture) {
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
	if (yPosition >= 0) {
		yPosition += yVelocity * deltaTime / 1000;
		yVelocity -= gravitationalAcceleration * deltaTime / 1e3;
	}
	if (yPosition < 0) {
		yPosition = 0;
		yVelocity = 0;
		isInAir = false;
	}
}

void Player::jump()
{
	if (!isInAir) {
		yVelocity = 2;
		isInAir = true;
	}
}
