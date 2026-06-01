#include <iostream>

template <typename T>
class node {
	T value;
	node<T>* right;
	node<T>* left;

	node(const T& value);
};

class binTree {
private:
	node<T>* root;
	int nodeCount;
public:
	binTree();
	binTree(binTree& other);
	~binTree();

	void insert(const T& val);
	void remove(const T& val);
	bool find(const T& val);
};