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
//���vector
void displist(vector* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}
//��Ԫ�صĶ��ֲ���
int bsearch(vector*& L,elemtype e)
{
	int low=0, high=L->length-1, mid=0;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (L->data[mid] == e)
			return mid+1;
		else if (L->data[mid] < e)
			low = mid + 1;
		else high = mid - 1;
	}
}

int main(void)
{
	int num = 0, i = 0, n = 0; elemtype e;
	vector* L; initlist(L); elemtype a[maxsize];
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.����vector  2.��Ԫ�ؽ��ж��ֲ���  3.���vector  ������q�˳���\n");
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
		case 2:printf("\n  �������Ԫ��"); scanf("%d", &e); if (bsearch(L, e)) printf("\n  ��Ԫ���ڵ� %d λ\n", bsearch(L, e)); else printf("\n  Ԫ�ز�����!\n"); break;
		case 3:printf("\n  vectorԪ�����£�\n"); displist(L); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.����vector  2.��Ԫ�ؽ��ж��ֲ���  3.���vector  ������q�˳���\n");
	}
	return 0;
}