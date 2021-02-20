#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <cmath>
#include "Ball.h"

#define NUM_SEG 300

Ball::Ball() {
    set_pos(0, 0);
    set_acc(0, 0);
    set_mass_rad(0.1, 1);
    set_color(1.0, 1.0, 1.0);
    set_speed(0, 0);
    set_rest();
}

Ball::Ball(double x_in, double y_in, double r_in, double m_in) {
    set_pos(x_in, y_in);
    set_acc(0, 0);
    set_mass_rad(r_in, m_in);
    set_color(1.0, 1.0, 1.0);
    set_speed(0, 0);
    set_rest();
}

void Ball::set_mass_rad(double r_in, double m_in) {
    r = r_in;
    m = m_in;
}

void Ball::set_pos(double x_in, double y_in) {
    x = x_p = x_in;
    y = y_p = y_in;
}

void Ball::set_rand_pos() {
    x = x_p = (1 - (rand() * 2.0 / RAND_MAX));
    y = y_p = (1 - (rand() * 2.0 / RAND_MAX));
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

void Ball::set_rand_speed(double v_scale) {
    vx = (1 - (rand() * 2.0 / RAND_MAX)) / 100.0 * v_scale;
    vy = (1 - (rand() * 2.0 / RAND_MAX)) / 100.0 * v_scale;
}

void Ball::set_acc(double ax_in, double ay_in) {
    ax = ax_in;
    ay = ay_in;
}

void Ball::set_rest(double rest_in) {
    rest = rest_in;
}

void Ball::update() {
    //Remember the old positions
    x_p = x;
    y_p = y;

    //update velocities
    vx += ax;
    vy += ay;

    //Update positions 
    x += vx;
    y += vy;

    //hit right/left wall
    if (x > 1 - r) {
        x = 2 * (1 - r) - x;
        vx = -vx * rest;
    } else if (x < -1 + r) {
        x = 2 * (-1 + r) - x;
        vx = -vx * rest;
    } 
    //hit top/bottom wall
    if (y > 1 - r) {
       y = 2 * (1 - r) - y;
        vy = -vy * rest;
    } else if (y < -1 + r) {
        y = 2 * (-1 + r) - y;
        vy = -vy * rest;
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

void Ball::collide(Ball* a, Ball* b) {
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

    //Rotate back to original frame of reference
    //Velocity
    a->vx = a->rest * ((cx * avx_final_c) - (cy * avy));
    a->vy = a->rest * ((cy * avx_final_c) + (cx * avy));
    b->vx = b->rest * ((cx * bvx_final_c) - (cy * bvy));
    b->vy = b->rest * ((cy * bvx_final_c) + (cx * bvy));
    //Position
    a->x = (cx * ax_final_c) - (cy * ay_p);
    a->y = (cy * ax_final_c) + (cx * ay_p);
    b->x = (cx * bx_final_c) - (cy * by_p);
    b->y = (cy * bx_final_c) + (cx * by_p);
}