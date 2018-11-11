#include<iostream>
#define DefaultSize 20

using namespace std;
template<class E>
class MinHeap
{
public:	
	MinHeap(int sz=DefaultSize);
	MinHeap(E arr[],int n);
	~MinHeap(){delete []heap;}
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	bool IsEmpty()const
	{return (currentSize==0)?true:false;}
	bool IsFull()const
	{return (currentSize==maxHeapSize)?true:false;}
	void MakeEmpty(){currentSize=0;}
	void Show();
private:
	E *heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start,int m);
	void siftUp(int start);	
}; 

template<class E>
MinHeap<E>::MinHeap(int sz)
{
	maxHeapSize=(DefaultSize<sz)?sz:DefaultSize;
	heap=new E[maxHeapSize];
	if(heap==NULL)
	{
		cerr<<"堆储存分配失败！"<<endl;
		exit(1);
	}
	currentSize=0;
}

template<class E>
MinHeap<E>::MinHeap(E arr[],int n)
{
	maxHeapSize=(DefaultSize<n)?n:DefaultSize;
	heap=new E[maxHeapSize];
	if(heap==NULL)
	{
		cerr<<"堆储存分配失败！"<<endl;
		exit(1);
	}
	for(int i=0;i<n;i++)
	{
		heap[i]=arr[i];
	}
	currentSize=n;
	int currentPos=(currentSize-2)/2;
	while(currentPos>=0)
	{
		siftDown(currentSize,currentSize-1);
		currentSize--;
	}
}

template<class E>
void MinHeap<E>::siftDown(int start,int m)//从节点start到m从上到下比较，如果子女的值小于
{										//父节点的值则调整 
	int i=start;
	int j=2*i+1;
	E temp=heap[i];
	while(j<=m)
	{
		if(j<m&&heap[j]>heap[j+1])j++;			//j->min(heap[j],heap[j+1])
		if(temp<=heap[j])break;
		else
		{
			heap[i]=heap[j];
			i=j;
			j=2*j+1;
		}
	}
	heap[i]=temp;
}

template<class E>
void MinHeap<E>::siftUp(int start)
{
	int j=start;				//子节点 
	int i=(j-1)/2;				//父节点 
	E temp=heap[j];				//子节点的值 
	while(j>0)
	{
		if(heap[i]<=temp)
		{
			break;
		}
		else
		{
			heap[j]=heap[i];
			j=i; 
			i=(i-1)/2;
		}
	}
	heap[j]=temp;
}

template<class E>
bool MinHeap<E>::Insert(const E& x)
{
	if(currentSize==maxHeapSize)
	{
		cerr<<"Heap Full!"<<endl;
		return false;
	}
	heap[currentSize]=x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template<class E>
bool MinHeap<E>::RemoveMin(E& x)
{
	if(!currentSize)
	{
		cout<<"Heap Empty!"<<endl;
		return false;
	}
	x=heap[0];
	heap[0]=heap[currentSize-1];
	currentSize--;
	siftDown(0,currentSize-1);
	return true;
}

template<class E>
void MinHeap<E>::Show()
{
	for(int i=0;i<currentSize;i++)
	{
		cout<<heap[i]<<' ';
	}
}








