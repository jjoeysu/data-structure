#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<malloc.h>
#define maxsize 100
typedef int ElemType;
typedef struct {
	ElemType data[maxsize];
	int length;
}sqlist;

//����˳���
sqlist* creatlist(sqlist *Lp, ElemType a[], int n)//��a�е�n��Ԫ�ؽ���˳���
{
	int i = 0, k = 0;//kΪL��Ԫ�ظ�������ʼֵΪ0
	Lp = (sqlist*)malloc(sizeof(sqlist));//��������Ա�Ŀռ�
	while (i < n) //iɨ������a��Ԫ��
	{
		Lp->data[k] = a[i];//��Ԫ��a[i]�ŵ�L��
		k++; i++;
	}
		Lp->length = k;//����L�ĳ���
		printf("%d", Lp->length);
		return Lp;
}
//��ʼ�����Ա�
void initlist(sqlist *Lp)
{
	Lp = (sqlist*)malloc(sizeof(sqlist));//��������Ա�Ŀռ�
	Lp->length = 0;
}
//�������Ա�
void destroylist(sqlist* Lp)
{
	free(Lp);
}
//������Ա�
void displist(sqlist *Lp)
{
	for (int i = 0; i < Lp->length; i++)
		printf("%d ", Lp->data[i]);
	printf("\n");
}
//�����Ա���ĳ������Ԫ��ֵ
ElemType* getelem(sqlist* Lp, int i, ElemType* ep)
{
	if (i<1 || i>Lp->length)
		return 0;//����i����ʱ����0
	*ep = Lp->data[i - 1];//ȡԪ��ֵ
	return ep;//�ɹ��ҵ�Ԫ��ʱ����Ԫ��ֵ
}
//��Ԫ��ֵ����
int locateelem(sqlist* Lp, ElemType e)
{
	int i = 0;
	while (i < Lp->length&& Lp->data[i] != e) i++;//����Ԫ��e
	if (i >= Lp->length) return 0;//δ�ҵ�����0
	else return i + 1;//�ҵ��������߼����
}
//��������Ԫ��
bool listinsert(sqlist* Lp, int i, ElemType e)
{
	int j;
	if (i<1 || i>Lp->length + 1 || Lp->length == maxsize)
		return false;
	i--;
	for (j = Lp->length; j > i; j--)
		Lp->data[j] = Lp->data[j - 1];
	Lp->data[j]=e;
	Lp->length++;
	return true;
}
//ɾ������Ԫ��
bool listdelete(sqlist *Lp, int i, ElemType* e)
{
	int j;
	if (i<1 || i>Lp->length)
		return false;
	i--;
	*e = Lp->data[i];
	for (j = i; j < Lp->length - 1; j++)
		Lp->data[j] = Lp->data[j + 1];
	Lp->length--;
	return true;
}

int main(void)
{
	int num = 0, i = 0, n = 0; ElemType e; ElemType* ep=&e;
	sqlist L; sqlist* Lp = &L; initlist(Lp); ElemType a[maxsize];
	printf("  ��ѡ����Ҫִ�еĲ�����\n  1.����˳���\n  2.�������Ա�\n  3.��������Ԫ��ֵ\n  4.����Ԫ��λ��\n  5.ɾ������Ԫ��\n  6.��������Ԫ��\n  ������q�˳���\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  ������˳���Ԫ�ظ�����"); scanf("%d", &n); 
			for (i = 0; i < n; i++) {
				printf("\n  �������%d��Ԫ��:", i + 1);
				scanf("%d", &a[i]);
			}
			Lp=creatlist(Lp, a, n);
			printf("\n  ˳������ɹ�!\n"); break;
		case 2:destroylist(Lp); printf("\n  ���Ա�ɾ���ɹ���\n"); break;
		case 3:printf("\n  ���������Ԫ�ص���ţ�"); scanf("%d", &i); ep = getelem(Lp, i, ep);
			if (ep) printf("\n  �� %d ��Ԫ��Ϊ  %d \n",i, e); else printf("\n  ����������\n"); break;
		case 4:printf("\n  ��������ҵ�Ԫ��ֵ��"); scanf("%d", ep);
			if (locateelem(Lp, e)) printf("\n  %d �Ǳ��е� %d ��Ԫ��\n", e, locateelem(Lp, e));
			else printf("\n  δ�ҵ�Ԫ��\n"); break;
		case 5:printf("\n  ������ɾ��Ԫ�ص���ţ�"); scanf("%d", &i);
			if (listdelete(Lp, i, ep)) printf("\n  Ԫ��ɾ���ɹ�\n"); else printf("\n����������\n"); break;
		case 6:printf("\n  ������Ԫ�ز�����ţ�"); scanf("%d", &i); printf("\n  ������Ԫ��ֵ��"); scanf("%d", ep);
			if (listinsert(Lp, i, e)) printf("\n  Ԫ�ز���ɹ�\n"); else printf("\n  ����������\n"); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ˳���Ԫ�����£�\n"); displist(Lp);
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.����˳���\n  2.�������Ա�\n  3.��������Ԫ��ֵ\n  4.����Ԫ��λ��\n  5.ɾ������Ԫ��\n  6.��������Ԫ��\n  ������q�˳���\n");
	}
	return 0;
}