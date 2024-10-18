#include "Vector.hpp"
#include "List.hpp"
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

int main()
{
    // testVector();
    testList();
    return 0;
}