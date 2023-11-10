#ifndef __SJM_MINSPAN_TREE_
#define _SJM_MINSPAN_TREE_

#define DEFAULT_SIZE 30
template<class T, class E>
struct MST_edge_node {//��С�������߽���������
	int tail, head;//�������λ��
	E key;//���ϵ�Ȩֵ��Ϊ�ؼ���
	MST_edge_node() :tail(-1), head(-1), key(0) {}//���캯��
	friend bool operator<(const MST_edge_node& a, const MST_edge_node& b) {
		return a.key < b.key;
	}

	friend bool operator>(const MST_edge_node& a, const MST_edge_node& b) {
		return a.key > b.key;
	}

	bool operator==(const MST_edge_node& b) {
		return key == b.key;
	}

	bool operator>=(const MST_edge_node& b) {
		return key >= b.key;
	}

	bool operator<=(const MST_edge_node& b) {
		return key <= b.key;
	}
};

template<class T, class E>
class MST {
protected:
	MST_edge_node<T, E>* edge_value;//�ñ�ֵ�����ʾ��
	int max_size, n;//��������Ԫ�ظ����͵�ǰ����
public:
	MST(int size = DEFAULT_SIZE - 1) :max_size(size), n(0) {//���캯��
		edge_value = new MST_edge_node<T, E>[size];
	}
	~MST() {//��������
		delete[]edge_value;
	}
	int insert(MST_edge_node<T, E>& item);
	void enlarge(int size);
	bool empty();
	int get_max_size() {
		return max_size;
	}
	int get_n() {
		return n;
	}
	MST_edge_node<T, E>* get_edge_value() {
		return edge_value;
	}

	int get_edge_node_tail(int i) {
		return edge_value[i].tail;
	}
	int get_edge_node_head(int i) {
		return edge_value[i].head;
	}

	int get_edge_node_key(int i) {
		return this->edge_value[i].key;
	}
};

template<class T, class E>
int MST<T, E>::insert(MST_edge_node<T, E>& item) {
	if (n == max_size)
		return false;//���������ܲ���
	edge_value[n].key = item.key;
	edge_value[n].tail = item.tail;
	edge_value[n].head = item.head;
	n++;
	return true;
}

template<class T, class E>
void MST<T, E>::enlarge(int size) {
	MST_edge_node<T, E>* e;
	if (!(size > max_size))
		return;
	e = new MST_edge_node<T, E>[size];
	for (int i = 0; i < n; i++) {
		e[i] = edge_value[i];//ÿ���߸�ֵ��ȥ
	}
	max_size = size;
	delete[]edge_value;
	edge_value = e;
}

template<class T, class E>
bool MST<T, E>::empty() {
	return (edge_value == NULL) ? true : false;
}
#endif