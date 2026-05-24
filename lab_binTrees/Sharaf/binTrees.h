#ifndef BINTREES_H
#define BINTREES_H

#include <iostream>

template <typename T>
class binTree {
private:
    template <typename U>
    class node {
    public:
        U value;
        node<U>* right;
        node<U>* left;

        node(const U& val) : value(val), right(nullptr), left(nullptr) {}
    };

    node<T>* root;
    int nodeCount;

    node<T>* copyTree(node<T>* otherRoot);
    void destroyTree(node<T>* node);
    node<T>* insertHelper(node<T>* node, const T& val);
    node<T>* removeHelper(node<T>* node, const T& val);
    node<T>* findMin(node<T>* node);
    bool findHelper(node<T>* node, const T& val) const;

public:
    binTree();
    binTree(const binTree<T>& other);
    ~binTree();

    void insert(const T& val);
    bool remove(const T& val);
    bool find(const T& val) const;
    
    int size() const { return nodeCount; }
    bool empty() const { return nodeCount == 0; }
};

#include "binTrees.cpp"

#endif // BINTREES_H