// /// @file Deque.hpp
// /// @brief 双向队列
// #pragma once
// #include "../adapter/ReverseIterator.hpp"
// #include "../adapter/ConstIterator.hpp"
// #include "../adapter/ConstReverseIterator.hpp"
// #include "Vector.hpp"
// #include <iostream>
// #include <initializer_list>

// namespace XuSTL
// {

//     template <class T, size_t BLOCK_SIZE = 64>
//     class Deque;

//     template <class T, class Ref = T &, class Ptr = T *, size_t BLOCK_SIZE = 64>
//     class DequeIterator
//     {
//     private:
//         using Self = ListIterator<T, Ref, Ptr>; ///< 自身类型
//     public:
//         DequeIterator(T **blocks, size_t block_count,
//                       size_t block_index, size_t element_index) : _blocks(blocks), _block_count(block_count),
//                                                                   _block_index(block_index), _element_index(element_index) {}
//         DequeIterator(const Self &other) : _blocks(other._blocks), _block_count(other._block_count),
//                                            _block_index(other._block_index), _element_index(other._element_index) {}

//         DequeIterator(Self &&other) : _blocks(std::move(other._blocks)), _block_count(other._block_count),
//                                       _block_index(other._block_index), _element_index(other._element_index) { other._blocks = nullptr; }

//         Self &operator=(const Self &other)
//         {
//             if (this != &other)
//             {
//                 _blocks = other._blocks;
//                 _block_count = other._block_count;
//                 _block_index = other._block_index;
//                 _element_index = other._element_index;
//             }
//             return *this;
//         }
//         Self &operator=(Self &&other) noexcept
//         {
//             if (this != &other)
//             {
//                 _blocks = std::move(other._blocks);
//                 _block_count = other._block_count;
//                 _block_index = other._block_index;
//                 _element_index = other._element_index;
//                 other._blocks = nullptr;
//             }
//             return *this;
//         }
//         Ref operator*() const;
//         Ptr operator->();
//         Self &operator++();
//         Self operator++(int);
//         Self &operator--();
//         Self operator--(int);
//         bool operator==(const Self &other) const;
//         bool operator!=(const Self &other) const;

//     private:
//         T **_blocks;           ///< 指针数组
//         size_t _block_count;   ///< 内存块数量
//         size_t _block_index;   ///< 当前内存块下标
//         size_t _element_index; ///< 当前块中的元素下标
//     };

//     template <class T, size_t BLOCK_SIZE = 64>
//     class Deque
//     {
//     private:
//         using Ref = T &;
//         using Ptr = T *;

//     public:
//         using iterator = DequeIterator<T, Ref, Ptr, BLOCK_SIZE>;       ///< 普通迭代器
//         using const_iterator = ConstIterator<iterator>;                ///< const 迭代器
//         using reverse_iterator = ReverseIterator<iterator>;            ///< 反向迭代器
//         using const_reverse_iterator = ConstReverseIterator<iterator>; ///< const 反向迭代器

//         Deque();
//         ~Deque();
//         size_t size();
//         bool empty();
//         void push_front();
//         void push_back();
//         void pop_front();
//         void pop_back();
//         T &operator[](size_t index);
//         const T &operator[](size_t index);

//     private:
//         void resize(int new_block_count);
//         void ensure_capacity();

//     private:
//         T **_blocks;
//         size_t _block_count;
//         size_t _size;
//         size_t _front;
//         size_t _back;
//     };
// }