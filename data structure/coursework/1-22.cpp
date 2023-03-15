#include<stdio.h> 
#include<malloc.h> 
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 20

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
		printf("输入错误");
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

void twoSum(vector* L, int target)
{
	int res[2];
	int i = 0;
	int r = L->length - 1;
	while (i < r)
	{
		if (L->p_list[i] + L->p_list[r] == target)
		{
			res[0] = i + 1;
			res[1] = r + 1;
			break;
		}
		else if (L->p_list[i] + L->p_list[r] < target)
		{
			i++;
		}
		else
		{
			r--;
		}
	}
	printf("这两个数分别在数组中的第%d个和第%d个\n", res[0], res[1]);
	printf("这两个数为\n");
	int j = res[0];
	printf(" %d ", L->p_list[j - 1]);
	j = res[1];
	printf(" %d ", L->p_list[j - 1]);
}


int main()
{
	int i, n;int target;int a[2];vector arry;
	InitList(&arry, MAXSIZE);
	for (i = 1; i <= MAXSIZE; i++)
	{
		Append(&arry, i);
	}
	printf("初始数组为\n");
	ShowList(&arry);
	printf("请输入目标数值：");
	scanf_s("%d", &target);
	twoSum(&arry, target);
	return 0;
}