#include<stdio.h>
#define len 9
typedef int ElementType;
void Shellsort(ElementType A[],int N)
{
    int i,j,Increment;
    int X = 7;
    ElementType Tmp;
    for(Increment = X;Increment > 0;Increment /= 2 )
        for(i = Increment;i < N;i++)
        {
            Tmp = A[i];
            for(j = i;j >= Increment;j -= Increment)
                if(Tmp < A[j - Increment])
                    A[j] = A[j - Increment];
                else
                    break;
                A[j] = Tmp;
        }
}
int main()
{
    ElementType Array[] = {9,8,7,6,5,4,3,2,1};
    int i;
    	printf("未排序前：\n"); 
	for(i=0;i<len;i++)
	{
		printf("%d  ", Array[i]);
	}
	printf("\n经过直接插入排序后：\n"); 
	Shellsort(Array,len);
	for(i=0;i<len;i++)
	{
		printf("%d  ", Array[i]);
	}
    getchar();
}
