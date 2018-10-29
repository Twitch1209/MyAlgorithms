#ifndef __LINKNODE_H__
#define __LINKNODE_H__
#include<iostream>
using namespace std;
//LinkNode
template<class T>
struct LinkNode
{
	T data;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *next=NULL):link(next){}
	LinkNode(const T& d,LinkNode<T> *next=NULL):data(d),link(next){}
};

#endif
