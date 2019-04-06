Makefile
---

  - <br>makefile如何记录整个项目工程的所有需要编译的文件列表及如何反映整个项目中各个模块的依赖关系？</br>
  - <br>提供了makefile策略描述后，make工具又是如何解析makefile文件来帮助哦我们构建其编译系统的？</br>

#### 1. 最简单的例子

  &emsp;&emsp;makefile文件内容：
```shell
# 最简单的makefile文件
all:
  echo "Hello world!"   #注意：每行命令都必须以tab键开始
```

  &emsp;&emsp;make命令的四种形式：
```console
$ make
$ make -f <makefile_name>
$ make <target>
$ make -C <subdir> <target>
```



#### 2. 简单的例子

```console
$ tree project_simple
project_simple
|--main.c
|--Makefile
|--simple.c

```

```c
// ---------------------------------------------
// simple.c
void simple()
{
    printf("This is simple project!\n");
}
```

```c
// ---------------------------------------------
// main.c
extern void simple();

int main()
{
    simple();
    return 0;
}
```

```make
# Makefile
simple:
    gcc -o simple main.c simple.c
```

```shell
$ make
```

#### 3. 进阶的例子

```console
$ tree project_complicated
project_complicated
|--complicated.c
|--complicated.h
|--main.c
|--Makefile

```

```c
// ---------------------------------------------
// main.c
#include <stdio.h>
#include "complicated.h"
int main()
{
    printf("%s\n", HELLO_STRING);
    complicated();
    return 0;
}
```

```c
// ---------------------------------------------
// complicated.h
#ifndef __COMPLICATED_H__
#define __COMPLICATED_H__
#define HELLO_STRING "Hello !"
#define PROJECT_NAME "complicated"
extern void complicated(void);
#endif
```

```c
// ---------------------------------------------
// complicated.c
#include <stdio.h>
#include "complicated.h"
void complicated(void)
{
    printf("This is a %s porject!\n", PROJECT_NAME);
}
```

&emsp;&emsp;精确的分析清楚项目的依赖关系，是编写一个好的makefile的关键。（添加注释增加可读性）

```make
# ---------------------------------------------
# Makefile
# 描述：complicated 项目 makefile文件
# 版本：v1.1
# 修改记录：
# 1. 为complicated项目makefile添加注释

# 终极目标规则，生成 complicated 可执行文件
complicated: main.o complicated.o
    gcc -o complicated main.o complicated.o

# 子规则1， main.o的生成规则
main.o: main.c
    gcc -o main.o -c main.c

# 子规则2，complicated.o的生成规则
complicated.o: complicated.c
    gcc -o complicated.o -c complicated.c
```
&emsp;&emsp;(头文件呢？？？ 会保留中间的 .o 文件)


#### 4. makefile中的变量

&emsp;&emsp;定义与引用的例子：
```make
object = program.o foo.o utils.o

program: $(object)
    gcc -o program $(object)
    
$(object): def.h    
```

&emsp;&emsp;直接展开与递归展开：**=, :=, +=, ?=**



&emsp;&emsp;特殊变量（自动化变量，）
- $@ 代表规则中的目标文件名
- $< 代表规则的第一个依赖的文件名
- $^ 代表规则中所有依赖文件的列表，文件名用空格分割

```make
all: first second third
    echo "\$$@ = $@"
    echo "$$< = $<"
    echo "$$^ = $^"

first second third:
```

&emsp;&emsp;变量的替换引用：
```make
# 将变量“VAR”所表示的值中所有字符串“A”结尾的字符替换为“B”的字
$(VAR:A=B)
${VAR:A=B}
```

#### 5. 进阶例子的进一步修改

```make
# ---------------------------------------------
# Makefile
# 描述：complicated 项目 makefile文件
# 版本：v1.2
# 修改记录：
# 1. 为complicated项目makefile添加注释
# 2. 使用变量改进我们complicated项目的makefile

# 定义可执行文件变量
executable := complicated
# 定义源文件列表变量
sources := main.c complicated.c
# 使用变量的引用替换，定义object 文件列表
objects := $(sources:.c=.o)
# 定义编译命令变量
CC := gcc


# 终极目标规则，生成 complicated 可执行文件
$(executable): $(objects)
    $(CC) -o $@ $^

# 子规则1， main.o的生成规则
main.o: main.c
    $(CC) -o $@ $^

# 子规则2，complicated.o的生成规则
complicated.o: complicated.c
    g$(CC) -o $@ $^
```




