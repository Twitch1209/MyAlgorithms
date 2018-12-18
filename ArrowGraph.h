#ifndef __GRAPHLNK_H__
#define __GRAPHLNK_H__

//����ͼ���ඨ���AOE�㷨
//writen by Twitch
 
#include<iostream>
using namespace std;
 
const int DefaultVertices=50;//max vertives

//E--->edge,T--->vertex
template<class T,class E>
struct Edge
{
	int dest;		//the other vertex
	E cost;			//value
	Edge<T,E>* link;  //next point
	Edge():dest(0),cost(0),link(NULL){}
	Edge(int num,E weight):dest(num),cost(weight),link(NULL){}
	bool operator!=(Edge<T,E>&R)const
	{
		return (dest!=R.dest)?true:false;
	}
	
};

template<class T,class E>
struct Vertex
{
	T data;						//the name of the Vertex
	Edge<T,E> *adj;				//*first to the list
};


template<class T,class E>
class Graphlnk
{
public:
	Graphlnk(int sz=DefaultVertices);
	~Graphlnk();
	T getValue(int i){return (i>=0 && i<numVertices)?NodeTable[i].data:0;}							//get the value of Vertices(i)
	void changeValue(int i,int j)
	{
		if(i>=0 && i<numVertices)
		{
			T p=NodeTable[i].data;
			NodeTable[i].data=NodeTable[j].data;
			NodeTable[j].data=p;
		}
	}
	E getWeight(int v1,int v2);					//get the value of edge(v1,v2)
	bool insertVertex(const T& v);				//insert vertex v
	bool removeVertex(int v);					//delete vertex 
	bool insertEdge(int v1,int v2,E cost);		//insert edge(v1,v2)
	bool removeEdge(int v1,int v2);				//delete edge(v1,v2)
	int getFirstNeighbor(int v);				//get v's first neighbor
	int getNextNeighbor(int v,int w);			//get v->w's next
	int getNumVertices(){return numVertices;}
	int getNumEdges(){return numEdges;}
	int getVertexPos(const T vertex)			//return i from vertex  like:get 0 form a
	{
		for(int i=0;i<numVertices;i++)
		{
			if(NodeTable[i].data==vertex) return i;
		}
		return -1;
	}
	void setNumVertices(int num){numVertices=num;}
private:
	Vertex<T,E> *NodeTable;						//��������������ͷ��㣩
	int maxVertices;							//max of Vertices
	int numEdges;								//the number of edges
	int numVertices;							//the number of vertices	
};

template<class T,class E>
Graphlnk<T,E>::Graphlnk(int sz)
{
	maxVertices=sz;
	numVertices=0;
	numEdges=0;
	NodeTable=new Vertex<T,E>[maxVertices];
	if(NodeTable==NULL) { cerr<<"�洢�������"<<endl;exit(1);}
	for(int i=0;i<maxVertices;i++)
	{
		NodeTable[i].adj=NULL;
	}
}

template<class T,class E>
Graphlnk<T,E>::~Graphlnk()
{
	for(int i=0;i<numVertices;i++)
	{
		Edge<T,E> *p=NodeTable[i].adj;
		while(p!=NULL)
		{
			NodeTable[i].adj=p->link;
			delete p;
			p=NodeTable[i].adj;
		}
	}
	delete []NodeTable;
}

template<class T,class E>
int Graphlnk<T,E>::getFirstNeighbor(int v)
{
	if(v!=-1)
	{
		Edge<T,E> *p=NodeTable[v].adj;
		if(p!=NULL) return p->dest;
	}
	return -1;
}

template<class T,class E>
int Graphlnk<T,E>::getNextNeighbor(int v,int w)
{
	if(v!=-1)
	{
		Edge<T,E> *p=NodeTable[v].adj;			//�������һ���߽ڵ� 
		while(p!=NULL && p->dest!=w)			//Ѱ���ڽӽڵ�w			
		{
			p=p->link;							
		}
		if(p!=NULL && p->link!=NULL)
		{
			return p->link->dest;				//������һ���ڽӽڵ� 
		}
	}
	return -1;
}

template<class T,class E>
E Graphlnk<T,E>::getWeight(int v1,int v2)
{
	if(v1!=-1 &&v2!=-1)
	{
		Edge<T,E> *p=NodeTable[v1].adj;
		while(p!=NULL && p->dest!=v2)
		{
			p=p->link;
		}
		if(p!=NULL)  return p->cost;
	}
	return 0;
}

template<class T,class E>
bool Graphlnk<T,E>::insertVertex(const T& v)
{
	if(numVertices==maxVertices) return false;
	NodeTable[numVertices].data=v;
	numVertices++;
	return true;
}

template<class T,class E>
bool Graphlnk<T,E>::removeVertex(int v)
{
	//��ջ��߶���ų�����Χ 
	if(numVertices==1 || v<0 || v>numVertices) return false;
	Edge<T,E> *p,*s;
	int i,k;
	while(NodeTable[v].adj!=NULL)//delete all vertices
	{
		p=NodeTable[v].adj;
		NodeTable[v].adj=p->link;
		delete p;
		numEdges--;
	}
	numVertices--;
	NodeTable[v].data=NodeTable[numVertices].data;
	NodeTable[v].adj=NodeTable[numVertices].adj;
	return true;
}


 //insert (v1,v2)
template<class T,class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		Edge<T, E> *p = NodeTable[v1].adj;
		while (p != NULL && p->dest !=v2)
		{
			p = p->link;
		}
		if (p != NULL){return false;}					// if find this edge, return false
		//if do not find ,then create new node
		p = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;					//link to v1's list
		NodeTable[v1].adj = p;
		numEdges++;
		return true;
	}
	return false;
}

//remove edge(v1,v2)
template<class T,class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E> *p = NodeTable[v1].adj;
		Edge<T, E> *q = NULL;
		Edge<T, E> *s = p;
		while (p != NULL && p->dest!=v2)							//�ұ�ɾ���
		{
			q = p;
			p = p->link;
		}
		if (p != NULL)
		{
			if (p == s){NodeTable[v1].adj = p->link;}				//�ý���Ǳ�������׽��
			else q->link = p->link;									//���ǣ���������
			delete p;
		}
		else return false;											//û���ҵ���ɾ�߽��
		return true;
	}
	return false;
}


template<class T,class E>
bool TopologicalSort(Graphlnk<T, E>& G,int M)
{
	int i, j, w, v;
	int top = -1;						//���Ϊ�㶥���ջ��ʼ��
	int n = G.getNumVertices();			//�����ж������
	int *count = new int[n];			//�����������Ϊ�㶥��ջ
	int *topsort = new int[n];
	int sum=0;							//��¼���������õ������� 
	
	for (i = 0; i < n; i++)
	{
		count[i] = 0;
	}
	int v1, v2, cost;
	for (i = 0; i<M; i++)
	{
		cin >> v1 >> v2 >> cost;
		v1--;
		v2--;
		count[v2]++;
		G.insertEdge(v1, v2, cost);
	}
	for (i = 0; i < n; i++)			//������������еĶ���
	{
		if (count[i] == 0)				//���Ϊ��Ķ����ջ
		{
			count[i] = top;
			top = i;
		}
	}
	for (i = 0; i < n; i++)			//�������n������
	{
		if (top == -1)				//��;ջ�գ�ת��
		{
			cout<<0;
			return false;
		}
		else						//������������
		{
			v = top;
			top = count[top];		//v��ջ
			//���õ�����������������topsort���� 
			topsort[sum]=G.getValue(v);
			sum++;
			w = G.getFirstNeighbor(v);
			while (w != -1)				//ɨ����߱�
			{
				if (--count[w] == 0)		//�ڽӶ�����ȼ���1
				{
					count[w] = top;
					top = w;				//������ȼ��ٵ�0����ջ
				}
				w = G.getNextNeighbor(v, w);
			}
		}
	}
	if(sum!=n) return false;
	return true;
}

template<class T,class E>
void CriticalPath(Graphlnk<T, E>& G)
{
	int i, j, k;
	E Ae, Al, w;
	int n = G.getNumVertices();
	E *Ve = new E[n];
	E *Vl = new E[n];
	int sum=0;
	for (i = 0; i < n; i++)
	{
		Ve[i] = 0;
	}
	for (i = 0; i < n; i++)						//�������Ve[]
	{
		j = G.getFirstNeighbor(i);
		while (j != -1)
		{
			w = G.getWeight(i, j);
			if (Ve[i] + w > Ve[j]) Ve[j] = Ve[i] + w;
			j = G.getNextNeighbor(i, j);
		}
	}
	Vl[n-1] = Ve[n-1];
	for (j = n - 2; j >= 0; j--)					//�������Vl[]
	{
		k = G.getFirstNeighbor(j);
		Vl[j]=Vl[k]-G.getWeight(j, k);
		while (k != -1)
		{
			w = G.getWeight(j, k);
			if (Vl[k] - w < Vl[j]) Vl[j] = Vl[k] - w;
			k = G.getNextNeighbor(j, k);
		}
	}
	int start=0;
	int end=0;
	for (i = 0; i < n; i++)
	{
		j = G.getFirstNeighbor(i);
		if(end==i) start=i;
		while (j != -1)
		{
			Ae = Ve[i];
			Al = Vl[j] - G.getWeight(i, j);
			if (Al == Ae)
			{
				//cout << G.getValue(i)+1 << "->" << G.getValue(j)+1 << endl;
				end=j;
			}
			j = G.getNextNeighbor(i,j);
		}
		if(start==i) sum += G.getWeight(start, end);
	}
	cout<<sum<<endl;
	for (i = 0; i < n; i++)
	{
		j = G.getFirstNeighbor(i);
		while (j != -1)
		{
			Ae = Ve[i];
			Al = Vl[j] - G.getWeight(i, j);
			if (Al == Ae)
			{
				cout << G.getValue(i)+1 << "->" << G.getValue(j)+1 << endl;
			}
			j = G.getNextNeighbor(i,j);
		}
	}
	delete[]Ve;
	delete[]Vl;

}


#endif
