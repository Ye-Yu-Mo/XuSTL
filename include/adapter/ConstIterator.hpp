/// @file ConstIterator.hpp
/// @brief Const迭代器适配器
#pragma once
#include <iostream>
namespace XuSTL
{
    /// @brief Const迭代器类
    /// @tparam Iterator 迭代器
    /// @tparam Ref 自动推导的常量引用
    /// @tparam Ptr 自动推导的常量指针
    template <class Iterator,
              class Ref = typename std::iterator_traits<Iterator>::reference,
              class Ptr = typename std::iterator_traits<Iterator>::pointer>
    class ConstIterator
    {
    public:
        using Self = ConstIterator<Iterator, Ref, Ptr>; ///< 简化
        /// @brief 构造函数 禁止隐式类型转换
        explicit ConstIterator(Iterator it) : _it(it) {}
        /// @brief 拷贝构造函数
        ConstIterator(const Self &other) : _it(other._it) {}
        /// @brief 移动构造函数
        ConstIterator(ConstIterator &&other) noexcept : _it(other._it) {}
        /// @brief 赋值运算符
        Self &operator=(const Self &other)
        {
            if (this != &other)
            {
                _it = other._it;
            }
            return *this;
        }
        /// @brief 移动赋值运算符
        Self &operator=(Self &&other) noexcept
        {
            if (this != &other)
            {
                _it = other._it;
            }
            return *this;
        }
        /// @brief 获取迭代器内容
        /// @return 常量引用
        Ref operator*() const
        {
            return *_it;
        }
        /// @brief operator-> 实现
        Ptr operator->() const
        {
            return _it; // 返回当前元素的指针
        }
        /// @brief 前置++
        /// @return ++后的迭代器
        Self &operator++()
        {
            ++_it;
            return *this;
        }
        /// @brief 后置++
        /// @return ++前的迭代器
        Self operator++(int)
        {
            Self tmp = *this;
            ++_it;
            return tmp;
        }
        /// @brief 前置--
        /// @return --后的迭代器
        Self &operator--()
        {
            --_it;
            return *this;
        }
        /// @brief 后置--
        /// @return --前的迭代器
        Self operator--(int)
        {
            Self tmp = *this;
            --_it;
            return tmp;
        }
        /// @brief 判断迭代器是否相等
        /// @param other 另一个迭代器
        /// @return 相等返回 true 否则返回false
        bool operator==(const Self &other) const { return _it == other._it; }
        /// @brief 判断迭代器是否不相等
        /// @param other 另一个迭代器
        /// @return 不相等返回 true 否则返回false
        bool operator!=(const Self &other) const { return _it != other._it; }

    public:
        Iterator _it; ///< 正向迭代器
    };
}