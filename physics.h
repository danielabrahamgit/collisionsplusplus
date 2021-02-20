#include "Ball.h"

class physics {
    public:
    Ball* balls;
    unsigned num_balls;

    physics();
    physics(unsigned);
    void next_frame();
};