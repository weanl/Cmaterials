
#ifndef CHATROOM_SERVER_H
#define CHATROOM_SERVER_H


#include <string>
#include "Common.h"

using namespace std;


class Server {

public:
    Server ();

    void Init ();
    void Close ();
    void Start ();

private:
    // set as private
    int SendBroadcastMessage (int client_fd);
    struct sockaddr_in serverAddr;
    int listenser;
    int epfd;
    list<int> clients_list;
};


#endif // CHATROOM_SERVER_H