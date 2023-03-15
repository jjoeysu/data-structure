#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>
#define maxsize 100
#define elemtype int

/*双链表结点类型声明*/
typedef struct dnode
{
	elemtype data;
	struct dnode* prior;
	struct dnode* next;
}dlinknode;

/*初始化链表*/
void initlist(dlinknode*& L)
{
	L = (dlinknode*)malloc(sizeof(dlinknode));
	L->next =L->prior= NULL;
}

/*头插法建立双链表*/
void createlistf(dlinknode*& L, elemtype a[], int n)
{
	dlinknode* s;
	L = (dlinknode*)malloc(sizeof(dlinknode));//创建头结点
	L->prior = L->next = NULL;//前后指针域置为NULL
	for (int i = 0; i < n; i++)//循环建立数据结点s
	{
		s = (dlinknode*)malloc(sizeof(dlinknode));
		s->data = a[i];//创建数据结点s
		s->next = L->next;//将s结点插入到头结点之后
		if (L->next != NULL)//若L存在数据结点，修改L->next的前驱指针
			L->next->prior = s;
		s->prior = L;
	}
}

/*尾插法建立双链表*/
void createlistr(dlinknode*& L, elemtype a[], int n)
{
	dlinknode* s, * r;
	L = (dlinknode*)malloc(sizeof(dlinknode));//创建头结点
	r = L;//r始终指向尾结点，开始时指向头结点
	for (int i = 0; i < n; i++)//循环建立数据结点
	{
		s = (dlinknode*)malloc(sizeof(dlinknode));
		s->data = a[i];//创建数据结点s
		r->next = s; s->prior = r;//将s结点插入到r结点之后
		r = s;//r指向尾结点
	}
	r->next = NULL;//尾结点的next域置为NULL
}


/*销毁链表*/
void destroylist(dlinknode*& L)
{
	dlinknode* pre = L, * p = L->next;//pre指向p的前驱结点
	while (p != NULL)//扫描链表L
	{
		free(pre);//释放pre结点
		pre = p;//pre、p同步后移一个节点
		p = pre->next;
	}
	free(pre);//循环结束时p为NULL，pre指向尾结点，释放它
}

/*判断链表是否为空表*/
bool listempty(dlinknode* L)
{
	return(L->next == NULL);
}

/*求链表的长度*/
int listlength(dlinknode* L)
{
	int n = 0;
	dlinknode* p = L;//p指向头结点,n置为0（即头结点的序号为0）
	while (p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return(n);//循环结束，p指向尾结点，其序号n为结点个数
}

/*输出链表*/
void displist(dlinknode* L)
{
	dlinknode* p = L->next;
	while (p != NULL)
	{
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

/*求链表中的某个数据元素值*/
bool getelem(dlinknode* L, int i, elemtype& e)
{
	int j = 0;
	dlinknode* p = L;//p指向头结点，j置为0（即头结点的序号为0）
	if (i <= 0)return false;//i错误返回false
	while (j < i && p != NULL)//找第i个结点p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)return false;//不存在第i个数据结点，返回false
	else//存在第i个数据结点，返回true
	{
		e = p->data;
		return true;
	}
}

/*按元素值查找*/
int locateelem(dlinknode*L, elemtype e)
{
	int i = 1;//p指向首结点，i置为1（即首结点的序号为1）
	dlinknode* p = L->next;//查找data值为e的结点，其序号为i
	while (p != NULL && p->data != e)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)return(0);//不存在值为e的结点，返回0
	else return(i);//存在值为e的结点，返回其逻辑序号i
}

/*插入结点*/
bool listinsert(dlinknode*& L, int i, elemtype e)
{
	int j = 0;
	dlinknode* p = L, * s;//p指向头结点，j设置为0
	if (i <= 0)return false;//i错误返回false
	while (j < i - 1 && p != NULL)//查找第i-1个结点
	{
		j++; p = p->next;
	}
	if (p == NULL)//未找到第i-1个结点，返回false
		return false;
	else
	{
		s = (dlinknode*)malloc(sizeof(dlinknode));
		s->data = e;//创建新结点s
		s->next = p->next;//在p结点之后插入s结点
		if (p->next != NULL)//若p结点存在后继结点，修改其前驱指针
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

/*删除结点*/
bool listdelete(dlinknode*& L, int i, elemtype& e)
{
	int j = 0;
	dlinknode* p = L, * q;//p指向头结点，j设置为0
	if (i <= 0)return false;//i错误返回false
	while (j < i - 1 && p != NULL)//查找第i-1个结点
	{
		j++; p = p->next;
	}
	if (p == NULL)//未找到第i-1个结点，返回false
		return false;
	else//找到第i-1个结点（由p指向它）
	{
		q = p->next;//q指向第i个结点
		if (q == NULL)return false;//不存在第i个结点时返回false
		e = q->data;
		p->next = q->next;//从双链表中删除结点q
		if (q->next != NULL)//若q结点存在后继结点，修改其前驱指针
			q->next->prior = p;
		free(q);//释放q结点
		return true;
	}
}

int main(void)
{
	int num = 0, i = 0, n = 0; elemtype e; elemtype c;
	dlinknode* L; initlist(L); elemtype a[maxsize];
	printf("\n  请选择需要执行的操作：\n  1.尾插法建立链表  2.销毁链表  3.按值查找结点  4.插入结点\n  5.删除结点\
  6.判断链表是否为空  7.输出链表  （输入q退出）\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  请输入结点个数："); scanf("%d", &n);
			for (i = 0; i < n; i++) {
				printf("\n  请输入第%d个结点的值:", i + 1);
				scanf("%d", &a[i]);
			}
			createlistr(L, a, n);
			printf("\n  链表建立成功!\n"); break;
		case 2:destroylist(L); printf("\n  链表删除成功！\n"); break;
		case 3:printf("\n  请输入查找的结点值："); scanf("%d", &e);
			if (locateelem(L, e)) printf("\n  值为 %d 的结点存在\n", e); else printf("\n  值为 %d 的结点不存在\n", e); break;
		case 4: printf("\n  请输入插入结点的值和其后驱结点的值："); scanf("%d %d", &e,&c);
			if (locateelem(L, c)) { listinsert(L, locateelem(L, c), e); printf("\n  结点插入成功\n"); }
			 else printf("\n  输入结点不存在！\n"); break;
		case 5:printf("\n  请输入删除结点的值："); scanf("%d", &e);
			if (locateelem(L, e)) { listdelete(L, locateelem(L, e),c); printf("\n  结点删除成功\n"); }
			else printf("\n  输入结点不存在！\n"); break;
		case 6:if (listempty(L)) printf("\n  链表为空\n"); else printf("\n  链表非空\n"); break;
		case 7:printf("\n  链表如下：\n"); displist(L); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  请选择需要执行的操作：\n  1.尾插法建立链表  2.销毁链表  3.按值查找结点  4.插入结点\n  5.删除结点\
  6.判断链表是否为空  7.输出链表  （输入q退出）\n");
	}
	return 0;
}