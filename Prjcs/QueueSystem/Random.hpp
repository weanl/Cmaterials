


enum RandomType {
    UNIFORM,
    EXPONETIAL,
    POSSION
};


class Random
{
private:
    /* data */
public:
    Random(/* args */);
    ~Random();

    static double getRandom (RandomType type, double parameter) {}
    static double uniform (double max = 1) {}
    static double exponential (double lambda) {}
    static double poisson (double lambda) {}
};

