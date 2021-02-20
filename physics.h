#include "Ball.h"

class physics {
    public:
    Ball* balls;
    unsigned num_balls;

    physics();
    physics(unsigned, double);
    void next_frame();
    void collide(Ball*, Ball*);
    double compute_energy();
};