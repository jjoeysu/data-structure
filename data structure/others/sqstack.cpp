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
	printf("\n  请选择需要执行的操作：\n  1.入栈  2.出栈  3.取栈顶元素  4.判断栈是否为空  （输入q退出）\n");
	while (scanf("%d", &num) != 0)
	{
		switch (num)
		{
		case 1: printf("\n  请输入入栈元素："); scanf("%d", &e); if (push(s, e))  printf("\n  入栈成功\n");
			  else printf("\n  栈满，无法入栈\n"); break;
		case 2: if (pop(s, e))  printf("\n  元素%d已出栈\n", e); else printf("\n  栈空，无元素出栈\n"); break;
		case 3: if (gettop(s, e))  printf("\n  栈顶元素为%d\n", e); else printf("\n  栈空，栈顶无元素\n"); break;
		case 4: if (stackempty(s))  printf("\n  栈空\n"); else printf("\n  栈非空\n"); break;
		default: printf("\n  输入错误！\n");
		}
		printf("\n  请选择需要执行的操作：\n  1.入栈  2.出栈  3.取栈顶元素  4.判断栈是否为空  （输入q退出）\n");
	}
	return 0;
}


























