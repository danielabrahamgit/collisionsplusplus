#include "physics.h"
#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

physics::physics() {
    physics(10);
}

physics::physics(unsigned num_balls_in){
    srand(time(NULL));
    num_balls = num_balls_in;
    balls = new Ball[num_balls];
    balls[0].set_rand_color();
    balls[0].set_rand_speed();
    balls[0].set_pos(-0.5, 0.5, 0.1);


    balls[1].set_rand_color();
    balls[1].set_rand_speed();
    balls[1].set_pos(0.5, -0.5, 0.1);
    //iterate through all the balls
    /*
    for (int i = 0; i < num_balls; i++) {
      balls[i].set_rand_color();
      balls[i].set_rand_speed();
      balls[i].set_pos(-0.5 + i * 1/2, 0.5, 0.1);
    }
    */
}

void physics::next_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < num_balls; i++) {
        balls[i].draw();
        balls[i].update();
        for (int j = i + 1; j < num_balls; j++) {
            double dist = pow(balls[i].x - balls[j].x, 2) 
                        + pow(balls[i].y - balls[j].y, 2);
            if (dist < pow(balls[i].r + balls[j].r, 2)) {
                cout << "Collision Detected" << endl;
            }
        }
    }
    glutSwapBuffers();
}

void physics::collide(Ball* a, Ball* b) {
    //collision vector
    double cx = a->x - b->x;
    double cy = a->y - b->y;
    //Normalize
    double norm = sqrt(pow(cx, 2) + pow(cy, 2));
    cx = cx / norm;
    cy = cy / norm;
    //c is a unit vector
    double nx = -cy;
    double ny = cx;
    //New a vector:
    double ax = (cx * a->x) + (cy * a->y);
    double ay = (-cy * a->x) + (cx * a->y);
    //New b vector:
    double bx = (cx * b->x) + (cy * b->y);
    double ay = (-cy * b->x) + (cx * b->y);
}