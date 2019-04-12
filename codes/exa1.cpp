//
// Created by weanl on 4/11/19.
//

#include <iostream>
#include <thread>

#include <mutex>

using namespace std;

void thread_task () {
    cout << "hello thread" << endl;
}

// https://changkun.de/modern-cpp/book/07-thread/index.html
void some_operation (const string &message) {
    static mutex mtx;
    lock_guard<mutex> lock(mtx);

    // TODO:

}



int main (int argc, const char *argv[]) {
    cout << "\texa1: multi-thread. ######" << endl;

    thread t(thread_task);
    t.join();

    return 0;
}

