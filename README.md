# XuSTL
Simulate the implementation of STL library

模拟实现STL

## 容器

### Vector

* 支持模板
* 使用原生指针作为迭代器
* 支持普通迭代器 const迭代器 反向迭代器 const反向迭代器
* 支持无参构造（有缓冲区）数量+数据构造 范围构造 拷贝构造 移动构造 初始化列表构造
* 支持赋值重载 移动赋值
* 支持判等 判不等 判空
* 支持获取当前数据个数 当前容量大小
* 支持reserve resize clear swap
* 支持[]获取数据
* 支持push_back pop_back insert erase 

### List
* 支持模板
* 是带头双向非循环链表
* 头节点的前驱指向尾节点 尾节点的后继指向nullptr
* 支持普通迭代器 const迭代器 反向迭代器 const反向迭代器
* 支持无参构造数量+数据构造 范围构造 拷贝构造 移动构造 初始化列表构造
* 支持赋值重载 移动赋值
* 支持判等 判不等 判空
* 支持获取当前数据个数
* 支持front back
* 支持clear swap
* 支持[]获取数据
* 支持push_back pop_back insert erase 

## 适配器

### 迭代器适配器

const iterator
reverse iterator
const reverse iterator