#include"Heap.h"

struct HuffmanNode
{
	float data;
	HuffmanNode *leftChild,*rightChild,*parent;
	HuffmanNode():leftChild(NULL),rightChild(NULL),parent(NULL){}
	HuffmanNode(float elem,HuffmanNode* left=NULL,
			HuffmanNode* right=NULL,HuffmanNode* pr=NULL)
			:data(elem),leftChild(left),rightChild(right),parent(pr){}
	bool operator<=(HuffmanNode& R){return data<=R.data;}
	bool operator>(HuffmanNode& R){return data>R.data;}
};


class HuffmanTree
{
public:
	HuffmanTree(float w[],int n);
	~HuffmanTree(){delete root;}
	float Show();
	//void PrintTree(HuffmanNode *ht);
	//HuffmanNode* getRoot(){return root;}
protected:
	float sum;
	HuffmanNode *root;
	void deleteTree(HuffmanNode* t);
	void mergeTree(HuffmanNode& ht1,HuffmanNode& ht2,HuffmanNode* &parent);	
};

//construction
HuffmanTree::HuffmanTree(float w[],int n)		//给出n个权值来构造huffman树 
{
	MinHeap<HuffmanNode> hp;
	HuffmanNode *parent;
	HuffmanNode first,second,work;
	sum=0;
	for(int i=0;i<n;i++)
	{
		work.data=w[i];
		work.leftChild=NULL;
		work.rightChild=NULL;
		work.parent=NULL;
		hp.Insert(work);
	}
	for(int i=0;i<n-1;i++)
	{
		hp.RemoveMin(first);
		hp.RemoveMin(second);
		mergeTree(first,second,parent);
		hp.Insert(*parent);
	}
	root=parent;
}

void HuffmanTree::mergeTree(HuffmanNode& ht1,HuffmanNode& ht2,HuffmanNode* &pr)
{
	pr=new HuffmanNode;
	pr->leftChild=&ht1;
	pr->rightChild=&ht2;
	pr->data=ht1.data+ht2.data;
	sum+=pr->data;
	ht1.parent=ht2.parent=pr;
}

float HuffmanTree::Show()
{
	return sum;
}














