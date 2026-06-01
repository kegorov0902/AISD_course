#include "binTrees.h"

template <typename T>
binTree<T>::binTree() : root(nullptr), nodeCount(0) {
}

template <typename T>
binTree<T>::binTree(const binTree<T>& other) : root(nullptr), nodeCount(0) {
    root = copyTree(other.root);
    nodeCount = other.nodeCount;
}

template <typename T>
binTree<T>::~binTree() {
    destroyTree(root);
    root = nullptr;
    nodeCount = 0;
}

template <typename T>
typename binTree<T>::template node<T>* binTree<T>::copyTree(node<T>* otherRoot) {
    if (otherRoot == nullptr) {
        return nullptr;
    }
    
    node<T>* newNode = new node<T>(otherRoot->value);
    newNode->left = copyTree(otherRoot->left);
    newNode->right = copyTree(otherRoot->right);
    return newNode;
}

template <typename T>
void binTree<T>::destroyTree(node<T>* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename T>
typename binTree<T>::template node<T>* binTree<T>::findMin(node<T>* node) {
    if (node == nullptr) {
        return nullptr;
    }
    
    node<T>* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template <typename T>
void binTree<T>::insert(const T& val) {
    root = insertHelper(root, val);
}

template <typename T>
typename binTree<T>::template node<T>* binTree<T>::insertHelper(node<T>* node, const T& val) {
    if (node == nullptr) {
        nodeCount++;
        return new node<T>(val);
    }
    
    if (val < node->value) {
        node->left = insertHelper(node->left, val);
    } else if (val > node->value) {
        node->right = insertHelper(node->right, val);
    }
    
    return node;
}

template <typename T>
bool binTree<T>::remove(const T& val) {
    if (!findHelper(root, val)) {
        return false; 
    }
    
    int oldCount = nodeCount;
    root = removeHelper(root, val);
    return nodeCount < oldCount; 
}

template <typename T>
typename binTree<T>::template node<T>* binTree<T>::removeHelper(node<T>* node, const T& val) {
    if (node == nullptr) {
        return nullptr;
    }
    if (val < node->value) {
        node->left = removeHelper(node->left, val);
    } else if (val > node->value) {
        node->right = removeHelper(node->right, val);
    } else {
        if (node->left == nullptr) {
            node<T>* temp = node->right;
            delete node;
            nodeCount--;
            return temp;
        } else if (node->right == nullptr) {
            node<T>* temp = node->left;
            delete node;
            nodeCount--;
            return temp;
        }
        
        node<T>* temp = findMin(node->right);
        
        node->value = temp->value;
        
        node->right = removeHelper(node->right, temp->value);
    }
    
    return node;
}

template <typename T>
bool binTree<T>::find(const T& val) const {
    return findHelper(root, val);
}

template <typename T>
bool binTree<T>::findHelper(node<T>* node, const T& val) const {
    if (node == nullptr) {
        return false;
    }
    
    if (val == node->value) {
        return true;
    } else if (val < node->value) {
        return findHelper(node->left, val);
    } else {
        return findHelper(node->right, val);
    }
}