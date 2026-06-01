#pragma once
#include <iostream>

template <typename T>
class node {
public:
    T value;
    node<T>* right;
    node<T>* left;

    node(const T& val);
};

template <typename T>
class binTree {
private:
    node<T>* root;
    int nodeCount;

    node<T>* insertHelper(node<T>* n, const T& val);
    node<T>* removeHelper(node<T>* n, const T& val, bool& removed);
    node<T>* findMin(node<T>* n);
    bool     findHelper(node<T>* n, const T& val);
    node<T>* copyTree(node<T>* n);
    void     clearTree(node<T>* n);

public:
    binTree();
    binTree(const binTree<T>& other);
    ~binTree();

    void insert(const T& val);
    bool remove(const T& val);
    bool find(const T& val);
};
