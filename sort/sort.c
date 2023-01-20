#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//��ӡ����
void PrintArry(int* arr,int n)
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

//ֱ�Ӳ������� ʱ�临�Ӷ� O(n^2)
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

//ϣ������ ƽ��ʱ�临�Ӷ�: O(n^1.4)
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
 
//ֱ��ѡ������ ʱ�临�Ӷȣ�O(n^n) ������������
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

//������ ʱ�临�Ӷȣ�O(N*logN)
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

void SelectSortTest()
{
	int arr1[] = { 100,15,19,18,28,34,65,49,10,-1 };
	SelectSort(arr1, sizeof(arr1) / sizeof(arr1[0]));
	PrintArry(arr1, sizeof(arr1) / sizeof(arr1[0]));
}

void HeapTest()
{
	int arr1[] = { 27,15,19,18,28,34,65,49,25,37 };

	HeapSort(arr1, sizeof(arr1) / sizeof(arr1[0]));
	PrintArry(arr1, sizeof(arr1) / sizeof(arr1[0]));
}

void AdjustDownTest()
{
	int arr1[] = { 27,15,19,18,28,34,65,49,25,37 };
	
	AdjustDown(arr1, sizeof(arr1)/sizeof(arr1[0]), 0);
	PrintArry(arr1, sizeof(arr1) / sizeof(arr1[0]));
}

void TimeTest()
{
	unsigned long i,max;
	max = 10000000;
	int* arr1 =(int*)malloc(max * sizeof(int));
	int* arr2 = (int*)malloc(max * sizeof(int));
	//int* arr3 = (int*)malloc(max * sizeof(int));
	//int* arr4 = (int*)malloc(max * sizeof(int));
	//int* arr5 = (int*)malloc(max * sizeof(int));
	for (i = 0;i < max; i++)
	{
		arr1[i] = rand();
		arr2[i] = arr1[i];
		//arr3[i] = arr1[i];
		//arr4[i] = arr1[i];
		//arr5[i] = arr1[i];
	}

	clock_t begin,finish;

	begin = clock();
	ShellSort(arr2, max);
	finish = clock();
	printf("ShellSort: %d\n", finish - begin);

	begin = clock();
	HeapSort(arr1, max);
	finish = clock();
	printf("HeapSort: %d\n", finish - begin);

	/*begin = clock();
	InsertSort(arr1, max);
	finish = clock();
	printf("InsertSort: %d\n", finish - begin);*/

	free(arr1);
	free(arr2);
	/*free(arr3);
	free(arr4);
	free(arr5);*/
}

int main()
{
	//AdjustDownTest();
	//TimeTest();
	//HeapTest();
	SelectSortTest();
	return 0;
}