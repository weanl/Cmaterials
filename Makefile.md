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
// simple.c
void simple()
{
    printf("This is simple project!\n");
}
```

```c
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
```




