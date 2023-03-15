#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include<stdio.h>

#define maxsize 100
#define elemtype int
typedef struct {
	elemtype data[maxsize];
	int top;
}sqstack;

void initstack(sqstack*& s)
{
	s = (sqstack*)malloc(sizeof(sqstack));
	s->top = -1;
}
void destroy(sqstack*& s)
{
	free(s);
}

bool stackempty(sqstack* s)
{
	return(s->top == -1);
}

bool push(sqstack*& s, elemtype &e)
{
	if (s->top == maxsize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool pop(sqstack*& s, elemtype& e)
{
	if(s->top==-1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

bool gettop(sqstack*& s, elemtype& e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

int main(void)
{
	sqstack* s; initstack(s); elemtype e; int num=0;
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.��ջ  2.��ջ  3.ȡջ��Ԫ��  4.�ж�ջ�Ƿ�Ϊ��  ������q�˳���\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  ��������ջԪ�أ�"); scanf("%d", &e); if (push(s, e))  printf("\n  ��ջ�ɹ�\n");
			  else printf("\n  ջ�����޷���ջ\n"); break;
		case 2: if (pop(s, e))  printf("\n  Ԫ��%d�ѳ�ջ\n", e); else printf("\n  ջ�գ���Ԫ�س�ջ\n"); break;
		case 3: if (gettop(s, e))  printf("\n  ջ��Ԫ��Ϊ%d\n", e); else printf("\n  ջ�գ�ջ����Ԫ��\n"); break;
		case 4: if (stackempty(s))  printf("\n  ջ��\n"); else printf("\n  ջ�ǿ�\n"); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.��ջ  2.��ջ  3.ȡջ��Ԫ��  4.�ж�ջ�Ƿ�Ϊ��  ������q�˳���\n");
	}
	return 0;
}


























