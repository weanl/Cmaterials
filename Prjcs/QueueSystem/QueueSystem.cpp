

#include "QueueSystem.hpp"
#include "Random.hpp"
#include "Event.hpp"
#include "stdio.h"

#include <iostream>

QueueSystem::QueueSystem (int total_service_time, int window_num):
    total_service_time(total_service_time),
    window_num(window_num),
    total_customer_stay_time(0), 
    total_customer_num(0) {
        this->windows = new ServiceWindow[window_num];
}

QueueSystem::~QueueSystem () {
    delete[] windows;
}

void QueueSystem::simulate (int simulate_num) {
    double sum=0;
    for (int i=0; i<simulate_num; i++) {
        sum += run();
    }
    avg_stay_time = (double)sum / simulate_num;
    avg_customers = (double)total_customer_num / (total_service_time*simulate_num);
}

double QueueSystem::run () {
    this->init();
    while (current_event) {
        if (current_event->event_type == -1) {
            customerArrived();
        } else {
            customerDeparture();
        }
        delete current_event;
        current_event = event_list.dequeue();
        // ++
        //std::cout << total_customer_stay_time << "\n";
    }
    this->end();
    return (double)total_customer_stay_time/total_customer_num;
}

void QueueSystem::init () {
    // 第一个事件初始化为顾客到达事件
    current_event = new Event;
}

void QueueSystem::end () {
    for (int i=0; i<window_num; i++) {
        windows[i].setIdle();
    }
    customer_list.clearQueue();
    event_list.clearQueue();    
}

int QueueSystem::getIdleServiceWindow () {
    for (int i=0; i<window_num; i++) {
        if (windows[i].isIdle()) {return i;}
    }
    return -1;
}

void QueueSystem::customerArrived () {
    total_customer_num++;
    // create next event
    int inter_time = Random::getRandom(POISSON, 0.5);
    int next_arrive_time = current_event->occur_time + inter_time;
    Event next_arrive_event(next_arrive_time);

    if (next_arrive_time < total_service_time) {
        event_list.orderEnqueue(next_arrive_event);
    }

    // arange the current_event and the corresponding customer
    auto *current_customer = new Customer(current_event->occur_time);
    if (!current_customer) {
        perror("current_customer is created fally!");
        exit(-1);
    }
    customer_list.enqueue(*current_customer);
    // ++
    delete current_customer;

    // there is an idle window -> dequeue the customer in the front of customer queue.
    int idleIndex = getIdleServiceWindow();
    if (idleIndex >= 0) {
        current_customer = customer_list.dequeue();
        windows[idleIndex].serveCustomer(*current_customer);
        windows[idleIndex].setBusy();
        // time to leave and add the corresponding event
        Event departure_event(current_event->occur_time + current_customer->duration, idleIndex);
        event_list.orderEnqueue(departure_event);
    }

    // else ??? what if there is no idle window for current event
    // 我觉得应该有阻塞的设置啊
    // 本项目中采用了，事件队列+顾客队列的方式，
    // 即，由到达事件创建的顾客没有获得及时的服务，则被加入到顾客等待队列（阻塞队列）
    // 阻塞队列会被后续的顾客离开事件触发
}

void QueueSystem::customerDeparture () {
    if (current_event->occur_time < total_service_time) {
    /*
    std::cout << total_service_time << ":" 
    << current_event->occur_time << " - " << windows[current_event->event_type].getCustomerArriveTime() << "\n";*/
        total_customer_stay_time += current_event->occur_time - windows[current_event->event_type].getCustomerArriveTime();
        //
        if (customer_list.getLength()) {
        //if (customer_list.length()) {    
            Customer *next_customer = customer_list.dequeue();
            windows[current_event->event_type].serveCustomer(*next_customer);
            // deal with next depture event
            Event next_depature_event(
                current_event->occur_time + next_customer->duration,
                current_event->event_type
            );
            event_list.orderEnqueue(next_depature_event);
            delete next_customer;
        } else {
            windows[current_event->event_type].setIdle();
        }
    }
}
