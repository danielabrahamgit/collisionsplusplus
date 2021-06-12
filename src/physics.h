#include "Ball.h"
#include <vector>

class physics {
    public:
    std::vector<Ball*> balls;
    unsigned num_balls;
    unsigned width;
    unsigned height;

    physics(unsigned, unsigned, unsigned);
    void random_init(double);
    void next_frame(bool);
    double compute_energy();
};