#include<iostream>
#include"huffman_tree.h"
using namespace std;
#include"min_heap.h"
int main(){
	int n, *arr;
	cout << "�����������";
	while (1) {//��׳��
		cin >> n;
		if (cin.fail() || n < 1) {
			cout << "����Ƿ�������������!" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
			break;
	}
	arr = new int[n];
	cout << "�����㣺" << endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	if (n == 1) {
		cout << arr[0] << "��" << "0";
		delete[]arr;
		return 0;
	}
	huffmanTree<int> tree(arr,n);//���ɹ������������
	delete[]arr;
	return 0;
}