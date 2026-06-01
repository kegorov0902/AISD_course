#include "binTrees.h"
#include <iostream>
using namespace std;

template <typename T>
node<T>::node(const T& val)
    : value(val), right(nullptr), left(nullptr) {
}

template <typename T>
binTree<T>::binTree() {
    root = nullptr;
    nodeCount = 0;
}

template <typename T>
binTree<T>::binTree(const binTree<T>& other) {
    root = copyTree(other.root);
    nodeCount = other.nodeCount;
}

template <typename T>
binTree<T>::~binTree() {
    clearTree(root);
}

template <typename T>
node<T>* binTree<T>::copyTree(node<T>* n) {
    if (n == nullptr) return nullptr;
    node<T>* newNode = new node<T>(n->value);
    newNode->left = copyTree(n->left);
    newNode->right = copyTree(n->right);
    return newNode;
}

template <typename T>
void binTree<T>::clearTree(node<T>* n) {
    if (n == nullptr) return;
    clearTree(n->left);
    clearTree(n->right);
    delete n;
}

template <typename T>
node<T>* binTree<T>::insertHelper(node<T>* n, const T& val) {
    if (n == nullptr)
        return new node<T>(val);

    if (val < n->value)
        n->left = insertHelper(n->left, val);
    else if (val > n->value)
        n->right = insertHelper(n->right, val);

    return n;
}

template <typename T>
node<T>* binTree<T>::findMin(node<T>* n) {
    while (n->left != nullptr)
        n = n->left;
    return n;
}

template <typename T>
node<T>* binTree<T>::removeHelper(node<T>* n, const T& val, bool& removed) {
    if (n == nullptr) {
        removed = false;
        return nullptr;
    }

    if (val < n->value) {
        n->left = removeHelper(n->left, val, removed);
    }
    else if (val > n->value) {
        n->right = removeHelper(n->right, val, removed);
    }
    else {
        removed = true;
        if (n->left == nullptr) {
            node<T>* temp = n->right;
            delete n;
            return temp;
        }
        if (n->right == nullptr) {
            node<T>* temp = n->left;
            delete n;
            return temp;
        }
        node<T>* temp = findMin(n->right);
        n->value = temp->value;
        bool dummy = false;
        n->right = removeHelper(n->right, temp->value, dummy);
    }

    return n;
}

template <typename T>
bool binTree<T>::findHelper(node<T>* n, const T& val) {
    if (n == nullptr)    return false;
    if (val == n->value) return true;

    if (val < n->value)
        return findHelper(n->left, val);
    else
        return findHelper(n->right, val);
}

template <typename T>
void binTree<T>::insert(const T& val) {
    if (!find(val)) {
        root = insertHelper(root, val);
        nodeCount++;
    }
}

template <typename T>
bool binTree<T>::remove(const T& val) {
    bool removed = false;
    root = removeHelper(root, val, removed);
    if (removed) nodeCount--;
    return removed;
}

template <typename T>
bool binTree<T>::find(const T& val) {
    return findHelper(root, val);
}

template class node<int>;
template class binTree<int>;
