#include <iostream>
using namespace std;
int main()
{
	int A, B, C, D, E;
//A:ӪҵԱA͵���ֱ�
//B:ӪҵԱB͵���ֱ�
//C : ��������Ӫҵʱ��
//D : B�ṩ��֤����ȷ
//E : ����δ����
	bool success = false;//��׳�ԣ����޽��
	for (A = 0; A <= 1; A++)//ӪҵԱA͵���ֱ����
		for (B = 0; B <= 1; B++)//ӪҵԱB͵���ֱ����
			for (C = 0; C <= 1; C++)//C : ��������Ӫҵʱ�����
				for (D = 0; D <= 1; D++)//D : B�ṩ��֤����ȷ���
					for (E = 0; E <= 1; E++)//E : ����δ�������
						if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E){//�������ʽ��
							cout << "A=" << A << ",B=" << B << endl;//������
							success = true;//�ҵõ�ָ��
						}
	if(success==false)
	    cout << "û����Ӧ��ֵָ��" << endl;
	return 0;
}
