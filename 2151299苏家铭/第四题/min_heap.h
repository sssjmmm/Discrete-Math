/*小根堆，根结点编号为0*/
#ifndef _SJM_MINHEAP_
#define _SJM_MINHEAP_

#define Default_size 20
template <class T>
class minHeap {
private:
	T* pheap;//存放小根堆中元素的数组
	int current_size;//小根堆中当前元素个数
	int minHeap_size;//小根堆最多允许元素个数
	void down_sift(int start, int m);//自上向下调整
	void up_sift(int start);//自下向上调整
public:
	minHeap(int size = Default_size);//构造函数：建立空堆
	minHeap(T arr[], int size);//构造函数：通过一个数组建堆
	~minHeap() {
		delete[]pheap;
	}
	bool insert(const T& x);//将x插入到小根堆中
	bool remove_min(T& x);//删除小根堆上的最小元素
	bool empty()const {//判断堆是否为空
		return (current_size == 0) ? true : false;
	}
};

template<class T>
minHeap<T>::minHeap(int size) {//构造函数
	this->current_size = 0;
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];//创建存储空间
	if (pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
}

template<class T>
minHeap<T>::minHeap(T arr[], int size) {//构造函数
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];
	if (pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		pheap[i] = arr[i];
	current_size = size;//建立当前大小
	int currentPos = (current_size - 2) / 2;//找到最初调整位置：末结点的父结点
	while (currentPos >= 0) {//自底向上
		down_sift(currentPos, current_size - 1);
		currentPos--;
	}
}

template<class T>
void minHeap<T>::down_sift(int start, int m) {
	//从结点strat开始到m位置，自上向下比较
	int i = start, j = 2 * i + 1;//j是i的左子女
	T temp = pheap[i];
	while (j <= m) {
		if (j < m && pheap[j] >pheap[j + 1])//让j指向两子女中的小者
			j++;
		if (temp <= pheap[j])//temp小则不调整
			break;
		else {//小则上移。i、j下降
			pheap[i] = pheap[j];
			i = j;
			j = 2 * j + 1;
		}
	}//end of while
	pheap[i] = temp;
}

template<class T>
void minHeap<T>::up_sift(int start) {
	//从结点start开始到结点0，自下而上比较
	int j = start, i = (j - 1) / 2;
	T temp = pheap[j];
	while (j > 0) {//沿父结点路径向上直达根节点
		if (pheap[i] <= temp)//父结点值小，不调整
			break;
		else {//父结点小，调整
			pheap[j] = pheap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	pheap[j] = temp;
}

template<class T>
bool minHeap<T>::insert(const T& x) {
	//将x插入到小根堆中
	if (current_size == minHeap_size) {//堆满
		cerr << "Heap Full!" << endl;
		return false;
	}
	pheap[current_size] = x;//插入
	up_sift(current_size);//向上调整
	current_size++;//堆计数++
	return true;
}

template<class T>
bool minHeap<T>::remove_min(T& x) {
	if (current_size == 0) {
		cout << "Heap Full!" << endl;
		return false;
	}//堆空，最后返回false
	x = pheap[0];
	pheap[0] = pheap[current_size - 1];//最后元素填补到根结点
	current_size--;
	down_sift(0, current_size - 1);//自上向下调整堆
	return true;//返回最小元素
}



#endif


