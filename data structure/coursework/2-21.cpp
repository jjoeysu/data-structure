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

void createbtree(btnode*& b, char* str)
{
	btnode* st[maxsize], * p; p = NULL;
	int top = -1, k, j = 1;
	char ch;
	b = NULL;
	ch = str[j];
	while (ch != '\0')
	{
		switch (ch) {
		case'(':top++; st[top] = p; k = 1; break;
		case')':top--; break;
		case',':k = 2; break;
		default:p = (btnode*)malloc(sizeof(btnode));
			p->data = ch;
			p->lchild = p->rchild = p->parent = NULL;
			if (b == NULL)
				b = p;
			else {
				switch (k) {
				case 1:st[top]->lchild = p; st[top]->lchild->parent = st[top]; break;
				case 2:st[top]->rchild = p; st[top]->rchild->parent = st[top]; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}

void destroybtree(btnode*& b)
{
	if (b != NULL)
	{
		destroybtree(b->lchild);
		destroybtree(b->rchild);
		free(b);
	}
}

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


int btheight(btnode* b)
{
	int lchildh, rchildh;
	if (b == NULL) return 0;
	else
	{
		lchildh = btheight(b->lchild);
		rchildh = btheight(b->rchild);
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}

int btsize(btnode* b)
{
	if (b == NULL) return(0);
	else return btsize(b->lchild) + btsize(b->rchild) + 1;
}


void dispbtree(btnode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			dispbtree(b->lchild);
			if (b->rchild != NULL) printf(",");
			dispbtree(b->rchild);
			printf(")");
		}
	}
}

void preorder(btnode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		preorder(b->lchild);
		preorder(b->rchild);
	}
}

void inorder(btnode* b)
{
	if (b != NULL)
	{
		inorder(b->lchild);
		printf("%c", b->data);
		inorder(b->rchild);
	}
}

void postorder(btnode* b)
{
	if (b != NULL)
	{
		postorder(b->lchild);
		postorder(b->rchild);
		printf("%c", b->data);
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

class growstack
{
public:
#define stackdatatype int
	typedef struct {
		stackdatatype data[maxsize];
		int top1, top2;
	}dstack;

	void initstack(dstack*& s)
	{
		s = (dstack*)malloc(sizeof(dstack));
		s->top1 = -1;
		s->top2 = maxsize;
	}

	void destroy(dstack*& s)
	{
		free(s);
	}

	bool stackempty(dstack* s, int i)
	{
		if (i == 1)
			return(s->top1 == -1);
		else return(s->top2 == maxsize);
	}

	bool push(dstack*& s, stackdatatype& e, int i)
	{
		if (s->top1 == s->top2 - 1)
			return false;
		if (i == 1) {
			s->top1++;
			s->data[s->top1] = e;
		}
		else {
			s->top2--;
			s->data[s->top2] = e;
		}

		return true;
	}

	bool pop(dstack*& s, stackdatatype& e, int i)
	{
		if (s->top1 == s->top2 - 1)
			return false;
		if (i == 1) {
			e = s->data[s->top1];
			s->top1--;
		}
		else {
			e = s->data[s->top2];
			s->top2++;
		}
		return true;
	}

	bool gettop(dstack*& s, stackdatatype& e, int i)
	{
		if ((i == 1 && s->top1 == -1) || (i == 2 && s->top2 == maxsize))
			return false;
		if (i == 1)
			e = s->data[s->top1];
		else e = s->data[s->top2];
		return true;
	}
};


elemtype comancestor1(btnode* b, int i, int j)
{
	growstack s; growstack::dstack* stack; s.initstack(stack); int  x, y, u, v; btnode* p; p = b;
	if (i == 1 || j == 1)
		return b->data;
	else {
		while (i != 0) {
			s.push(stack, i , 1);
			i = i / 2;
		}
		while (j != 0) {
			s.push(stack, j, 2);
			j = j / 2;
		}
		do {
			s.pop(stack, x, 1); s.pop(stack, y, 2);
			if (x == y) u = x;
		} while (x == y);
		s.destroy(stack); s.initstack(stack); 
		int k = 0;
		while (u != 0) {
			k = u % 2;
			s.push(stack, k, 1);
			u = u / 2;
		}
		s.pop(stack, k, 1);
		if (s.stackempty(stack, 1) == true) return p->data;
		else {
			while (s.stackempty(stack, 1) == false) {
				s.pop(stack, k, 1);
				if (k == 0) p = p->lchild;
				else p = p->rchild;
			}
			return p->data;
		}
	}
}



int main(void) {
	btnode* b;	char g[8] = {'a','b','c','d','e','f','g'}; char* str = g; int i, j; elemtype k;
	createbt(b, str);
	printf("二叉树先序遍历为："); preorder(b);
	printf("\n寻找下标为4和6的结点的最近共同祖先结点\n");
	k = comancestor1(b, 4, 6);
	printf("这两个结点最近的共同祖先结点的值为：%c",k);
	return 0;

}