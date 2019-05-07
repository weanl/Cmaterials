

struct Node
{
    /* data */
    int arrive_time;
    int duration;
    struct Node *next;

    Node () {}
};

typedef struct Node Node;
typedef struct Node Customer;
