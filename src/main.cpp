#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "physics.h"

#define WIDTH 1000
#define HEIGHT 1000
#define FPS 120
#define NUM_BALLS 50

using namespace std;

physics* phys_handler;
int num_frames = -1;
int frame_count = 0;

void display(void) {
  phys_handler->next_frame();
}

void display_rendered(void) {
  printf("Yo\n");
}

void Timer(int value) {
  glutPostRedisplay();
  glutTimerFunc(0 * 1000 / FPS, Timer, 0);
}


int main(int argc, char** argv)
{   
    double vel_scaling = 0;
    phys_handler = new physics(NUM_BALLS, WIDTH, HEIGHT);
    phys_handler->random_init(vel_scaling);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Collision Simulator");
    //Needs rendering, grab number of seconds
    if (argc == 2) {
        printf("Rendering ...\n");
        num_frames = FPS * atoi(argv[1]);
        glutDisplayFunc(display_rendered);
    } else {
        glutDisplayFunc(display);
    }
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}


