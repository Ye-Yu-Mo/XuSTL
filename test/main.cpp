#include "vector.hpp"
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

    // 测试清空
    vec3.clear();
    std::cout << "清空后，Vector 中的元素: " << vec3.size() << std::endl;
}

int main()
{
    testVector();
    return 0;
}