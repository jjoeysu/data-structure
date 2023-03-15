#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define maxsize 100
typedef int elemtype;


typedef struct {
	elemtype data[maxsize];
	int length;
}vector;

//����vector
void createlist(vector*& L, elemtype a[], int n)//��a�е�n��Ԫ�ؽ���vector
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
void initlist(vector*& L)
{
	L = (vector*)malloc(sizeof(vector));//�����vector�Ŀռ�
	L->length = 0;
}
//����vector
void destroylist(vector*& L)
{
	free(L);
}
//���vector
void displist(vector* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}
//��vector��������
void cbsort(vector*& L)
{
	int i = L->length, j = 0, k = i; elemtype a;
	while (k > 0)
	{
		k = floor(k / 1.3);
		for (j = 0; j+k < i; j=j+1)
			if (L->data[j+k] < L->data[j])
			{
				a = L->data[j+k];
				L->data[j+k] = L->data[j];
				L->data[j] = a;
			}
	}
}

int main(void)
{
	int num = 0, i = 0, n = 0;
	vector* L; initlist(L); elemtype a[maxsize];
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.����vector\n  2.����vector\n  3.��vector����������\n  4.���vector\n  ������q�˳���\n");
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
		case 3:cbsort(L); printf("\n  ��������ɣ�\n"); break;
		case 4:printf("\n  vectorԪ�����£�\n"); displist(L); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.����vector\n  2.����vector\n  3.��vector����������\n  4.���vector\n  ������q�˳���\n");
	}
	return 0;
}