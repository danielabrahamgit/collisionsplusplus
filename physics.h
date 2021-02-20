#include "Ball.h"

class physics {
    public:
    Ball* balls;
    unsigned num_balls;

    physics();
    physics(unsigned);
    void random_init(double, double, double);
    void next_frame();
    double compute_energy();
};