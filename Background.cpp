#include "Background.h"
#include <iostream>

Background::Background(Shader* shader){
	this->shader = shader;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glGenBuffers(1, &VBO_coords);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &VBO_color);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

void Background::update(int deltaTime) {
	offset -= deltaTime * speed;
	if (offset < -4) {
		offset += 4;
	}

	shader->setFloat("xOffset", offset);
}

void Background::render(){
	shader->use();
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 1, 3);
	glDrawArrays(GL_TRIANGLES, 4, 3);
	glDrawArrays(GL_TRIANGLES, 5, 3);
	glDrawArrays(GL_TRIANGLES, 8, 3);
	glDrawArrays(GL_TRIANGLES, 9, 3);
}

void Background::freeResources(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_coords);
	glDeleteBuffers(1, &VBO_color);
}
