#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
typedef struct value
{
	int n;
	struct value *next;
}value;
void hash(value *head,int n,int size);
void find(value *head);
void find(value *head)
{
	value *p;
	int i;
	int t = 0;
	for(i = 0;i<10;i++)
	{
		p = head[i].next;
		while(p!=NULL)
		{
			printf("%3d:%d\n",++t,p->n);
			p = p->next;
		}
	}
}
void hash(value *head,int n,int size)
{
	int i;
	value *p;
	i = n%size;
	p = &head[i];
	while(p->next != NULL)
	{
	
		
		p = p->next;
	}
	p->next = (value *)malloc(sizeof(value));
	p = p->next;
	p->n = n;
	p->next = NULL;
}
int main()
{
	value head[10];
	int i ;
	srand(time(0));
 
	for(i = 0;i<10;i++)
	{
		head[i].n = i;
		head[i].next = NULL;
	}
	for(i = 0;i<100;i++)
	{
	
		 hash(head,rand()%1000+1,10);
	}
	
	find(head);
}	
