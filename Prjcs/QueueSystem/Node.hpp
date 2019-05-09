

#ifndef Node_hpp
#define Node_hpp

#include "Random.hpp"

struct Node
{
    /* data */
    int arrive_time;
    int duration;
    struct Node *next;

    Node (int arrive_time = 0, 
          int duration = Random::getRandom(EXPONETIAL, 0.1)):
          arrive_time(arrive_time), 
          duration(duration), 
          next(nullptr) {}
};

typedef struct Node Node;
typedef struct Node Customer;

#endif /* Node_hpp */