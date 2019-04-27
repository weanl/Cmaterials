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
