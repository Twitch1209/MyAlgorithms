#include"Heap.h"
#include"Graphlnk.h"
#include<iomanip>
#include<string>

using namespace std;
//const float maxValue=FLOAT_MAX;
//最小生成树边结点的定义 
template<class T,class E>
struct MSTEdgeNode
{
	int tail,head;//两顶点 
	E key;//边的权值 
	MSTEdgeNode():tail(-1),head(-1),key(0) {}//具有默认参数的构造函数
	bool operator<=(MSTEdgeNode<T,E>& R){return key<=R.key;}
	bool operator>(MSTEdgeNode<T,E>& R){return key>R.key;}
};

//最小生成树 
template<class T,class E>
class MinSpanTree
{
public:	
	MinSpanTree(int sz=DefaultSize-1):maxSize(sz),n(0)
	{
		edgevalue=new MSTEdgeNode<T,E>[sz];
	}
	void Insert(MSTEdgeNode<T,E> &item);
	bool isEmpty(){return (n==0)?true:false;}
	void show()
	{
		for(int i=0;i<n;i++)
		{
			cout<<edgevalue[i].tail<<"-("
				<<edgevalue[i].key<<")->"
				<<edgevalue[i].head<<endl;
		}
	}
	int getTail(int i) { return edgevalue[i].tail; }
	int getKey(int i) { return edgevalue[i].key; }
	int getHead(int i) { return edgevalue[i].head; }
protected:
	MSTEdgeNode<T,E> *edgevalue;
	int maxSize,n;
};

template<class T,class E>
void MinSpanTree<T,E>::Insert(MSTEdgeNode<T,E> &item)
{
	edgevalue[n]=item;
	n++;
}

template<class T,class E>
bool Prim(Graphlnk<T,E>& G,const T u0,MinSpanTree<T,E>& MST)
{
	MSTEdgeNode<T,E> ed;
	int i,v,count;
	int n=G.getNumVertices();						//顶点数 
	int m=G.getNumEdges();							//边数 
	int u=G.getVertexPos(u0);						//求起始顶点号
	MinHeap< MSTEdgeNode<T,E> > H(m);					//最小堆，关键码类型为E
	bool *Vmst=new bool[n];				
	for(i=0;i<n;i++)
	{
		Vmst[i]=false;
	} 
	Vmst[u]=0;
	count=1;										//u加入最小生成树 
	do
	{
		v=G.getFirstNeighbor(u);
		while(v!=-1)								//重复检测u的所有邻接节点 
		{	
			if(Vmst[v]==false)						//若v不在生成树，把（u，v）加入堆 
			{
				ed.tail=u;							//tail在树内，head不在 
				ed.head=v;
				ed.key=G.getWeight(u,v);
				H.Insert(ed);
			}
			v=G.getNextNeighbor(u,v);				//下一个邻接节点 
		}
		while(H.IsEmpty()==false && count<n)
		{
			H.RemoveMin(ed);						//从堆中退出具有最下权值的边ed
			if(Vmst[ed.head]==false)
			{
				MST.Insert(ed);
				u=ed.head;
				Vmst[u]=true;
				count++;
				break;
			 } 
		}
	}while(count<n);
	if(MST.isEmpty())
	{
		return false;
	}
	return true;
}

