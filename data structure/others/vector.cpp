#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#define maxsize 100
typedef int elemtype;
typedef struct {
	elemtype data[maxsize];
	int length;
}vector;

//����vector
void createlist(vector* &L, elemtype a[], int n)//��a�е�n��Ԫ�ؽ���vector
{
	int i = 0, k = 0;//kΪL��Ԫ�ظ�������ʼֵΪ0
	L = (vector*)malloc(sizeof(vector));//�����vector�Ŀռ�
	while (i < n) //iɨ������a��Ԫ��
	{
		L->data[k] = a[i];//��Ԫ��a[i]�ŵ�L��
		k++; i++;
	}
	L->length = k;//����L�ĳ���
}
//��ʼ��vector
void initlist(vector* &L)
{
	L = (vector*)malloc(sizeof(vector));//�����vector�Ŀռ�
	L->length = 0;
}
//����vector
void destroylist(vector* &L)
{
	free(L);
}
//�ж�vector�Ƿ�Ϊ��
bool listempty(vector* L)
{
	return(L->length == 0);
}
//��vector�ĳ���
int listlength(vector* L)
{
	return(L->length);
}
//���vector
void displist(vector* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}
//��vector��ĳ������Ԫ��ֵ
bool getelem(vector* L, int i, elemtype&e)
{
	if (i<1 || i>L->length)
		return 0;//����i����ʱ����0
	e = L->data[i - 1];//ȡԪ��ֵ
	return true;//�ɹ��ҵ�Ԫ��ʱ����Ԫ��ֵ
}
//��Ԫ��ֵ����
int locateelem(vector* L, elemtype e)
{
	int i = 0;
	while (i < L->length&& L->data[i] != e) i++;//����Ԫ��e
	if (i >= L->length) return 0;//δ�ҵ�����0
	else return i + 1;//�ҵ��������߼����
}
//��������Ԫ��
bool listinsert(vector* &L, int i, elemtype e)
{
	int j;
	if (i<1 || i>L->length + 1 || L->length == maxsize)
		return false;
	i--;
	for (j = L->length; j > i; j--)
		L->data[j] = L->data[j - 1];
	L->data[j] = e;
	L->length++;
	return true;
}
//ɾ������Ԫ��
bool listdelete(vector* &L, int i, elemtype&e)
{
	int j;
	if (i<1 || i>L->length)
		return false;
	i--;
	e = L->data[i];
	for (j = i; j < L->length - 1; j++)
		L->data[j] = L->data[j + 1];
	L->length--;
	return true;
}

int main(void)
{
	int num = 0, i = 0, n = 0; elemtype e;
	vector* L; initlist(L); elemtype a[maxsize];
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.����vector  2.����vector  3.��������Ԫ��ֵ  4.����Ԫ��λ��  5.ɾ������Ԫ��\n\
  6.��������Ԫ��  7.����vector��ǰ�ĳ���  8.�ж�vector�Ƿ�Ϊ��  9.��˳�����vector\n  ������q�˳���\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  ������vectorԪ�ظ�����"); scanf("%d", &n);
			for (i = 0; i < n; i++) {
				printf("\n  �������%d��Ԫ��:", i + 1);
				scanf("%d", &a[i]);
			}
			createlist(L, a, n);
			printf("\n  vector�����ɹ�!\n"); break;
		case 2:destroylist(L); printf("\n  vectorɾ���ɹ���\n"); break;
		case 3:printf("\n  ���������Ԫ�ص���ţ�"); scanf("%d", &i); getelem(L, i, e);
			if (e) printf("\n  �� %d ��Ԫ��Ϊ  %d \n", i, e); else printf("\n  ����������\n"); break;
		case 4:printf("\n  ��������ҵ�Ԫ��ֵ��"); scanf("%d", &e);
			if (locateelem(L, e)) printf("\n  %d �Ǳ��е� %d ��Ԫ��\n", e, locateelem(L, e));
			else printf("\n  δ�ҵ�Ԫ��\n"); break;
		case 5:printf("\n  ������ɾ��Ԫ�ص���ţ�"); scanf("%d", &i);
			if (listdelete(L, i, e)) printf("\n  Ԫ��ɾ���ɹ�\n"); else printf("\n����������\n"); break;
		case 6:printf("\n  ������Ԫ�ز�����ţ�"); scanf("%d", &i); printf("\n  ������Ԫ��ֵ��"); scanf("%d", &e);
			if (listinsert(L, i, e)) printf("\n  Ԫ�ز���ɹ�\n"); else printf("\n  ����������\n"); break;
		case 7:printf("\n  vector����Ϊ��%d\n",listlength(L)); break;
		case 8:if(listempty(L)) printf("\n  vectorΪ��\n"); else printf("\n  vector�ǿ�\n"); break;
		case 9:printf("\n  vectorԪ�����£�\n"); displist(L); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.����vector  2.����vector  3.��������Ԫ��ֵ  4.����Ԫ��λ��  5.ɾ������Ԫ��\n\
  6.��������Ԫ��  7.����vector��ǰ�ĳ���  8.�ж�vector�Ƿ�Ϊ��  9.��˳�����vector\n  ������q�˳���\n");
	}
	return 0;
}