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
	init();//��ʼ������
	show();//չʾ��ʼ���ľ���
	select();//ѡ���㷨,choice
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

void delete_shuzu(int** arrx, int n) {//��������Ŀռ�ĺ������������ڴ�
	for (int i = 0; i < n; ++i) 
		delete []arrx[i];
}
void exit() {//�˳��ĺ���
	cout << "���س��˳�......." << endl;
	cin.get();
}
void init() {//��ʼ������
	cout << "�����������(��)��:";
	while (1) {//��׳�ԣ��Է��Ƿ�����
		cin >> n;
		if (cin.fail() || n < 0) {
			cout << "����Ƿ������ٴ�����:" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "������ʼ����:" << endl;
	arr = new int* [n];
	for (int i = 0; i < n; ++i)
		arr[i] = new int[n];
	for (int i = 0; i < n; i++) {//������ ѭ���������
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
}

void select() {
	cout << "=======================" << endl;
	cout << "=======1:�Է��հ�======" << endl;
	cout << "=======2:���ݱհ�======" << endl;
	cout << "=======3:�ԳƱհ�======" << endl;
	cout << "=======4:�˳�==========" << endl;
	cout << "=======================" << endl;
	cout << "��������Ӧ���ѡ���Ӧ�㷨:";

	while (1) {//��׳��
		cin >> choice;
		if (cin.fail()|| choice < 0 || choice>4) {
			cout << "����������ٴ�����:";
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
void zifan() {//�Է�,���Խ�����1
	for (int i = 0; i < n; i++)
		arr[i][i] = 1;
}
void duichen() {//���������ij��1����ôjiҲҪ��1
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 1)
				arr[j][i] = 1;
		}
	}
}
void chuandi() {//���ݣ�ʱ�临�Ӷ�O(n4)��δ��������㷨
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
	for (int m = 0; m < n; m++) {//n���������
		for (int i = 0; i < n; i++) {//��i��ÿ��Ԫ��*��j��ÿ��Ԫ��
			for (int j = 0; j < n; j++) {
				temp = 0;
				for (int d=0; d < n; d++){
					temp+=(M[i][d] * arr[d][j]);
				}
				if (temp >= 1)
					next[i][j] = 1;
			}
		}
		for (int i = 0; i < n; i++) {//��arr��M���������
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
	delete_shuzu(next, n);//����ռ�
	delete_shuzu(ans, n);
	delete_shuzu(M, n);
}

void show() {//չʾ����
	cout << "����" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}