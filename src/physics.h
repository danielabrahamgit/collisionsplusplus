#include "Ball.h"

class physics {
    public:
    Ball* balls;
    unsigned num_balls;
    unsigned width;
    unsigned height;

    physics(unsigned, unsigned, unsigned);
    void random_init(double);
    void next_frame();
    double compute_energy();
};