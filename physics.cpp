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
    double x = -1;
    double y = 0.8;
    double w = 0.05;
    for (int i = 0; i < num_balls; i++) {
        balls[i].set_mass_rad(w, 100);
        balls[i].set_rand_color();
        balls[i].set_rand_speed();
        if (x < 1 - 2 * (balls[i].r + w))
            x += 2 * (balls[i].r + w);
        else {
            x = -1 + 2 * (balls[i].r + w);
            y -= 2 * (balls[i].r + w);
        }
        balls[i].set_pos(x, y);
    }
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
                collide(&balls[i], &balls[j]);
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

    //New a positions
    double ax_p = (cx * a->x_p) + (cy * a->y_p);
    double ay_p = (-cy * a->x_p) + (cx * a->y_p);
    //New b poistions
    double bx_p = (cx * b->x_p) + (cy * b->y_p);
    double by_p = (-cy * b->x_p) + (cx * b->y_p);

    //New a velocity:
    double avx = (cx * a->vx) + (cy * a->vy);
    double avy = (-cy * a->vx) + (cx * a->vy);
    //New b vector:
    double bvx = (cx * b->vx) + (cy * b->vy);
    double bvy = (-cy * b->vx) + (cx * b->vy);

    //Compute new velocities in new coordinate system
    double avx_final_c = (((a->m - b->m) * avx) + (2.0 * b->m * bvx)) / (b->m + a->m);
    double bvx_final_c = ((2 * a->m * avx) - ((a->m - b->m) * bvx)) / (b->m + a->m);

    //Calculate tc (collision time)
    double tc = (abs(bx_p - ax_p) - (a->r + b->r)) / abs(avx - bvx);
    //Find final positions
    double ax_final_c = ax_p + (tc * avx) + (1 - tc) * avx_final_c;
    double bx_final_c = bx_p + (tc * bvx) + (1 - tc) * bvx_final_c;

    double temp_ax = ax_p + (tc * avx);
    double temp_bx = bx_p + (tc * bvx);

    //Rotate back to original frame of reference
    //Velocity
    a->vx = (cx * avx_final_c) - (cy * avy);
    a->vy = (cy * avx_final_c) + (cx * avy);
    b->vx = (cx * bvx_final_c) - (cy * bvy);
    b->vy = (cy * bvx_final_c) + (cx * bvy);
    //Position
    a->x = (cx * ax_final_c) - (cy * ay_p);
    a->y = (cy * ax_final_c) + (cx * ay_p);
    b->x = (cx * bx_final_c) - (cy * by_p);
    b->y = (cy * bx_final_c) + (cx * by_p);
}

double physics::compute_energy() {
    double total_energy = 0;
    for (int i = 0; i < num_balls; i++) {
        total_energy += 0.5 * balls[i].m * (pow(balls[i].vx, 2) + pow(balls[i].vy, 2));
    }
    return total_energy;
}