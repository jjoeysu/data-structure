#include<stdio.h> 
#include<malloc.h> 
#include<stdlib.h>
#include<string.h>
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

void Showarry(vector* L, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf(" %d ", L->p_list[i]);
	putchar('\n');
}

int deletarry(vector* L)
{
	if (L->length <= 2)
		return L->length;
	int index = 2;
	for (int i = 2; i < L->length; i++)
	{
		if (L->p_list[i] != L->p_list[index - 2])
			L->p_list[index++] = L->p_list[i];
	}
	return index;
}

int main()
{
	int i, n;
	vector arry;
	InitList(&arry, MAXSIZE);
	for (i = MAXSIZE; i > 0; i--)
	{
		printf("请依次输入10个数组元素：");
		scanf_s("%d", &n);
		Append(&arry, n);
	}
	printf("原数组为\n");
	ShowList(&arry);
	int newlength = deletarry(&arry);
	printf("删除后数组长度为%d\n", newlength);
	printf("删除后的数组为：\n");
	Showarry(&arry, newlength);
	return 0;
}