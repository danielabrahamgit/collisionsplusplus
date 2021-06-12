#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "PoissonGenerator.h"
#include "physics.h"


using namespace std;

physics::physics(unsigned num_balls_in, unsigned width_in, unsigned height_in) {
    /* Initialize class variables */
    num_balls = num_balls_in;
    width = width_in;
    height = height_in;
}

void physics::random_init(double v_scale) {
    //Generate radius and mass
    double radius = sqrt(width * height / num_balls) / 4 / width;
    double mass = radius * 200.0;

    //Poisson Disk distribution of balls
    PoissonGenerator::DefaultPRNG PRNG;
    srand(time(NULL));
    const auto Points = PoissonGenerator::
                        generatePoissonPoints(
                            num_balls, 
                            PRNG, 
                            false, 
                            30, 
                            2 * radius);
    int i = -1;
    auto rnd_point = Points.begin();
    while (++i < num_balls) {
        Ball* new_ball = new Ball(
            (1 - radius) * (1 - 2 * rnd_point->x),
            (1 - radius) * (1 - 2 * rnd_point->y),
            radius,
            mass);
        new_ball->set_rand_color();
        new_ball->set_rand_speed(0 * v_scale);
        new_ball->set_acc(0, -0.00005);
        balls.push_back(new_ball);
        rnd_point++;
    }
}


void physics::next_frame(bool draw) {
    if (draw)
        glClear(GL_COLOR_BUFFER_BIT);
    //Update ball positions
    for (auto it = balls.begin(); it != balls.end(); it++) {
        if (draw)
            (*it)->draw();
        (*it)->update();
    }

    //Sort Balls by x position
    vector<Ball*> active_list;
    sort(balls.begin(), balls.end(), [](const Ball* f, const Ball* s) { return f->x < s->x; });

    for (auto it = balls.begin(); it != balls.end(); it++) {
        auto act_it = active_list.begin();
        while (act_it != active_list.end()) {
            if (abs((*it)->x - (*act_it)->x) < (*it)->r + (*act_it)->r) {
                double dist = pow((*it)->x -(*act_it)->x, 2) 
                            + pow((*it)->y - (*act_it)->y, 2);
                if (dist < pow((*it)->r + (*act_it)->r, 2)) {
                    Ball::collide((*it), (*act_it));
                }
                act_it++;
            } else {
                act_it = active_list.erase(act_it);
            }
        }
        active_list.insert(active_list.end(), *it);
    }

    

    // for (int i = 0; i < num_balls; i++) {
    //     for (int j = 0; j < i; j++) {
    //         double dist = pow(balls[i].x - balls[j].x, 2) 
    //             + pow(balls[i].y - balls[j].y, 2);
    //         if (dist < pow(balls[i].r + balls[j].r, 2)) {
    //             Ball::collide(&balls[i], &balls[j]);
    //         }
    //     }
    // }
    if (draw)
        glutSwapBuffers();
}

double physics::compute_energy() {
    double total_energy = 0;
    for (auto it = balls.begin(); it != balls.end(); it++) {
        total_energy += 0.5 * (*it)->m * (pow((*it)->vx, 2) + pow((*it)->vy, 2));
    }
    return total_energy;
}