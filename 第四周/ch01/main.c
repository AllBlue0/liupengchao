#include<stdio.h>
#define N 10
void swap(int num[],int i,int j)//交换结点
{
	int temp;
	temp=num[i];
	num[i]=num[j];
	num[j]=temp;
}
void Heapify(int num[],int len,int k)//最大堆调整
{
	if(k<len)
	{
		int max=k;//根结点
		int s1=2*k+1;//左子节点
		int s2=2*k+2;//右子结点
		//找出最大结点
		if(num[s1]>num[max]&&s1<len)
			max=s1;
		if(num[s2]>num[max]&&s2<len)
			max=s2;
		//交换最大子节点到根结点并做递归
		if(max!=k)
		{
			swap(num,max,k);
			Heapify(num,len,max);
		}
	}
}
void CreateHeap(int num[],int len)//创建最大堆
{
	int last=len-1;				//最后一个子结点位置
	int parent=(last-1)/2;		//最后一个子结点的父结点
	for(int i=parent;i>=0;i--)	
	{
		Heapify(num,len,i);		//从最后一个父结点开始做最大堆调整
	}
}
void HeapSort(int num[],int len)//堆排序
{

	CreateHeap(num,len);		//创建最大堆

	for(int i=len-1;i>=0;i--)	//依次将最大堆的根结点（最大值）取出
	{
		//将最大堆的根（最大值）换到最后
		swap(num,i,0);			
		//除去最大值,对交换后的二叉树做最大堆调整，使二叉树根结点始终为最大值	
		Heapify(num,i,0);		
	}
}
int main()
{
	int num[N]={6,5,8,4,1,3,9,7,2,0};
	HeapSort(num,N);
	for(int i=0;i<N;i++)
		printf("%d ",num[i]);
	printf("\n");
	getchar();
	return 0;
}

