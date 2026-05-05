#include "binTrees.h"

// ============= node =============
template <typename T>
node<T>::node(const T& val)
    : value(val), right(nullptr), left(nullptr) {
}

// ============= binTree =============

template <typename T>
binTree<T>::binTree() {
    root = nullptr;
    nodeCount = 0;
}

template <typename T>
binTree<T>::binTree(const binTree<T>& other) {
    root = nullptr;
    nodeCount = 0;
}

template <typename T>
binTree<T>::~binTree() {
}

template <typename T>
void binTree<T>::insert(const T& val) {
    if (root == nullptr) {
        root = new node<T>(val);
        nodeCount++;
        return;
    }

    node<T>* current = root;
    node<T>* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (val < current->value)
            current = current->left;
        else if (val > current->value)
            current = current->right;
        else {
            remove(val);
            return;
        }
    }

    if (val < parent->value)
        parent->left = new node<T>(val);
    else
        parent->right = new node<T>(val);

    nodeCount++;
}

template <typename T>
bool binTree<T>::remove(const T& val) {

    node<T>* parent = nullptr;
    node<T>* current = root;

    while (current != nullptr && current->value != val) {
        parent = current;

        if (val < current->value)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr)
        return false;

    if (current->left != nullptr && current->right != nullptr) {
        node<T>* successorParent = current;
        node<T>* successor = current->right;

        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        current->value = successor->value;
        parent = successorParent;
        current = successor;
    }

    node<T>* child;

    if (current->left != nullptr)
        child = current->left;
    else
        child = current->right;

    if (parent == nullptr)
        root = child;
    else if (parent->left == current)
        parent->left = child;
    else
        parent->right = child;

    delete current;
    nodeCount--;

    return true;
}

template <typename T>
bool binTree<T>::find(const T& val) {
    node<T>* current = root;

    while (current != nullptr) {
        if (val == current->value)
            return true;

        if (val < current->value)
            current = current->left;
        else
            current = current->right;
    }

    return false;
}

template class node<int>;
template class binTree<int>;