#include<iostream>
using namespace std;

void warshell();
void show();
void init();
void select();
void delete_shuzu(int** arrx, int n);
int** arr, n;


/*
1 0 1 0 0 0 1
0 0 0 1 1 1 0
0 1 0 1 0 0 1
0 1 0 1 1 1 0
0 1 1 0 1 1 1
1 1 1 0 0 0 1
1 0 0 1 0 1 0

0 0 1
1 0 1
0 1 1

0 1 0 0
1 0 1 0
0 0 0 1
0 0 0 0
*/
int main() {
	init();//初始化矩阵
	show();//显示初始矩阵
	cout << "=======================" << endl;
	cout << "===Warshell传递闭包====" << endl;
	cout << "=======================" << endl;
	warshell();//用warshell算法求传递闭包
	show();//显示传递闭包矩阵
	delete_shuzu(arr, n);//释放存储空间

	return 0;
}

void delete_shuzu(int** arrx, int n) {
	for (int i = 0; i < n; ++i)
		delete[]arrx[i];
}

void init() {
	cout << "请输入矩阵行(列)数:";
	while (1) {
		cin >> n;
		if (cin.fail() || n < 1) {
			cout << "输入矩阵行(列)数非法，请再次输入:" << endl;
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
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
}


void warshell() {
//(1)i＝0；
//(2)对所有j如果a[j，i]＝1，则对k＝0，1，…，n-1，a[j，k]＝a[j，k]∨a[i，k]；
//(3)i加1；
//(4)如果i<n，则转到步骤2，否则停止
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < n; i++)//共n次遍历，i是列
	{
		for (j = 0; j < n; j++)//检查第i列是否有1
		{
			if (arr[j][i]==1)//若第j行i列是1，则把第i行各个元素对应加到第j行
			{
				for (k = 0; k < n; k++)
				{
					arr[j][k] = arr[j][k] | arr[i][k];//逻辑加 
				}
			}
		}
	}
}

void show() {
	cout << "矩阵：" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}