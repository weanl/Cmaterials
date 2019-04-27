#ifndef CHATROOM_COMMON_H
#define CHATROMM_COMMON_H


#include <list>

#include <netinet/in.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h> // Unix Standard

#include <string.h>

// buffer size is 65535
#define BUF_SIZE 0xFFFF

#define EPOLL_SIZE 150

#define SERVER_IP "127.0.0.1"
// #define SERVER_IP "114.212.87.130"
#define SERVER_PORT 8888
#define SERVER_WELCOME "Welcome you join the chat room! Your chat ID is: Client #%d"
#define CAUTION "There is only one in the chat room!"
#define SERVER_MESSAGE "ClientID #%d say >> %s"

#define EXIT "exit"

// add new fd into epoll_fd (a table)
// Edge Triggered(ET) and Level Triggered(LT)
static void addfd (int epoll_fd, int fd, bool enable_ET) {

    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;

    if (enable_ET) {ev.events |= EPOLLET;}

    // epoll 的事件注册函数
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);

    // 设置socket为nonblocking模式
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
    // F_SETFL means Set file status flags. 
    printf("fd added to epoll!\n\n");
}


#endif // CHATROOM_COMMON_H