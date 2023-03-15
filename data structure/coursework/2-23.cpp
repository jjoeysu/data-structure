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

bool aresame(btnode* b1, btnode* b2)
{
	if (b1 == NULL && b2 == NULL) return true;
	else if (b1 == NULL || b2 == NULL || b1->data != b2->data) return false;
	else return aresame(b1->lchild, b2->lchild) && aresame(b1->rchild , b2->rchild);
}


int main(void) {
	btnode* b1, *b2 ;	char g1[8]; char* str1 = g1;	char g2[8]; char* str2 = g2;
	printf("请按层次遍历输入第一个完全二叉树（7个结点）：");
	scanf("%s", g1);	createbt(b1, str1);
	printf("请按层次遍历输入第二个完全二叉树（7个结点）：");
	scanf("%s", g2);	createbt(b2, str2);
	if (aresame(b1, b2)) printf("这两个树相等");else printf("这两个树不相等");
	return 0;

}


