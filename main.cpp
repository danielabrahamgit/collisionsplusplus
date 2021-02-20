#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "physics.h"

#define WIDTH 1000
#define HEIGHT 1000
#define FPS 10
#define NUM_BALLS 2

using namespace std;

physics* phys_handler;

void display(void)
{
  phys_handler->next_frame();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, Timer, 0);
}


int main(int argc, char** argv)
{
    phys_handler = new physics(NUM_BALLS, 0.2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Let us hope his works");
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}


