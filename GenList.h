#ifndef __GENLIST_H__
#define __GENLIST_H__

#include<iostream>
#include<assert.h>


//广义表节点类定义 
template<class T>
class GenListNode
{
public:
	GenListNode():utype(0),tlink(NULL),info.ref(0) {}
	GenListNode(GenListNode<T>& RL){utype=RL.utype;tlink=RL.tlink;info=RL.info;}
private:
	int utype;
	GenListNode<T> *tlink;
	union{
		int ref;
		T value;
		GenListNode<T> * hlink;
	}info;
};

//返回值的类定义 
template<class T>
struct Items
{
	int utype;
	union{
		int ref;
		T value;
		GenListNode<T> * hlink;
	}info;
	Items():utype(0),info.ref(0){}
	Items(Items<T>& RL){utype=RL.utype;info=RL.info;}//复制构造函数
};

//广义表类定义 
template<class T>
class GenList
{
public:
	GenList();
	~GenList(){Remove(first);}
	bool Head(Items& x);
	bool Tail(GenList<T> &lt);
	GenList<T> *First();
	GenList<T> *Next(GenListNode<T> *elem);
	void Copy(const GenList<T>& R);
	int Length();
	int depth();
private:
	GenList<T> *first;
	GenList<T> *Copy(GenListNode<T> *ls);
	int Length(GenListNode<T> *ls);
	int depth(GenListNode<T> *ls);
	bool equal(GenListNode<T> *s,GenListNode<T> *t);
	void Remove(GenListNode<T> *ls);
}

template<class T>
GenList<T>::GenList(){
	first=new GenListNode;
	assert(first!=NULL);
}

template<class T>
bool GenList<T>::Head(Items<T>& x)
{
	if(first->tlink==NULL) return false;
	else
	{
		x.utype=first->tlink->utype;
		x.info=first->tlink->info;
		return true;
	}
}

template<class T>
bool GenList<T>::Tail(GenList<T> &lt)
{
	if(first->tlink==NULL) return false;
	else
	{
		lt.first->utype=0;
		lt.first->info.ref=0;
		lt.first->tlink=Copy(first->tlink->tlink);
		return true;
	}
}

template<class T>
GenListNode<T> *GenList<T>::First()
{
	if(elem->tlink==NULL) return NULL;
	else return elem->tlink;
}

template<class T>
void GenList<T>::Copy(const GenList<T>& R)
{
	first=Copy(R.first);
}

template<class T>
GenListNode *GenList<T>::Copy(GenListNode<T> *ls)
{
	GebListNode<T> *q=NULL;
	if(ls!=NULL)
	{
		q=new GenListNode<T>;
		q->utype=ls->utype;
		switch(ls->utype)
		{
			case 0:q->info.ref=ls->info.ref;break;
			case 1:q->info.value=ls->info.value;break;
			case 2:q->info.hlink=Copy(ls->info.hlink);break;
		}
		q->tlink=Copy(ls->tlink);
	}
	return q;
}

template<class T>
int GenList<T>::Length()
{
	return Length(first);
}

template<class T>
int GenList<T>::Length(GenListNode<T> *ls)
{
	if(ls!=NULL)return 1+Length(ls->tlink);
	else return 0;
}


template<class T>
int GenList<T>::depth()
{
	return depth(first);
}

template<class T>
int GenList<T>::depth(GenListNode<T> *ls)
{
	if(ls->tlink==NULL) return 1;
	GenListNode<T> *temp=ls->tlink;
	int m=0;
	int n;
	while(temp!=NULL)
	{
		if(temp->utype==2)
		{
			n=depth(temp->info.hlink);
			if(m<n) m=n;
		}
		temp=temp->tlink;
	}
	return m+1;
}

template<class T>
void GenList<T>::Remove(GenListNode<T> *ls)
{
	ls->info.ref--;
	if(ls->info.ref<=0)
	{
		GenListNode<T> *q;
		while(ls->tlink!=NULL)
		{
			q=ls->tlink;
			if(q->utype==2)
			{
				Remove(q->info.hlink);
				if(q->info.hlink->info.ref<=0)
				delete q->info.hlink;
			}
			ls->tlink=q->tlink;delete q;
		}
	}
}
#endif






