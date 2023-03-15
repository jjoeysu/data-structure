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
	printf("\n  请选择需要执行的操作：\n  1.入栈  2.出栈  3.取栈顶元素  4.判断栈是否为空  （输入q退出）\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  请输入入栈元素和操作栈号："); scanf("%d %d", &e,&i); if(gs.push(s, e,i))  printf("\n  入栈成功\n");
			  else printf("\n  栈满，无法入栈\n"); break;
		case 2: printf("\n  请输入操作栈号："); scanf("%d", &i); 
			if (gs.pop(s, e,i))  printf("\n  元素%d已出栈\n", e); else printf("\n  栈空，无元素出栈\n"); break;
		case 3: printf("\n  请输入操作栈号："); scanf("%d", &i);
			if (gs.gettop(s, e,i))  printf("\n  栈顶元素为%d\n", e); else printf("\n  栈空，栈顶无元素\n"); break;
		case 4: printf("\n  请输入操作栈号："); scanf("%d", &i);
			if (gs.stackempty(s,i))  printf("\n  栈空\n"); else printf("\n  栈非空\n"); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  请选择需要执行的操作：\n  1.入栈  2.出栈  3.取栈顶元素  4.判断栈是否为空  （输入q退出）\n");
	}
	return 0;
}


















