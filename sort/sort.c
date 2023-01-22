#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//打印数组
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

//直接插入排序 时间复杂度 O(n^2)
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

//希尔排序 平均时间复杂度: O(n^1.4)
void ShellSort(int* arr, int n)
{
	int gap=n;
	while (gap > 1)//分组进行预排
	{
		//必须保证最后一次gap=1
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
 
//直接选择排序 时间复杂度：O(n^n) 最垃圾的排序
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
		//如果开始处恰好是最大值的处就需要修正最大值下标
		if (begin == maxi)
		{
			maxi = mini;
		}
		Swap(&arr[end], &arr[maxi]);
		begin++;
		end--;
	}
}

//堆-->用数组表示完全二叉树：
//leftchild = parent*2+1
//rightchild = parent*2+2
//parent = (child-1)/2 -->child为左右孩子均可
//向下调整算法：将一个满二叉树调整成一个大堆或小堆，前提：root的左右子树都是大堆或小堆
void AdjustDown(int* arr, int n, int root)
{
	//时间复杂度：O(logN)->高度次
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		//1.选出左右孩子中较大的那个(大堆，小堆反之)
		if (child + 1 < n && arr[child + 1] > arr[child])
		{
			child += 1;
		}
		//2.将孩子与父节点比较，孩子大于父亲则交换(大堆，小堆反之)
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

//堆排序 时间复杂度：O(N*logN)
void HeapSort(int* arr, int n)
{
	int lastchild = n-1;
	int parent = (lastchild - 1) / 2;
	//1.建立一个大堆(升序)
	while (parent >= 0)
	{
		AdjustDown(arr, n, parent);
		parent--;
	}
	for (int i = n - 1; i > 0; i--)
	{
		//2.将第一个数和最后一个数交换
		Swap(&arr[0],&arr[i]);
		//此时最大一个数已经到最后，将n-1个数重新弄成大堆 重复2
		AdjustDown(arr, i, 0);
	}
}

//冒泡排序 时间复杂度：O(N^2)
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

//快排 时间复杂度：O( )
void QuickSort(int* arr, int left,int right)
{
	//待排序数组元素个数不超过1个时无需再排序了
	if (left>right)
		return;

	int begin=left, end=right, key,hole;
	key = arr[begin];
	hole = begin;
	//1.将数组分为三部分：左边的数都小于key--key--右边的数都大于key
	while (begin < end)
	{
		while (begin<end && arr[end] >= key)
		{
			end--;
		}
		arr[hole] = arr[end];
		hole = end;
		while (begin<end && arr[begin] <= key)
		{
			begin++;
		}
		arr[hole] = arr[begin];
		hole = begin;
	}
	arr[hole] = key;

	//2.此时key在数组正确的位置只需使左右两部分有序即可-->分治
	QuickSort(arr, left, hole - 1);
	QuickSort(arr, hole + 1, right);
}

void QuickSortTest()
{
	int arr1[] = { 100,15,19,18,28,34,65,49,10,-1 };

	QuickSort(arr1, 0, sizeof(arr1) / sizeof(arr1[0])-1);
	PrintArry(arr1, sizeof(arr1) / sizeof(arr1[0]));
}

void TimeTest()
{
	unsigned long i,max;
	max = 10000000;
	int* arr1 =(int*)malloc(max * sizeof(int));
	int* arr2 = (int*)malloc(max * sizeof(int));
	int* arr3 = (int*)malloc(max * sizeof(int));
	//int* arr4 = (int*)malloc(max * sizeof(int));
	//int* arr5 = (int*)malloc(max * sizeof(int));
	for (i = 0;i < max; i++)
	{
		arr1[i] = rand();
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
		//arr4[i] = arr1[i];
		//arr5[i] = arr1[i];
	}

	clock_t begin,finish;

	begin = clock();
	HeapSort(arr1, max);
	finish = clock();
	printf("HeapSort: %d\n", finish - begin);

	begin = clock();
	QuickSort(arr3, 0, max - 1);
	finish = clock();
	printf("QuickSort: %d\n", finish - begin);

	begin = clock();
	ShellSort(arr2, max);
	finish = clock();
	printf("ShellSort: %d\n", finish - begin);

	
	free(arr1);
	free(arr2);
	free(arr3);
	//free(arr4);
	//free(arr5);
}

int main()
{
	TimeTest();

	//AdjustDownTest();
	//HeapTest();
	//SelectSortTest();
	//BubbleSortTest();
	//QuickSortTest();
	return 0;
}