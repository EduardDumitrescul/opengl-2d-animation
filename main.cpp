// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"
#include "base/Shader.h"

#include "Player.h"
#include "Background.h"

Shader* backgroundShader;
Background* background;

int previousTime = 0;


void RenderFunction(void)
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME); // current time in milliseconds
	int deltaTime = (currentTime - previousTime);
	previousTime = currentTime;
	background->update(deltaTime);

	glClear(GL_COLOR_BUFFER_BIT);       

	

	//Shader playerShader = Shader("player.vert", "player.frag");
	//Player player = Player(&playerShader);
	background->render();

	glFlush();
	glutPostRedisplay();
}
void Cleanup(void)
{
	
}

int main(int argc, char* argv[])
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
	glutInitWindowSize(600, 600); //dimensiunile ferestrei
	glutCreateWindow("Grafica pe calculator - primul exemplu"); // titlul ferestrei
	glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);

	backgroundShader = new Shader("background.vert", "background.frag");
	background = new Background(backgroundShader);


	glutMainLoop();
}

