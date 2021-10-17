#include<stdio.h>
#include<stdlib.h>
#define REMAINDER 13
#define SIZE 50 

typedef struct element
{
	int key;		// key值  唯一不重复 
	int data;		// data 域  
}Element;

typedef struct table
{
	Element **elm;	//  
	int count;		// 记录表中记录的数据个数 
	int size;	// 哈希表的大小 = SIZE = 50
}Table;

int hash(int key)
{
	return key%REMAINDER;	
}

Table * init_Table()
{
	Table *t = (Table*)malloc(sizeof(Table));
	t->size = SIZE;
	t->count = 0;
	t->elm = (Element **)malloc(SIZE*sizeof(Element*));
	/*
	创建一个长度为13的指针数组，类型为Element* 
	并将数组头地址赋值给 elm 的二级指针 
	*/ 
	int i;
	for(i=0 ; i<t->size ; i++)
	{
		t->elm[i] = NULL;	// 将数组的每个域赋空 
	}	
	return t;
}

void Insert(Table *t,Element * k)		//将key值插入到哈希表中 
{
	int i=0;
	int position;
	position = hash(k->key);
	
	for(i=1 ; t->elm[position]!=NULL && i<t->size ;i++ )
	{
		position=(hash(position)+i)%t->size;
	}
	t->elm[position] = k;	
	t->count += 1;
	return ;
}

int serch(Table *t, Element * k)		//查找 value 并返回其所在的地址 
{
	int position=hash(k->key);
	while(t->elm[position]->key != k->key)
	{
		position = hash(position+1);
		if(t->elm[position]==NULL || position == hash(k->key))
		/*
		出现以下几种情况即判断查找失败
		1.对应的 position 位置的地址为空 
		2.遍历整个表都没有对应的 key 值 
		*/ 
		return -1;
	}
	
	return position;	
}


void Print_Table(Table *t)		//打印部分哈希表 
{
	int i;
	for(i=0 ; i<13 ; i++)
	{
		if(t->elm[i])
		printf("[%d %d] ",t->elm[i]->key , t->elm[i]->data);
		else printf("NULL ");
	}	
	printf("\n");
}

int main()
{
	Table *t = init_Table();
	
	Element a[]={{12,99},{13,98},{26,87},{14,77},{15,100},{10,59}};
	int length = sizeof(a)/sizeof(Element);
	
	int i;
	for(i=0 ; i<length ; i++)
	{
		Insert(t,&a[i]);
	}
	Print_Table(t);
	printf("a[3] is locat %d\n",serch(t,&a[3]));
	free(t);
    getchar();//用vscode不加getchar会闪退
}


