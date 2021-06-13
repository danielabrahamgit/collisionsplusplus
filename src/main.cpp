#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "physics.h"

#define WIDTH 1000
#define HEIGHT 1000
#define FPS 120

using namespace std;

//Global Physics engine
physics* phys_handler;
//To be intialized
unsigned NUM_BALLS;

//Used for rendering
int num_frames = -1;
int frame_count = 0;
bool is_forward = true;
typedef struct list_of_rendered_balls {
    vector<Ball> balls;
} ball_list_t;
ball_list_t* rendered_balls;


//Regular display function
void display(void) {
    phys_handler->next_frame(true);
}

//Display function for rendered scenes
void display_rendered(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    ball_list_t blist = rendered_balls[frame_count];
    for (int i = 0; i < NUM_BALLS; i++) {
        blist.balls.at(i).draw();
    }
    glutSwapBuffers();
    
    frame_count += is_forward ? 1 : -1;

    if (frame_count == num_frames) {
        is_forward = false;
        frame_count--;
    } else if (frame_count == -1) {
        is_forward = true;
        frame_count++;
    }
}

//Glut timer function
void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, Timer, 0);
}

//Rendering function, this one takes a while
void render_scene(bool reversed) {
    cout << "Rendering ... " << endl; 
    rendered_balls = new ball_list_t[num_frames];
    if (reversed) {
        for (int f = num_frames - 1; f >= 0; f--) {
            for (int i = 0; i < NUM_BALLS; i++) {
                rendered_balls[f].balls.push_back(*(phys_handler->balls.at(i)));
            }
            phys_handler->next_frame(false);
        }
    } else {
        for (int f = 0; f < num_frames; f++) {
            for (int i = 0; i < NUM_BALLS; i++) {
                rendered_balls[f].balls.push_back(*(phys_handler->balls.at(i)));
            }
            phys_handler->next_frame(false);
        }
    }
    cout << "Rendering Completed. Starting Simulation" << endl;
}


int main(int argc, char** argv)
{   
    //Setup stuff
    double vel_scaling = 0;
    double gravity = 0;
    double radius = 0.007;
    //Only used for random_init
    NUM_BALLS = 15;

    phys_handler = new physics(NUM_BALLS, WIDTH, HEIGHT);
    phys_handler->structured_init(vel_scaling, gravity, radius);
    //phys_handler->random_init(vel_scaling, gravity);
    NUM_BALLS = phys_handler->num_balls;

    //Initialize the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);

    //Render
    if (argc == 2) {
        num_frames = FPS * atoi(argv[1]);
        render_scene(false);
        glutCreateWindow("Collision Simulator: Rendered");
        glutDisplayFunc(display_rendered);
    } 
    //Dont render
    else {
        glutCreateWindow("Collision Simulator");
        glutDisplayFunc(display);
    }

    //Specify how often to draw
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}


