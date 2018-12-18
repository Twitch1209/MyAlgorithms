#include"Heap.h"
#include"Graphlnk.h"
#include<iomanip>
#include<string>

using namespace std;
//const float maxValue=FLOAT_MAX;
//��С�������߽��Ķ��� 
template<class T,class E>
struct MSTEdgeNode
{
	int tail,head;//������ 
	E key;//�ߵ�Ȩֵ 
	MSTEdgeNode():tail(-1),head(-1),key(0) {}//����Ĭ�ϲ����Ĺ��캯��
	bool operator<=(MSTEdgeNode<T,E>& R){return key<=R.key;}
	bool operator>(MSTEdgeNode<T,E>& R){return key>R.key;}
};

//��С������ 
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
	int n=G.getNumVertices();						//������ 
	int m=G.getNumEdges();							//���� 
	int u=G.getVertexPos(u0);						//����ʼ�����
	MinHeap< MSTEdgeNode<T,E> > H(m);					//��С�ѣ��ؼ�������ΪE
	bool *Vmst=new bool[n];				
	for(i=0;i<n;i++)
	{
		Vmst[i]=false;
	} 
	Vmst[u]=0;
	count=1;										//u������С������ 
	do
	{
		v=G.getFirstNeighbor(u);
		while(v!=-1)								//�ظ����u�������ڽӽڵ� 
		{	
			if(Vmst[v]==false)						//��v�������������ѣ�u��v������� 
			{
				ed.tail=u;							//tail�����ڣ�head���� 
				ed.head=v;
				ed.key=G.getWeight(u,v);
				H.Insert(ed);
			}
			v=G.getNextNeighbor(u,v);				//��һ���ڽӽڵ� 
		}
		while(H.IsEmpty()==false && count<n)
		{
			H.RemoveMin(ed);						//�Ӷ����˳���������Ȩֵ�ı�ed
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

