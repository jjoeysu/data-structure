#include<stdio.h>
#include<stdlib.h>
typedef struct _stack
{
	char dat;
	struct _stack* next;

} stype; 

int recoginze(char x)
{
	if (x == '+' || x == '-')
		return 0;
	else if (x == '*' || x == '/')
		return 1;
	else if (x == '@' || x == '(' || x == ')')
		return -1;
}
int main()
{
	int rs = 0;stype* s, * top; int calc[50], i = 0;char c;
	s = (stype*)malloc(sizeof(stype));
	s->dat = '@';s->next = NULL;top = s;c = getchar();
	while (c != '\n')
	{
		if (c >= '0' && c <= '9') 
		{
			i++;
			calc[i] = c - 48;
			printf("%c ", c);
		}
		else if (c == '(') 
		{
			s = (stype*)malloc(sizeof(stype));
			s->dat = c;
			s->next = top;
			top = s;
		}
		else if (c == ')') 
		{
			while (top->dat != '(')
			{
				s = top;
				printf("%c ", top->dat);
				if (top->dat == '+')
				{
					calc[i - 1] = calc[i - 1] + calc[i];
					i--;
				}
				else if (top->dat == '-')
				{
					calc[i - 1] = calc[i - 1] - calc[i];
					i--;
				}
				else if (top->dat == '*')
				{
					calc[i - 1] = calc[i - 1] * calc[i];
					i--;
				}
				else if (top->dat == '/')
				{
					calc[i - 1] = calc[i - 1] / calc[i];
					i--;
				}
				top = top->next;
				free(s);
			}
			s = top;
			top = top->next;
			free(s);
		}
		else
		{
			int a = recoginze(c);int b = recoginze(top->dat);
			if (a > b)  
			{
				s = (stype*)malloc(sizeof(stype));
				s->dat = c;
				s->next = top;
				top = s;
			}
			else 
			{
				while (a <= b)
				{
					s = top;
					printf("%c ", top->dat);
					if (top->dat == '+')
					{
						calc[i - 1] = calc[i - 1] + calc[i];
						i--;
					}
					else if (top->dat == '-')
					{
						calc[i - 1] = calc[i - 1] - calc[i];
						i--;
					}
					else if (top->dat == '*')
					{
						calc[i - 1] = calc[i - 1] * calc[i];
						i--;
					}
					else if (top->dat == '/')
					{
						calc[i - 1] = calc[i - 1] / calc[i];
						i--;
					}
					top = top->next;free(s);
					b = recoginze(top->dat);
				}
				s = (stype*)malloc(sizeof(stype));
				s->dat = c;
				s->next = top;
				top = s;
			}
		}
		c = getchar();  
	}
	while (top->dat != '@') 
	{
		s = top;
		printf("%c ", top->dat);
		if (top->dat == '+')
		{
			calc[i - 1] = calc[i - 1] + calc[i];
			i--;
		}
		else if (top->dat == '-')
		{
			calc[i - 1] = calc[i - 1] - calc[i];
			i--;
		}
		else if (top->dat == '*')
		{
			calc[i - 1] = calc[i - 1] * calc[i];
			i--;
		}
		else if (top->dat == '/')
		{
			calc[i - 1] = calc[i - 1] / calc[i];
			i--;
		}
		top = top->next;
		free(s);
	}
	printf("\n");printf("%d\n", calc[1]);
	return 0;
}