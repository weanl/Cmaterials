Queue System
---

## 1. 需求分析



## 2. 设计思路

- 2.1 事件驱动程序设计


## 3. 代码结构

- 3.1 事件类 `Event.hpp`

    `Event`的默认构造函数构造达到事件，且到达时间服从泊松分布。


- 3.2 顾客类 `Node.hpp`


- 3.3 顾客队列 `Queue.hpp`


- 3.4 随机数类 `Random.hpp`


- 3.5 服务窗口类 `ServiceWindow.hpp`


- 3.6 排队系统类 `QueueSystem.hpp` && `QueueSystem.cpp`

    `QueueSystem::customerArrived()`: (1) exit() is in "stdlib.h" header. 
    (2)perror() is in "stdio.h".

    `QueueSystem::customerDepature()`

- 3.7 代码编译
```bash
g++ -g -std=c++11 QueueSystem.cpp main.cpp -o main
```

## 4


