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
	init();//��ʼ������
	show();//��ʾ��ʼ����
	cout << "=======================" << endl;
	cout << "===Warshell���ݱհ�====" << endl;
	cout << "=======================" << endl;
	warshell();//��warshell�㷨�󴫵ݱհ�
	show();//��ʾ���ݱհ�����
	delete_shuzu(arr, n);//�ͷŴ洢�ռ�

	return 0;
}

void delete_shuzu(int** arrx, int n) {
	for (int i = 0; i < n; ++i)
		delete[]arrx[i];
}

void init() {
	cout << "�����������(��)��:";
	while (1) {
		cin >> n;
		if (cin.fail() || n < 1) {
			cout << "���������(��)���Ƿ������ٴ�����:" << endl;
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
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
}


void warshell() {
//(1)i��0��
//(2)������j���a[j��i]��1�����k��0��1������n-1��a[j��k]��a[j��k]��a[i��k]��
//(3)i��1��
//(4)���i<n����ת������2������ֹͣ
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < n; i++)//��n�α�����i����
	{
		for (j = 0; j < n; j++)//����i���Ƿ���1
		{
			if (arr[j][i]==1)//����j��i����1����ѵ�i�и���Ԫ�ض�Ӧ�ӵ���j��
			{
				for (k = 0; k < n; k++)
				{
					arr[j][k] = arr[j][k] | arr[i][k];//�߼��� 
				}
			}
		}
	}
}

void show() {
	cout << "����" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}