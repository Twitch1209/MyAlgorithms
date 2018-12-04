
const int DefaultVertices=30;//max vertives

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
	
}

template<class T,class E>
struct Vertex
{
	T data;						//teh name of the Vertex
	Edge<T,E> *adj;				//*first to the list
}


template<class T,class E>
class Graphlnk
{
public:
	Graphlnk(int sz=DefaultVertices);
	~Graphlnk();
	T getValue(int i)							//get the value of Vertices(i)
	{return(i>=0 && i<NumVertices)?NodeTable[i].data:0;}
	E getWeight(int v1,int v2);					//get the value of edge(v1,v2)
	bool insertVertex(const T& v);				//insert vertex v
	bool removeVertex(int v);					//delete vertex 
	bool insertEdge(int v1,int v2,E weight);		//insert edge(v1,v2)
	bool removeEdge(int v1,int v2);				//delete edge(v1,v2)
	int getFirstNeighbor(int v);				//get v's first neighbor
	int getNextNeighbor(int v,int w);			//get v->w's next
private:
	Vertex<T,E> *NodeTable;						//��������������ͷ��㣩
	int maxVertices;							//max of Vertices
	int numEdges;								//the number of edges
	int numVertices;							//the number of vertices
	int getVertexPos(const T vertex)			//return i from vertex  like:get 0 form a
	{
		for(int i=0;i<numVertices;i++)
		{
			if(NodeTable[i].data==vertex) return i;
		}
	}	
};

template<class T,class E>
Graphlnk<T,E>::Graphlnk(int sz)
{
	maxVertices=sz;
	numVertices=0;
	numEdges=0;
	NodeTable=new Vertex<T,E>[maxVertices];
	if(NodeTable==NULL) {cerr<<"�洢�������"<<endl;exit(1);}
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
		Edge<T,E> *p=NodeTable[v].adj;
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
	Edge<T,E> *p,*s,*t;
	int i,k;
	while(NodeTable[v].adj!=NULL)//delete all vertices
	{
		p=NodeTable[v].adj;
		k=p->dest;				//get neighbor k
		s=NodeTable[k].adj;    	//�ҵ��Գƴ�ŵı߽ڵ� 
		t=NULL;
		while(s!=NULL && s->dest!=v)
		{
			t=s;s=s->link;
		}
		if(s!=NULL)				//ɾ���Գƴ�ŵı߽�� 
		{
			if(t==NULL) NodeTable[k].adj=s->link;
			else t->link=s->link;
			delete s;
		}
		NodeTable[v].adj=p->link;
		delete p;
		numEdge--;
	}
	numVertices--;
	NodeTable[v].data=NodeTable[numVertices].data;
	p=NodeTable[v].adj=NodeTable[numVertices].adj;
	while(p!=NULL)
	{
		s=NodeTable[p->dest].adj;
		while(s!=NULL)
		{
			if(s->dest==numVertices)
			{
				s->dest=v;
				break;
			}
			else s=s->link;
		}
		p=p->link;
	}
	return true;
}

//insert (v1,v2)
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		Edge<T, E> *q, *p = NodeTable[v1].adj;
		while (p != NULL && p->dest !=v2)
		{
			p = p->link;
		}
		if (p != NULL){return false;}					// if find this edge, return false
		//if do not find ,then create new node
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;					//link to v1's list
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
}

//remove edge(v1,v2)
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
		//v2��Ӧ��������ɾ��
		p = NodeTable[v2].adj;
		q = NULL;
		s = p;
		while (p->dest != v1) { q = p; p = p->link; }
		if (p == s) NodeTable[v2].adj = p->link;				//�ý���Ǳ�������׽��
		else q->link = p->link;									//���ǣ���������
		delete p;
		return true;
	}
	return false;
}





