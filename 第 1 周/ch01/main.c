#include<stdio.h>
#include<string.h>
#define N 10	//数组长度
#define D 10	//最大位数

int GetDigit(int M, int i) //取整数M的第i位数
{
	while(i > 1)
	{
		M /= 10;
		i--;
	}
	return M % 10;
}

void RadixSort(int num[], int len)
{
	int i, j, k, l, digit;
	int allot[10][N];	//《分配数组》

	memset(allot, 0, sizeof(allot));//初始化《分配数组》

	for(i = 1; i <= D; i++)
	{
		int flag = 0;
		//分配相应位数的数据，并存入《分配数组》
		for(j = 0; j < len; j++)	
		{			
			digit = GetDigit(num[j], i);
			k = 0;
			while(allot[digit][k])
				k++;
			allot[digit][k] = num[j];
			if(digit) //判断是否达到了最高位数
				flag = 1;
		}
		if(!flag)	//如果数组每个数的第i位都为零
			break;	//即可直接退出循环

		//将《分配数组》的数据依次收集到原数组中
		l = 0; 
		for(j = 0; j < 10; j++)	
		{	
			k = 0;
			while(allot[j][k] > 0)
			{
				num[l++] = allot[j][k];
				k++;
			}
		}
		//每次分配，收集后初始化《分配数组》，用于下一位数的分配和收集
		memset(allot, 0, sizeof(allot));
	}
}

int main()
{
	int num[N] = {52, 20, 4, 10, 17, 39, 8, 300, 60, 81};

	RadixSort(num, N);

	for(int i = 0; i < N; i++)
		printf("%d ", num[i]);
	printf("\n");
	return 0;
}
