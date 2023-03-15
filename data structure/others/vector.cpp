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
void createlist(vector* &L, elemtype a[], int n)//由a中的n个元素建立vector
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
void initlist(vector* &L)
{
	L = (vector*)malloc(sizeof(vector));//分配放vector的空间
	L->length = 0;
}
//销毁vector
void destroylist(vector* &L)
{
	free(L);
}
//判断vector是否为空
bool listempty(vector* L)
{
	return(L->length == 0);
}
//求vector的长度
int listlength(vector* L)
{
	return(L->length);
}
//输出vector
void displist(vector* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}
//求vector中某个数据元素值
bool getelem(vector* L, int i, elemtype&e)
{
	if (i<1 || i>L->length)
		return 0;//参数i错误时返回0
	e = L->data[i - 1];//取元素值
	return true;//成功找到元素时返回元素值
}
//按元素值查找
int locateelem(vector* L, elemtype e)
{
	int i = 0;
	while (i < L->length&& L->data[i] != e) i++;//查找元素e
	if (i >= L->length) return 0;//未找到返回0
	else return i + 1;//找到返回其逻辑序号
}
//插入数据元素
bool listinsert(vector* &L, int i, elemtype e)
{
	int j;
	if (i<1 || i>L->length + 1 || L->length == maxsize)
		return false;
	i--;
	for (j = L->length; j > i; j--)
		L->data[j] = L->data[j - 1];
	L->data[j] = e;
	L->length++;
	return true;
}
//删除数据元素
bool listdelete(vector* &L, int i, elemtype&e)
{
	int j;
	if (i<1 || i>L->length)
		return false;
	i--;
	e = L->data[i];
	for (j = i; j < L->length - 1; j++)
		L->data[j] = L->data[j + 1];
	L->length--;
	return true;
}

int main(void)
{
	int num = 0, i = 0, n = 0; elemtype e;
	vector* L; initlist(L); elemtype a[maxsize];
	printf("\n  请选择需要执行的操作：\n  1.建立vector  2.销毁vector  3.查找数据元素值  4.查找元素位置  5.删除数据元素\n\
  6.插入数据元素  7.返回vector当前的长度  8.判断vector是否为空  9.按顺序输出vector\n  （输入q退出）\n");
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
		case 3:printf("\n  请输入查找元素的序号："); scanf("%d", &i); getelem(L, i, e);
			if (e) printf("\n  第 %d 个元素为  %d \n", i, e); else printf("\n  序号输入错误！\n"); break;
		case 4:printf("\n  请输入查找的元素值："); scanf("%d", &e);
			if (locateelem(L, e)) printf("\n  %d 是表中第 %d 个元素\n", e, locateelem(L, e));
			else printf("\n  未找到元素\n"); break;
		case 5:printf("\n  请输入删除元素的序号："); scanf("%d", &i);
			if (listdelete(L, i, e)) printf("\n  元素删除成功\n"); else printf("\n序号输入错误！\n"); break;
		case 6:printf("\n  请输入元素插入序号："); scanf("%d", &i); printf("\n  请输入元素值："); scanf("%d", &e);
			if (listinsert(L, i, e)) printf("\n  元素插入成功\n"); else printf("\n  序号输入错误！\n"); break;
		case 7:printf("\n  vector长度为：%d\n",listlength(L)); break;
		case 8:if(listempty(L)) printf("\n  vector为空\n"); else printf("\n  vector非空\n"); break;
		case 9:printf("\n  vector元素如下：\n"); displist(L); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  请选择需要执行的操作：\n  1.建立vector  2.销毁vector  3.查找数据元素值  4.查找元素位置  5.删除数据元素\n\
  6.插入数据元素  7.返回vector当前的长度  8.判断vector是否为空  9.按顺序输出vector\n  （输入q退出）\n");
	}
	return 0;
}