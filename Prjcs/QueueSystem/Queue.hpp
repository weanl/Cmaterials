

template <typename T>
class Queue
{
private:
    /* data */
    T *font, *rear;

public:
    Queue(/* args */);
    ~Queue();

    void clearQueue ();
    T* enqueue (T &node);
    T* dequeue ();
    T* orderEnqueue (Event &event);
    int length ();
};


