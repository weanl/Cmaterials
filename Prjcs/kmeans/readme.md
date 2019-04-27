K-Means
---

#### 1. 主要知识点

    - C++ 语言语法
    - K-Means 算法思路与实现
    - 并行计算思路与实现
    - boost 库的常用技巧 (Smart Pointers, Variant, tokenizer)
<br>实验环境： boost=1.68.0, mpich=3.2.1</br>


#### 2. 项目结构与框架

```
|-- cluster
|   |-- distance.hpp
|-- datasets
|-- mainalgorithm
|-- utilities

```

#### 3. 环境配置

##### 3.1 mpich 的下载与安装
```bash
>> wget http://labfile.oss.aliyuncs.com/courses/1193/mpich-3.2.1.zip
>> unzip mpich-3.2.1.zip
>> cd mpich-3.2.1
>> sudo make install
```