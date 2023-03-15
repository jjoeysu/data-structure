#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define datasize 100

typedef struct Queue
{
	int* data;
	int front;
	int rear;
}queue;

queue* initqueue(queue* q)
{
	q->data = (int*)malloc(sizeof(int) * datasize);
	if (q->data != NULL)
		q->front = q->rear = 0;
	return q;
}

int isempty(queue* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

bool isfull(queue* q)
{
	if ((q->rear + 1) % datasize == q->front)
		return true;
	else
		return false;
}

void inqueue(queue* q, int value)
{
	if (isfull(q) != true)
	{
		q->data[q->rear] = value;
		q->rear = (q->rear + 1) % datasize; 
	}
}


int outqueue(queue* q)
{
	int value=0;
	if (isempty(q) != true)
	{

		value = q->data[q->front];
		q->data[q->front] = 0;
		q->front = (q->front + 1) % datasize;
	}
	return value;
}

void show(queue* q)
{
	if (isempty(q) != true)
	{
		int r = q->front;
		while (r != q->rear)
		{
			printf("%d  ", q->data[r]);
			r = (r + 1) % datasize;
		}
	}
	printf("\n");
}

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

void DisplayList(vector t1)
{
	int m, i, j;
	int k = 0;
	printf("\n");
	printf("请输入出列号数:\n");
	scanf_s("%d", &m);
	printf("\n出队列顺序为:\n");
	for (i = t1.length; i > 0; i--)
	{
		k = (k + m - 1) % i;
		printf("%d ", t1.p_list[k]);
		for (j = k; j < i - 1; j++)
		{
			t1.p_list[j] = t1.p_list[j + 1];
		}
		t1.length = t1.length - 1;
	}
	printf(" \n");
}


int main()
{
	int n, i, m, count, x;
	queue q;
	printf("输入队列长: ");
	scanf_s("%d", &n);
	initqueue(&q);
	for (int i = 1; i <= n; i++)
	{
		inqueue(&q, i);
	}
	show(&q);
	printf("输入出队号数:");
	scanf_s("%d", &m);
	printf("\n出队列顺序为:\n");
	count = n;
	while (count != 1)
	{
		i = 1;
		while (i != m)
		{
			q.front = (q.front + 1) % n;
			if (q.data[q.front] != 0)
			{
				i++;
			}
		}
		x = outqueue(&q);
		while (q.data[q.front] == 0)
		{
			q.front = (q.front + 1) % n;
		}
		printf(" %d ", x);
		count--;
	}
	x = outqueue(&q);
	printf(" %d \t", x);
	printf("\n");
	vector list1;
	InitList(&list1, n);
	for (i = 1; i <= n; i++)
	{
		Append(&list1, i);
	}
	ShowList(&list1);
	DisplayList(list1);
}
