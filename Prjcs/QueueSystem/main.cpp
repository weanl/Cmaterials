

#include "QueueSystem.hpp"

#include <iostream>
#include <cstdlib>


int main () {

#ifdef __APPLE__
    std::srand((unsigned)std::time(0));
#else
    std::srand(time(0));
#endif

    int total_service_time = 240;
    int window_num = 4;
    int simulate_num = 100000;

    QueueSystem system(total_service_time, window_num);
    system.simualte(simulate_num);

    std::cout << system.getAvgStayTime();
    std::cout << system.getAvgCustomers();

    return 0;
}