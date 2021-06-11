#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "physics.h"

#define WIDTH 1000
#define HEIGHT 1000
#define FPS 120
#define NUM_BALLS 1000

using namespace std;

//Global Physics engine
physics* phys_handler;
//Used for rendering
int num_frames = -1;
int frame_count = 0;
typedef struct list_of_rendered_balls {
    Ball balls[NUM_BALLS];
} ball_list_t;

ball_list_t* rendered_balls;

void display(void) {
    phys_handler->next_frame(true);
}

void display_rendered(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (frame_count == num_frames)
        glutDestroyWindow(0);
    ball_list_t blist = rendered_balls[frame_count++];
    for (int i = 0; i < NUM_BALLS; i++) {
        blist.balls[i].draw();
    }
    glutSwapBuffers();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, Timer, 0);
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
    //Needs rendering, grab number of seconds
    if (argc == 2) {
        cout << "Rendering ... " << endl; 
        num_frames = FPS * atoi(argv[1]);
        rendered_balls = (ball_list_t*) malloc(sizeof(ball_list_t) * num_frames);
        for (int f = 0; f < num_frames; f++) {
            for (int i = 0; i < NUM_BALLS; i++) {
                rendered_balls[f].balls[i] = phys_handler->balls[i];
            }
            phys_handler->next_frame(false);
        }
        cout << "Rendering completed. Starting Simulation" << endl;
        glutCreateWindow("Collision Simulator: Rendered");
        glutDisplayFunc(display_rendered);
    } else {
        glutCreateWindow("Collision Simulator");
        glutDisplayFunc(display);
    }
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    free(rendered_balls);
    return 0;
}


