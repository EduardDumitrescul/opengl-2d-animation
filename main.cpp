#include <windows.h>  // Include libraries
#include <stdlib.h>   // For shader reading
#include <stdio.h>
#include <GL/glew.h>  // GLEW must be included before freeglut
#include <GL/freeglut.h>
#include "loadShaders.h"
#include "base/Shader.h"

#include "Player.h"
#include "Background.h"
#include "Texture.h"

Shader* backgroundShader;
Background* background;

Shader* playerShader;
Texture* playerTexture;
Player* player;

int previousTime = 0;
const int FPS = 60;
const int frameDelay = 1000 / FPS; // Milliseconds per frame (16.67 ms for 60 FPS)

void TimerFunction(int value)
{
    // Schedule the next frame
    glutPostRedisplay();
    glutTimerFunc(frameDelay, TimerFunction, 0);
}

void RenderFunction(void)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME); // Get current time in milliseconds
    int deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    player->update(deltaTime);
    background->update(deltaTime);  // Update background based on deltaTime

    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer

    background->render(); // Render background
    player->render();     // Render player

    glutSwapBuffers();    // Swap buffers for smooth animation (double-buffered display)
}

void UserControls(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': {
            player->jump();
            break;
        }
    }
}

void Cleanup(void)
{
    delete backgroundShader;
    delete background;
    delete playerShader;
    delete playerTexture;
    delete player;
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set up a double-buffered display mode
    glutInitWindowPosition(100, 100);            // Initial window position
    glutInitWindowSize(1600, 960);                // Window dimensions
    glutCreateWindow("Grafica pe calculator - primul exemplu"); // Window title
    glewInit();                                  // Initialize GLEW

    // Set up rendering and cleanup functions
    glutDisplayFunc(RenderFunction);
    glutCloseFunc(Cleanup);

    // Set up shaders, background, and player
    backgroundShader = new Shader("background.vert", "background.frag");
    background = new Background(backgroundShader);

    playerShader = new Shader("player.vert", "player.frag");
    playerTexture = new Texture("player.jpg");
    player = new Player(playerShader, playerTexture);

    glutKeyboardFunc(UserControls);

    // Initialize timer function to control frame rate
    glutTimerFunc(frameDelay, TimerFunction, 0);

    glutMainLoop();
}
