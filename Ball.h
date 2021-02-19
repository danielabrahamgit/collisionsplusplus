class Ball {
    public:

    double r;
    double x, y;
    double x_p, y_p;
    double vx, vy;

    Ball(double, double, double);
    Ball();
    
    void draw();
    void update();
    void set_speed(double, double);
    void set_rand_speed();
};