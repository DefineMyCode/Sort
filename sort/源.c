#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//打印数组
void PrintArry(int* arr, unsigned long n)
{
	unsigned long i;
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

void test()
{
	int arr[] = { 3,2,1,6,5,4,9,8,7,0 };
	/*PrintArry(arr, sizeof(arr) / sizeof(arr[0]));
	printf("排序后：\n");
	InsertSort(arr, sizeof(arr) / sizeof(arr[0]));
	PrintArry(arr, sizeof(arr) / sizeof(arr[0]));*/

	PrintArry(arr, sizeof(arr) / sizeof(arr[0]));
	printf("排序后：\n");
	ShellSort(arr, sizeof(arr) / sizeof(arr[0]));
	PrintArry(arr, sizeof(arr) / sizeof(arr[0]));
}

void TimeTest()
{
	unsigned long i,max;
	max = 1000000;
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
	InsertSort(arr1, max);
	finish = clock();
	printf("InsertSort: %d\n", finish - begin);

	free(arr1);
	free(arr2);
	/*free(arr3);
	free(arr4);
	free(arr5);*/
}

int main()
{
	//test();
	TimeTest();
	return 0;
}