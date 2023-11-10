#ifndef _SJM_MINHEAP_
#define _SJM_MINHEAP_
#include"min_heap.h"
#include<iostream>
using namespace std;
char ans[50];
template<class T>
struct huffmanNode//树结点
{
	T data;//每个结点的数据，可能是结构体
	huffmanNode<T>* left, * right;//每个结点的左右指针
	huffmanNode():data(0),left(NULL),right(NULL){}//构造函数
	huffmanNode(T val,huffmanNode<T>*leftx=NULL,huffmanNode<T>*rightx=NULL):data(val),left(leftx),right(rightx){}//带数值的构造函数

};
template<class T>
struct node //该结点包括树结点指针和下标
{
	huffmanNode<T>* ptr=NULL;
	int key=-1;
	node(huffmanNode<T>* ptr = NULL, int key = 0)
		: ptr(ptr), key(key) {}

	friend bool operator<=(const node& n1, const node& n2)
	{
		return n1.key <= n2.key;
	}
	friend bool operator>(const node& n1, const node& n2)
	{
		return n1.key > n2.key;
	}
};
template<class T>
class huffmanTree {//哈夫曼树
private:
	huffmanNode<T>* root;//树的根结点指针

public:
	huffmanTree(T weight[], int n);//构造函数
	void merge(huffmanNode<T>* l,
		huffmanNode<T>* r, huffmanNode<T>*& father);//合并两棵二叉树
	void preorder(huffmanNode<T>* p,int h);//深度优先搜索输出编码

};

template<class T>
huffmanTree<T>::huffmanTree(T weight[], int n) {
	//给出权值序列weight[],构造huffman树
	minHeap<node<T>> heap;
	huffmanNode<T> *nodelist = new huffmanNode<T>[n];//n棵树组成的森林
	huffmanNode<T>*father=NULL;
	node<T> temp, first, second ;

	for (int i = 0; i < n; ++i) {//森林中所有树结点初始化
		nodelist[i].data = weight[i];
		nodelist[i].left = nodelist[i].right = NULL;
		temp.key = nodelist[i].data;
		temp.ptr = &nodelist[i];
		heap.insert(temp);//插入最小堆
	}

	for (int i = 0; i < n - 1; i++) {//做n-1趟，形成哈夫曼树
		heap.remove_min(first);//权值最小的树
		heap.remove_min(second);//权值次小的树
		merge(first.ptr, second.ptr, father);//合并两个子树
		temp.key = father->data;
		temp.ptr = father;
		heap.insert(temp);//重新插入最小堆
	}
	root = father;

	preorder(root, 0);

}


template<class T>
void huffmanTree<T>::merge(huffmanNode<T>* l,
	huffmanNode<T>* r, huffmanNode<T>*& father) {
	father = new huffmanNode<T>;
	father->left = l;
	father->right = r;
	father->data = l->data + r->data;
}
template<class T>
void huffmanTree<T>::preorder(huffmanNode<T>* p,int h) {//深度优先搜索

	if (p->left == NULL&& p->right==NULL) {//左右子树都没有，那就是根结点
		ans[h] = '\0';
		int i = 0;
		cout << p->data << "：";
		while (ans[i] != '\0') {
			cout << ans[i];
			i++;
		}
		cout << endl;
		return;
	}
	if (p->left != NULL) {//左子树不为空
		ans[h] = '0';
		preorder(p->left, h + 1);//到左子树中继续搜索
	}
	if (p->right != NULL) {//右子树不为空
		ans[h] = '1';
		preorder(p->right, h + 1);//到右子树中继续搜索
	}
}
#endif
