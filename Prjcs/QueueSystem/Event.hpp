

#ifndef Event_hpp
#define Event_hpp

#include "Random.hpp"

struct Event
{
    /* data */
    int occur_time;
    int event_type;
    Event *next;

    Event (int occur_time = Random::getRandom(POISSON, 0.5),
           int event_type = -1): 
           occur_time(occur_time), 
           event_type(event_type), 
           next(nullptr) {}
};

#endif /* Event_hpp */
