Solar System
---

#### 1. 设计知识点

  - C++ 语言基础
  - 基本的 Makefile
  - 基本的 OOP 编程思想
  - OpenGL GLUT的结构基本使用 (OpenGL Utility Toolkit)






#### 2. OpenGL 和 GLUT

```shell
$sudo apt-get install freeglut3 freeglut3-dev
```
一个标准的 GLUT程序结构如下：
```c
// 使用 GLUT 的基本头文件
#include <GL/glut.h>

// 创建图形窗口的基本宏
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

// 用于注册 GLUT 的回调
void onDisplay(void);
void onUpdate(void);
void onKeyboard(unsigned char key, int x, int y);

int main(int argc, char*  argv[]) {

    // 对 GLUT 进行初始化，并处理所有的命令行参数
    glutInit(&argc, argv);
    // 这个函数指定了使用 RGBA 模式韩式颜色索引模式。另外还可以
    // 指定是使用单缓冲还是双缓冲窗口。这里我们使用 RGBA 和 双缓冲窗口
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);
    // 设置窗口被创建时左上角位于屏幕上的位置
    glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
    // 设置窗口被创建时的宽高, 为了简便起见
    glutInitWindowSize(WIDTH, HEIGHT);
    // 创建一个窗口，输入的字符串为窗口的标题
    glutCreateWindow("SolarSystem at Shiyanlou");

    // glutDisplayFunc 的函数原型为 glutDisplayFunc(void (*func)(void))
    // 这是一个回调函数，每当 GLUT 确定一个窗口的内容需要更新显示的时候,
    // glutDisplayFunc 注册的回调函数就会被执行.
    //
    // glutIdleFunc(void (*func)(void)) 将指定一个函数，用于处理当事件循环
    // 处于空闲的时候，就执行这个函数。这个回调函数接受一个函数指针作为它的唯一参数
    //
    // glutKeyboardFunc(void (*func)(unsigned char key, int x, int y))
    // 会将键盘上的键与一个函数关联，当这个键被按下或者释放时，函数就会调用
    //
    // 因此下面的三行实际上是在向 GLUT 注册关键的三个回调函数
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onUpdate);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();
    return 0;

}
```





#### 3.

main.cpp文件
```cpp
//
//  main.cpp
//  solarsystem
//
#include <GL/glut.h>
#include "solarsystem.hpp"

#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;

void onDisplay(void) {
    solarsystem.onDisplay();
}
void onUpdate(void) {
    solarsystem.onUpdate();
}
void onKeyboard(unsigned char key, int x, int y) {
    solarsystem.onKeyboard(key, x, y);
}

int main(int argc, char*  argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);
    glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
    glutCreateWindow("SolarSystem at Shiyanlou");
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onUpdate);
    glutKeyboardFunc(onKeyboard);
    glutMainLoop();
    return 0;
}
```





















#### 4.
