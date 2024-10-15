#include <iostream>
#include <initializer_list>
namespace XuSTL
{
    template <class T>
    class Vector
    {
    public:
        using iterator = T *;
        using const_iterator = const T *;
        // 迭代器相关
        iterator begin() { return _start; }
        iterator end() { return _finish; }
        const_iterator begin() const { return _start; }
        const_iterator end() const { return _finish; }

        // 构造函数和析构函数
        Vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) { reserve(10); }
        Vector(int n, const T &value = T())
            : _start(new T[n]), _finish(_start + n), _end_of_storage(_start + n)
        {
            for (size_t i = 0; i < n; i++)
                _start[i] = value;
        }
        template <class T_iterator>
        Vector(T_iterator first, T_iterator second)
        {
            size_t n = std::distance(first, second); // 计算范围大小
            _start = new T[n];
            _finish = _start + n;
            _end_of_storage = _start + n;
            std::copy(first, second, _start);
        }
        Vector(const Vector<T> &other)
        {
            swap(other);
        }
        Vector(Vector<T> &&other) : Vector(other.begin(), other.end()) {}
        Vector(std::initializer_list<T> list) : Vector(list.begin(), list.end()) {}
        ~Vector()
        {
            if (_start != nullptr)
                delete[] _start;
            _start = nullptr;
            _finish = nullptr;
            _end_of_storage = nullptr;
        }

        // 重载
        Vector<T> &operator=(Vector<T> other)
        {
            swap(other);
            return *this;
        }
        Vector<T> &operator=(Vector<T> &&other)
        {
            for (auto &it : other)
                push_back(it);
            return *this;
        }
        bool operator==(const Vector<T> &other)
        {
            for (size_t i = 0; i < other.size(); i++)
                if (this[i] != other[i])
                    return false;
            return true;
        }
        bool operator!=(const Vector<T> &other)
        {
            return !((*this) == other);
        }

        bool empty()
        {
            return _start == _finish;
        }

        // 容量操作
        size_t size() const { return (_finish - _start); }
        size_t capacity() const { return (_end_of_storage - _start); }
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
        void clear()
        {
            _finish = _start;
        }

        // 获取数据
        T &operator[](size_t pos)
        {
            if (pos >= size())
            {
                throw std::out_of_range("越界访问！");
            }
            return *(_start + pos);
        }
        const T &operator[](size_t pos) const
        {
            return this[pos];
        }

        // 修改
        void push_back(const T &value) { insert(_finish, value); }
        void pop_back() { erase(_finish - 1); }
        void swap(Vector<T> &v) noexcept
        {
            std::swap(this->_start, v._start);
            std::swap(this->_finish, v._finish);
            std::swap(this->_end_of_storage, v._end_of_storage);
        }
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