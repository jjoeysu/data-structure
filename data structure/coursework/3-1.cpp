#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include<time.h>
#define maxsize 8
#define elemtype int
enum tcolor { red, black };
typedef struct node
{
	elemtype data;
	struct node* lchild;
	struct node* rchild;
	struct node* parent;
	tcolor color;
}rbtnode;
/*����*/
void leftrotate(rbtnode*& b, rbtnode* x)
{
	rbtnode* y = x->rchild;x->rchild = y->lchild;
	if (y->lchild != NULL)
		y->lchild->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL){
		b = y;  
	}
	else{
		if (x->parent->lchild == x)
			x->parent->lchild = y; 
		else
			x->parent->rchild = y; 
	}
	y->lchild = x;x->parent = y;
}
/*����*/
void rightrotate(rbtnode*& b, rbtnode* y)
{
	
	rbtnode* x = y->lchild;y->lchild = x->rchild;
	if (x->rchild != NULL)
		x->rchild->parent = y;
	x->parent = y->parent;
	if (y->parent == NULL)
		b = x; 
	else{
		if (y == y->parent->rchild)
			y->parent->rchild = x;
		else
			y->parent->lchild = x;
	}
	x->rchild = y;y->parent = x;
}
/*��������*/
void insertfix(rbtnode*& b, rbtnode* newnode)
{
	rbtnode* f, * gf;
	while (newnode->parent != NULL && newnode->parent->color == red)
	{
		f = newnode->parent; gf = f->parent;
		if (f == gf->lchild){
				rbtnode* uncle = gf->rchild;
				if (uncle != NULL && uncle->color == red){
					uncle->color = black;f->color = black;
					gf->color = red;newnode = gf;continue;
			}
			if (newnode == f->rchild){
				rbtnode* temp;leftrotate(b, f);
				temp = f;f = newnode;newnode = temp;
			}
			if (newnode == f->lchild){
				f->color = black;gf->color = red;rightrotate(b, gf);
			}
		}
		else{
			  rbtnode* uncle = gf->lchild;
			    if (uncle != NULL && uncle->color == red){
					uncle->color = black;f->color = black;
					gf->color = red;newnode = gf;continue;
				}
			if (newnode == f->lchild){
				rbtnode* temp;rightrotate(b, f);
				temp = f;f = newnode;newnode = temp;
			}
			if (newnode == f->rchild){
				f->color = black;gf->color = red;leftrotate(b, gf);
			}
		}
	}
	b->color = black;
}
/*����*/
bool insert(rbtnode*& b, rbtnode* newnode)
{
	rbtnode* y = NULL;rbtnode* x = b;
	while (x != NULL)
	{
		y = x;
		if (x->data > newnode->data)
			x = x->lchild;
		else if (x->data < newnode->data)
			x = x->rchild;
		else if (x->data == newnode->data)
		{
			printf("��ֵ�Ѵ��ڣ������ظ�����\n");
			return false;
		}
	}
	newnode->parent = y;
	if (y != NULL){
		if (y->data > newnode->data)
			y->lchild = newnode;
		else
			y->rchild = newnode;
	}
	else
		b = newnode;
	newnode->color = red;insertfix(b, newnode);
	return true;
}

void destroybtree(rbtnode*& b)
{
	if (b != NULL){
		destroybtree(b->lchild);destroybtree(b->rchild);free(b);
	}
}

rbtnode* findnode(rbtnode* b, elemtype x)
{
	rbtnode* p;
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
/*������Ĳ���*/
rbtnode* findrbtree(rbtnode* b, elemtype x)
{
	rbtnode* g = b;
	while (g != NULL){
		if (g->data > x)
			g = g->lchild;
		else if (g->data < x)
			g = g->rchild;
		else
			return g;
	}
	if (g == NULL)
		return NULL;
}
/*���ĸ߶�*/
int btheight(rbtnode* b)
{
	int lchildh, rchildh;
	if (b == NULL) return 0;
	else{
		lchildh = btheight(b->lchild);rchildh = btheight(b->rchild);
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
/*���Ĵ�С*/
int btsize(rbtnode* b)
{
	if (b == NULL) return(0);
	else return btsize(b->lchild) + btsize(b->rchild) + 1;
}
/*��Сֵ*/
elemtype minrbtree(rbtnode* b)
{
	rbtnode* g = b;rbtnode* m = NULL;
	while (g != NULL){
		m = g;g = g->lchild;
	}
	return(m->data);
}
/*���ֵ*/
elemtype maxrbtree(rbtnode* b)
{
	rbtnode* g = b;rbtnode* m = NULL;
	while (g != NULL){
		m = g;g = g->rchild;
	}
	return(m->data);
}
/*ǰ�����*/
void preorder(rbtnode* b)
{
	if (b != NULL){
		printf(" %d ", b->data);
		preorder(b->lchild);
		preorder(b->rchild);
	}
}
/*�������*/
void inorder(rbtnode* b)
{
	if (b != NULL){
		inorder(b->lchild);
		printf(" %d ", b->data);
		inorder(b->rchild);
	}
}
/*�������*/
void postorder(rbtnode* b)
{
	if (b != NULL){
		postorder(b->lchild);
		postorder(b->rchild);
		printf(" %d ", b->data);
	}
}
/*��������*/
void rbprint(rbtnode* b, int data, int direction)
{
	if (b != NULL){
		if (direction == 0) 
			printf(" %d (��)�Ǹ����\n", b->data);
		else
			printf(" %d(%s)�� %d ��%s����\n", b->data\
				, (b->color == red) ? "��" : "��", data, (direction == 1) ? "��" : "��");

		rbprint(b->lchild, b->data, -1);
		rbprint(b->rchild, b->data, 1);
	}
}

int main()
{
	int n=0, m = 0;
	rbtnode* set[maxsize];
	for (int i = 0; i < maxsize; i++){
		set[i] = (rbtnode*)malloc(sizeof(rbtnode));
		set[i]->data = 2 * (i + 1)+1;
		set[i]->lchild = NULL;set[i]->rchild = NULL;
		set[i]->parent = NULL;set[i]->color = black;
	}
	rbtnode* b = set[maxsize - 1];
	printf("�����ĺ�����������£�\n");
	for (int i = 0; i < maxsize - 1; i++)
	{
		if (insert(b, set[i]) == false)
			printf("����ʧ��\n");
	}
	printf("ǰ�������\n"); preorder(b);
	printf("\n���������\n"); inorder(b);
	printf("\n���������\n"); postorder(b);
	printf("\n���Ĵ�СΪ��%d\n", btsize(b));
	printf("���ĸ߶�Ϊ��%d\n", btheight(b));
	printf("��������ҽ���ֵ��");
	scanf("%d", &n);
	findrbtree(b, n);
	if (findrbtree(b, n) != NULL)
		printf("������\n");
	else
		printf("��㲻����\n");

	printf("������������ֵ��");
	scanf("%d", &m);
	rbtnode* p;
	p = (rbtnode*)malloc(sizeof(rbtnode));
	p->data = m;
	p->lchild = NULL;p->rchild = NULL;p->parent = NULL;p->color = black;
	if (insert(b, p) == false)
		printf("����ʧ��\n");
	else
		printf("����ɹ�\n");
	printf("�º����ǰ�������\n"); preorder(b);
	printf("\n���ϵ���Ϊ��%d\n", btsize(b));
	printf("�������ֵΪ��%d\n", maxrbtree(b));
	printf("������СֵΪ��%d\n", minrbtree(b));
    printf("���������£�\n");
	if (b != NULL)
		rbprint(b, b->data, 0);
	else
		printf("����\n");
	return 0;
}