/*
7 12
1 2 20
2 3 15
3 4 3
4 5 17
5 6 28
6 1 23
1 7 1
2 7 4
3 7 9
4 7 16
5 7 25
6 7 36
*/
#include<iostream>
using namespace std;
#include"min_heap.h"
#include"graph.h"
#include"min_span_tree.h"
#include<climits>
void choice_A(graph<char, int>& G);
void choice_B(graph<char, int>& G);
void choice_C(graph<char, int>& G, MST<char, int>& mst);
void choice_D(graph<char, int>& G, MST<char, int>& mst);
void choice_E(graph<char, int>& G, MST<char, int>& mst);
void choice_F();
template<class T, class E>
void prim_toMST(graph<T, E>& G, const T u0, MST<T, E>& mst);
template<class T, class E>
void kruskal_toMST(graph<T, E>& G, MST<T, E>& mst);

int main() {
	cout << "**       离散数学——最小生成树           **" << endl;
	cout << "============================================" << endl;
	cout << "**          A --- 创建图的顶点            **" << endl;
	cout << "**          B --- 添加图的边              **" << endl;
	cout << "**          C --- 构造最小生成树(prim)    **" << endl;
	cout << "**          D --- 构造最小生成树(kruscal) **" << endl;
	cout << "**          E --- 显示最小生成树          **" << endl;
	cout << "**          F --- 退出程序                **" << endl;
	cout << "**          F --- 退出程序                **" << endl;
	cout << "**          若输入的边数小于N(N-1)/2      **" << endl;
	cout << "**          (N为顶点数)请输入0 0 0结束    **" << endl;
	cout << "============================================" << endl;

	char choice;
	graph<char, int> G;
	MST<char, int>mst;
	bool loop = true;
	while (loop) {
		while (1) {
			cout << "请选择操作：" << endl;
			cin >> choice;
			if (choice >= 'a' && choice <= 'z') {
				choice = choice + 'A' - 'a';
			}
			if (cin.fail() || !(choice >= 'A' && choice <= 'F')) {
				cout << "输入操作有误，请再次输入：" << endl;
				cin.ignore(65535, '\n');
				cin.clear();
			}
			else
				break;
		}
		switch (choice) {
		case 'A':
			choice_A(G);
			break;
		case'B':
			choice_B(G);
			break;
		case'C':
			choice_C(G, mst);
			break;
		case'D':
			choice_D(G, mst);
			break;
		case'E':
			choice_E(G, mst);
			break;
		case'F':
			loop = false;//退出
			choice_F();
			break;
		}
	}

	return 0;
}

void choice_A(graph<char, int>& G) {
	int n, i = 0;
	char name;
	cout << "请输入图结点个数：";
	while (1) {
		cin >> n;
		if (cin.fail() || n < 0) {
			cout << "输入错误，请再次输入！" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "请以此输入各结点的名称" << endl;
	while (i < n) {
		cin >> name;
		G.insert_vertex(name);
		i++;
	}
	cout << endl;
}

void choice_B(graph<char, int>& G) {
	int i = 0, m = G.vertices_number(), weight, j, k;
	char e1, e2;
	while (i < m * (m - 1) / 2) {
		cout << "请输入顶点及边：";
		cin >> e1 >> e2 >> weight;//输入端点信息
		if (e1 == '0' && e2 == '0')
			break;
		j = G.get_vertex_pos(e1);
		k = G.get_vertex_pos(e2);//查顶点号
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，请重新输入！" << endl;
		else {
			G.insert_edge(j, k, weight);
			++i;
		}
	}

}

void choice_C(graph<char, int>& G, MST<char, int>& mst) {
	char name;
	cout << "请输入起始顶点：";
	cin >> name;
	prim_toMST(G, name, mst);
	if (!mst.empty())
		cout << "生成prim最小生成树！" << endl;
	else
		cout << "无法生成最小生成树！" << endl;

}

void choice_D(graph<char, int>& G, MST<char, int>& mst) {
	kruskal_toMST(G, mst);
	if (!mst.empty())
		cout << "生成kruskal最小生成树！" << endl;
	else
		cout << "无法生成最小生成树！" << endl;

}

template<class T, class E>
void prim_toMST(graph<T, E>& G, const T u0, MST<T, E>& mst) {
	if (G.vertices_number() > mst.get_max_size())
		mst.enlarge(G.vertices_number());
	MST_edge_node<T, E> ed;//边结点
	int i, v, count;
	int n = G.vertices_number();//顶点数
	int m = G.edges_number();//边数
	int u = G.get_vertex_pos(u0);//起始顶点号u
	minHeap<MST_edge_node<T, E> > heap(m);//建立最小堆
	bool* Vmst = new bool[n];//最小生成树顶点集合，判断够没够n-1条边
	for (i = 0; i < n; i++) {
		Vmst[i] = false;
	}
	Vmst[u] = true;//u加入生成数
	count = 1;
	while (count < n) {
		v = G.get_first_neighbor(u);
		while (v != -1) {//遍历u的所有邻接结点
			if (Vmst[v] == false) {//若v不在生成树，则(u,v)加入最小堆
				ed.tail = u;//tail在树内
				ed.head = v;//head不在树内
				ed.key = G.get_weight(u, v);
				heap.insert(ed);
			}
			v = G.get_next_neighbor(u, v);//下一个邻接结点
		}//end of while
		while (heap.empty() == false && count < n) {
			heap.remove_min(ed);//取出最小权值的边ed
			if (Vmst[ed.head] == false) {
				mst.insert(ed);//加入最小生成树
				u = ed.head;
				Vmst[u] = true;//u加入生成树顶点集合
				count++;
				break;
			}
		}//end of while
	}//end of whlie(count<n)
	delete[] Vmst;
}


class uf {//每个数组元素初始指向自己，fa[x]指向父亲
public:
	int find(int x)//找到根结点
	{
		while (fa[x] != x)
		{
			fa[x] = fa[fa[x]];
			x = fa[x];
		}
		return x;
	}
	bool union_xy(int x, int y)//合并两个集合
	{
		int root_x = find(x);
		int root_y = find(y);
		if (root_x == root_y)
			return false;
		fa[root_x] = root_y;
		return true;
	}
	bool is_connected(int x, int y) {//判断是否是等价类
		int root_x = find(x);
		int root_y = find(y);
		return root_x == root_y;
	}
	uf(const int& sz)
	{
		fa = new int[sz];
		if (fa == NULL)
			return;
		for (int i = 0; i < sz; ++i)
			fa[i] = i;
	}
	~uf() {
		delete[] fa;
	}
private:
	int* fa;
};

template<class T, class E>
void kruskal_toMST(graph<T, E>& G, MST<T, E>& mst)
{
	MST_edge_node<T, E> edge;

	uf _uf(G.vertices_number());//建立一个并查集，大小为图的顶点数

	minHeap<MST_edge_node<T, E> > heap(G.edges_number());//建立最小堆
	//遍历将所有边加入heap
	for (int i = 0; i < G.vertices_number(); i++) {
		for (int j = i + 1; j < G.vertices_number(); j++) {
			if (G.get_weight(i, j) != INT_MAX) {//插入堆中
				edge.tail = i;
				edge.head = j;
				edge.key = G.get_weight(i, j);
				heap.insert(edge);
			}
		}
	}
	//开始kruskal
	int cnt = 0;
	MST_edge_node<T, E> temp;
	for (int i = 0; i < G.edges_number(); ++i) {
		//完成n-1条边的连接
		if (cnt == G.vertices_number() - 1)
			break;
		//取出最小
		heap.remove_min(temp);
		if (_uf.is_connected(temp.tail, temp.head))
			continue;
		_uf.union_xy(temp.tail, temp.head);
		//记录答案
		mst.insert(temp);
	}

}

void choice_E(graph<char, int>& G, MST<char, int>& mst) {
	cout << "最小生成树的顶点及边权值为：" << endl;
	for (int i = 0; i < mst.get_n(); i++) {
		cout << "最小耗费是：";
		cout << G.get_value(mst.get_edge_node_tail(i)) << "-(" <<
			mst.get_edge_node_key(i) << ")->" << G.get_value(mst.get_edge_node_head(i)) << endl;
	}
	cout << endl;
}

void choice_F() {
	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
}
