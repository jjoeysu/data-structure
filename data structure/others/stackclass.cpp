#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include<stdio.h>

#define maxsize 100
#define elemtype int
typedef struct {
	elemtype data[maxsize];
	int top1, top2;
}dstack;

class growstack
{
public:
	void initstack(dstack*& s)
	{
		s = (dstack*)malloc(sizeof(dstack));
		s->top1 = -1;
		s->top2 = maxsize;
	}

	void destroy(dstack*& s)
	{
		free(s);
	}

	bool stackempty(dstack* s, int i)
	{
		if (i == 1)
			return(s->top1 == -1);
		else return(s->top2 == maxsize);
	}

	bool push(dstack*& s, elemtype& e, int i)
	{
		if (s->top1 == s->top2 - 1)
			return false;
		if (i == 1) {
			s->top1++;
			s->data[s->top1] = e;
		}
		else {
			s->top2--;
			s->data[s->top2] = e;
		}

		return true;
	}

	bool pop(dstack*& s, elemtype& e, int i)
	{
		if (s->top1 == s->top2 - 1)
			return false;
		if (i == 1) {
			e = s->data[s->top1];
			s->top1--;
		}
		else {
			e = s->data[s->top2];
			s->top2--;
		}
		return true;
	}

	bool gettop(dstack*& s, elemtype& e, int i)
	{
		if ((i == 1 && s->top1 == -1) || (i == 2 && s->top2 == maxsize))
			return false;
		if (i == 1)
			e = s->data[s->top1];
		else e = s->data[s->top2];
		return true;
	}
};


int main(void)
{
	growstack gs; dstack* s; gs.initstack(s); elemtype e; int i, num = 0;
	printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.��ջ  2.��ջ  3.ȡջ��Ԫ��  4.�ж�ջ�Ƿ�Ϊ��  ������q�˳���\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  ��������ջԪ�غͲ���ջ�ţ�"); scanf("%d %d", &e,&i); if(gs.push(s, e,i))  printf("\n  ��ջ�ɹ�\n");
			  else printf("\n  ջ�����޷���ջ\n"); break;
		case 2: printf("\n  ���������ջ�ţ�"); scanf("%d", &i); 
			if (gs.pop(s, e,i))  printf("\n  Ԫ��%d�ѳ�ջ\n", e); else printf("\n  ջ�գ���Ԫ�س�ջ\n"); break;
		case 3: printf("\n  ���������ջ�ţ�"); scanf("%d", &i);
			if (gs.gettop(s, e,i))  printf("\n  ջ��Ԫ��Ϊ%d\n", e); else printf("\n  ջ�գ�ջ����Ԫ��\n"); break;
		case 4: printf("\n  ���������ջ�ţ�"); scanf("%d", &i);
			if (gs.stackempty(s,i))  printf("\n  ջ��\n"); else printf("\n  ջ�ǿ�\n"); break;
		default: printf("\n  �������\n");
		}
		printf("\n  ��ѡ����Ҫִ�еĲ�����\n  1.��ջ  2.��ջ  3.ȡջ��Ԫ��  4.�ж�ջ�Ƿ�Ϊ��  ������q�˳���\n");
	}
	return 0;
}


















