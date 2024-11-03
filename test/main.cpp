#include "Vector.hpp"
#include "List.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "HashTable.hpp"
using namespace XuSTL;
void testVector()
{
    // 测试默认构造函数
    XuSTL::Vector<int> vec1;
    std::cout << "默认构造的 Vector，初始大小: " << vec1.size() << ", 容量: " << vec1.capacity() << std::endl;

    // 测试带值构造函数
    XuSTL::Vector<int> vec2(5, 10);
    std::cout << "带值构造的 Vector，大小: " << vec2.size() << ", 容量: " << vec2.capacity() << std::endl;

    // 测试 push_back 和访问元素
    vec2.push_back(20);
    vec2.push_back(30);
    std::cout << "添加元素后，Vector 中的元素: ";
    for (const auto &value : vec2)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // 测试 pop_back
    vec2.pop_back();
    std::cout << "pop_back 后，Vector 中的元素: ";
    for (const auto &value : vec2)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // 测试插入元素
    vec2.insert(vec2.begin() + 1, 15);
    std::cout << "插入元素后，Vector 中的元素: ";
    for (const auto &value : vec2)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // 测试大小和容量
    std::cout << "当前大小: " << vec2.size() << ", 当前容量: " << vec2.capacity() << std::endl;

    // 测试移动构造
    XuSTL::Vector<int> vec3 = std::move(vec2);
    std::cout << "移动构造后的 Vector，大小: " << vec3.size() << ", 容量: " << vec3.capacity() << std::endl;

    // 测试反向迭代器
    for (auto rit = vec3.rbegin(); rit != vec3.rend(); rit++)
        std::cout << *rit << " ";
    std::cout << std::endl;

    // 测试清空
    vec3.clear();
    std::cout << "清空后，Vector 中的元素: " << vec3.size() << std::endl;
}

void testList()
{
    XuSTL::List<int> list;

    // 测试 push_back 和 size
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    std::cout << "Size after push_back(1, 2, 3): " << list.size() << std::endl; // 应该输出 3

    // 测试 front 和 back
    std::cout << "Front: " << list.front() << std::endl; // 应该输出 1
    std::cout << "Back: " << list.back() << std::endl;   // 应该输出 3

    // 测试 push_front
    list.push_front(0);
    std::cout << "Front after push_front(0): " << list.front() << std::endl; // 应该输出 0
    std::cout << "Back after push_front(0): " << list.back() << std::endl;   // 应该输出 3

    // 测试下标操作
    std::cout << "Element at index 1: " << list[1] << std::endl; // 应该输出 1

    // 测试迭代器
    std::cout << "List contents using iterator: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 pop_back
    list.pop_back();
    std::cout << "Size after pop_back: " << list.size() << std::endl; // 应该输出 3

    // 测试 pop_front
    list.pop_front();
    std::cout << "Size after pop_front: " << list.size() << std::endl; // 应该输出 2

    // 测试插入和删除
    auto it = list.begin();
    list.insert(it, -1); // 在头部插入 -1
    std::cout << "List after insert(-1) at the beginning: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 删除第二个元素
    it++;
    list.erase(it); // 删除值为 1 的元素
    std::cout << "List after erase(1): ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试清空和大小
    list.clear();
    std::cout << "Size after clear: " << list.size() << std::endl; // 应该输出 0
}

void testStack()
{
    XuSTL::Stack<int, XuSTL::List<int>> intStack;

    // 测试栈是否为空
    std::cout << "栈是否为空？: " << (intStack.empty() ? "是" : "否") << std::endl;

    // 向栈中推入元素
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    std::cout << "推入元素后，栈大小: " << intStack.size() << std::endl;

    // 查看栈顶元素
    std::cout << "栈顶元素: " << intStack.top() << std::endl;

    // 弹出元素
    intStack.pop();
    std::cout << "弹出一个元素后，栈顶元素: " << intStack.top() << std::endl;

    // 再次弹出一个元素
    intStack.pop();
    std::cout << "再次弹出一个元素后，栈大小: " << intStack.size() << std::endl;

    // 弹出最后一个元素
    intStack.pop();
    std::cout << "弹出所有元素后，栈是否为空？: " << (intStack.empty() ? "是" : "否") << std::endl;
}

void testQueue()
{
    XuSTL::Queue<int> intQueue;

    try
    {
        std::cout << "队列是否为空？: " << (intQueue.empty() ? "是" : "否") << std::endl;

        // 入队操作
        intQueue.push(10);
        intQueue.push(20);
        intQueue.push(30);
        std::cout << "入队元素后，队列大小: " << intQueue.size() << std::endl;

        // 查看队头元素
        std::cout << "队头元素: " << intQueue.front() << std::endl;

        // 出队操作
        intQueue.pop();
        std::cout << "出队一个元素后，队头元素: " << intQueue.front() << std::endl;

        intQueue.pop();
        std::cout << "再次出队一个元素后，队列大小: " << intQueue.size() << std::endl;

        // 再次出队一个元素
        intQueue.pop();
        std::cout << "出队所有元素后，队列是否为空？: " << (intQueue.empty() ? "是" : "否") << std::endl;

        // 测试出队空队列时的异常
        intQueue.pop();
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
    }
}
struct KeyOfVal
{
    int operator()(const std::pair<int, std::string> &pair) const
    {
        return pair.first; // 假设第一个元素为键
    }
};

struct Hash
{
    size_t operator()(int key) const
    {
        return std::hash<int>()(key); // 使用标准库的哈希函数
    }
};
void testHash()
{

    XuSTL::HashTable<int, std::pair<int, std::string>, KeyOfVal, Hash> hashTable;
    hashTable.Insert({1, "one"});
    hashTable.Insert({2, "two"});

    if (hashTable.Find(1))
    {
        std::cout << "Key 1 found!" << std::endl;
    }

    hashTable.Erase(1);

    if (!hashTable.Find(1))
    {
        std::cout << "Key 1 erased!" << std::endl;
    }
}

int main()
{
    // testVector();
    // testList();
    // testStack();
    // testQueue();
    testHash();
    return 0;
}