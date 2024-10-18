/// @file ReverseIterator.hpp
/// @brief 反向迭代器适配器
#include <iostream>
#pragma once

namespace XuSTL
{
    /// @brief 反向迭代器类
    /// @tparam Iterator 迭代器
    /// @tparam Ref 自动推导的引用
    /// @tparam Ptr 自动推导的指针
    template <class Iterator,
              class Ref = typename std::iterator_traits<Iterator>::reference,
              class Ptr = typename std::iterator_traits<Iterator>::pointer>
    class ReverseIterator
    {
    public:
        using Self = ReverseIterator<Iterator, Ref, Ptr>; ///< 简化
        /// @brief 构造函数 禁止隐式类型转换
        explicit ReverseIterator(Iterator it) : _it(it) {}
        /// @brief 拷贝构造函数
        /// @param other 另一个迭代器
        ReverseIterator(const Self &other) : _it(other._it) {}
        /// @brief 移动构造函数
        /// @param other 另一个迭代器的右值
        ReverseIterator(ReverseIterator &&other) noexcept : _it(other._it) {}
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
        Self &operator=(ReverseIterator &&other) noexcept
        {
            if (this != &other)
            {
                _it = other._it;
            }
            return *this;
        }
        /// @brief 获取迭代器内容
        /// @return 引用
        Ref operator*() const
        {
            Iterator tmp = _it; // 使用临时变量
            return *(--tmp);    // 返回前一个元素的引用
        }
        /// @brief operator-> 实现
        Ptr operator->()
        {
            Iterator tmp = _it; // 使用临时变量
            --tmp;              // 返回前一个元素的指针
            return tmp;
        }
        /// @brief 反向迭代器 前置++
        /// @return ++后的反向迭代器
        Self &operator++()
        {
            --_it;
            return *this;
        }
        /// @brief 反向迭代器 后置++
        /// @return ++前的反向迭代器
        Self operator++(int)
        {
            Self tmp = *this;
            --_it;
            return tmp;
        }
        /// @brief 反向迭代器 前置--
        /// @return --后的反向迭代器
        Self &operator--()
        {
            ++_it;
            return *this;
        }
        /// @brief 反向迭代器 后置--
        /// @return --前的迭代器
        Self operator--(int)
        {
            Self tmp = *this;
            ++_it;
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