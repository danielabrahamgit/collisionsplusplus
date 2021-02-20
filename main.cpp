#include <GL/glut.h>
#include <iostream>
#include "physics.h"

#define WIDTH 800
#define HEIGHT 800
#define FPS 60
#define NUM_BALLS 2

physics* phys_handler;

using namespace std;

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
    phys_handler = new physics(NUM_BALLS);
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