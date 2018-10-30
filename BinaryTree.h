#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include<iostream>

template<class T>
class BinTreeNode
{
	T data;
	BinTreeNode<T> *leftChild, *rightChild;
	BinTreeNode():leftChild(NULL),rightChild(NULL){}
	BinTreeNode(T x,BinTreeNode<T> *l=NULL,BinTreeNode<T>* r=NULL)
		:data(x),leftChild(l),rightChild(r){}
	~BinTreeNode() {}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree() :root(NULL) {}
	BinaryTree(T value):RefValue(value),root(NULL){}
	~BinaryTree();

protected:
	BinTreeNode<T>* root;
	T RefValue;							//数据输入停止标志
	void CreateBinTree(istream& in, BinTreeNode<T> *&subTree);
	bool Insert(BinTreeNode<T> *& subTree, const T& x);
	void destory(BinTreeNode<T> *& subTree);



};



#endif