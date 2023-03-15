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
	L->p_list[L->length + 1] = x;
	L->length++;
	return 1;
}

void ShowList(vector* L)
{
	int i;
	for (i = 1; i <= L->length; ++i)
		printf(" %d ", L->p_list[i]);
	putchar('\n');
}

void swap(vector* L, int i, int j)
{
	int temp = L->p_list[i];
	L->p_list[i] = L->p_list[j];
	L->p_list[j] = temp;
}
int partition(vector* L, int low, int high)
{
	int pivotkey;
	pivotkey = L->p_list[low];
	while (low < high)      		
	{
		while (low < high && L->p_list[high] >= pivotkey)
			high--;
		swap(L, low, high);  

		while (low < high && L->p_list[low] <= pivotkey)
			low++;
		swap(L, low, high);

	}
	return low;
}


void sort(vector* L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = partition(L, low, high);	
		sort(L, low, pivot - 1);
		sort(L, pivot + 1, high);	
	}
}

void quickSort(vector* L)
{
	sort(L, 1, L->length);
}

int main()
{
	int i;vector list1;InitList(&list1, MAXSIZE);
	for (i = MAXSIZE; i > 0; i--)
	{
		Append(&list1, i);
	}
	printf("初始向量为\n");
	ShowList(&list1);quickSort(&list1);
	printf("快速排序后为: \n");
	for (i = 1; i <= list1.length; i++)
		printf(" %d ", list1.p_list[i]);
	printf("\n");
}