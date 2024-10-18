/// @file List.hpp
/// @brief 双向带头非循环链表
#pragma once
#include "../adapter/ReverseIterator.hpp"
#include "../adapter/ConstIterator.hpp"
#include "../adapter/ConstReverseIterator.hpp"
#include <iostream>
#include <initializer_list>

namespace XuSTL
{
    /// @brief 节点结构
    /// @tparam T 数据类型
    template <class T>
    struct ListNode
    {
        T _data;         ///< 数据
        ListNode *_next; ///< 指向下一个节点的指针
        ListNode *_prev; ///< 指向前一个节点的指针

        /// @brief 构造函数
        /// @param val 数据
        ListNode(const T &val = T()) : _data(val), _next(nullptr), _prev(nullptr) {}
    };
    /// @brief 前向声明
    /// @tparam T 数据类型
    template <class T>
    class List;
    /// @brief 链表迭代器
    /// @tparam T 数据类型
    /// @tparam Ref 数据引用
    /// @tparam Ptr 数据指针
    template <class T, class Ref = T &, class Ptr = T *>
    class ListIterator
    {
        friend class List<T>; ///< 允许 List 访问 ListIterator 的私有成员

    private:
        using Node = ListNode<T> *;             ///< 指向 ListNode 的指针类型
        using Self = ListIterator<T, Ref, Ptr>; ///< 自身类型

    public:
        /// @brief 构造函数
        /// @param node 节点指针
        ListIterator(Node node = nullptr) : _pnode(node) {}
        /// @brief 拷贝构造
        /// @param other 另一个迭代器
        ListIterator(const Self &other) : _pnode(other._pnode) {}
        /// @brief 移动构造
        /// @param other 另一个迭代器
        ListIterator(ListIterator &&other) : _pnode(other._pnode) { other._pnode = nullptr; }
        /// @brief 赋值重载
        /// @param other 另一个迭代器
        /// @return 迭代器
        Self &operator=(const Self &other)
        {
            if (this != &other)
                _pnode = other._pnode;
            return *this;
        }
        /// @brief 移动赋值重载
        /// @param other 另一个迭代器
        /// @return 迭代器
        Self &operator=(ListIterator &&other) noexcept
        {
            if (this != &other)
            {
                _pnode = other._pnode;
                other._pnode = nullptr;
            }
            return *this;
        }
        /**
         * @brief 解引用操作符，返回当前节点的数据
         * @return 当前节点的数据引用
         */
        Ref operator*() const
        {
            return _pnode->_data;
        }
        /**
         * @brief 箭头操作符，返回当前节点的数据指针
         * @return 当前节点的数据指针
         */
        Ptr operator->()
        {
            return &_pnode->_data;
        }
        Self &operator++()
        {
            if (_pnode != nullptr)
                _pnode = _pnode->_next;
            return *this;
        }
        Self operator++(int)
        {
            Self tmp = *this;
            ++(*this);
            return tmp;
        }
        Self &operator--()
        {
            if (_pnode != nullptr)
                _pnode = _pnode->_prev;
            return *this;
        }
        Self operator--(int)
        {
            Self tmp = *this;
            --(*this);
            return tmp;
        }
        bool operator==(const Self &other) const { return _pnode == other._pnode; }
        bool operator!=(const Self &other) const { return _pnode != other._pnode; }

    private:
        Node _pnode; ///< 当前节点
    };

    /// @brief 双向链表
    /// @tparam T 数据类型
    template <class T>
    class List
    {
    private:
        using Node = ListNode<T>;    ///< 节点类型
        using PNode = ListNode<T> *; ///< 节点指针类型
        using Ref = T &;             ///< 数据引用类型
        using Ptr = T *;             ///< 数据指针类型

    public:
        // 迭代器相关
        using iterator = ListIterator<T, Ref, Ptr>;
        using const_iterator = ConstIterator<iterator, iterator &, iterator *>;
        using reverse_iterator = ReverseIterator<iterator, iterator &, iterator *>;
        using const_reverse_iterator = ConstReverseIterator<iterator, iterator &, iterator *>;
        iterator begin() { return iterator(_phead->_next); }
        iterator end() { return iterator(nullptr); }
        const_iterator begin() const { return const_iterator(begin()); }
        const_iterator end() const { return const_iterator(end()); }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }
        // 构造函数和析构函数
        List() : _size(0), _phead(nullptr)
        {
            CreateHead();
        }
        /**
         * @brief 指定数量和初始值构造链表
         * @param n 初始化节点数量
         * @param value 节点初始值
         */
        List(int n, const T &value = T())
        {
            CreateHead();
            while (n--)
                push_back(value);
        }
        /**
         * @brief 使用迭代器范围构造链表
         * @tparam T_iterator 迭代器类型
         * @param first 开始迭代器
         * @param end 结束迭代器
         */
        template <class T_iterator>
        List(T_iterator first, T_iterator end)
        {
            CreateHead();
            while (first != end)
                push_back(*(first++));
        }
        /**
         * @brief 拷贝构造函数
         * @param other 另一个链表
         */
        List(const List<T> &other)
        {
            CreateHead();
            for (auto &val : other)
                push_back(val);
        }
        /**
         * @brief 移动构造函数
         * @param other 另一个链表
         */
        List(List<T> &&other) : _size(other._size), _phead(other._phead)
        {
            other._phead = nullptr;
            other.size = 0;
        }
        /**
         * @brief 初始化列表构造函数
         * @param list 初始化列表
         */
        List(const std::initializer_list<T> &list) : List(list.begin(), list.end()) {}
        /**
         * @brief 析构函数
         */
        ~List()
        {
            clear();
            delete _phead;
        }

        // 重载
        List<T> &operator=(const List<T> &other)
        {
            for (auto &val : other)
                push_back(val);
        }
        List<T> &operator=(List<T> &&other) noexcept
        {
            clear();
            _size = other._size;
            _phead = other._phead;
            other.size = 0;
            other._phead = nullptr;
            return *this;
        }
        bool operator==(const List<T> &other)
        {
            if (_size != other._size)
                return false;
            auto it1 = begin();
            auto it2 = other.begin();
            while (it1 != end() && it2 != end())
                if (*(it1++) != *(it2++))
                    return false;
            return true;
        }
        bool operator!=(const List<T> &other) { return !(*this == other); }
        Ref operator[](size_t pos)
        {
            if (pos >= _size)
                throw std::out_of_range("越界访问！");
            auto it = begin();
            for (size_t i = 0; i < pos; ++i)
                --it;
            return *it;
        }

        // 容量相关
        /**
         * @brief 获取链表的大小
         * @return 链表中元素的数量
         */
        size_t size() { return _size; }
        /**
         * @brief 检查链表是否为空
         * @return 如果链表为空返回 true，否则返回 false
         */
        bool empty() { return _size == 0; }
        /**
         * @brief 清空链表
         */
        void clear()
        {
            while (!empty())
                pop_back();
        }

        // 获取数据
        /**
         * @brief 获取链表的第一个元素
         * @return 第一个元素的引用
         * @throws std::out_of_range 当链表为空时抛出异常
         */
        Ref front()
        {
            if (empty())
                throw std::out_of_range("链表为空！");
            return _phead->_next->_data;
        }
        /**
         * @brief 获取链表的第一个元素
         * @return 第一个元素的const引用
         * @throws std::out_of_range 当链表为空时抛出异常
         */
        const Ref front() const
        {
            return front();
        }
        /**
         * @brief 获取链表的最后一个元素
         * @return 最后一个元素的引用
         * @throws std::out_of_range 当链表为空时抛出异常
         */
        Ref back()
        {
            if (empty())
                throw std::out_of_range("链表为空！");
            return _phead->_prev->_data;
        }
        /**
         * @brief 获取链表的最后一个元素
         * @return 最后一个元素的const引用
         * @throws std::out_of_range 当链表为空时抛出异常
         */
        const Ref back() const
        {
            return back();
        }

        // 修改

        /// @brief 尾插
        /// @param value 数据
        void push_back(const T &value)
        {
            PNode newNode = new Node(value);
            if (_size == 0)
            {
                _phead->_next = newNode;
                newNode->_prev = _phead;
                _phead->_prev = newNode; // 方便找最后一个元素
            }
            else
            {
                PNode tail = _phead->_prev;
                tail->_next = newNode;
                newNode->_prev = tail;
                _phead->_prev = newNode;
            }
            ++_size;
        }
        /// @brief 尾删
        void pop_back()
        {
            if (empty())
                throw std::out_of_range("链表为空！");
            PNode tail = _phead->_prev;
            PNode newTail = tail->_prev;
            newTail->_next = nullptr;
            _phead->_prev = newTail;
            delete tail;
            --_size;
        }
        /// @brief 头插
        /// @param value 数据
        void push_front(const T &value)
        {
            PNode newNode = new Node(value);
            if (_size == 0)
            {
                _phead->_next = newNode;
                newNode->_prev = _phead;
                _phead->_prev = newNode;
            }
            else
            {
                PNode headNext = _phead->_next;
                _phead->_next = newNode;
                newNode->_prev = _phead;
                newNode->_next = headNext;
                headNext->_prev = newNode;
            }
            ++_size;
        }
        /// @brief 头删
        void pop_front()
        {
            if (empty())
                throw std::out_of_range("链表为空！");
            PNode headNext = _phead->_next;
            _phead->_next = headNext->_next;
            if (headNext->_next != nullptr)
                headNext->_next->_prev = _phead;
            else
                _phead->_prev = _phead; // 空链表
            delete headNext;
            --_size;
        }
        /// @brief 指定位置插入
        /// @param pos 指定位置迭代器
        /// @param value 数据
        /// @return 插入后的迭代器
        iterator insert(iterator pos, const T &value)
        {
            PNode newNode = new Node(value);
            PNode currentNode = pos._pnode;
            if (currentNode != nullptr)
            {
                PNode prevNode = currentNode->_prev;
                prevNode->_next = newNode;
                newNode->_prev = prevNode;
                newNode->_next = currentNode;
                currentNode->_prev = newNode;
            }
            else
            {
                push_back(value);
                return iterator(_phead->_prev);
            }
            ++_size;
            return iterator(newNode);
        }
        /// @brief 删除指定位置数据
        /// @param pos 指定位置迭代器
        /// @return 删除前的下一个元素迭代器
        iterator erase(iterator pos)
        {
            PNode currentNode = pos._pnode;
            if (currentNode == nullptr)
                return end();
            PNode prevNode = currentNode->_prev;
            PNode nextNode = currentNode->_next;
            if (prevNode != nullptr)
                prevNode->_next = nextNode;
            if (nextNode != nullptr)
                nextNode->_prev = prevNode;
            if (currentNode == _phead->_next)
                _phead->_next = nextNode;
            if (currentNode == _phead->_prev)
                _phead->_prev = prevNode;
            delete currentNode;
            --_size;
            return iterator(nextNode);
        }
        /// @brief 交换两个链表
        /// @param other 另一个链表
        void swap(List<T> &other) noexcept
        {
            std::swap(_size, other._size);
            std::swap(_phead, other._phead);
        }

    private:
        /// @brief 创建头节点
        void CreateHead()
        {
            _phead = new Node();
            _phead->_next = nullptr;
            _phead->_prev = _phead;
        }

    private:
        size_t _size; ///< 元素个数
        PNode _phead; ///< 头节点指针
    };
}