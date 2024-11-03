/// @file Queue.hpp
/// @brief 队列
#pragma once
#include "List.hpp"
#include <iostream>
#include <initializer_list>

namespace XuSTL
{
    template <class T, class Con = List<T>>
    class Queue
    {
    public:
        Queue() {}
        void push(const T &value)
        {
            _queue.push_back(value);
        }
        void pop()
        {
            _queue.erase(_queue.begin());
        }
        T &front()
        {
            return _queue[0];
        }
        const T &front() const
        {
            return _queue[0];
        }
        size_t size() const
        {
             return _queue.size();
        }
        bool empty() const
        {
            return _queue.empty();
        }

    private:
        Con _queue;
    };
}