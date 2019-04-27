
#include <iostream>

#include "Server.h"

using namespace std;


Server::Server () {
    serverAddr.sin_family = PF_INET; // IP protocol family.
    serverAddr.sin_port = htons(SERVER_PORT); // Port number.
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP); // IP string --> uint32_t

    listenser = 0; // socket's returned value
    epfd = 0; // epoll fd
}


void Server::Init () {
    cout << "Init Server ..." << endl;

    listenser = socket(PF_INET, SOCK_STREAM, 0);
    // Returns a file descriptor for the new socket, or -1 for errors.
    if (listenser < 0) {perror("listenser"); exit(-1);}

    // Give the socket FD the local address ADDR (which is LEN bytes long)
    if (bind(listenser, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind error");
        exit(-1);
    }

    /* 
    Prepare to accept connections on socket FD
        Returns 0 on success, -1 for errors 
    */
    int ret = listen(listenser, 5);
    if (ret < 0) {perror("listen error"); exit(-1);}

    cout << "Start to listen: " << SERVER_IP << endl;

    // 在内核中创建事件表
/* Creates an epoll instance.  Returns an fd for the new instance.
   The "size" parameter is a hint specifying the number of file
   descriptors to be associated with the new instance.  The fd
   returned by epoll_create() should be closed with close().  */    
    epfd = epoll_create(EPOLL_SIZE);
    if (epfd < 0) {perror("epfd error"); exit(-1);}

    // 往事件表中添加监听事件 (socket)
    addfd(epfd, listenser, true);

}


void Server::Close () {
    // Close the file descriptor FD
    close(listenser);
    close(epfd);
}


int Server::SendBroadcastMessage (int client_fd) {

    char buf[BUF_SIZE], message[BUF_SIZE];
    bzero(buf, BUF_SIZE);
    bzero(message, BUF_SIZE);

    cout << "read from client(clientID = " << client_fd << ")" << endl;
    int len = recv(client_fd, buf, BUF_SIZE, 0);

    // the client close the connection
    if (len == 0) {
        close(client_fd);

        clients_list.remove(client_fd);
        cout << "ClientID = " << client_fd
            << " closed.\n now there are "
            << clients_list.size()
            << " client in the chat romm"
            << endl;
    }
    // broadcast
    else {
        // only one left
        if (clients_list.size() == 1) {
            send(client_fd, CAUTION, strlen(CAUTION), 0);
            return len;
        }
        // in the form of SERVER_MESSAGE="ClientID #%d say >> %s"
        sprintf(message, SERVER_MESSAGE, client_fd, buf);
        for (list<int>::iterator it=clients_list.begin(); it!=clients_list.end(); it++) {
            if (*it != client_fd) {
                if (send(*it, message, BUF_SIZE, 0) < 0) {
                    return -1;
                }
            }
        }

    }

    return len;
}


void Server::Start () {

    // allocate "events" buffer
    static struct epoll_event events[EPOLL_SIZE];

    Init();

    while (true) {
        /*
         Returns the number of triggered events returned in "events" buffer.
        */
        // 如何统计被激活的事件的个数的？？
        int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        if (epoll_events_count < 0) {perror("epoll failure"); break;}

        cout << "epoll_events_count = " << epoll_events_count << endl;

        for (int i=0; i<epoll_events_count; i++) {
            int sockfd = events[i].data.fd;

            // 监听端口的文件描述符被激活，有新的连接请求
            if (sockfd == listenser) {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                // return the fd of a new socket
                int clientfd = accept(listenser, (struct sockaddr*)&client_address, &client_addrLength);

                cout << "client connection from: " 
                    << inet_ntoa(client_address.sin_addr) << ":"
                    << ntohs(client_address.sin_port) << ", clientfd = "
                    << clientfd << endl;
                
                addfd(epfd, clientfd, true);

                // push the connection to client_list
                clients_list.push_back(clientfd);
                cout << "Add new clientfd = " << clientfd << " to epoll" << endl;
                cout << "Now there are " << clients_list.size() << " clients in the chat room" << endl;

                cout << "welcome message" << endl;
                char message[BUF_SIZE];
                bzero(message, BUF_SIZE);
                sprintf(message, SERVER_WELCOME, clientfd);
                
                // 一个连接失败就关闭服务器吗。。。
                int ret = send(clientfd, message, BUF_SIZE, 0);
                if (ret < 0) {
                    perror("send error");
                    Close();
                    exit(-1);
                }
            }
            // 已有的连接有数据请求，对应的文件描述符被激活
            else {
                int ret = SendBroadcastMessage(sockfd);
                if (ret < 0) {
                    perror("error");
                    Close();
                    exit(-1);
                }
            }
        }
    } 

    Close();
}