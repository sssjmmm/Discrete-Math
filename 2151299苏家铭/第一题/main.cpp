#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

typedef map<char, int> Map_ci;
typedef map<int, char> Map_ic;
typedef map<int, int> Map_ii;
//typedef map<int, bool> Map_ib;

Map_ci priority;

Map_ic getProposition(string formula);
int findProposition(Map_ic, char p);
int pow2(int n);
Map_ii toBinary(int n_proposition, int index);
int calculate(string formula, Map_ic pSet, Map_ii value);
void check(stack<int>& value, stack<char>& opter);
int judge(string str);

int main()
{
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;
	priority['#'] = 0;
	//��������ȼ�

	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "Please enter a legitimate proposition formula: " << endl;
	string formula;
tt:	cin >> formula;
//1����������ƥ�� 2��a| a& 3��|a|b 4��#���� 5��ab&c����
	int T = judge(formula);
	switch (T)
	{
	case 1:
		cout << "���Ų�ƥ�䣡���ٴ����룺" << endl;
		goto tt;
		break;
	case 2:
		cout << "ĩβ��Ӧ�������Ӵʣ����ٴ����룺" << endl;
		goto tt;
		break;
	case 3:
		cout << "��ͷ��Ӧ����˫Ŀ���Ӵʣ����ٴ����룺" << endl;
		goto tt;
		break;
	case 4:
		cout << "���зǷ������ַ������ٴ����룺" << endl;
		goto tt;
		break;
	case 5:
		cout << "���������Ӵʲ�Ӧ���������ٴ����룺" << endl;
		goto tt;
		break;
	default:
		break;
	}
	Map_ic proposition_set = getProposition(formula);
	cout << "��ʽ���еı�������Ϊ��" << proposition_set.size() << endl << "�����ֵ�����£�" << endl;
	for (unsigned int i = 0; i < proposition_set.size(); i++){
		cout << proposition_set[i] << "\t";
	}
	cout << formula << endl;
	int* m;
	m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));   //���������δ�����⹫ʽ�ĸ���(0��1)����������ֵ
	// int z = pow2(proposition_set.size());
	// cout << z << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		Map_ii bina_set = toBinary(proposition_set.size(), i);
		for (unsigned int j = 0; j < bina_set.size(); j++)
		{
			cout << bina_set[j] << "\t";
		}
		int result = calculate(formula, proposition_set, bina_set);
		//m[i] = result;
		*(m + i) = result;
		cout << result << endl;
	}
	int n_m = 0, n_M = 0;
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 1)//����ȡ��ʽ��ֵΪ��
		{
			if (n_m == 0)//��һ����ʽ
			{
				cout << "m<" << i << ">";
			}
			else
			{
				cout << " \\/ m<" << i << "> ";
			}
			n_m++;
		}
	}
	if (n_m == 0)//û�з�ʽ
	{
		cout << "0";
	}
	cout << endl;
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 0)//����ȡ��ʽ��ֵΪ��
		{
			if (n_M == 0)//��һ����ʽ
			{
				cout << "M<" << i << ">";
			}
			else
			{
				cout << " /\\ M<" << i << "> ";
			}
			n_M++;
		}
	}
	if (n_M == 0)//û�з�ʽ
	{
		cout << "0";
	}
	cout << endl;
	return 0;
}

int findProposition(Map_ic pSet, char p) //����-1����ʾ�����������δ�����������ɼ���������˵������������ѱ������������ظ����������⣬�����Է���ָ�����������±�
{
	Map_ic::iterator it = pSet.begin();
	while (it != pSet.end())
	{
		if (it->second == p)
		{
			return it->first;
		}
		it++;
	}
	return -1;
}


Map_ic getProposition(string formula) //�ú������������빫ʽ�е��������(�����������)
{
	Map_ic proposition;
	int n_proposition = 0;
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//���������������
			int r = findProposition(proposition, c);
			//cout << r << endl;
			if (r == -1)
			{
				//˵�������������δ��������
				proposition[n_proposition] = c;
				n_proposition++;
			}
		}
		else if (!priority.count(c))
		{
			cout << c << " is undefined!" << endl;
			exit(2);
		}
	}
	return proposition;
}

Map_ii toBinary(int n_proposition, int index)  //�ú��������������Ķ�����(0��1)ȡֵ
{
	Map_ii result;
	for (int i = 0; i < n_proposition; i++)
	{
		int r = index % 2;
		result[n_proposition - 1 - i] = r;
		index = index / 2;
	}
	return result;
}

int pow2(int n)    //�ú�������ָ�����ֵĶ��η���ֵ
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}


int calculate(string formula, Map_ic pSet, Map_ii value) //�ú������ظ������������(ֵȡ0��1���ɺ�����)��ϵ�������
{
	stack<char> opter;
	stack<int> pvalue;
	opter.push('#');
	formula = formula + "#";
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			pvalue.push(value[findProposition(pSet, c)]);
		}
		else
		{
			//��ʱ�������������
			char tmp = opter.top();
			if (priority[tmp] > priority[c])
			{
				while (priority[tmp] > priority[c] && tmp != '(')
				{
					check(pvalue, opter);
					tmp = opter.top();
					if (tmp == '#' && c == '#')
					{
						return pvalue.top();
					}
				}
				opter.push(c);
			}
			else
				opter.push(c);
		}
	}
	return -1;
}


void check(stack<int>& value, stack<char>& opter) //�ú������������������(ȡֵ0��1)�ĸ���������(0��1)
{
	int p, q, result;
	char opt = opter.top();

	switch (opt)
	{
	case '&':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p && q;
		value.push(result);
		opter.pop();
		break;

	case '|':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p || q;
		value.push(result);
		opter.pop();
		break;

	case '!':
		p = value.top();
		value.pop();
		result = !p;
		value.push(result);
		opter.pop();
		break;

	case '^':
		q = value.top();
		value.pop();
		p = value.top();
		value.pop();
		result = !p || q;
		value.push(result);
		opter.pop();
		break;

	case '~':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = (!p || q) && (p || !q);
		value.push(result);
		opter.pop();
		break;

	case '#':
		break;

	case '(':
		break;

	case ')':
		opter.pop();
		while (opter.top() != '(')
		{
			check(value, opter);
		}
		if (opter.top() == '(')
		{
			opter.pop();
		}
		break;

	default:
		break;
	}
}
//�жϴ�������
int judge(string str) {
	stack<char> st;
	size_t i = 0,len=str.length();
	//��������Ƿ�ƥ��
	while (i < len) {
		if (str[i] == '(')//������
			st.push(str[i]);
		else if (str[i] == ')' && !st.empty())//�����Ų���ջ����������
			st.pop();
		else if(str[i]==')')//ջ��û�����ŵ���������
			return 1;
		i++;
	}
	if (!st.empty())
		return 1;
	//���ż�����
	i = 0;
	//���a|  a&����
	if (str[len - 1] == '!' || str[len - 1] == '|' ||
		str[len - 1] == '&' || str[len - 1] == '~' ||
		str[len - 1] == '^')
		return 2;
	//��β���������
	//���|a|b����
	if (str[0] == '|' ||str[0] == '&' || str[0] == '~' ||str[0] == '^')
		return 3;
	//��鿪ͷ���
	//���Ƿ�����
	while (i < len) {
		if (str[i] == '(' || str[i] == ')' ||
			(str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			str[i] == '!' || str[i] == '|' ||
			str[i] == '&' || str[i] == '^' ||
			str[i] == '~')
			i++;
		else
			return 4;
	}
	//���Ƿ��ַ����
	//���ab&c����ͬ�Ϸ��ַ����������
	i = 0;
	while (i < len) {
		if ((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') )
			if ((str[i + 1] >= 'a' && str[i + 1] <= 'z') ||
				(str[i + 1] >= 'A' && str[i + 1] <= 'Z'))
				return 5;
		if (str[i] == '!' || str[i] == '|' ||
			str[i] == '&' || str[i] == '^' ||
			str[i] == '~')
			if (str[i + 1] == '!' || str[i + 1] == '|' ||
				str[i + 1] == '&' || str[i + 1] == '^' ||
				str[i + 1] == '~')
				return 5;
		i++;
	}
	//�����Ϸ�������
	return 0;
}

#if 0
#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	int a[4];
	int i = -1, j = -1;
	char s;
tt:cout << "***************************************" << endl;  //����
	cout << "**                                   **" << endl;
	cout << "**        ��ӭ�����߼��������       **" << endl;
	cout << "**                                   **" << endl;
	cout << "***************************************\n" << endl;
	cout << "\n  ������P��ֵ��0��1��,�Իس�����:";
	cin >> i;  //��ȡP��ֵ
	if (i != 0 && i != 1)
	{
		cout << "\n  P��ֵ��������,����������!";
		Sleep(2000);
		system("cls");  //����
		goto tt;
	}
	cout << "\n  ������Q��ֵ��0��1��,�Իس�����:";
	cin >> j;  //��ȡQ��ֵ
	if (j != 0 && j != 1)
	{
		cout << "\n  Q��ֵ��������,����������!";
		Sleep(2000);
		system("cls");  //����
		goto tt;
	}
	a[0] = i && j;  //������
	a[1] = i || j;  //������
	a[2] = (!i) || j;  //�̺����㣬����ת��Ϊ������ʽ
	a[3] = ((!i) || j) && ((!j) || i);  //��ֵ���㣬����ת��Ϊ������ʽ
	cout << "\n\n  ��ȡ:\n       P/\\Q = " << a[0] << endl;  //������
	cout << "  ��ȡ:\n       P\\/Q = " << a[1] << endl;
	cout << "  ����:\n       P->Q = " << a[2] << endl;
	cout << "  ˫����:\n       P<->Q = " << a[3] << endl;
bb:cout << "\n�Ƿ��������?��y/n��";  //ѯ���Ƿ��������
	cin >> s;
	if (s == 'y' || s == 'n')
	{
		if (s == 'y')
		{
			system("cls");  //����
			goto tt;  //���ض���
		}
		else
		{
			cout << "��ӭ�´��ٴ�ʹ��!" << endl;  //�˳�
			exit(0);
		}
	}
	else
	{
		cout << "�������,����������!" << endl; //����У��
		goto bb;
	}
	return 0;
}
#endif