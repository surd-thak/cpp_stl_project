#ifndef MY_MAP_H
#define MY_MAP_H

#include "MyAVLTree.h"
#include <iostream>

template <typename Key, typename Value>
class MyMap {
private:
    MyAVLTree<Key, Value> tree;

public:
    MyMap() = default;
    
    // Transfer ownership of the underlying tree
    MyMap(MyMap&& other) noexcept : tree(std::move(other.tree)) {}

    // Retrieves a reference to the value associated with the key
    // Inserts a default-constructed value if the key does not exist
    Value& operator[](const Key& key) {
        Value* v = tree.find(key);
        if (v) {
            return *v;
        } else {
            tree.insert(key, Value{});
            return *tree.find(key);
        }
    }

    // Checks for existence of a key without inserting
    bool contains(const Key& key) {
        return tree.find(key) != nullptr;
    }

    // Inserts a key-value pair into the map
    void insert(const Key& k, const Value& v) {
        tree.insert(k, v);
    }

    // Prints all elements in sorted order (In-order traversal)
    void printAll() {
        tree.inOrderTraversal(tree.root, [](const Key& k, const Value& v) {
            std::cout << k << " : " << v << std::endl;
        });
    }
};

#endif