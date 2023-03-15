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
	L->next =L->prior= NULL;
}

/*ͷ�巨����˫����*/
void createlistf(dlinknode*& L, elemtype a[], int n)
{
	dlinknode* s;
	L = (dlinknode*)malloc(sizeof(dlinknode));//����ͷ���
	L->prior = L->next = NULL;//ǰ��ָ������ΪNULL
	for (int i = 0; i < n; i++)//ѭ���������ݽ��s
	{
		s = (dlinknode*)malloc(sizeof(dlinknode));
		s->data = a[i];//�������ݽ��s
		s->next = L->next;//��s�����뵽ͷ���֮��
		if (L->next != NULL)//��L�������ݽ�㣬�޸�L->next��ǰ��ָ��
			L->next->prior = s;
		s->prior = L;
	}
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

/*�ж������Ƿ�Ϊ�ձ�*/
bool listempty(dlinknode* L)
{
	return(L->next == NULL);
}

/*������ĳ���*/
int listlength(dlinknode* L)
{
	int n = 0;
	dlinknode* p = L;//pָ��ͷ���,n��Ϊ0����ͷ�������Ϊ0��
	while (p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return(n);//ѭ��������pָ��β��㣬�����nΪ������
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

/*�������е�ĳ������Ԫ��ֵ*/
bool getelem(dlinknode* L, int i, elemtype& e)
{
	int j = 0;
	dlinknode* p = L;//pָ��ͷ��㣬j��Ϊ0����ͷ�������Ϊ0��
	if (i <= 0)return false;//i���󷵻�false
	while (j < i && p != NULL)//�ҵ�i�����p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)return false;//�����ڵ�i�����ݽ�㣬����false
	else//���ڵ�i�����ݽ�㣬����true
	{
		e = p->data;
		return true;
	}
}

/*��Ԫ��ֵ����*/
int locateelem(dlinknode*L, elemtype e)
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

int main(void)
{
	int num = 0, i = 0, n = 0; elemtype e; elemtype c;
	dlinknode* L; initlist(L); elemtype a[maxsize];
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.β�巨��������  2.��������  3.��ֵ���ҽ��  4.������\n  5.ɾ�����\
  6.�ж������Ƿ�Ϊ��  7.�������  ������q�˳���\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  �������������"); scanf("%d", &n);
			for (i = 0; i < n; i++) {
				printf("\n  �������%d������ֵ:", i + 1);
				scanf("%d", &a[i]);
			}
			createlistr(L, a, n);
			printf("\n  �������ɹ�!\n"); break;
		case 2:destroylist(L); printf("\n  ����ɾ���ɹ���\n"); break;
		case 3:printf("\n  ��������ҵĽ��ֵ��"); scanf("%d", &e);
			if (locateelem(L, e)) printf("\n  ֵΪ %d �Ľ�����\n", e); else printf("\n  ֵΪ %d �Ľ�㲻����\n", e); break;
		case 4: printf("\n  ������������ֵ�����������ֵ��"); scanf("%d %d", &e,&c);
			if (locateelem(L, c)) { listinsert(L, locateelem(L, c), e); printf("\n  ������ɹ�\n"); }
			 else printf("\n  �����㲻���ڣ�\n"); break;
		case 5:printf("\n  ������ɾ������ֵ��"); scanf("%d", &e);
			if (locateelem(L, e)) { listdelete(L, locateelem(L, e),c); printf("\n  ���ɾ���ɹ�\n"); }
			else printf("\n  �����㲻���ڣ�\n"); break;
		case 6:if (listempty(L)) printf("\n  ����Ϊ��\n"); else printf("\n  ����ǿ�\n"); break;
		case 7:printf("\n  �������£�\n"); displist(L); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.β�巨��������  2.��������  3.��ֵ���ҽ��  4.������\n  5.ɾ�����\
  6.�ж������Ƿ�Ϊ��  7.�������  ������q�˳���\n");
	}
	return 0;
}