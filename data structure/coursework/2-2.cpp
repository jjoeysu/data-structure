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
			lp->lchild = lp->rchild = NULL; lp->parent = p; cq.enq(q, lp);
			rp = (btnode*)malloc(sizeof(btnode)); rp->data = ch;
			rp->lchild = rp->rchild = NULL; rp->parent = p; cq.enq(q, rp);
			p->lchild = lp; p->rchild = rp;
		}
		i = i + 2; ch = str[i]; chp = str[i - 1];
	}
}

int main(void) {
	btnode* b;	char g[8]; char* str = g;
	printf("请输入层次遍历的完全二叉树(7个结点)：");
	scanf("%s", g);
	createbt(b, str);	printf("\n该完全二叉树前序遍历为："); preorder(b);
	createbt(b, str);	printf("\n该完全二叉树中序遍历为："); inorder(b);
	createbt(b, str);	printf("\n该完全二叉树后序遍历为："); postorder(b);
	printf("\n该完全二叉树高度为：%d", btheight(b));
	printf("\n该完全二叉树结点数为：%d", btsize(b));
}

