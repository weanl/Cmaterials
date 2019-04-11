//
// Created by weanl on 4/11/19.
//
/*
 * refer to:
 *  https://www.jianshu.com/p/835f4d37395b
 */

#include "exa1.h"

#include <iostream>
#include <thread>
#include <mutex>

void multithread () {

    std::cout << "hello, Exa1_multithread!\n";
}

// one thread can interrupt another one, without lock
void foo1 (int i) {
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "thread_func: id = " << this_id << ", " << i<< std::endl;
}
int run_fool () {

    for (uint8_t i=0; i<4; i++) {
        std::thread t(foo1, i);

        //?
        t.detach();
    }

    return 0;
}


// one thread cannot interrupt another one, with lock, but ...
//  the latter threads will run until the former ends, if t.detach() --> t.join()
std::mutex g_displaymutex;
void foo2 (int i) {
    g_displaymutex.lock();
    std::thread::id this_id = std::this_thread::get_id();
    //
    //g_displaymutex.lock();
    std::cout << "thread_func: id = " << this_id << ", " << i<< std::endl;
    //
    g_displaymutex.unlock();
}
int run_foo2 () {

    for (uint8_t i=0; i<4; i++) {
        std::thread t(foo1, i);

        //?
        //t.detach();
        t.join();
    }

    return 0;
}















int main () {

    run_foo2();
    return 0;
}