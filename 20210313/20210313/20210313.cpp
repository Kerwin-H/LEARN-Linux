#include<iostream>

using namespace std;


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int SLDataType;

//��̬˳���
typedef struct seqList{
	SLDataType* _data;  //��̬���ٵ�����
	size_t _size;		//��ЧԪ�ظ���
	size_t _capacity;   //�ɴ�����Ԫ�ظ���


}seqList;

void initSeqList(seqList* sl){  //ע����г�ʼ��
	sl->_data = NULL;
	sl->_size = sl->_capacity = 0;
}




void seqListcheckCapacity(seqList* sl){

	assert(sl);//debug��Ч

	if (sl == NULL){
		return;
	}

	//���Ԫ�ظ�����������ͬ,������,Ҫ�����ռ�
	if (sl->_size == sl->_capacity){

		int newCapacity = sl->_capacity == 0 ? 1 : 2 * sl->_capacity;

		//����һ�������,������������,�ͷ�ԭ���ռ�
		SLDataType* tmp = (SLDataType*)malloc(sizeof(SLDataType)*newCapacity);
		memcpy(tmp, sl->_data, sizeof(SLDataType)* sl->_size);
		free(sl->_data);

		//��һ��д��  
		//sl->_data = (SLDataType*)realloc(sl->_data, sizeof(SLDataType)*newCapacity);


		//����
		sl->_data = tmp;
		sl->_capacity = newCapacity;

	}
}

//β��һ������O(1)
void seqListpushBack(seqList* sl, SLDataType val){
	//�������
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

//βɾO(1)
void seqListpopBack(seqList* sl){
	if (sl == NULL)
		return;
	if (sl->_size>0)
		sl->_size--;
}


//ͷ��  1.�ƶ�Ԫ�� O(n)
//Ч�ʵ�
void seqListpushFornt(seqList* sl, SLDataType val){

	if (sl == NULL)
		return;

	seqListcheckCapacity(sl);  //�������
	//1.����Ԫ�ص��ƶ�,�Ӻ���ǰ
	int end = sl->_size;
	while (end > 0){
		sl->_data[end] = sl->_data[end - 1];  //��������ƶ�
		--end;
	}
	//2. ͷ��
	sl->_data[0] = val;

	sl->_size++;

	//insert(sl, 0, val);

}

//ͷɾO(n)
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

//�������,ԭʼ��������ƶ�
void seqListinsert(seqList* sl, int pos, SLDataType val){
	//���
	if (sl == NULL)
		return;

	seqListcheckCapacity(sl);
	//�ƶ�Ԫ��
	int end = sl->_size;
	while (end >pos){
		sl->_data[end] = sl->_data[end - 1];
		--end;
	}
	//��������
	sl->_data[pos] = val;
	//����
	sl->_size++;

}

//ѡ��ɾ��
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
//����
int seqListfind(seqList* sl, SLDataType val){
	int i = 0;
	for (i = 0; i < sl->_size; i++){
		if (sl->_data[i] == val)
			return i;
	}
	return -1;
}


//��ȡĳһ��λ��
SLDataType seqListgetId(seqList* sl, int pos){
	if (pos >= 0 && pos < sl->_size)
		return sl->_data[pos];


}

void seqListdestroy(seqList* sl){
	if (sl){
		if (sl->_data){
			//�ͷ�
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

//==========��������
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

//���ֺ���
int partion(int* arr, int begin, int end){

	//��ȡ��׼ֵλ��
	int mid = getMid(arr, begin, end);
	//�ѻ�׼ֵ�ŵ���ʼλ��
	Swap(arr, begin, end);

	//����ѡ���׼ֵ
	int key = arr[begin];
	int start = begin;

	while (begin < end){

		//�Ӻ���ǰ��С�ڻ�׼ֵ��λ��
		while (begin < end&&arr[end] >= key)
			--end;

		//��ǰ����Ҵ��ڵ�λ��
		while (begin < end&&arr[begin] <= key)
			++begin;
		//���ú�������
		Swap(arr, begin, end);
	}
	//������׼ֵ������λ�õ�����
	Swap(arr, start, begin);
	return begin;
}

void quickSort(int* arr, int begin, int end){

	if (begin >= end)
		return;
	//div:һ�λ��ֺ��׼ֵ
	//int div = partion(arr, begin, end);
	//int div = partion2(arr, begin, end);
	int div = partion(arr, begin, end);
	//�ֱ�����������ߵĿ���
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
