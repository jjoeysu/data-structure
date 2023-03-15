#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<math.h>
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
//销毁vector
void destroylist(vector*& L)
{
	free(L);
}
//输出vector
void displist(vector* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}
//对vector的梳排序
void cbsort(vector*& L)
{
	int i = L->length, j = 0, k = i; elemtype a;
	while (k > 0)
	{
		k = floor(k / 1.3);
		for (j = 0; j+k < i; j=j+1)
			if (L->data[j+k] < L->data[j])
			{
				a = L->data[j+k];
				L->data[j+k] = L->data[j];
				L->data[j] = a;
			}
	}
}

int main(void)
{
	int num = 0, i = 0, n = 0;
	vector* L; initlist(L); elemtype a[maxsize];
	printf("\n  请选择需要执行的操作：\n  1.建立vector\n  2.销毁vector\n  3.对vector进行梳排序\n  4.输出vector\n  （输入q退出）\n");
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
		case 2:destroylist(L); printf("\n  vector删除成功！\n"); break;
		case 3:cbsort(L); printf("\n  梳排序完成！\n"); break;
		case 4:printf("\n  vector元素如下：\n"); displist(L); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  请选择需要执行的操作：\n  1.建立vector\n  2.销毁vector\n  3.对vector进行梳排序\n  4.输出vector\n  （输入q退出）\n");
	}
	return 0;
}