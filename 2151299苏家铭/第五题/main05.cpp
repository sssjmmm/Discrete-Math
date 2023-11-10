#include<iostream>
#include"huffman_tree.h"
using namespace std;
#include"min_heap.h"
int main(){
	int n, *arr;
	cout << "输入结点个数：";
	while (1) {//健壮性
		cin >> n;
		if (cin.fail() || n < 1) {
			cout << "输入非法，请重新输入!" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
			break;
	}
	arr = new int[n];
	cout << "输入结点：" << endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	if (n == 1) {
		cout << arr[0] << "：" << "0";
		delete[]arr;
		return 0;
	}
	huffmanTree<int> tree(arr,n);//生成哈夫曼树并输出
	delete[]arr;
	return 0;
}