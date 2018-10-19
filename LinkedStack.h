#include<iostream>
#include"LinkNode&&List.h"
#include"stack.h"
using namespace std;

template<class T>
class LinkedStack:public Stack<T>
{
public:
	LinkedStack():top(NULL){}
	~LinkedStack(){makeEmpty();}
	void Push(const T& x);
	bool Push(T& x);
	bool getTop(T& x)const;
	bool IsEmpty()const{return (top==NULL)?true:false;}
	int getSize()const;
	void makeEmpty();
	friend ostream& operator<< <T>(ostream& os,SeqStack<T>& s);
private:
	LinkNode<T> *top;
}

template<class T>
LinkStack<T>::makeEmpty()
{
	LinkNode<T> *p;
	while(top!=NULL)
	{
		p=top;
		top=top->link;
		delete p;
	}
}

template<class T>
void LinkedStack<T>::Push(const T&x)
{
	top=new LinkNode<T>(x,top);
	assert(top!=NULL);
}

template<class T>
bool LinkedStack<T>::Pop(T& x)
{
	if(IsEmpty())return false;
	LinkNode<T>*p=top;
	top=top->link;
	x=p->data;
	delete p;
	return true;
}

template<class T>
bool LinkStack<T>::getTop(T& x)const
{
	if(IsEmpty())return false;
	x=top->data;
	return true;
}

template<class T>
int LinkedStack<T>::getSize()const
{
	LinkNode<T> *p=top;
	int k=0;
	while(top!=NULL)
	{
		top=top->link;
		k++;
	}
	return k;
}

template<class T>
ostream& operator<<(ostream& os,LinkNode<T>& s)
{
	os<<"栈中元素的重载个数="<<s.getSize()<<endl;
	LinkNode<T> *p=S.top;
	int i=0;
	while(p!=NULL)
	{
		os<<++i<<":"<<p->data<<endl;
		p=p->link;
	}
	return os;
}



