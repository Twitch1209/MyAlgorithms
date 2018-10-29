#include"MyQueue.h"
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int N;
	cin>>N;
	int cus=0;
	bool flag=true;
	LinkedQueue<int> *q1,*q2;
	for(int i=0;i<N;i++)
	{
		cin>>cus;
		if(cus%2==0)
		{
			flag=q2->EnQueue(cus);
			cout<<flag;
			cout<<q2->getFront(cus);
		}
		else
		{
			q1->EnQueue(cus);
		}
	}
	if(q1->getSize()==0)
	{
		q2->show();
	}
	else if(q2->getSize()==0)
	{
		q1->show();
	}
	int count=1;
	int deque=0;
	while(count<=max(q1->getSize(),q2->getSize()))
	{
		if(count%2==0)
		{
			if(q2->DeQueue(deque))
			{
				cout<<deque<<' ';
			}
		}
		if(q1->DeQueue(deque))
		{
			cout<<deque<<' ';
		}
		count++;
	}
}
