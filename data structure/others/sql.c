#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<malloc.h>
#define maxsize 100
typedef int ElemType;
typedef struct {
	ElemType data[maxsize];
	int length;
}sqlist;

//建立顺序表
sqlist* creatlist(sqlist *Lp, ElemType a[], int n)//由a中的n个元素建立顺序表
{
	int i = 0, k = 0;//k为L中元素个数，初始值为0
	Lp = (sqlist*)malloc(sizeof(sqlist));//分配放线性表的空间
	while (i < n) //i扫描数组a的元素
	{
		Lp->data[k] = a[i];//将元素a[i]放到L中
		k++; i++;
	}
		Lp->length = k;//设置L的长度
		printf("%d", Lp->length);
		return Lp;
}
//初始化线性表
void initlist(sqlist *Lp)
{
	Lp = (sqlist*)malloc(sizeof(sqlist));//分配放线性表的空间
	Lp->length = 0;
}
//销毁线性表
void destroylist(sqlist* Lp)
{
	free(Lp);
}
//输出线性表
void displist(sqlist *Lp)
{
	for (int i = 0; i < Lp->length; i++)
		printf("%d ", Lp->data[i]);
	printf("\n");
}
//求线性表中某个数据元素值
ElemType* getelem(sqlist* Lp, int i, ElemType* ep)
{
	if (i<1 || i>Lp->length)
		return 0;//参数i错误时返回0
	*ep = Lp->data[i - 1];//取元素值
	return ep;//成功找到元素时返回元素值
}
//按元素值查找
int locateelem(sqlist* Lp, ElemType e)
{
	int i = 0;
	while (i < Lp->length&& Lp->data[i] != e) i++;//查找元素e
	if (i >= Lp->length) return 0;//未找到返回0
	else return i + 1;//找到返回其逻辑序号
}
//插入数据元素
bool listinsert(sqlist* Lp, int i, ElemType e)
{
	int j;
	if (i<1 || i>Lp->length + 1 || Lp->length == maxsize)
		return false;
	i--;
	for (j = Lp->length; j > i; j--)
		Lp->data[j] = Lp->data[j - 1];
	Lp->data[j]=e;
	Lp->length++;
	return true;
}
//删除数据元素
bool listdelete(sqlist *Lp, int i, ElemType* e)
{
	int j;
	if (i<1 || i>Lp->length)
		return false;
	i--;
	*e = Lp->data[i];
	for (j = i; j < Lp->length - 1; j++)
		Lp->data[j] = Lp->data[j + 1];
	Lp->length--;
	return true;
}

int main(void)
{
	int num = 0, i = 0, n = 0; ElemType e; ElemType* ep=&e;
	sqlist L; sqlist* Lp = &L; initlist(Lp); ElemType a[maxsize];
	printf("  请选择需要执行的操作：\n  1.建立顺序表\n  2.销毁线性表\n  3.查找数据元素值\n  4.查找元素位置\n  5.删除数据元素\n  6.插入数据元素\n  （输入q退出）\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  请输入顺序表元素个数："); scanf("%d", &n); 
			for (i = 0; i < n; i++) {
				printf("\n  请输入第%d个元素:", i + 1);
				scanf("%d", &a[i]);
			}
			Lp=creatlist(Lp, a, n);
			printf("\n  顺序表建立成功!\n"); break;
		case 2:destroylist(Lp); printf("\n  线性表删除成功！\n"); break;
		case 3:printf("\n  请输入查找元素的序号："); scanf("%d", &i); ep = getelem(Lp, i, ep);
			if (ep) printf("\n  第 %d 个元素为  %d \n",i, e); else printf("\n  序号输入错误！\n"); break;
		case 4:printf("\n  请输入查找的元素值："); scanf("%d", ep);
			if (locateelem(Lp, e)) printf("\n  %d 是表中第 %d 个元素\n", e, locateelem(Lp, e));
			else printf("\n  未找到元素\n"); break;
		case 5:printf("\n  请输入删除元素的序号："); scanf("%d", &i);
			if (listdelete(Lp, i, ep)) printf("\n  元素删除成功\n"); else printf("\n序号输入错误！\n"); break;
		case 6:printf("\n  请输入元素插入序号："); scanf("%d", &i); printf("\n  请输入元素值："); scanf("%d", ep);
			if (listinsert(Lp, i, e)) printf("\n  元素插入成功\n"); else printf("\n  序号输入错误！\n"); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  顺序表元素如下：\n"); displist(Lp);
		printf("\n  请选择需要执行的操作：\n  1.建立顺序表\n  2.销毁线性表\n  3.查找数据元素值\n  4.查找元素位置\n  5.删除数据元素\n  6.插入数据元素\n  （输入q退出）\n");
	}
	return 0;
}