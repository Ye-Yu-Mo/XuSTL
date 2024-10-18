/// @file Vector.hpp
/// @brief 动态数组
#pragma once
#include "../adapter/ReverseIterator.hpp"
#include "../adapter/ConstIterator.hpp"
#include "../adapter/ConstReverseIterator.hpp"
#include <iostream>
#include <initializer_list>
namespace XuSTL
{
    /**
     * @brief 自定义 Vector 类，提供动态数组功能。
     *
     * @tparam T 元素类型
     */
    template <class T>
    class Vector
    {
    public:
        using iterator = T *;                                          ///< 普通迭代器
        using const_iterator = ConstIterator<iterator>;                ///< const 迭代器
        using reverse_iterator = ReverseIterator<iterator>;            ///< 反向迭代器
        using const_reverse_iterator = ConstReverseIterator<iterator>; ///< const 反向迭代器
        // 迭代器相关
        /**
         * @brief 返回指向第一个元素的迭代器。
         * @return 指向第一个元素的迭代器。
         */
        iterator begin() { return _start; }
        /**
         * @brief 返回指向最后一个元素之后的迭代器。
         * @return 指向最后一个元素之后的迭代器。
         */
        iterator end() { return _finish; }
        /**
         * @brief 返回指向第一个元素的 const 迭代器。
         * @return 指向第一个元素的 const 迭代器。
         */
        const_iterator begin() const { return const_iterator(begin()); }
        /**
         * @brief 返回指向最后一个元素之后的 const 迭代器。
         * @return 指向最后一个元素之后的 const 迭代器。
         */
        const_iterator end() const { return const_iterator(end()); }
        /**
         * @brief 返回指向最后一个元素的反向迭代器。
         * @return 指向最后一个元素的反向迭代器。
         */
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        /**
         * @brief 返回指向第一个元素之前的反向迭代器。
         * @return 指向第一个元素之前的反向迭代器。
         */
        reverse_iterator rend() { return reverse_iterator(begin()); }
        /**
         * @brief 返回指向最后一个元素的 const 反向迭代器。
         * @return 指向最后一个元素的 const 反向迭代器。
         */
        const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
        /**
         * @brief 返回指向第一个元素之前的 const 反向迭代器。
         * @return 指向第一个元素之前的 const 反向迭代器。
         */
        const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

        // 构造函数和析构函数
        /**
         * @brief 默认构造函数，初始化容量为10。
         */
        Vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) { reserve(10); }
        /**
         * @brief 用指定数量和默认值构造 Vector。
         * @param n 元素数量。
         * @param value 默认值，默认为 T 的默认构造函数。
         */
        Vector(int n, const T &value = T())
            : _start(new T[n]), _finish(_start + n), _end_of_storage(_start + n)
        {
            for (size_t i = 0; i < n; i++)
                _start[i] = value;
        }
        /**
         * @brief 用迭代器范围构造 Vector。
         * @tparam T_iterator 迭代器类型。
         * @param first 范围开始迭代器。
         * @param second 范围结束迭代器。
         */
        template <class T_iterator>
        Vector(T_iterator first, T_iterator second)
        {
            size_t n = std::distance(first, second); // 计算范围大小
            _start = new T[n];
            _finish = _start + n;
            _end_of_storage = _start + n;
            std::copy(first, second, _start);
        }
        /**
         * @brief 拷贝构造函数。
         * @param other 另一个 Vector。
         */
        Vector(const Vector<T> &other)
        {
            swap(other);
        }
        /**
         * @brief 移动构造函数。
         * @param other 另一个 Vector。
         */
        Vector(Vector<T> &&other) : Vector(other.begin(), other.end()) {}
        /**
         * @brief 用初始化列表构造 Vector。
         * @param list 初始化列表。
         */
        Vector(const std::initializer_list<T> &list) : Vector(list.begin(), list.end()) {}
        /**
         * @brief 析构函数。
         */
        ~Vector()
        {
            if (_start != nullptr)
                delete[] _start;
            _start = nullptr;
            _finish = nullptr;
            _end_of_storage = nullptr;
        }

        // 重载
        /**
         * @brief 赋值运算符重载。
         * @param other 另一个 Vector。
         * @return 当前 Vector 的引用。
         */
        Vector<T> &operator=(Vector<T> other)
        {
            swap(other);
            return *this;
        }
        /**
         * @brief 移动赋值运算符重载。
         * @param other 另一个 Vector。
         * @return 当前 Vector 的引用。
         */
        Vector<T> &operator=(Vector<T> &&other)
        {
            for (auto &it : other)
                push_back(it);
            return *this;
        }
        /**
         * @brief 相等比较运算符重载。
         * @param other 另一个 Vector。
         * @return 如果相等则返回 true，否则返回 false。
         */
        bool operator==(const Vector<T> &other)
        {
            for (size_t i = 0; i < other.size(); i++)
                if (this[i] != other[i])
                    return false;
            return true;
        }
        /**
         * @brief 不相等比较运算符重载。
         * @param other 另一个 Vector。
         * @return 如果不相等则返回 true，否则返回 false。
         */
        bool operator!=(const Vector<T> &other) { return !((*this) == other); }
        // 容量操作
        /**
         * @brief 返回当前元素数量。
         * @return 当前元素数量。
         */
        size_t size() const { return (_finish - _start); }
        /**
         * @brief 返回当前容量。
         * @return 当前容量。
         */
        size_t capacity() const { return (_end_of_storage - _start); }
        /**
         * @brief 预留容量。
         * @param n 预留的容量大小。
         */
        void reserve(size_t n)
        {
            size_t sz = size();
            if (n < capacity())
                return;
            iterator new_start = new T[n];
            std::copy(_start, _finish, new_start);
            delete[] _start;
            _start = new_start;
            _finish = _start + sz;
            _end_of_storage = _start + n;
        }
        /**
         * @brief 调整大小，增加或减少元素数量。
         * @param n 新的大小。
         * @param value 新增元素的默认值，默认为 T 的默认构造函数。
         */
        void resize(size_t n, const T &value = T())
        {
            size_t sz = size();
            size_t cp = capacity();
            if (n < sz)
            {
                _finish = _start + n;
                return;
            }
            if (n > cp)
                reserve(n);
            for (size_t i = sz; i < n; i++)
                _start[i] = value;
            _finish = _start + n;
        }
        /**
         * @brief 清空 Vector，移除所有元素。
         */
        void clear() { _finish = _start; }
        /**
         * @brief 检查 Vector 是否为空。
         * @return 如果为空则返回 true，否则返回 false。
         */
        bool empty() { return _start == _finish; }

        // 获取数据
        T &operator[](size_t pos)
        {
            if (pos >= size())
            {
                throw std::out_of_range("越界访问！");
            }
            return *(_start + pos);
        }
        /**
         * @brief 返回指定位置的元素。
         * @param pos 元素位置。
         * @return 指定位置的元素。
         * @throws std::out_of_range 如果 pos 越界。
         */
        const T &operator[](size_t pos) const { return this[pos]; }

        // 修改
        /**
         * @brief 在末尾添加新元素。
         * @param value 要添加的元素。
         */
        void push_back(const T &value) { insert(_finish, value); }
        /**
         * @brief 移除末尾元素。
         */
        void pop_back() { erase(_finish - 1); }
        /**
         * @brief 交换当前 Vector 和另一个 Vector 的内容。
         * @param v 另一个 Vector。
         */
        void swap(Vector<T> &v) noexcept
        {
            std::swap(this->_start, v._start);
            std::swap(this->_finish, v._finish);
            std::swap(this->_end_of_storage, v._end_of_storage);
        }
        /**
         * @brief 在指定位置插入新元素。
         * @param pos 插入位置。
         * @param value 要插入的元素。
         * @return 新插入元素的位置迭代器。
         */
        iterator insert(iterator pos, const T &value)
        {
            size_t offset = pos - _start;
            size_t sz = size();
            size_t cp = capacity();
            if ((sz + 1) * 10 >= cp * 8)
                reserve(cp * 1.5);
            pos = _start + offset;
            for (auto it = _finish; it != pos; it--)
                *it = std::move(*(it - 1));
            *pos = value;
            _finish++;
            return pos;
        }
        /**
         * @brief 移除指定位置的元素。
         * @param pos 要移除的元素位置。
         * @return 移除后的位置迭代器。
         * @throws std::out_of_range 如果 pos 越界。
         */
        iterator erase(iterator pos)
        {
            if (pos < _start || pos >= _finish)
            {
                throw std::out_of_range("越界移除！");
            }
            for (auto it = pos; it != _finish - 1; it++)
                *it = std::move(*(it + 1));
            _finish--;
            return pos;
        }

        // 其他
    private:
        iterator _start;          ///< 元素开始迭代器
        iterator _finish;         ///< 元素结束迭代器
        iterator _end_of_storage; ///< 内存末尾迭代器
    };
}