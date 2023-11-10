#include <iostream>
using namespace std;
int main()
{
	int A, B, C, D, E;
//A:营业员A偷了手表
//B:营业员B偷了手表
//C : 作案不在营业时间
//D : B提供的证据正确
//E : 货柜未上锁
	bool success = false;//健壮性，有无结果
	for (A = 0; A <= 1; A++)//营业员A偷了手表与否
		for (B = 0; B <= 1; B++)//营业员B偷了手表与否
			for (C = 0; C <= 1; C++)//C : 作案不在营业时间与否
				for (D = 0; D <= 1; D++)//D : B提供的证据正确与否
					for (E = 0; E <= 1; E++)//E : 货柜未上锁与否
						if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E){//若满足该式子
							cout << "A=" << A << ",B=" << B << endl;//输出结果
							success = true;//找得到指派
						}
	if(success==false)
	    cout << "没有相应真值指派" << endl;
	return 0;
}
