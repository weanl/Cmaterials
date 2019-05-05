oneline chart room
---

#### 1. 实验知识点与环境

    - 

#### 2. 需求分析
    - 服务器：能够接受新的客户端连接，并将每个客户端发过来的信息发给所有其他的客户端
    - 客户端：能够连接服务器，并向服务器发送消息，同时接收服务器发过来的任何消息
<br>这是一个简单的聊天室需求，。。。</br>

#### 3. 抽象与细化

##### 3.1 客户端
（连接服务器、支持用户输入聊天信息并发送给服务器、接收并现实服务器的消息、退出连接）
<br>子进程1：</br>

....

#### 4. 



#### 5. 代码结构

```
|-- chatroom

    |-- Common.h

    |-- Client.h
    |-- Client.cpp
    |-- ClientMain.cpp

    |-- Server.h
    |-- Server.cpp
    |-- ServerMain.cpp

    |-- Makefile
```

#### 6. 疑点、难点
    - 文件描述符是怎样的？
    - epfd是epoll的文件描述符，与事件表的关系
    - close(int __fd) in <unistd.h>
    - htons 将主机字节顺序转为网络字节顺序
    -  bzero() in <string.h>
    - pid = fork() 系统调用，返回：-1，错误；0，标志位子进程；1，标志为原父进程。
    （子进程拥有父进程所有内存段的精确副本。在现代的UNIX变种中，这遵循出自SunOS-4.0的虚拟内存模型，
    根据寫入時複製语义，物理内存不需要被实际复制。取而代之的是，两个进程的虚拟内存页面可能指向物理内存中的同一个页，
    直至它们写入该页时，写入才会发生。来自维基百科）

#### 7. epoll 基本流程

##### 7.1 epfd = epoll_create(EPOLL_SIZE)

##### 7.2 add fd to epoll 
    客户端和服务器有自己的 epoll及对应文件描述符。
    addfd(epfd, sock, true); 客户端初始化时，将连接服务端的请求进行注册。
    addfd(epfd, pipe_fd[0], true); 客户端初始化时，将管道的读端进行注册。
    addfd(epfd, listenser, true); 服务器初始化时，将监听套接字进行注册。
    addfd(epfd, clientfd, true); 对于新的客户端连接，服务器将其进行注册。
```c++
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
```

##### 7.3 创建事件表，并监测triggered的事件

```c++
// allocate "events" buffer
static struct epoll_event events[EPOLL_SIZE];

int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);

for (int i=0; i<epoll_events_count; i++) {
    int sockfd = events[i].data.fd;
    if (sockfd == listenser) {continue;}
    else {continue;}
}

```


#### 8. 管道的使用
    - 客户端利的管道设计思路
```c++
int pipe_fd[2];
if (pipe(pipe_fd) < 0) {perror("pipe error"); exit(-1);}
addfd(epfd, pipe_fd[0], true);
// ...
// sub process to write the pipe_fd[1]
write(pipe_fd[1], message, strlen(message)-1); 
// will trigger read in pipe_fd[0]
read(events[i].data.fd, message, BUF_SIZE);
```