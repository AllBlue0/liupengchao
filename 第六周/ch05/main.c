#include<stdio.h>
using namespace std;
void greedMoney(int m[],int k,int n){
	int i;
	for( i=0;i<k;i++){
		while(n>=m[i]){
			printf("%d",m[i]);
			n=n-m[i];
		}
	}
	printf("\n");
}
/* 
*  m[]:存放可供找零的面值，降序排列  
*   k:可供找零的面值种类数  
*   n:需要找零数  
*/ 
int main(){
	int money[]={20,10,5,1};
	int k;
	k=sizeof(money)/sizeof(money[0]);
	greedMoney(money,k,25);
    getchar();
}
