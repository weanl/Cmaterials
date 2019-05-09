

#ifndef Random_hpp
#define Random_hpp

#include <cstdlib>
#include <cmath>

enum RandomType {
    UNIFORM,
    EXPONETIAL,
    POISSON
};


class Random
{
private:
    /* data */
public:
    Random(/* args */);
    ~Random();

    static double getRandom (RandomType type, double parameter) {
        switch (type)
        {
        case UNIFORM:
            return uniform(parameter);
            break;
        case EXPONETIAL:
            return exponential(parameter);
            break;
        case POISSON:
            return poisson(parameter);
            break;

        default:
            return 0;
            break;
        }
    }

    static double uniform (double max = 1) {
        return ((double)std::rand()/RAND_MAX) * max;
    }

    static double exponential (double lambda) {
        return -log(1 - uniform()) / lambda;
    }
    
    static double poisson (double lambda) {
        int t = 0;
        double p = exp(-lambda);
        double sum = p, upper = uniform();
        while (true) {
            if (sum > upper) {break;}
            t++;
            p *= (lambda/t);
            sum += p;
        }
        return t;
    }
};

#endif /* Random_hpp */