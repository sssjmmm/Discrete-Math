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
	cout << "**       ��ɢ��ѧ������С������           **" << endl;
	cout << "============================================" << endl;
	cout << "**          A --- ����ͼ�Ķ���            **" << endl;
	cout << "**          B --- ���ͼ�ı�              **" << endl;
	cout << "**          C --- ������С������(prim)    **" << endl;
	cout << "**          D --- ������С������(kruscal) **" << endl;
	cout << "**          E --- ��ʾ��С������          **" << endl;
	cout << "**          F --- �˳�����                **" << endl;
	cout << "**          F --- �˳�����                **" << endl;
	cout << "**          ������ı���С��N(N-1)/2      **" << endl;
	cout << "**          (NΪ������)������0 0 0����    **" << endl;
	cout << "============================================" << endl;

	char choice;
	graph<char, int> G;
	MST<char, int>mst;
	bool loop = true;
	while (loop) {
		while (1) {
			cout << "��ѡ�������" << endl;
			cin >> choice;
			if (choice >= 'a' && choice <= 'z') {
				choice = choice + 'A' - 'a';
			}
			if (cin.fail() || !(choice >= 'A' && choice <= 'F')) {
				cout << "��������������ٴ����룺" << endl;
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
			loop = false;//�˳�
			choice_F();
			break;
		}
	}

	return 0;
}

void choice_A(graph<char, int>& G) {
	int n, i = 0;
	char name;
	cout << "������ͼ��������";
	while (1) {
		cin >> n;
		if (cin.fail() || n < 0) {
			cout << "����������ٴ����룡" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "���Դ��������������" << endl;
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
		cout << "�����붥�㼰�ߣ�";
		cin >> e1 >> e2 >> weight;//����˵���Ϣ
		if (e1 == '0' && e2 == '0')
			break;
		j = G.get_vertex_pos(e1);
		k = G.get_vertex_pos(e2);//�鶥���
		if (j == -1 || k == -1)
			cout << "�����˵���Ϣ�������������룡" << endl;
		else {
			G.insert_edge(j, k, weight);
			++i;
		}
	}

}

void choice_C(graph<char, int>& G, MST<char, int>& mst) {
	char name;
	cout << "��������ʼ���㣺";
	cin >> name;
	prim_toMST(G, name, mst);
	if (!mst.empty())
		cout << "����prim��С��������" << endl;
	else
		cout << "�޷�������С��������" << endl;

}

void choice_D(graph<char, int>& G, MST<char, int>& mst) {
	kruskal_toMST(G, mst);
	if (!mst.empty())
		cout << "����kruskal��С��������" << endl;
	else
		cout << "�޷�������С��������" << endl;

}

template<class T, class E>
void prim_toMST(graph<T, E>& G, const T u0, MST<T, E>& mst) {
	if (G.vertices_number() > mst.get_max_size())
		mst.enlarge(G.vertices_number());
	MST_edge_node<T, E> ed;//�߽��
	int i, v, count;
	int n = G.vertices_number();//������
	int m = G.edges_number();//����
	int u = G.get_vertex_pos(u0);//��ʼ�����u
	minHeap<MST_edge_node<T, E> > heap(m);//������С��
	bool* Vmst = new bool[n];//��С���������㼯�ϣ��жϹ�û��n-1����
	for (i = 0; i < n; i++) {
		Vmst[i] = false;
	}
	Vmst[u] = true;//u����������
	count = 1;
	while (count < n) {
		v = G.get_first_neighbor(u);
		while (v != -1) {//����u�������ڽӽ��
			if (Vmst[v] == false) {//��v��������������(u,v)������С��
				ed.tail = u;//tail������
				ed.head = v;//head��������
				ed.key = G.get_weight(u, v);
				heap.insert(ed);
			}
			v = G.get_next_neighbor(u, v);//��һ���ڽӽ��
		}//end of while
		while (heap.empty() == false && count < n) {
			heap.remove_min(ed);//ȡ����СȨֵ�ı�ed
			if (Vmst[ed.head] == false) {
				mst.insert(ed);//������С������
				u = ed.head;
				Vmst[u] = true;//u�������������㼯��
				count++;
				break;
			}
		}//end of while
	}//end of whlie(count<n)
	delete[] Vmst;
}


class uf {//ÿ������Ԫ�س�ʼָ���Լ���fa[x]ָ����
public:
	int find(int x)//�ҵ������
	{
		while (fa[x] != x)
		{
			fa[x] = fa[fa[x]];
			x = fa[x];
		}
		return x;
	}
	bool union_xy(int x, int y)//�ϲ���������
	{
		int root_x = find(x);
		int root_y = find(y);
		if (root_x == root_y)
			return false;
		fa[root_x] = root_y;
		return true;
	}
	bool is_connected(int x, int y) {//�ж��Ƿ��ǵȼ���
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

	uf _uf(G.vertices_number());//����һ�����鼯����СΪͼ�Ķ�����

	minHeap<MST_edge_node<T, E> > heap(G.edges_number());//������С��
	//���������б߼���heap
	for (int i = 0; i < G.vertices_number(); i++) {
		for (int j = i + 1; j < G.vertices_number(); j++) {
			if (G.get_weight(i, j) != INT_MAX) {//�������
				edge.tail = i;
				edge.head = j;
				edge.key = G.get_weight(i, j);
				heap.insert(edge);
			}
		}
	}
	//��ʼkruskal
	int cnt = 0;
	MST_edge_node<T, E> temp;
	for (int i = 0; i < G.edges_number(); ++i) {
		//���n-1���ߵ�����
		if (cnt == G.vertices_number() - 1)
			break;
		//ȡ����С
		heap.remove_min(temp);
		if (_uf.is_connected(temp.tail, temp.head))
			continue;
		_uf.union_xy(temp.tail, temp.head);
		//��¼��
		mst.insert(temp);
	}

}

void choice_E(graph<char, int>& G, MST<char, int>& mst) {
	cout << "��С�������Ķ��㼰��ȨֵΪ��" << endl;
	for (int i = 0; i < mst.get_n(); i++) {
		cout << "��С�ķ��ǣ�";
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
