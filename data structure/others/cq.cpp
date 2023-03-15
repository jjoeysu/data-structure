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
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.�����  2.������  3.�ж϶����Ƿ�Ϊ��  ������q�˳���\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  ���������Ԫ�أ�"); scanf("%d", &e); if (enq(q, e))  printf("\n  ����гɹ�\n");
			  else printf("\n  �������޷������\n"); break;
		case 2: if (deq(q, e))  printf("\n  Ԫ��%d�ѳ�����\n", e); else printf("\n  �ӿգ���Ԫ�س�����\n"); break;
		case 3:if (qempty(q))  printf("\n  ����Ϊ��\n"); else printf("\n  ���зǿ�\n"); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.�����  2.������  3.�ж϶����Ƿ�Ϊ��  ������q�˳���\n");
	}
	return 0;
}
































