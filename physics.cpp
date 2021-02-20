#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include "PoissonGenerator.h"
#include "physics.h"

using namespace std;

physics::physics() {
    physics(10);
}

physics::physics(unsigned num_balls_in){
    num_balls = num_balls_in;
    balls = new Ball[num_balls];
}

void physics::random_init(double v_scale, double radius, double mass) {
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
        balls[i].set_acc(0, -.00001);
        balls[i].set_mass_rad(radius, mass);
        balls[i].set_rand_color();
        balls[i].set_rand_speed(v_scale);
        balls[i].set_pos((1 - radius) * (1 - 2 * rnd_point->x), 
                         (1 - radius) * (1 - 2 * rnd_point->y));
        rnd_point++;
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
                Ball::collide(&balls[i], &balls[j]);
            }
        }
    }
    glutSwapBuffers();
}

double physics::compute_energy() {
    double total_energy = 0;
    for (int i = 0; i < num_balls; i++) {
        total_energy += 0.5 * balls[i].m * (pow(balls[i].vx, 2) + pow(balls[i].vy, 2));
    }
    return total_energy;
}