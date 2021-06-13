#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include "PoissonGenerator.h"
#include "physics.h"

#define WORD_FILE "word_to_balls/word_as_balls"

using namespace std;

physics::physics(unsigned num_balls_in, unsigned width_in, unsigned height_in) {
    /* Initialize class variables */
    num_balls = num_balls_in;
    width = width_in;
    height = height_in;
}

void physics::structured_init(double v_scale, double gravity, double radius) {
    //Call python file to generate the location file that we need
    string cmd = "python word_to_balls/main.py ";
    cmd += to_string(width);
    cmd += " ";
    cmd += to_string(height);
    cmd += " ";
    cmd += "Raz Processing";
    system(cmd.c_str());

    //Initialize ball map which is about to get populated
    uint8_t ball_map[height][width];

    //Read the file
    unsigned i = 0;
    unsigned j = 0;
    int next_int;
    ifstream myfile(WORD_FILE);
    if (myfile.is_open())
    {
        while (myfile >> next_int )
        {
            ball_map[i][j] = next_int;
            j++;
            if (j == width) {
                i++;
                j = 0;
            }
        }
        myfile.close();
    }
    
    //Generate radius and mass
    double mass = radius * 200.0;

    //Counts number of balls
    unsigned ball_count = 0;
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            if (ball_map[r][c]) {
                ball_count++;
                Ball* new_ball = new Ball(
                    (2.0 * c - width)  * 1.0 / width,
                    (2.0 * r - height) * 1.0 / height,
                    radius,
                    mass
                );
                //new_ball->set_rand_color();
                new_ball->set_color(1, 1, 1);
                new_ball->set_rand_speed(v_scale);
                new_ball->set_acc(0, gravity);
                balls.push_back(new_ball);
            }
        }
    }

    //Primer balls
    double p_radius = 3 * radius;
    double p_mass = 3 * mass;
    for (int i = 0; i < 4; i++) {
        int val1 = 1 - 2 * (i & 1);
        int val2 = 1 - 2 * ((i >> 1) & 1);
        Ball* primer_ball = new Ball(val1 * (1 - p_radius), val2 * (1 - p_radius), p_radius, p_mass);
        primer_ball->set_color(1, 0, 0);
        primer_ball->set_speed(val1 * 0.01, val2 * 0.01);
        balls.push_back(primer_ball);
        ball_count++;
    }
    num_balls = ball_count;
}

void physics::random_init(double v_scale, double gravity) {
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
        new_ball->set_rand_speed(v_scale);
        new_ball->set_acc(0, gravity);
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
    sort(balls.begin(), balls.end(), [](const Ball* f, const Ball* s) { return f->x - f->r < s->x - s->r; });

    for (auto it = balls.begin(); it != balls.end(); it++) {
        auto act_it = active_list.begin();
        //active_list.insert(active_list.end(), *it);
        while (act_it != active_list.end()) {
            if (abs((*it)->x - (*act_it)->x) < (*it)->r + (*act_it)->r) {
                double dist = pow((*it)->x - (*act_it)->x, 2) 
                            + pow((*it)->y - (*act_it)->y, 2);
                if (dist < pow((*it)->r + (*act_it)->r, 2)) {
                    Ball::collide((*it), (*act_it));
                }
                act_it++;
            } else {
                act_it = active_list.erase(act_it);
            }
        }
        active_list.push_back(*it);
    }

    // Dumb but working solution
    // for (int i = 0; i < num_balls; i++) {
    //     for (int j = 0; j < i; j++) {
    //         Ball* ball1 = balls.at(i);
    //         Ball* ball2 = balls.at(j);
    //         double dist = pow(ball1->x - ball2->x, 2) 
    //                     + pow(ball1->y - ball2->y, 2);
    //         if (dist < pow(ball1->r + ball2->r, 2)) {
    //             cout << "Actual Hit" << endl;
    //             Ball::collide(ball1, ball2);
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