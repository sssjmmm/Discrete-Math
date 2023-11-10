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
	//运算符优先级

	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "Please enter a legitimate proposition formula: " << endl;
	string formula;
tt:	cin >> formula;
//1、（）括号匹配 2、a| a& 3、|a|b 4、#错误 5、ab&c报错
	int T = judge(formula);
	switch (T)
	{
	case 1:
		cout << "括号不匹配！请再次输入：" << endl;
		goto tt;
		break;
	case 2:
		cout << "末尾不应出现连接词！请再次输入：" << endl;
		goto tt;
		break;
	case 3:
		cout << "开头不应出现双目连接词！请再次输入：" << endl;
		goto tt;
		break;
	case 4:
		cout << "含有非法输入字符！请再次输入：" << endl;
		goto tt;
		break;
	case 5:
		cout << "变量或连接词不应连续！请再次输入：" << endl;
		goto tt;
		break;
	default:
		break;
	}
	Map_ic proposition_set = getProposition(formula);
	cout << "该式子中的变量个数为：" << proposition_set.size() << endl << "输出真值表如下：" << endl;
	for (unsigned int i = 0; i < proposition_set.size(); i++){
		cout << proposition_set[i] << "\t";
	}
	cout << formula << endl;
	int* m;
	m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));   //该数组依次存放命题公式的各行(0或1)的运算结果的值
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
	cout << "该命题公式的主析取范式：" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 1)//主析取范式，值为真
		{
			if (n_m == 0)//第一个范式
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
	if (n_m == 0)//没有范式
	{
		cout << "0";
	}
	cout << endl;
	cout << "该命题公式的主合取范式：" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 0)//主合取范式，值为假
		{
			if (n_M == 0)//第一个范式
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
	if (n_M == 0)//没有范式
	{
		cout << "0";
	}
	cout << endl;
	return 0;
}

int findProposition(Map_ic pSet, char p) //返回-1，表示该命题变项尚未被遍历过，可计数；否则说明该命题变项已被遍历过，则不重复计数。另外，还可以返回指定命题变项的下标
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


Map_ic getProposition(string formula) //该函数返回所输入公式中的命题变项(不包括运算符)
{
	Map_ic proposition;
	int n_proposition = 0;
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//遍历所有命题变项
			int r = findProposition(proposition, c);
			//cout << r << endl;
			if (r == -1)
			{
				//说明该命题变项尚未被遍历过
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

Map_ii toBinary(int n_proposition, int index)  //该函数返回命题变项的二进制(0或1)取值
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

int pow2(int n)    //该函数返回指定数字的二次方的值
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}


int calculate(string formula, Map_ic pSet, Map_ii value) //该函数返回给定，命题变项(值取0或1，可含括号)组合的运算结果
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
			//此时遍历的是运算符
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


void check(stack<int>& value, stack<char>& opter) //该函数返回两个命题变项(取值0或1)的各种运算结果(0或1)
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
//判断错误输入
int judge(string str) {
	stack<char> st;
	size_t i = 0,len=str.length();
	//检查括号是否匹配
	while (i < len) {
		if (str[i] == '(')//左括号
			st.push(str[i]);
		else if (str[i] == ')' && !st.empty())//右括号并且栈内有左括号
			st.pop();
		else if(str[i]==')')//栈内没左括号但有右括号
			return 1;
		i++;
	}
	if (!st.empty())
		return 1;
	//括号检查完毕
	i = 0;
	//检查a|  a&错误
	if (str[len - 1] == '!' || str[len - 1] == '|' ||
		str[len - 1] == '&' || str[len - 1] == '~' ||
		str[len - 1] == '^')
		return 2;
	//结尾错误检查完毕
	//检查|a|b错误
	if (str[0] == '|' ||str[0] == '&' || str[0] == '~' ||str[0] == '^')
		return 3;
	//检查开头完毕
	//检查非法符号
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
	//检查非法字符完毕
	//检查ab&c等相同合法字符连续的情况
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
	//连续合法检查完毕
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
tt:cout << "***************************************" << endl;  //标语
	cout << "**                                   **" << endl;
	cout << "**        欢迎进入逻辑运算程序       **" << endl;
	cout << "**                                   **" << endl;
	cout << "***************************************\n" << endl;
	cout << "\n  请输入P的值（0或1）,以回车结束:";
	cin >> i;  //读取P的值
	if (i != 0 && i != 1)
	{
		cout << "\n  P的值输入有误,请重新输入!";
		Sleep(2000);
		system("cls");  //清屏
		goto tt;
	}
	cout << "\n  请输入Q的值（0或1）,以回车结束:";
	cin >> j;  //读取Q的值
	if (j != 0 && j != 1)
	{
		cout << "\n  Q的值输入有误,请重新输入!";
		Sleep(2000);
		system("cls");  //清屏
		goto tt;
	}
	a[0] = i && j;  //与运算
	a[1] = i || j;  //或运算
	a[2] = (!i) || j;  //蕴含运算，将其转化为与或非形式
	a[3] = ((!i) || j) && ((!j) || i);  //等值运算，将其转化为与或非形式
	cout << "\n\n  合取:\n       P/\\Q = " << a[0] << endl;  //输出结果
	cout << "  析取:\n       P\\/Q = " << a[1] << endl;
	cout << "  条件:\n       P->Q = " << a[2] << endl;
	cout << "  双条件:\n       P<->Q = " << a[3] << endl;
bb:cout << "\n是否继续运算?（y/n）";  //询问是否继续操作
	cin >> s;
	if (s == 'y' || s == 'n')
	{
		if (s == 'y')
		{
			system("cls");  //清屏
			goto tt;  //返回顶层
		}
		else
		{
			cout << "欢迎下次再次使用!" << endl;  //退出
			exit(0);
		}
	}
	else
	{
		cout << "输入错误,请重新输入!" << endl; //错误校验
		goto bb;
	}
	return 0;
}
#endif