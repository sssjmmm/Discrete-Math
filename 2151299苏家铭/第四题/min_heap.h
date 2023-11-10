/*С���ѣ��������Ϊ0*/
#ifndef _SJM_MINHEAP_
#define _SJM_MINHEAP_

#define Default_size 20
template <class T>
class minHeap {
private:
	T* pheap;//���С������Ԫ�ص�����
	int current_size;//С�����е�ǰԪ�ظ���
	int minHeap_size;//С�����������Ԫ�ظ���
	void down_sift(int start, int m);//�������µ���
	void up_sift(int start);//�������ϵ���
public:
	minHeap(int size = Default_size);//���캯���������ն�
	minHeap(T arr[], int size);//���캯����ͨ��һ�����齨��
	~minHeap() {
		delete[]pheap;
	}
	bool insert(const T& x);//��x���뵽С������
	bool remove_min(T& x);//ɾ��С�����ϵ���СԪ��
	bool empty()const {//�ж϶��Ƿ�Ϊ��
		return (current_size == 0) ? true : false;
	}
};

template<class T>
minHeap<T>::minHeap(int size) {//���캯��
	this->current_size = 0;
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];//�����洢�ռ�
	if (pheap == NULL) {
		cerr << "С���Ѵ洢����ʧ�ܣ�" << endl;
		return;
	}
}

template<class T>
minHeap<T>::minHeap(T arr[], int size) {//���캯��
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];
	if (pheap == NULL) {
		cerr << "С���Ѵ洢����ʧ�ܣ�" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		pheap[i] = arr[i];
	current_size = size;//������ǰ��С
	int currentPos = (current_size - 2) / 2;//�ҵ��������λ�ã�ĩ���ĸ����
	while (currentPos >= 0) {//�Ե�����
		down_sift(currentPos, current_size - 1);
		currentPos--;
	}
}

template<class T>
void minHeap<T>::down_sift(int start, int m) {
	//�ӽ��strat��ʼ��mλ�ã��������±Ƚ�
	int i = start, j = 2 * i + 1;//j��i������Ů
	T temp = pheap[i];
	while (j <= m) {
		if (j < m && pheap[j] >pheap[j + 1])//��jָ������Ů�е�С��
			j++;
		if (temp <= pheap[j])//tempС�򲻵���
			break;
		else {//С�����ơ�i��j�½�
			pheap[i] = pheap[j];
			i = j;
			j = 2 * j + 1;
		}
	}//end of while
	pheap[i] = temp;
}

template<class T>
void minHeap<T>::up_sift(int start) {
	//�ӽ��start��ʼ�����0�����¶��ϱȽ�
	int j = start, i = (j - 1) / 2;
	T temp = pheap[j];
	while (j > 0) {//�ظ����·������ֱ����ڵ�
		if (pheap[i] <= temp)//�����ֵС��������
			break;
		else {//�����С������
			pheap[j] = pheap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	pheap[j] = temp;
}

template<class T>
bool minHeap<T>::insert(const T& x) {
	//��x���뵽С������
	if (current_size == minHeap_size) {//����
		cerr << "Heap Full!" << endl;
		return false;
	}
	pheap[current_size] = x;//����
	up_sift(current_size);//���ϵ���
	current_size++;//�Ѽ���++
	return true;
}

template<class T>
bool minHeap<T>::remove_min(T& x) {
	if (current_size == 0) {
		cout << "Heap Full!" << endl;
		return false;
	}//�ѿգ���󷵻�false
	x = pheap[0];
	pheap[0] = pheap[current_size - 1];//���Ԫ����������
	current_size--;
	down_sift(0, current_size - 1);//�������µ�����
	return true;//������СԪ��
}



#endif


