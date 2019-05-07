
#include "Event.hpp"
#include "Queue.hpp"
#include "ServiceWindow.hpp"


class QueueSystem
{
private:
    /* data */
    // 让系统运行一次
    double run ();
    // 初始化参数
    void init ();
    // 清空参数
    void end ();

    // 获得空闲窗口索引
    int getIdleServiceWindow ();
    // 处理顾客达到事件
    void customerArrived ();
    // 处理顾客离开事件
    void customerDepature ();

    int window_num;
    int total_serive_time;
    int total_customer_stay_time;
    int total_customer_num;

    ServiceWindow   *windows;
    Queue<Customer> customer_list;
    Queue<Event>    event_list;
    Event           *current_event;

    double avg_customers;
    double avg_stay_time;

public:
    QueueSystem (int total_service_time, int window_num);
    ~QueueSystem ();

    void simualte (int simulate_num);

    inline double getAvgStayTime () {return avg_stay_time;}
    inline double getAvgCustomers () {return avg_customers;}
};
