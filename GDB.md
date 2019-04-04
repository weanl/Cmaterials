The GUN Project Debugger
---
#### 1. 基本命令
  - list
  <br>行编号，函数名</br>
  
  - info breakpoints
  <br>所有断点的信息</br>
  
  - break
  <br>行编号，函数名</br>
  
  - delete
  <br>断点编号</br>
  
  - disable, enable
  <br>断点编号</br>
  
  - enable once, enable delete
  <br>一次使能</br>
  
  - next, step, finish, continue, until
  <br>单步执行，</br>
  
  - info locals, print

#### 2. 实战进阶

  - 下列有执行错误
  
 ```shell
  gcc -g -o test_linked_list linked_list.c test_linked_list.c
  ./test_linked_list
 ```
  - 可以做如下的 Debugging 流程
```shell
  1. $ gdb test_linked_list
  2. list main
  3. run
  4. backtrace
  5. break ###
  6. list ###
  7. next 2
  8. info locals
  9. step
  10. backtrace full
  11. next 4
  12. print #
  13. next
  ...
```

#### 3. 进一步考虑

GDB 的一个缺点是源码和调试过程分开，导致经常需要 list 查看代码。gdbtui 是带图形界面的，有兴趣的可以自行尝试。











