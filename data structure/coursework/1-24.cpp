#include<stdio.h>
#include<malloc.h> 
#include<stdlib.h>
#include<string.h>
#define maxsize 100
typedef int elementype;
typedef struct
{
    elementype* data;
    int top;
}stack;

void initstack(stack* s)
{
    s->data = (elementype*)malloc(maxsize * sizeof(elementype));
    s->top = -1;
}
int push(stack* s, elementype e)
{
    if (maxsize - 1 == (s->top))
    {
        return 0;
    }
    s->top++;
    s->data[s->top] = e;
    return 1;
}

bool pop(stack* s, elementype e)
{
    if (s->top == -1)
        return false;
    e = s->data[s->top];
    s->top--;
    return true;
}

bool gettop(stack* s, elementype e)
{
    if (s->top == -1)
        return false;
    e = s->data[s->top];
    printf("%d\n", e);
    return true;
}

bool isempty(stack* s)
{
    return(s->top == -1);
}

void Show(stack* s)
{
    int i;
    for (i = 0; i < 1 + s->top; i++)
        printf(" %d ", s->data[i]);
    putchar('\n');
}

void fun(int a[maxsize], int n)
{
    int i, j; printf("数组为：\n");
    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        printf(" %d ", a[i]);
    }
    printf("\n答案为：\n");
    for (i = 0; i < n - 1; i++)
    {
        int count = 0;
        for (j = i + 1; j < n; j++)
        {
            if (a[i] >= a[j])
                count++;
            else
                break;
        }
        if (j == n)
            printf(" %d ", count - count);
        else
            printf(" %d ", count + 1);

    }
    printf(" 0 ");
}

int main()
{
    int n, a[maxsize];
    printf("输入元素个数n:");
    scanf_s("%d", &n);
    fun(a, n);
    return 0;
}