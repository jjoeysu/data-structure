#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#define maxsize 100
typedef int elemtype;


typedef struct {
	elemtype data[maxsize];
	int length;
}vector;

//建立vector
void createlist(vector*& L, elemtype a[], int n)//由a中的n个元素建立vector
{
	int i = 0, k = 0;//k为L中元素个数，初始值为0
	L = (vector*)malloc(sizeof(vector));//分配放vector的空间
	while (i < n) //i扫描数组a的元素
	{
		L->data[k] = a[i];//将元素a[i]放到L中
		k++; i++;
	}
	L->length = k;//设置L的长度
}
//初始化vector
void initlist(vector*& L)
{
	L = (vector*)malloc(sizeof(vector));//分配放vector的空间
	L->length = 0;
}
//输出vector
void displist(vector* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}
//对元素的二分查找
int bsearch(vector*& L,elemtype e)
{
	int low=0, high=L->length-1, mid=0;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (L->data[mid] == e)
			return mid+1;
		else if (L->data[mid] < e)
			low = mid + 1;
		else high = mid - 1;
	}
}

int main(void)
{
	int num = 0, i = 0, n = 0; elemtype e;
	vector* L; initlist(L); elemtype a[maxsize];
	printf("\n  请选择需要执行的操作：\n  1.建立vector  2.对元素进行二分查找  3.输出vector  （输入q退出）\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  请输入vector元素个数："); scanf("%d", &n);
			for (i = 0; i < n; i++) {
				printf("\n  请输入第%d个元素:", i + 1);
				scanf("%d", &a[i]);
			}
			createlist(L, a, n);
			printf("\n  vector建立成功!\n"); break;
		case 2:printf("\n  输入查找元素"); scanf("%d", &e); if (bsearch(L, e)) printf("\n  该元素在第 %d 位\n", bsearch(L, e)); else printf("\n  元素不存在!\n"); break;
		case 3:printf("\n  vector元素如下：\n"); displist(L); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  请选择需要执行的操作：\n  1.建立vector  2.对元素进行二分查找  3.输出vector  （输入q退出）\n");
	}
	return 0;
}