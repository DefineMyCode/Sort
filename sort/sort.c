#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Stack.h"

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//��ӡ����
void PrintArray(int* arr,int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (i % 20 == 0)
			printf("\n");
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//����Ƿ�Ϊ����
int IsAscenOrder(int* arr, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("��ʼ�±�Ϊ%d", i);
			return 0;
		}
	}
	printf("��������\n");
	return 1;
}

//ֱ�Ӳ������� ʱ�临�Ӷ� O(n^2) �ȶ��ԣ��ȶ�
void InsertSort(int* arr,int n)
{
	int i;
	for (i = 0; i < n - 1; i++)
	{
		int end = i;
		int next = arr[end + 1];
		while (end >= 0)
		{
			if (arr[end] > next)
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
			{
				break;
			}
		}
		arr[end + 1] = next;
	}
}

//ϣ������ ƽ��ʱ�临�Ӷ�: O(n^1.4) �ȶ��ԣ����ȶ�
void ShellSort(int* arr, int n)
{
	int gap=n;
	while (gap > 1)//�������Ԥ��
	{
		//���뱣֤���һ��gap=1
		gap /= 2;
		//gap = gap / 3 + 1;
		int i;
		for (i = 0; i < n - gap; i++)
		{
			int end = i;
			int next = arr[end + gap];
			while (end >= 0)
			{
				if (arr[end] > next)
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			arr[end + gap] = next;
		}
	}
}
 
//ֱ��ѡ������ ʱ�临�Ӷȣ�O(n^n) ������������ �ȶ��ԣ����ȶ�
void SelectSort(int* arr, int n)
{
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		int maxi = end, mini = begin;
		for (int i = begin; i <= end; i++)
		{
			if (arr[maxi] < arr[i])
			{
				maxi = i;
			}
			if (arr[mini] > arr[i])
			{
				mini = i;
			}
		}
		Swap(&arr[begin], &arr[mini]);
		//�����ʼ��ǡ�������ֵ�Ĵ�����Ҫ�������ֵ�±�
		if (begin == maxi)
		{
			maxi = mini;
		}
		Swap(&arr[end], &arr[maxi]);
		begin++;
		end--;
	}
}

//��-->�������ʾ��ȫ��������
//leftchild = parent*2+1
//rightchild = parent*2+2
//parent = (child-1)/2 -->childΪ���Һ��Ӿ���
//���µ����㷨����һ����������������һ����ѻ�С�ѣ�ǰ�᣺root�������������Ǵ�ѻ�С��
void AdjustDown(int* arr, int n, int root)
{
	//ʱ�临�Ӷȣ�O(logN)->�߶ȴ�
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		//1.ѡ�����Һ����нϴ���Ǹ�(��ѣ�С�ѷ�֮)
		if (child + 1 < n && arr[child + 1] > arr[child])
		{
			child += 1;
		}
		//2.�������븸�ڵ�Ƚϣ����Ӵ��ڸ����򽻻�(��ѣ�С�ѷ�֮)
		if (arr[parent] < arr[child])
		{
			Swap(&arr[parent], &arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//������ ʱ�临�Ӷȣ�O(N*logN) �ȶ��ԣ����ȶ�
void HeapSort(int* arr, int n)
{
	int lastchild = n-1;
	int parent = (lastchild - 1) / 2;
	//1.����һ�����(����)
	while (parent >= 0)
	{
		AdjustDown(arr, n, parent);
		parent--;
	}
	for (int i = n - 1; i > 0; i--)
	{
		//2.����һ���������һ��������
		Swap(&arr[0],&arr[i]);
		//��ʱ���һ�����Ѿ�����󣬽�n-1��������Ū�ɴ�� �ظ�2
		AdjustDown(arr, i, 0);
	}
}

//ð������ ʱ�临�Ӷȣ�O(N^2) �ȶ��ԣ����ȶ�
void BubbleSort(int* arr, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		int Ischanged = 0;
		for (j = 1; j < n - i; j++)
		{
			if (arr[j - 1] > arr[j])
			{
				Swap(&arr[j - 1], &arr[j]);
				Ischanged = 1;
			}
		}
		if (!Ischanged)
		{
			break;
		}
	}
}

//����ȡ��
int MidIndex(int* arr, int left, int right)
{
	int mid = (left + right) >>1;
	if (arr[left] < arr[mid])
	{
		if (arr[mid] < arr[right])
			return mid;
		else if (arr[left] > arr[right])
			return left;
		else 
			return right;
	}
	else
	{
		if (arr[left] < arr[right])
			return left;
		else if (arr[right] > arr[mid])
			return right;
		else return mid;
	}
}

//����->�ڿӷ���
int QuickSortPart1(int* arr, int left, int right)
{
	int begin = left, end = right, key, pivot;

	//�Ż�1.�������� 
	//����ͨ���� ����������(���򡢽���)ʱ ʱ�临�Ӷ�Ϊ��O(N^2)
	//��˲����������н�� key Ϊ��ֵʱ ʱ�临�Ӷ�̫��
	int index = MidIndex(arr, left, right);
	Swap(&arr[begin], &arr[index]);

	key = arr[begin];
	pivot = begin;

	while (begin < end)
	{
		while (begin < end && arr[end] >= key)
		{
			end--;
		}
		arr[pivot] = arr[end];
		pivot = end;
		while (begin < end && arr[begin] <= key)
		{
			begin++;
		}
		arr[pivot] = arr[begin];
		pivot = begin;
	}
	arr[pivot] = key;
	return pivot;
}

//����->����ָ�뷨��
int QuickSortPart2(int* arr, int left, int right)
{
	int begin = left, end = right, keyi;

	//�Ż�1.�������� 
	//����ͨ���� ����������(���򡢽���)ʱ ʱ�临�Ӷ�Ϊ��O(N^2)
	//��˲����������н�� key Ϊ��ֵʱ ʱ�临�Ӷ�̫��
	int index = MidIndex(arr, left, right);
	Swap(&arr[begin], &arr[index]);

	keyi = begin;
	while (begin < end)
	{
		while (begin<end && arr[end] >= arr[keyi])
			end--;
		while (begin < end && arr[begin] <= arr[keyi])
			begin++;
		Swap(&arr[begin], &arr[end]);
	}
	Swap(&arr[keyi], &arr[begin]);
	return begin;
}

//����->ǰ��ָ�뷨��
int QuickSortPart3(int* arr, int left, int right)
{
	int index = MidIndex(arr, left, right);
	int cur = left, prev = left + 1,pivot=left;
	Swap(&arr[cur], &arr[index]);

	while (prev<=right)
	{
		if (arr[pivot] >= arr[prev] && ++cur != prev )
			Swap(&arr[cur],&arr[prev]);
		prev++;
	}
	Swap(&arr[pivot], &arr[cur]);
	return cur;
}

//���� ʱ�临�Ӷȣ�O(N*logN) �ȶ��ԣ����ȶ�
void QuickSort(int* arr, int left,int right)
{
	//����������Ԫ�ظ���������1��ʱ������������
	if (left>right)
		return;

	//1.�������Ϊ�����֣���ߵ�����С��key--key--�ұߵ���������key
	int index=QuickSortPart3(arr,left,right);

	//2.��ʱkey��������ȷ��λ��ֻ��ʹ�������������򼴿�-->����
	
	// �Ż�2.С��ģ�Ż�
	//С��ģ�Ż�-->������Ԫ�غܶ�ʱ ʹ��С��ģ�Ż� �ɼ��ٵݹ鿪��
	if (index - left > 10)
		QuickSort(arr, left, index - 1);
	else 
		InsertSort(arr+left,index-left);
	if (right - index > 10)
		QuickSort(arr, index + 1, right);
	else
		InsertSort(arr+index+1, right - index);
}

//���ŷǵݹ� �����ݽṹ�е�ջ��ģ�⺯����ջ֡
void QuickSortNonR(int *arr,int n)
{
	ST st;
	StackInit(&st);
	int left = 0, right = n - 1;
	StackPush(&st,right);
	StackPush(&st,left);

	while (!StackEmpty(&st))
	{
		left = StackTop(&st);
		StackPop(&st);
		right = StackTop(&st);
		StackPop(&st);
		
		int pivot = QuickSortPart1(arr, left, right);
		//left      pivot         right
		//ֻ���������1(Ϊ1��0ʱ�Ѿ�������)ʱ����ջ
		if (left < pivot - 1)
		{
			//����������ջ
			StackPush(&st, pivot - 1);
			StackPush(&st, left);
		}
		
		if (right > pivot + 1)
		{
			//����������ջ
			StackPush(&st, right);
			StackPush(&st, pivot + 1);
		}
	}
	
	StackDestroy(&st);
}

void _MergeSort(int*arr,int left,int right,int* tmp)
{
	if (left >= right)
		return;
	int mid = (left + right) >> 1;
	_MergeSort(arr, left, mid, tmp);
	_MergeSort(arr, mid + 1, right, tmp);

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] < arr[begin2])
			tmp[index++] = arr[begin1++];
		else
			tmp[index++] = arr[begin2++];
	}
	while (begin1 <= end1)
	{
		tmp[index++] = arr[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = arr[begin2++];
	}
	for (int i = left; i <= right; i++)
	{
		arr[i] = tmp[i];
	}
}

//�鲢���� ʱ�临�Ӷȣ�O(N*logN) �ȶ��ԣ��ȶ�
void MergeSort(int* arr, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(arr, 0, n - 1, tmp);
	free(tmp);
	
}

//�鲢���� �ǵݹ� (�鲢��˼���Ͽ��Ը�����)
void MergeSortNonR(int* arr, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
		return;
	int gap = 1;//ÿ�����ݸ���
	while (gap < n)
	{
		int i;
		for (i = 0;i < n;i += 2*gap)
		{
			//�ϲ� [i,i+gap-1] [i+gap,i+2*gap-1]
			int begin1 = i, end1 = i+gap-1;
			int begin2 = i+gap, end2 = i+2*gap-1;
			int index = i;
			//�����䲻����ʱ�������Ѿ�����
			if (begin2 >= n)
				break;
			//��������ڵ�ʵ�����ݸ����������䲻���
			if (end2 >= n)
			{
				//����������
				end2 = n-1;
			}
			
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (arr[begin1] < arr[begin2])
					tmp[index++] = arr[begin1++];
				else
					tmp[index++] = arr[begin2++];
			}
			while (begin1 <= end1)
			{
				tmp[index++] = arr[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[index++] = arr[begin2++];
			}
			for (int j = i; j <= end2; j++)
			{
				arr[j] = tmp[j];
			}
		}
		gap *= 2;
	}

	free(tmp);
}

//�������� ʱ�临�Ӷȣ�O(N+range) �ռ临�Ӷȣ�O(range)
//�����ݷ�Χ��Сʱ�ǳ�NB �����ݷ�Χ�ܴ���������Сʱ
//ʱ��Ϳռ临�Ӷȶ����ǳ�����������N^2
void CountSort(int* arr, int n)
{
	int min = arr[0], max = arr[0];
	
	//�ҳ������С��
	for (int i = 1;i < n;i++)
	{
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}

	//���ټ�������->����ͳ��ÿһ�������ֵĴ���
	int range = max - min + 1;
	int* CountArr = (int*)calloc(sizeof(int) * range, sizeof(int));
	if (CountArr == NULL)
		return;

	//ͳ��ÿһ�������ֵĴ���  ���ӳ��
	for (int i = 0;i < n;i++)
	{
		CountArr[arr[i] - min]++;
	}

	//����
	int j = 0;
	for (int i = 0;i < range;i++)
	{
		
		while (CountArr[i]--)
			arr[j++] = min + i;
	}
	free(CountArr);
}

void MergeSortNonRTest()
{
	int n = 100000;
	int* arr = (int*)malloc(n * sizeof(int));
	int* arr1 = (int*)malloc(n * sizeof(int));
	int* arr2 = (int*)malloc(n * sizeof(int));
	int* arr3 = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand();
		arr1[i] = rand();
		arr2[i] = rand();
		arr3[i] = rand();
	}

	MergeSort(arr, n);
	//PrintArray(arr, n);
	IsAscenOrder(arr, n);

	MergeSort(arr1, n);
	//PrintArray(arr1, n);
	IsAscenOrder(arr1, n);

	MergeSort(arr2, n);
	//PrintArray(arr2, n);
	IsAscenOrder(arr2, n);

	MergeSort(arr3, n);
	//PrintArray(arr3, n);
	IsAscenOrder(arr3, n);

	free(arr);
	free(arr1);
	free(arr2);
	free(arr3);
}

void QuickSortNonRTest()
{
	int n = 20;
	int* arr = (int*)malloc(n * sizeof(int));
	int* arr1 = (int*)malloc(n * sizeof(int));
	int* arr2 = (int*)malloc(n * sizeof(int));
	int* arr3 = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000;
		arr1[i] = rand() % 1000;
		arr2[i] = rand() % 1000;
		arr3[i] = rand() % 1000;
	}

	QuickSortNonR(arr, n);
	PrintArray(arr, n);
	IsAscenOrder(arr, n);

	QuickSortNonR(arr1, n);
	PrintArray(arr1, n);
	IsAscenOrder(arr1, n);

	QuickSortNonR(arr2, n);
	PrintArray(arr2, n);
	IsAscenOrder(arr2, n);

	QuickSortNonR(arr3, n);
	PrintArray(arr3, n);
	IsAscenOrder(arr3, n);

	free(arr);
	free(arr1);
	free(arr2);
	free(arr3);
	//int a[] = { 2,5,4,1,3,7,6,-1 };
	//QuickSortNonR(a, sizeof(a) / sizeof(a[0]));
	//PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void CountSortTest()
{
	int n = 20;
	int* arr = (int*)malloc(n * sizeof(int));
	int* arr1 = (int*)malloc(n * sizeof(int));
	int* arr2 = (int*)malloc(n * sizeof(int));
	int* arr3 = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000;
		arr1[i] = rand() % 1000;
		arr2[i] = rand() % 1000;
		arr3[i] = rand() % 1000;
	}

	CountSort(arr, n);
	PrintArray(arr, n);
	IsAscenOrder(arr, n);

	CountSort(arr1, n);
	PrintArray(arr1, n);
	IsAscenOrder(arr1, n);

	CountSort(arr2, n);
	PrintArray(arr2, n);
	IsAscenOrder(arr2, n);

	CountSort(arr3, n);
	PrintArray(arr3, n);
	IsAscenOrder(arr3, n);

	free(arr);
	free(arr1);
	free(arr2);
	free(arr3);
}

void TimeTest()
{
	unsigned long i,max;
	max = 10000000;
	int* arr1 =(int*)malloc(max * sizeof(int));
	int* arr2 = (int*)malloc(max * sizeof(int));
	int* arr3 = (int*)malloc(max * sizeof(int));
	int* arr4 = (int*)malloc(max * sizeof(int));
	int* arr5 = (int*)malloc(max * sizeof(int));
	int* arr6 = (int*)malloc(max * sizeof(int));
	for (i = 0;i < max; i++)
	{
		arr1[i] = rand();
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
		arr4[i] = arr1[i];
		arr5[i] = arr1[i];
		arr6[i] = arr1[i];
	}

	clock_t begin,finish;

	begin = clock();
	CountSort(arr1, max);
	finish = clock();
	printf("CountSort: %d\n", finish - begin);

	begin = clock();
	QuickSort(arr2, 0, max - 1);
	finish = clock();
	printf("QuickSort: %d\n", finish - begin);

	begin = clock();
	QuickSortNonR(arr3, max);
	finish = clock();
	printf("QuickSortNonR: %d\n", finish - begin);

	begin = clock();
	ShellSort(arr4, max);
	finish = clock();
	printf("ShellSort: %d\n", finish - begin);

	begin = clock();
	MergeSort(arr5, max);
	finish = clock();
	printf("MergeSort: %d\n", finish - begin);

	begin = clock();
	MergeSortNonR(arr6, max);
	finish = clock();
	printf("MergeSortNonR: %d\n", finish - begin);

	
	free(arr1);
	free(arr2);
	free(arr3);
	free(arr4);
	free(arr5);
	free(arr6);
}

int main()
{
	srand((unsigned int)time(NULL));
	TimeTest();

	//CountSortTest();
	//QuickSortNonRTest();
	//MergeSortNonRTest();
	return 0;
}