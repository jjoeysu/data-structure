#include<stdio.h> 
#include<malloc.h> 
#include<stdlib.h>
#include<string.h>
typedef int RedType;
#define MAXSIZE 10
typedef int Elem;

struct List
{
	Elem* p_list;
	int length;
	int capacity;
};
typedef struct List vector;

void InitList(vector* L, int capacity)
{
	if (capacity <= 0)
	{
		printf("输入错误 ");
		return;
	}
	L->length = 0;
	L->capacity = capacity;
	L->p_list = (Elem*)malloc(L->capacity * sizeof(Elem));
}
int Append(vector* L, Elem x)
{
	if (L->length == L->capacity)
		return 0;
	L->p_list[L->length] = x;
	L->length++;
	return 1;
}
void ShowList(vector* L)
{
	int i;
	for (i = 0; i < L->length; ++i)
		printf(" %d ", L->p_list[i]);
	putchar('\n');
}


void Merge(RedType R[], RedType* T, int low, int mid, int high)
{
	int i, j, k;
	i = low;
	j = mid + 1;;
	k = low;
	while (i <= mid && j <= high)
	{
		if (R[i] <= R[j])
			T[k++] = R[i++];
		else
			T[k++] = R[j++];
	}
	while (i <= mid)
		T[k++] = R[i++];
	while (j <= high)
		T[k++] = R[j++];
}

void MSort(RedType R[], RedType* T, int low, int high)
{
	int mid;
	RedType s[MAXSIZE];
	if (low == high)
		T[low] = R[low];
	else
	{
		mid = (low + high) / 2;
		MSort(R, s, low, mid);
		MSort(R, s, mid + 1, high);
		Merge(s, T, low, mid, high);
	}
}

void mergesort(vector* L)
{
	MSort(L->p_list, L->p_list, 0, L->length - 1);
}


int main()
{
	int i;vector list1;InitList(&list1, MAXSIZE);
	for (i = MAXSIZE; i > 0; i--)
	{
		Append(&list1, i);
	}
	printf("初始化向量为\n");
	ShowList(&list1);mergesort(&list1);
	printf("归并排序后为: \n");
	for (i = 0; i < list1.length; i++)
		printf(" %d ", list1.p_list[i]);
	printf("\n");
}