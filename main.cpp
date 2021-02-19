#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "Ball.h"

#define WIDTH 800
#define HEIGHT 800
#define FPS 60

using namespace std;

Ball* ball;

void displayMe(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  ball->draw();
  ball->update();
  glutSwapBuffers();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, Timer, 0);
}

int main(int argc, char** argv)
{
    ball = new Ball(0, 0, 0.1);
    ball->set_rand_speed();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Let us hope his works");
    glutDisplayFunc(displayMe);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}