#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>
#define maxsize 100
#define elemtype char
typedef struct node
{
	elemtype data;
	struct node* lchild;
	struct node* rchild;
	struct node* parent;
	int lt, rt;
}btnode;

void preorder(btnode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		preorder(b->lchild);
		preorder(b->rchild);
	}
}

class cq {
public:
#define datatype btnode*
	typedef struct {
		datatype data[maxsize];
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

	bool enq(sqq*& q, datatype& e)
	{
		if ((q->rear + 1) % maxsize == q->front)
			return false;
		q->rear = (q->rear + 1) % maxsize;
		q->data[q->rear] = e;
		return true;
	}

	bool deq(sqq*& q, datatype& e)
	{
		if (q->front == q->rear)
			return false;
		q->front = (q->front + 1) % maxsize;
		e = q->data[q->front];
		return true;
	}
};

void createbt(btnode*& b, char* str)
{
	cq cq;	btnode* p, * lp, * rp; cq::sqq* q;
	cq.initq(q);
	int i = 0;
	b = NULL;
	char ch; char chp = 1; ch = str[i];
	while (chp != '\0')
	{
		if (b == NULL) {
			b = (btnode*)malloc(sizeof(btnode)); b->data = ch;
			b->lchild = b->rchild = b->parent = NULL; cq.enq(q, b);
		}
		else {
			cq.deq(q, p); chp = str[i - 1];
			lp = (btnode*)malloc(sizeof(btnode)); lp->data = chp;
			lp->lchild = lp->rchild = NULL; if (chp == '*') p->lchild = NULL; 
			else { lp->parent = p; cq.enq(q, lp); p->lchild = lp; p->lt = 0; }
			rp = (btnode*)malloc(sizeof(btnode)); rp->data = ch;
			rp->lchild = rp->rchild = NULL; if (ch == '*') p->rchild = NULL;
			else { rp->parent = p; cq.enq(q, rp); p->rchild = rp; p->rt = 0; }
		}
		i = i + 2; ch = str[i]; chp = str[i - 1];
	}
}


void preorderthreading(btnode*&b,btnode*&prev)
{
	if (b)
	{
		if (b->lchild == NULL)
		{
			b->lt = 1;
			b->lchild = prev;
		}
		if (prev && prev->rchild == NULL)
		{
			prev->rt = 1;
			prev->rchild = b;
		}
		prev = b;
		if (!b->lt)
		preorderthreading(b->lchild, prev);
		if (!b->rt)
		preorderthreading(b->rchild, prev);
	}
}

void preordertbt(btnode* b)
{
	while (b)
	{
		while (b->lt != 1)
		{
			printf("%c", b->data);
			b = b->lchild;
		}
		printf("%c", b->data);
		b = b->rchild;
	}
}


int main(void) {
	btnode* b,*prev = NULL;	char g[8] = { 'a','b','c','d','e','f','g' }; char* str = g;
	createbt(b, str);
	printf("二叉树前序遍历为："); preorder(b); 
	preorderthreading(b, prev);
	printf("已将二叉树线索化");
	printf("\n前序输出线索化二叉树如下：\n");
	preordertbt(b);
	return 0;

}