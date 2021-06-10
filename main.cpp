#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "physics.h"

#define WIDTH 1000
#define HEIGHT 1000
#define FPS 60
#define NUM_BALLS 30

using namespace std;

physics* phys_handler;

void display(void)
{
  phys_handler->next_frame();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(0 * 1000 / FPS, Timer, 0);
}


int main(int argc, char** argv)
{   
    double vel_scaling = 0;
    double radius = 0.05;
    double mass = 10;
    phys_handler = new physics(NUM_BALLS);
    phys_handler->random_init(vel_scaling, radius, mass);

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


