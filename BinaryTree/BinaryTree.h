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
	BInaryTree(BinaryTree<T>& s);
	~BinaryTree();
	bool IsEmpty() { return (root == NULL) ? true : false; }
	BinTreeNode<T>* Parents(BinTreeNode<T>* current)
	{return (root == NULL || root == current) ? NULL : Parent(root, current);}
	BinTreeNode<T>* LeftChild(BinTreeNode<T>* current)
	{return (root == NULL) ? current->leftChild:NULL;}
	BinTreeNode<T>* RightChild(BinTreeNode<T>* current)
	{return (root == NULL) ? current->rightChild:NULL;}
	int Height() { return Height(root)l; }
	int Size() { return Size(root); }
	BinTreeNode<T> * getRoot()const { return root; }
	void preOrder(void(*visit)(BinTreeNode<T> *p))
	{preOrder(root, visit);}
	void inOrder(void(*visit)(BinTreeNode<T> *p))
	{inOrder(root, visit);}
	void postOrder(void(*visit)(BinTreeNode<T> *p))
	{PostOrder(root, visit);}
	void levelOrder(void(*visit)(BinTreeNode<T>* p));
	int Insert(const T& item);
	BinTreeNode<T>* Find(T& item)const;

protected:
	BinTreeNode<T>* root;
	T RefValue;							//��������ֹͣ��־
	void CreateBinTree(istream& in, BinTreeNode<T> *&subTree);
	bool Insert(BinTreeNode<T> *& subTree, const T& x);
	void destory(BinTreeNode<T> *& subTree);
	bool Find(BinTreeNode<T>* subTree, const T& x)const;
	BinTreeNode<T> *Copy(BinTreeNode<T> *orignode);
	int Height(BinTreeNode<T>* subTree);					//�������߶�
	int Size(BinTreeNode<T>* subTree);						//���ؽڵ���
	BinTreeNode<T> *Parent(BinTreeNode<T> * subTree, BinTreeNode<T> * current)const;		//���ظ��ڵ�
	BinTreeNode<T> *Parent(BinTreeNode<T> * subTree, const T& x)const;						//��Ѱx
	void Traverse(BinTreeNode<T> * subTree, ostream& out);									//ǰ��������
	void preOrder(BinTreeNode<T>& subTree ,void (*visit)(BinTreeNode<T> * p));				//ǰ�����
	void inOrder(BinTreeNode<T> * subTree, void(*visit)(BinTreeNode<T> * p));				//�������
	void postOrder(BinTreeNode<T> * subTree, void(*visit)(BinTreeNode<T> * p));				//�������

};



#endif