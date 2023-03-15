#include <stdio.h>
#include <stdlib.h>
#define size 10

typedef struct node
{
	int data;
	struct node* next;
}Node;
void creatlinklist(Node* L, int n)
{
	Node* rear = L;
	for (int i = 0; i < n; i++)
	{
		Node* s = (Node*)malloc(sizeof(Node));
		s->data = i + 1;
		s->next = NULL;
		rear->next = s;
		rear = s;
	}
}
void show2(Node* L)
{
	Node* p = L;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

Node* oddeven(Node* L)
{
	Node* p = L;
	if (p == NULL || p->next == NULL || p->next->next == NULL)
		return p;
	Node* q, * temp;q = p->next;
	while (q != NULL && q->next != NULL)
	{
		temp = p->next;
		p->next = q->next;
		q->next = q->next->next;
		p = p->next;
		p->next = temp;
		q = q->next;
	}
	return L;
}


int main()
{
	Node L2 = { 0,NULL };creatlinklist(&L2, size);
	printf("原单链表为：\n");
	show2(&L2);oddeven(&L2);
	printf("重排后的新链表为：\n");
	show2(&L2);
}