#include <stdio.h>
#include <malloc.h>
/*
编程思路:为实现符号平衡，先创建一个空栈，先读入一对符号
的左边，直到读入这对符号的右边，把符号弹出，如果这对符号
对称则继续，直到最后符号全部读完，并且栈为空。 
*/
struct node
{
    char symbol;
    struct node* next; 
};
typedef struct node Node;
typedef struct node* stack;
typedef struct node* position;
stack makeStack(void);
int isEmpty(stack S);
void push(stack S,char X);
void pop(stack S);
char top(stack S);
int match(char p,char q);
void checkSymbols(stack S);
stack makeStack(void)
{
    stack S=(struct node*)malloc(sizeof(struct node));
    if(S==NULL)
    printf("memory error");
    else
    {
        S->next=NULL;
        return S;
    }
}
int isEmpty(stack S)
{
    return S->next==NULL;
}
void push(stack S,char X)
{
    if(S==NULL)
    printf("Please make a stack first");
    position P = (struct node*)malloc(sizeof(struct node));
    if(P==NULL)
    printf("memory error");
    else
    {
        P->symbol=X;
        P->next=S->next;
        S->next=P;
    }   
}
void pop(stack S)
{
    position P;
    if(isEmpty(S))
    printf("Empty Stack");
    else
    {
        P=S->next;
        S->next=S->next->next;
        free(P);    
    }

}
char top(stack S)
{
    return S->next->symbol;
}
int match(char p,char q)
{
    if(abs(p-q)==1)
    return 1;
    else if(abs(p-q)==2)
    return 1;
    else
    return 0;

}
void checkSymbols(stack S)
{
    char ch;
    while((ch=getchar())!='#')
    {
        if(ch=='{'||ch=='['||ch=='(')
        push(S,ch);
        else if(ch=='}'||ch==']'||ch==')')
        {
            if(match(ch,top(S)))
            pop(S);
            else
            printf("error");
        }
    }
        if(isEmpty(S))
        printf("right\n");
}
int main(int argc, char *argv[])
{
    stack S = makeStack();
    checkSymbols(S);
    return 0;
}

