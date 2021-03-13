#include<iostream>

using namespace std;


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int SLDataType;

//动态顺序表
typedef struct seqList{
	SLDataType* _data;  //动态开辟的数组
	size_t _size;		//有效元素个数
	size_t _capacity;   //可存放最大元素个数


}seqList;

void initSeqList(seqList* sl){  //注意进行初始化
	sl->_data = NULL;
	sl->_size = sl->_capacity = 0;
}




void seqListcheckCapacity(seqList* sl){

	assert(sl);//debug有效

	if (sl == NULL){
		return;
	}

	//如果元素个数和容量相同,则满了,要调整空间
	if (sl->_size == sl->_capacity){

		int newCapacity = sl->_capacity == 0 ? 1 : 2 * sl->_capacity;

		//开辟一个更大的,拷贝已有数据,释放原来空间
		SLDataType* tmp = (SLDataType*)malloc(sizeof(SLDataType)*newCapacity);
		memcpy(tmp, sl->_data, sizeof(SLDataType)* sl->_size);
		free(sl->_data);

		//另一种写法  
		//sl->_data = (SLDataType*)realloc(sl->_data, sizeof(SLDataType)*newCapacity);


		//更新
		sl->_data = tmp;
		sl->_capacity = newCapacity;

	}
}

//尾插一个数据O(1)
void seqListpushBack(seqList* sl, SLDataType val){
	//检查容量
	seqListcheckCapacity(sl);
	sl->_data[sl->_size] = val;
	++sl->_size;

	//insert(sl, sl->_size, val);

}

void seqListprintSeqList(seqList* sl){
	for (int i = 0; i < sl->_size; ++i){
		printf("%d ", sl->_data[i]);
	}
	printf("\n");
}

//尾删O(1)
void seqListpopBack(seqList* sl){
	if (sl == NULL)
		return;
	if (sl->_size>0)
		sl->_size--;
}


//头插  1.移动元素 O(n)
//效率低
void seqListpushFornt(seqList* sl, SLDataType val){

	if (sl == NULL)
		return;

	seqListcheckCapacity(sl);  //检查容量
	//1.进行元素的移动,从后向前
	int end = sl->_size;
	while (end > 0){
		sl->_data[end] = sl->_data[end - 1];  //依次向后移动
		--end;
	}
	//2. 头插
	sl->_data[0] = val;

	sl->_size++;

	//insert(sl, 0, val);

}

//头删O(n)
void seqListpopFront(seqList* sl){
	if (sl == NULL || sl->_size == 0)
		return;
	int start = 1;
	while (start < sl->_size){
		sl->_data[start - 1] = sl->_data[start];
		++start;
	}
	--sl->_size;

}

//随机插入,原始数据向后移动
void seqListinsert(seqList* sl, int pos, SLDataType val){
	//检查
	if (sl == NULL)
		return;

	seqListcheckCapacity(sl);
	//移动元素
	int end = sl->_size;
	while (end >pos){
		sl->_data[end] = sl->_data[end - 1];
		--end;
	}
	//插入数据
	sl->_data[pos] = val;
	//更新
	sl->_size++;

}

//选择删除
void seqListerase(seqList* sl, int pos){
	if (sl == NULL || sl->_size == 0)
		return;
	if (pos >= 0 && pos < sl->_size){
		//1.(pos,size]
		int start = pos + 1;
		while (start < sl->_size){
			sl->_data[start - 1] = sl->_data[start];
			++start;
		}
		--sl->_size;
	}
}

int seqListempty(seqList* sl){
	if (sl == NULL || sl->_size == 0)
		return 1;
	else
		return 0;
}

int seqListsize(seqList* sl){
	if (sl == NULL)
		return 0;
	else
		return sl->_size;

}
//查找
int seqListfind(seqList* sl, SLDataType val){
	int i = 0;
	for (i = 0; i < sl->_size; i++){
		if (sl->_data[i] == val)
			return i;
	}
	return -1;
}


//获取某一个位置
SLDataType seqListgetId(seqList* sl, int pos){
	if (pos >= 0 && pos < sl->_size)
		return sl->_data[pos];


}

void seqListdestroy(seqList* sl){
	if (sl){
		if (sl->_data){
			//释放
			free(sl->_data);
			sl->_data = NULL;
		}
	}
}

int seqListBack(seqList* sl){

	return sl->_data[sl->_size - 1];
}

void Swap(int* arr, int pos1, int pos2){

	int tmp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = tmp;
}

//==========快速排序
int getMid(int* arr, int begin, int end){

	int mid = begin + (end - begin) / 2;

	if (arr[begin] > arr[mid]){

		if (arr[mid] > arr[end])
			return mid;
		else if (arr[begin] > arr[end])
			return end;
		else
			return begin;
	}
	else{

		if (arr[mid] < arr[end])
			return mid;
		else if (arr[begin] < arr[end])
			return end;
		else
			return begin;
	}
}

//划分函数
int partion(int* arr, int begin, int end){

	//获取基准值位置
	int mid = getMid(arr, begin, end);
	//把基准值放到起始位置
	Swap(arr, begin, end);

	//首先选择基准值
	int key = arr[begin];
	int start = begin;

	while (begin < end){

		//从后向前找小于基准值的位置
		while (begin < end&&arr[end] >= key)
			--end;

		//从前向后找大于的位置
		while (begin < end&&arr[begin] <= key)
			++begin;
		//调用函数交换
		Swap(arr, begin, end);
	}
	//交换基准值与相遇位置的数据
	Swap(arr, start, begin);
	return begin;
}

void quickSort(int* arr, int begin, int end){

	if (begin >= end)
		return;
	//div:一次划分后基准值
	//int div = partion(arr, begin, end);
	//int div = partion2(arr, begin, end);
	int div = partion(arr, begin, end);
	//分别进行左右两边的快排
	//[begin,div-1]
	//[div+1,end]
	quickSort(arr, begin, div - 1);
	quickSort(arr, div + 1, end);
}

void printArr(int* arr, int n){

	for (int i = 0; i < n; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}






int main(){


	system("pause");
	return 0;
}
