

#ifndef Queue_hpp
#define Queue_hpp

#include <cstdio>
#include "Event.hpp"
#include <iostream>

template <typename T>
class Queue
{
private:
    /* data */
    T *front, *rear;
    int length;

public:
    Queue () {
        this->front = new T;
        if (!this->front) {
            perror("memory allocated fally for Queue!");
            exit(-1);
        }
        this->front->next = nullptr;
        this->rear = this->front;
        this->length = 0;
    }
    ~Queue () {
        clearQueue();
        delete this->front;
        this->front = nullptr;
        this->rear = nullptr;
    }

    void clearQueue () {
        while (this->front->next) {
            T *curr = this->front->next;
            this->front->next = curr->next;
            delete curr;
        }
        this->rear = this->front;
        this->length = 0;
    }

    T* enqueue (T &node) {
        T *clone = new T;
        if (!clone) {
            perror("memory allocated fally for Queue!");
            exit(-1);
        }        
        *clone = node;
        this->rear->next = clone;
        this->rear = clone;
        this->length++;
        return this->front;
    }

    T* dequeue () {
        if (!this->front->next) {
            return nullptr;
        } 
        T *curr = this->front->next;
        this->front->next = curr->next;
        // notice if only one left
        if (curr == this->rear) {
            this->rear=this->front;
        }
        this->length--;
        return curr;
    }

    // when it is an event queue
    // ++ these codes are elegant
    T* orderEnqueue (Event &event) {
        Event *clone = new Event;
        if (!clone) {
            perror("memory allocated fally for Queue!");
            exit(-1);
        }
        *clone = event;
        if (!this->front->next) {
            enqueue(*clone);
            return this->front;
        }
        Event *prev = this->front;
        while (prev->next && prev->next->occur_time < clone->occur_time) {
            prev = prev->next;
        }
        clone->next = prev->next;
        prev->next = clone;
        return this->front;
    }

    inline int getLength () {return this->length;}
    
    /*   
    int length () {
        int length=0;
        T *tmp = this->front->next;
        while (tmp) {
            tmp = tmp->next;
            length++;
        }
        return length;
    }
    */
    
};


#endif /* Queue_hpp */
