#ifndef _TREE_H__
#define _TREE_H__

template<class T>
struct TreeNode {
	T data;																//�������
	TreeNode<T>* firstChild, *nextSibling;								//��Ů���ֵܽڵ�
	TreeNode(T value = 0, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL)
		:data(value), firstChild(fc), nextSibling(ns) {}					//���캯��
};

template<class T>
class Tree {
private:
	TreeNode<T> *root, *current;
	bool Find(TreeNode<T>*p, T value);
	void RemovesubTree(TreeNode<T> *p);
	bool FindParent(TreeNode<T>*t, TreeNode < T >*p);
public:
	Tree() { root = current = NULL; }
	bool Root();									//�����ĸ��ڵ��Ϊ���ĵ�ǰ�ڵ�
	bool IsEmpty() { return root == NULL; }			//�������ҵ�ǰ�ڵ�ĸ��ڵ㣬ʹ֮��Ϊ��ǰ�ڵ�
	bool FirstChild();
	bool NextSibling();
	bool Parent();
	bool Find(T target);

};

template<class T>
bool Tree<T>::Root()
{
	if (root == NULL)
	{
		current = NULL;
		return false;
	}
	else
	{
		current = root;
		return true;
	}
}
template<class T>
bool Tree<T>::Parent()
{
	TreeNode<T>* p = current;
	if (current == NULL || current == root)
	{
		current = root;
		return false;
	}
	return FindParent(root, p);
}

template<class T>
bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p)			//���ڵ�Ϊt��������p�ĸ��ڵ㣬ʹ֮��Ϊ��ǰ�ڵ�
{
	TreeNode<T> *q = t->firstChild;
	bool succ;
	while (q != NULL && q != p)
	{
		if (succ = FindParent(q, p))
		{
			return succ;
		}
		q = q->nextSibling;
	}
	if (q != NULL && q == p)
	{
		current = t;
		return true;
	}
	else
	{
		current = NULL;
		return false;
	}
}

template<class T>
bool Tree<T>::FirstChild()					//�������ҵ���ǰ�ڵ�ĳ��ӣ���ʹ֮��Ϊ��ǰ�ڵ�
{
	if (current != NULL && current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
}

template<class T>
bool Tree<T>::NextSibling()
{
	if (current != NULL && current->nextSibling != NULL)
	{
		current = current->nextSibling;
		return true;
	}
	current = NULL;
	return false;
}

template<class T>
bool Tree<T>::Find(T value)
{
	if (IsEmpty()) return false;
	return Find(root, value);
}

template<class T>
bool Tree<T>::Find(TreeNode<T>*p, T value)
{
	bool result = false;
	if (p->data == value)
	{
		result = true;
		current = p;
	}
	else
	{
		TreeNode<T> *q = p->firstChild;
		while (q != NULL && !(result = Find(q, value)))
		{
			q = q->nextSibling;
		}
	}
	return result;
}


#endif