#pragma once
#include<stdio.h>
#include <malloc.h>
class btnodeclass
{
public:

#define elemtype char
	typedef struct node
	{
		elemtype data;
		struct node* lchild;
		struct node* rchild;
		struct node* parent;
	}btnode;

	int height(btnode* b)
	{
		int lchildh, rchildh;
		if (b == NULL) return 0;
		else
		{
			lchildh = height(b->lchild);
			rchildh = height(b->rchild);
			return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
		}
	}

	int size(btnode* b)
	{
		if (b == NULL) return(0);
		else return size(b->lchild) + size(b->rchild) + 1;
	}
};
