#include<stdio.h>
#include<stdlib.h>

typedef struct PolyNode* Polynomial;

struct PolyNode {
	int coefficient;
	int expon;
	Polynomial next;
};

void Attach(int c, int e, Polynomial* p)   //在p后面添加结点
{
	Polynomial temp = (Polynomial)malloc(sizeof(struct PolyNode));
	temp->coefficient = c;
	temp->expon = e;
	temp->next = NULL;
	(*p)->next = temp;
	(*p) = temp;
}

Polynomial ReadPoly()    //读取并构建多项式
{
	Polynomial p, rear, temp;
	int c, e, N;
	p = (Polynomial)malloc(sizeof(struct PolyNode));
	p->next = NULL;
	rear = p;
	scanf_s("%d", &N);   //读入多项式项数，注：按照指数递减的顺序输入
	while (N--)
	{
		scanf_s("%d %d", &c, &e);
		Attach(c, e, &rear);
	}
	temp = p;           //删除临时生成的头结点;
	p = p->next;
	free(temp);
	return p;
}

Polynomial initPoly(Polynomial p1, Polynomial p2)//用p1第一项乘以p2初始化结果多项式
{
	Polynomial p, t, rear;
	p = (Polynomial)malloc(sizeof(struct PolyNode));
	p->next = NULL;
	t = (Polynomial)malloc(sizeof(struct PolyNode));
	t = p2;
	rear = p;
	while (t)
	{
		Attach((p1->coefficient) * (t->coefficient), p1->expon + t->expon, &rear);
		t = t->next;
	}
	return p;        //此时返回的多项式含头结点
}

Polynomial Mult(Polynomial p1, Polynomial p2)
{
	Polynomial p3 = initPoly(p1, p2);
	Polynomial t1, t2, rear, temp;
	int c, e;
	t1 = p1->next;
	while (t1)
	{
		rear = p3;
		t2 = p2;
		while (t2)
		{
			c = (t1->coefficient) * (t2->coefficient);
			e = (t1->expon) + (t2->expon);
			while ((rear->next) && (rear->next->expon > e))  //移动rear，找到插入位置
			{
				rear = rear->next;
			}
			if ((rear->next) && (rear->next->expon == e))    //合并同类项
			{
				if (rear->next->coefficient + c)             
				{
					rear->next->coefficient += c;
				}
				else                                         //同类项系数为0，删去该结点
				{
					temp = rear->next;
					rear->next = temp->next;
					free(temp);
				}
			}
			else                                             //不能合并同类项即插入结点
			{
				temp = (Polynomial)malloc(sizeof(struct PolyNode));
				temp->coefficient = c;
				temp->expon = e;
				temp->next = rear->next;
				rear->next = temp;
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	temp = p3;
	p3 = p3->next;
	free(temp);
	return p3;
}

void PrintPoly(Polynomial p)    //输出多项式
{
	Polynomial ptr;
	ptr = p;
	if (!ptr)
		printf("0\n");
	while (ptr->next)
	{
		printf("%dx^%d + ", ptr->coefficient, ptr->expon);
		ptr = ptr->next;
	}
	printf("%dx^%d\n", ptr->coefficient, ptr->expon);
}

int main()
{
	Polynomial p1, p2, result;
	p1 = ReadPoly();
	p2 = ReadPoly();
	result = Mult(p1, p2);
	printf("多项式1为：\n");
	PrintPoly(p1);
	printf("多项式2为：\n");
	PrintPoly(p2);
	printf("两式相乘结果为：\n");
	PrintPoly(result);
	return 0;
}
