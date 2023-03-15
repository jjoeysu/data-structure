#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <iostream>
#include <malloc.h>
#define maxsize 100
#define elemtype char
typedef struct node
{
	elemtype data;
	struct node* lchild;
	struct node* rchild;
	struct node* parent;
}btnode;

btnode* findnode(btnode* b, elemtype x)
{
	btnode* p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
		return b;
	else {
		p = findnode(b->lchild, x);
		if (p != NULL) return p;
		else
			return findnode(b->rchild, x);
	}
}

class cq {
public:
#define cqdatatype btnode*
	typedef struct {
		cqdatatype data[maxsize];
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

	bool enq(sqq*& q, cqdatatype& e)
	{
		if ((q->rear + 1) % maxsize == q->front)
			return false;
		q->rear = (q->rear + 1) % maxsize;
		q->data[q->rear] = e;
		return true;
	}

	bool deq(sqq*& q, cqdatatype& e)
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
			lp->lchild = lp->rchild = NULL; lp->parent = p; cq.enq(q, lp);
			rp = (btnode*)malloc(sizeof(btnode)); rp->data = ch;
			rp->lchild = rp->rchild = NULL; rp->parent = p; cq.enq(q, rp);
			p->lchild = lp; p->rchild = rp;
		}
		i = i + 2; ch = str[i]; chp = str[i - 1];
	}
}

btnode* comancestor2(btnode* b, btnode* p, btnode* q )
{
	btnode* lp,* lq,* rp,* rq; int k = 0;
	if (b == p || b == q) return b;
	else {
		while (k == 0) {
			lp = findnode(b->lchild, p->data);	lq = findnode(b->lchild, q->data);
			rp = findnode(b->rchild, p->data);	rq = findnode(b->rchild, q->data);
			if (lp != NULL && lq != NULL) b = b->lchild;
			else if (lp == NULL && lq == NULL) b = b->rchild;
			else { k = 1; return b; }
		}
	}
}

int main(void) {
	btnode* b, * k,*p,*q; char g[8]; char* str = g; char i, j;
	printf("请按层次遍历输入完全二叉树（7个结点）：");
	scanf("%s", g);	
	createbt(b, str);
	printf("请输入两个结点的值以查找其最近共同祖先结点：");
	scanf(" %c %c", &i, &j); printf("%c%c", i, j);
	p=findnode(b, i); q = findnode(b, j);
	k = comancestor2(b, p, q);
	printf("这两个结点最近的共同祖先结点的值为：%c", k->data);
	return 0;

}