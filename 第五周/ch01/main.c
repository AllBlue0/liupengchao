#include<stdio.h>
#define len 9
typedef int ElementType;
void  InsertionSort(ElementType A[],int N)
{
    int j,P;
    ElementType Tmp;
    for(P = 1;P < N;P++)
    {
        Tmp = A[P];
        for (j = P;j > 0 && A[j - 1] >= Tmp; j--)
        {
            A[j] = A[j - 1];
        }
        A[j] = Tmp;
    }
}
int main()
{
    ElementType Array[] = {3,1,4,1,5,9,2,6,5};
	int i;
    	printf("未排序前：\n"); 
	for(i=0;i<len;i++)
	{
		printf("%d  ", Array[i]);
	}
	printf("\n经过直接插入排序后：\n"); 
	InsertionSort(Array,len);
	for(i=0;i<len;i++)
	{
		printf("%d  ", Array[i]);
	}
    getchar();
}
