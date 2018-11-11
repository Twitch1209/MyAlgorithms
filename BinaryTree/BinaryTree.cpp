#include<iostream>
#include<stdlib.h>
#include"BinaryTree.h"

template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *subTree)
//private 若指针subTree不为空，则删除根为subTree的子树
{
	if (subTree != NULL)
	{
		destroy(subTree->leftChild);
		destroy(subTree->rightChild);
		delete subTree;
	}
}

template<class T>
BinTreeNode<T> * BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current)
{
	if (subTree == NULL) return NULL;
	if (subTree->leftChild == current || subTree->rightChild == current) return subTree;
	BinTreeNode<T> *p;
	if ((p = Parent(subTree->leftChild, current)) != NULL) return p;
	else reutrn Parent(subTree->rightChild, current);
}

template<class T>
void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream& out)
{
	if (subTree != NULL)
	{
		out << subTree->data << ' ';
		Traverse(subTree->leftChild, out);
		Traverse(subTree->rightChild, out);
	}
}