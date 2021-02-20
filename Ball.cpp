#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <cmath>
#include "Ball.h"


#define NUM_SEG 300

Ball::Ball() {
    set_pos(0, 0);
    set_mass_rad(100, 1);
    set_color(1.0, 1.0, 1.0);
    set_speed(0, 0);
}

Ball::Ball(double x_in, double y_in, double r_in, double m_in) {
    set_pos(x_in, y_in);
    set_mass_rad(r_in, m_in);
    set_color(1.0, 1.0, 1.0);
    set_speed(0, 0);
}

void Ball::set_mass_rad(double r_in, double m_in) {
    r = r_in;
    m = m_in;
}

void Ball::set_pos(double x_in, double y_in, double r_in) {
    x = x_in;
    y = y_in;
    r = r_in;
}

void Ball::set_rand_pos() {
    x = (1 - (rand() * 2.0 / RAND_MAX));
    y = (1 - (rand() * 2.0 / RAND_MAX));
}

void Ball::set_color(double red_in, double green_in, double blue_in) {
    red = red_in;
    blue = blue_in;
    green = green_in;
}

void Ball::set_rand_color() {
    red   = rand() * 1.0 / RAND_MAX;
    blue  = rand() * 1.0 / RAND_MAX;
    green = rand() * 1.0 / RAND_MAX;
}

void Ball::set_speed(double vx_in, double vy_in) {
    vx = vx_in;
    vy = vy_in;
}

void Ball::set_rand_speed() {
    vx = (1 - (rand() * 2.0 / RAND_MAX)) / 40.0;
    vy = (1 - (rand() * 2.0 / RAND_MAX)) / 40.0;
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
    glColor3f(red, green, blue);
    for (int i = 0; i <= NUM_SEG; i++)
    {
        double angle = 2 * M_PI * i / 300;
        double x = cos(angle) * this->r;
        double y = sin(angle) * this->r;
        glVertex2f(this->x + x, this->y + y); // output vertex
    }
    glEnd();
}