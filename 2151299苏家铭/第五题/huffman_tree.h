#ifndef _SJM_MINHEAP_
#define _SJM_MINHEAP_
#include"min_heap.h"
#include<iostream>
using namespace std;
char ans[50];
template<class T>
struct huffmanNode//�����
{
	T data;//ÿ���������ݣ������ǽṹ��
	huffmanNode<T>* left, * right;//ÿ����������ָ��
	huffmanNode():data(0),left(NULL),right(NULL){}//���캯��
	huffmanNode(T val,huffmanNode<T>*leftx=NULL,huffmanNode<T>*rightx=NULL):data(val),left(leftx),right(rightx){}//����ֵ�Ĺ��캯��

};
template<class T>
struct node //�ý����������ָ����±�
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
class huffmanTree {//��������
private:
	huffmanNode<T>* root;//���ĸ����ָ��

public:
	huffmanTree(T weight[], int n);//���캯��
	void merge(huffmanNode<T>* l,
		huffmanNode<T>* r, huffmanNode<T>*& father);//�ϲ����ö�����
	void preorder(huffmanNode<T>* p,int h);//������������������

};

template<class T>
huffmanTree<T>::huffmanTree(T weight[], int n) {
	//����Ȩֵ����weight[],����huffman��
	minHeap<node<T>> heap;
	huffmanNode<T> *nodelist = new huffmanNode<T>[n];//n������ɵ�ɭ��
	huffmanNode<T>*father=NULL;
	node<T> temp, first, second ;

	for (int i = 0; i < n; ++i) {//ɭ��������������ʼ��
		nodelist[i].data = weight[i];
		nodelist[i].left = nodelist[i].right = NULL;
		temp.key = nodelist[i].data;
		temp.ptr = &nodelist[i];
		heap.insert(temp);//������С��
	}

	for (int i = 0; i < n - 1; i++) {//��n-1�ˣ��γɹ�������
		heap.remove_min(first);//Ȩֵ��С����
		heap.remove_min(second);//Ȩֵ��С����
		merge(first.ptr, second.ptr, father);//�ϲ���������
		temp.key = father->data;
		temp.ptr = father;
		heap.insert(temp);//���²�����С��
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
void huffmanTree<T>::preorder(huffmanNode<T>* p,int h) {//�����������

	if (p->left == NULL&& p->right==NULL) {//����������û�У��Ǿ��Ǹ����
		ans[h] = '\0';
		int i = 0;
		cout << p->data << "��";
		while (ans[i] != '\0') {
			cout << ans[i];
			i++;
		}
		cout << endl;
		return;
	}
	if (p->left != NULL) {//��������Ϊ��
		ans[h] = '0';
		preorder(p->left, h + 1);//���������м�������
	}
	if (p->right != NULL) {//��������Ϊ��
		ans[h] = '1';
		preorder(p->right, h + 1);//���������м�������
	}
}
#endif
