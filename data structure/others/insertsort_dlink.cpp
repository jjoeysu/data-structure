#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>
#define maxsize 100
#define elemtype int

/*˫��������������*/
typedef struct dnode
{
	elemtype data;
	struct dnode* prior;
	struct dnode* next;
}dlinknode;

/*��ʼ������*/
void initlist(dlinknode*& L)
{
	L = (dlinknode*)malloc(sizeof(dlinknode));
	L->next = L->prior = NULL;
}

/*β�巨����˫����*/
void createlistr(dlinknode*& L, elemtype a[], int n)
{
	dlinknode* s, * r;
	L = (dlinknode*)malloc(sizeof(dlinknode));//����ͷ���
	r = L;//rʼ��ָ��β��㣬��ʼʱָ��ͷ���
	for (int i = 0; i < n; i++)//ѭ���������ݽ��
	{
		s = (dlinknode*)malloc(sizeof(dlinknode));
		s->data = a[i];//�������ݽ��s
		r->next = s; s->prior = r;//��s�����뵽r���֮��
		r = s;//rָ��β���
	}
	r->next = NULL;//β����next����ΪNULL
}

/*��������*/
void destroylist(dlinknode*& L)
{
	dlinknode* pre = L, * p = L->next;//preָ��p��ǰ�����
	while (p != NULL)//ɨ������L
	{
		free(pre);//�ͷ�pre���
		pre = p;//pre��pͬ������һ���ڵ�
		p = pre->next;
	}
	free(pre);//ѭ������ʱpΪNULL��preָ��β��㣬�ͷ���
}

/*�������*/
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

/*ɾ�����*/
bool listdelete(dlinknode*& L, int i, elemtype& e)
{
	int j = 0;
	dlinknode* p = L, * q;//pָ��ͷ��㣬j����Ϊ0
	if (i <= 0)return false;//i���󷵻�false
	while (j < i - 1 && p != NULL)//���ҵ�i-1�����
	{
		j++; p = p->next;
	}
	if (p == NULL)//δ�ҵ���i-1����㣬����false
		return false;
	else//�ҵ���i-1����㣨��pָ������
	{
		q = p->next;//qָ���i�����
		if (q == NULL)return false;//�����ڵ�i�����ʱ����false
		e = q->data;
		p->next = q->next;//��˫������ɾ�����q
		if (q->next != NULL)//��q�����ں�̽�㣬�޸���ǰ��ָ��
			q->next->prior = p;
		free(q);//�ͷ�q���
		return true;
	}
}

/*������*/
bool listinsert(dlinknode*& L, int i, elemtype e)
{
	int j = 0;
	dlinknode* p = L, * s;//pָ��ͷ��㣬j����Ϊ0
	if (i <= 0)return false;//i���󷵻�false
	while (j < i - 1 && p != NULL)//���ҵ�i-1�����
	{
		j++; p = p->next;
	}
	if (p == NULL)//δ�ҵ���i-1����㣬����false
		return false;
	else
	{
		s = (dlinknode*)malloc(sizeof(dlinknode));
		s->data = e;//�����½��s
		s->next = p->next;//��p���֮�����s���
		if (p->next != NULL)//��p�����ں�̽�㣬�޸���ǰ��ָ��
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

/*��Ԫ��ֵ����*/
int locateelem(dlinknode* L, elemtype e)
{
	int i = 1;//pָ���׽�㣬i��Ϊ1�����׽������Ϊ1��
	dlinknode* p = L->next;//����dataֵΪe�Ľ�㣬�����Ϊi
	while (p != NULL && p->data != e)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)return(0);//������ֵΪe�Ľ�㣬����0
	else return(i);//����ֵΪe�Ľ�㣬�������߼����i
}

/*�������������*/
void insertsort(dlinknode* &L) {
	dlinknode* p = L->next, * q, * r, * s; elemtype e;
	while (p->next!= NULL)
	{
		q = p;
		while (q->prior != L)
		{
			if (q->data < q->prior->data)
				listdelete(L, locateelem(L, q->data), e);

		}
	}
	
}



int main(void)
{
	int num = 0, i = 0, n = 0;
	dlinknode* L; initlist(L); elemtype a[maxsize];
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.β�巨��������  2.��������  3.��������в�������  4.������� ������q�˳���\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  �������������"); scanf("%d", &n);
			for (i = 0; i < n; i++) {
				printf("\n  �������%d������ֵ:", i + 1);
				scanf("%d", &a[i]);
			}
			initlist(L); createlistr(L, a, n);
			printf("\n  �������ɹ�!\n"); break;
		case 2:destroylist(L); printf("\n  ����ɾ���ɹ���\n"); break;
		case 3:insertsort(L); printf("\n  ��������ɹ���\n"); break;
		case 4: printf("\n  �������£�\n"); displist(L); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.β�巨��������  2.��������  3.��������в�������  4.������� ������q�˳���\n");
	}
	return 0;
}
/*�������������*/
void insertsort2(dlinknode*& L)
{
	dlinknode* p = L->next, * q, * s;
	if (p)
	{
		for (p = p->next; p; p = p->next)
		{
			s = p;
			for (q = p->prior; q != L; q = q->prior)
			{
				if (q->data < s->data) break;
			}
			if (q->next != p)
			{
				if (s->next)
				{
					s->prior->next = s->next;
					s->next->prior = s->prior;
					s->prior = q;
					q->next = s;
				}
				else
				{
					s->prior->next = NULL;
					s->next = q->next;
					q->next->prior = s;
					s->prior = q;
					q->next = s;
				}
			}
		}
	}
}