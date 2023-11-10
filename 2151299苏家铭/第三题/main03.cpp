#include<iostream>
using namespace std;
void duichen();
void chuandi();
void zifan();
void exit();
void show();
void init();
void select();
void delete_shuzu(int** arrx, int n);
int **arr,n,choice;


/*
7
1 0 1 0 0 0 1
0 0 0 1 1 1 0
0 1 0 1 0 0 1
0 1 0 1 1 1 0
0 1 1 0 1 1 1
1 1 1 0 0 0 1
1 0 0 1 0 1 0 

3
0 0 1
1 0 1
0 1 1

4
0 1 0 0
1 0 1 0
0 0 0 1
0 0 0 0
*/
int main() {
	init();//初始化矩阵
	show();//展示初始化的矩阵
	select();//选择算法,choice
	switch (choice) {
	case 1:
		zifan();
		show();
		break;
	case 2:
		chuandi();
		show();
		break;
	case 3:
		duichen();
		show();
		break;
	case 4:
		exit();
		break;
	}
	delete_shuzu(arr, n);
	return 0;
}

void delete_shuzu(int** arrx, int n) {//清理数组的空间的函数，以免损害内存
	for (int i = 0; i < n; ++i) 
		delete []arrx[i];
}
void exit() {//退出的函数
	cout << "按回车退出......." << endl;
	cin.get();
}
void init() {//初始化矩阵
	cout << "请输入矩阵行(列)数:";
	while (1) {//健壮性，以防非法输入
		cin >> n;
		if (cin.fail() || n < 0) {
			cout << "输入非法，请再次输入:" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "创建初始矩阵:" << endl;
	arr = new int* [n];
	for (int i = 0; i < n; ++i)
		arr[i] = new int[n];
	for (int i = 0; i < n; i++) {//用两个 循环输入矩阵
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
}

void select() {
	cout << "=======================" << endl;
	cout << "=======1:自反闭包======" << endl;
	cout << "=======2:传递闭包======" << endl;
	cout << "=======3:对称闭包======" << endl;
	cout << "=======4:退出==========" << endl;
	cout << "=======================" << endl;
	cout << "请输入相应序号选择对应算法:";

	while (1) {//健壮性
		cin >> choice;
		if (cin.fail()|| choice < 0 || choice>4) {
			cout << "输入错误，请再次输入:";
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
void zifan() {//自反,主对角线置1
	for (int i = 0; i < n; i++)
		arr[i][i] = 1;
}
void duichen() {//遍历，如果ij是1，那么ji也要是1
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 1)
				arr[j][i] = 1;
		}
	}
}
void chuandi() {//传递，时间复杂度O(n4)，未用沃舍尔算法
	int **next,**ans,**M,temp=0;
	next = new int* [n];
	for (int i = 0; i < n; ++i)
		next[i] = new int[n];
	ans = new int* [n];
	for (int i = 0; i < n; ++i)
		ans[i] = new int[n];
	M = new int* [n];
	for (int i = 0; i < n; ++i)
		M[i] = new int[n];

	//memset();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next[i][j] = 0;
			ans[i][j] = arr[i][j];
			M[i][j]= arr[i][j];
		}
	}
	for (int m = 0; m < n; m++) {//n个矩阵相加
		for (int i = 0; i < n; i++) {//第i行每个元素*第j列每个元素
			for (int j = 0; j < n; j++) {
				temp = 0;
				for (int d=0; d < n; d++){
					temp+=(M[i][d] * arr[d][j]);
				}
				if (temp >= 1)
					next[i][j] = 1;
			}
		}
		for (int i = 0; i < n; i++) {//把arr和M矩阵加起来
			for (int j = 0; j < n; j++) {
				M[i][j] = next[i][j];
				ans[i][j] = ans[i][j] + M[i][j];
				next[i][j] = 0;
				if (ans[i][j] > 1)//bool
					ans[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] =ans[i][j];
		}
	}
	delete_shuzu(next, n);//清理空间
	delete_shuzu(ans, n);
	delete_shuzu(M, n);
}

void show() {//展示矩阵
	cout << "矩阵：" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}