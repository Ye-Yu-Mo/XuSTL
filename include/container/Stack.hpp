/// @file Stack.hpp
/// @brief 栈
#pragma once
#include "Vector.hpp"
#include <iostream>
#include <initializer_list>

namespace XuSTL
{
    template <class T, class Con = Vector<T>>
    class Stack
    {
    public:
        Stack() {}
        void push(const T &value)
        {
            _stack.push_back(value);
        }
        void pop()
        {
            _stack.pop_back();
        }
        T &top()
        {
            return _stack[_stack.size() - 1];
        }
        const T &top() const
        {
            return _stack[_stack.size() - 1];
        }
        size_t size() const
        {
            return _stack.size();
        }
        bool empty() const
        {
            return _stack.empty();
        }

    private:
        Con _stack;
    };
}