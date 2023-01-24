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

//检测是否为升序
int IsAscenOrder(int* arr, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("开始下标为%d", i);
			return 0;
		}
	}
	printf("排序无误\n");
	return 1;
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

//三数找中
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

//快排->挖坑法：
int QuickSortPart1(int* arr, int left, int right)
{
	int begin = left, end = right, key, pivot;

	//优化1.三数找中 
	//当普通快排 排有序数列(升序、降序)时 时间复杂度为：O(N^2)
	//因此采用三数找中解决 key 为最值时 时间复杂度太高
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

//快排->左右指针法：
int QuickSortPart2(int* arr, int left, int right)
{
	int begin = left, end = right, keyi;

	//优化1.三数找中 
	//当普通快排 排有序数列(升序、降序)时 时间复杂度为：O(N^2)
	//因此采用三数找中解决 key 为最值时 时间复杂度太高
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

//快排->前后指针法：
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

//快排 时间复杂度：O(N*logN)
void QuickSort(int* arr, int left,int right)
{
	//待排序数组元素个数不超过1个时无需再排序了
	if (left>right)
		return;

	//1.将数组分为三部分：左边的数都小于key--key--右边的数都大于key
	int index=QuickSortPart3(arr,left,right);

	//2.此时key在数组正确的位置只需使左右两部分有序即可-->分治
	
	// 优化2.小规模优化
	//小规模优化-->当数组元素很多时 使用小规模优化 可减少递归开销
	if (index - left > 10)
		QuickSort(arr, left, index - 1);
	else 
		InsertSort(arr+left,index-left);
	if (right - index > 10)
		QuickSort(arr, index + 1, right);
	else
		InsertSort(arr+index+1, right - index);
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

void MergeSort(int* arr, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(arr, 0, n - 1, tmp);
	free(tmp);
	
}

void MergeSortTest()
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

	MergeSort(arr, n);
	PrintArry(arr, n);
	IsAscenOrder(arr, n);

	MergeSort(arr1, n);
	PrintArry(arr1, n);
	IsAscenOrder(arr1, n);

	MergeSort(arr2, n);
	PrintArry(arr2, n);
	IsAscenOrder(arr2, n);

	MergeSort(arr3, n);
	PrintArry(arr3, n);
	IsAscenOrder(arr3, n);

	free(arr);
	free(arr1);
	free(arr2);
	free(arr3);
}

void QuickSortTest()
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

	QuickSort(arr, 0,n-1);
	PrintArry(arr, n);
	IsAscenOrder(arr, n);

	QuickSort(arr1, 0, n - 1);
	PrintArry(arr1, n);
	IsAscenOrder(arr1, n);

	QuickSort(arr2, 0, n - 1);
	PrintArry(arr2, n);
	IsAscenOrder(arr2, n);

	QuickSort(arr3, 0, n - 1);
	PrintArry(arr3, n);
	IsAscenOrder(arr3, n);

	free(arr);
	free(arr1);
	free(arr2);
	free(arr3);
}

void TimeTest()
{
	unsigned long i,max;
	max = 1000000;
	int* arr1 =(int*)malloc(max * sizeof(int));
	int* arr2 = (int*)malloc(max * sizeof(int));
	int* arr3 = (int*)malloc(max * sizeof(int));
	int* arr4 = (int*)malloc(max * sizeof(int));
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

	//begin = clock();
	//InsertSort(arr4, max);
	//finish = clock();
	//printf("InsertSort: %d\n", finish - begin);

	
	free(arr1);
	free(arr2);
	free(arr3);
	//free(arr4);
	//free(arr5);
}

int main()
{
	srand((unsigned int)time(NULL));
	//TimeTest();

	//ShellSortTest();
	QuickSortTest();
	//MergeSortTest();
	return 0;
}