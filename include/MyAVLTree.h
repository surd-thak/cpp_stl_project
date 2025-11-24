#ifndef MY_AVL_TREE_H
#define MY_AVL_TREE_H

#include <algorithm>
#include <utility>

// Self-balancing Binary Search Tree
template <typename Key, typename Value>
class MyAVLTree {
public:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

private:
    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insertNode(Node* node, Key key, Value value) {
        // BST Insert
        if (!node) return new Node(key, value);

        if (key < node->key)
            node->left = insertNode(node->left, key, value);
        else if (key > node->key)
            node->right = insertNode(node->right, key, value);
        else {
            node->value = value;
            return node;
        }

        // Update height and balance
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Rebalance
        if (balance > 1 && key < node->left->key) return rightRotate(node);       // LL
        if (balance < -1 && key > node->right->key) return leftRotate(node);      // RR
        if (balance > 1 && key > node->left->key) {                               // LR
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {                             // RL
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* findNode(Node* node, const Key& key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return findNode(node->left, key);
        return findNode(node->right, key);
    }

    void clearTree(Node* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    MyAVLTree() : root(nullptr) {}
    
    ~MyAVLTree() { clearTree(root); }

    MyAVLTree(const MyAVLTree&) = delete;
    MyAVLTree& operator=(const MyAVLTree&) = delete;

    MyAVLTree(MyAVLTree&& other) noexcept : root(std::exchange(other.root, nullptr)) {}

    void insert(Key key, Value value) {
        root = insertNode(root, key, value);
    }

    Value* find(const Key& key) {
        Node* res = findNode(root, key);
        return res ? &(res->value) : nullptr;
    }
    
    template<typename Func>
    void inOrderTraversal(Node* node, Func f) {
        if(node) {
            inOrderTraversal(node->left, f);
            f(node->key, node->value);
            inOrderTraversal(node->right, f);
        }
    }
};

#endif