class Ball {
    public:
    //Radius
    double r;
    //Mass
    double m;
    //Colors
    double red, green, blue;
    //x, y positions
    double x, y;
    //Previous x, y positions
    double x_p, y_p;
    //x y velocities
    double vx, vy;
    //accerleration
    double ax, ay;
    //coefficient of restitution
    double rest;

    //Constructor
    Ball(double, double, double, double);
    Ball();
    //Draws the ball
    void draw();
    //Update the ball's position
    void update();
    //Set the ball's mass and radius
    void set_mass_rad(double, double);
    //Set the ball's pos
    void set_pos(double, double);
    void set_rand_pos();
    //set the ball's color
    void set_color(double, double, double);
    void set_rand_color();
    //set the ball's speed
    void set_speed(double, double);
    void set_rand_speed(double);
    //Set the ball's acceleration
    void set_acc(double, double);
    //Set the ball's restitution
    void set_rest(double=1.0);
    //Collision between two balls
    static void collide(Ball*, Ball*);
};