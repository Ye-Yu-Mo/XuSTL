/// @file HashTable.hpp
/// @brief 开散列哈希桶
#pragma once
#include <iostream>
#include <vector>

namespace XuSTL
{
    template <class T>
    struct HashNode
    {
        HashNode *_next;
        T _data;
        HashNode(const T &val = T()) : _next(nullptr), _data(val) {}
    };

    template <class Key, class Val, class KeyOfVal, class Hash>
    class HashTable
    {
        using Node = HashNode<Val>;
        using pNode = Node *;

    public:
        HashTable() { _tables.resize(10, nullptr); }
        ~HashTable()
        {
            for (auto node : _tables)
            {
                while (node != nullptr)
                {
                    pNode tmp = node;
                    node = node->_next;
                    delete tmp;
                }
            }
            _n = 0;
        }
        bool Insert(const Val &data)
        {
            Key key = KeyOfVal()(data);
            size_t index = Hash()(key) % _tables.size();

            pNode newNode = new Node(data);
            newNode->_next = _tables[index];
            _tables[index] = newNode;
            _n++;
            return true;
        }
        bool Find(const Key &key)
        {
            size_t index = Hash()(key) % _tables.size();
            pNode node = _tables[index];
            while (node != nullptr)
            {
                if (KeyOfVal()(node->_data) == key)
                    return true;
                node = node->_next;
            }
            return false;
        }
        bool Erase(const Key &key)
        {
            size_t index = Hash()(key) % _tables.size();
            pNode node = _tables[index];
            pNode prev = nullptr;
            while (node != nullptr)
            {
                if (KeyOfVal()(node->_data) == key)
                {
                    if (prev != nullptr)
                        prev->_next = node->_next;
                    else 
                        _tables[index] = node->_next;
                    delete node;
                    _n--;
                    return true;
                }
                prev = node;
                node = node->_next;
            }
            return false;
        }

    private:
        std::vector<pNode> _tables;
        size_t _n = 0;
    };
}