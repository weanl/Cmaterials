
#include "Node.hpp"


enum WindowStatus {
    SERVICE,
    IDLE,
};


class ServiceWindow
{
private:
    /* data */
    Customer customer;
    WindowStatus window_status;

public:
    inline ServiceWindow(/* args */) : window_status(IDLE) {};
    //
    // ~ServiceWindow();

    inline bool isIdle () const {return (window_status==IDLE);}
    inline void serveCustomer (Customer &customer) {this->customer=customer;}
    inline void setIdle () {window_status=IDLE;}
    inline void setBusy () {window_status=SERVICE;}

    inline int getCustomerArriveTime () const {return customer.arrive_time;}
    inline int getCustomerDuration () const {return customer.duration;}
};
