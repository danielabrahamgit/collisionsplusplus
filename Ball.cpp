#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include "Ball.h"

#define NUM_SEG 300

using namespace std;

Ball::Ball() {
    x = x_p = 0;
    y = y_p = 0;
    r = 100;
    vx = 0;
    vy = 0;
    set_speed(0, 0);
}

Ball::Ball(double x_in, double y_in, double r_in) {
    x = x_p = x_in;
    y = y_p = y_in;
    r = r_in;
    set_speed(0, 0);
}

void Ball::set_speed(double vx_in, double vy_in) {
    vx = vx_in;
    vy = vy_in;
}

void Ball::set_rand_speed() {
    srand(time(NULL));
    vx = (rand() * 1.0 / RAND_MAX) / 40.0;
    cout << vx << endl;
    vy = (rand() * 1.0/  RAND_MAX) / 40.0;
    cout << vy << endl;
}

void Ball::update() {
    //Update positions 
    x += vx;
    y += vy;

    //hit right/left wall
    if (x > 1 - r) {
        x = 2 * (1 - r) - x;
        vx = -vx;
    } else if (x < -1 + r) {
        x = 2 * (-1 + r) - x;
        vx = -vx;
    } 
    //hit top/bottom wall
    if (y > 1 - r) {
       y = 2 * (1 - r) - y;
        vy = -vy;
    } else if (y < -1 + r) {
        y = 2 * (-1 + r) - y;
        vy = -vy;
    } 
}

void Ball::draw() {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= NUM_SEG; i++)
    {
        double angle = 2 * M_PI * i / 300;
        double x = cos(angle) * this->r;
        double y = sin(angle) * this->r;
        glVertex2f(this->x + x, this->y + y); // output vertex
    }
    glEnd();
}