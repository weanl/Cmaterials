

#include "QueueSystem.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main () {

    clock_t start = clock();

#ifdef __APPLE__
    std::srand((unsigned)std::time(0));
#else
    std::srand(time(0));
#endif

    int total_service_time = 240;
    int window_num = 4;
    int simulate_num = 100000;

    QueueSystem system(total_service_time, window_num);
    system.simulate(simulate_num);

    clock_t end = clock();

    std::cout << "The average time of customer stay in bank: "
    << system.getAvgStayTime() << std::endl;

    std::cout << "The number of customer arrive bank per minute: "    
    << system.getAvgCustomers() << std::endl;

    std::cout << ""
    << system.getTotalCustomerNum() << std::endl;

    std::cout << "time consumed: "
    << (double)(end - start) / CLOCKS_PER_SEC << " /s" << std::endl;


    return 0;
}