#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include<stdio.h>

#define maxsize 100
#define elemtype int
typedef struct {
	elemtype data[maxsize];
	int front, rear;
}sqq;

void initq(sqq*& q)
{
	q = (sqq*)malloc(sizeof(sqq));
	q->front = q->rear = 0;
}

void destroyq(sqq*& q)
{
	free(q);
}

bool qempty(sqq* q)
{
	return(q->front == q->rear);
}

bool enq(sqq*& q,elemtype &e)
{
	if ((q->rear + 1) % maxsize == q->front)
		return false;
	q->rear = (q->rear + 1) % maxsize;
	q->data[q->rear] = e;
	return true;
}

bool deq(sqq*& q, elemtype& e)
{
	if (q->front == q->rear)
		return false;
	q->front = (q->front + 1) % maxsize;
	e = q->data[q->front];
	return true;
}

int main(void)
{
	 sqq* q; initq(q); elemtype e;int num = 0;
	printf("\n  请选择需要执行的操作：\n  1.入队列  2.出队列  3.判断队列是否为空  （输入q退出）\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  请输入入队元素："); scanf("%d", &e); if (enq(q, e))  printf("\n  入队列成功\n");
			  else printf("\n  队满，无法入队列\n"); break;
		case 2: if (deq(q, e))  printf("\n  元素%d已出队列\n", e); else printf("\n  队空，无元素出队列\n"); break;
		case 3:if (qempty(q))  printf("\n  队列为空\n"); else printf("\n  队列非空\n"); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  请选择需要执行的操作：\n  1.入队列  2.出队列  3.判断队列是否为空  （输入q退出）\n");
	}
	return 0;
}
































