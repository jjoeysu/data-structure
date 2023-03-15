#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>

//堆排序
void swap(int* a, int* b)
{
	int c = *b;
	*b = *a;
	*a = c;
}

void heaping(int a[], int start, int end)
{
	int father = start;
	int lchild = 2 * father + 1;
	while (lchild <= end)
	{
		if (lchild + 1 <= end && a[lchild] < a[lchild + 1])
			lchild++;
		if (a[father] > a[lchild])
			return;
		else
		{
			swap(&a[father], &a[lchild]);
			father = lchild;
			lchild = 2 * father + 1;
		}
	}
}

void heapsort(int a[], int len)
{
	int i;
	for (i = len / 2 - 1; i >= 0; i--)
		heaping(a, i, len - 1);
	for (i = len - 1; i > 0; i--)
	{
		swap(&a[0], &a[i]);
		heaping(a, 0, i - 1);
	}
}

int main(void)
{
	int a[] = { 3,5,9,6,2,7 }; int len = 6;
	printf("原始序列为\n");
	for (int i = 0; i < len; i++)
		printf(" %d ", a[i]);
	heapsort(a, len);
	printf("\n堆排序后为\n");
	for (int i = 0; i < len; i++)
		printf(" %d ", a[i]);
	return 0;
}



