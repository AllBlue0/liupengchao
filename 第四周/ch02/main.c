//  头文件 
#include<stdio.h>
#include<stdlib.h>
#define Insert(X, H) (H = Insert1((X),H))
typedef struct TreeNode* LeftTree;
typedef int ElementType;
LeftTree Initialize(void);
LeftTree Merge(LeftTree H1, LeftTree H2);
int IsEmpty(LeftTree H);
LeftTree Merge1(LeftTree H1, LeftTree H2);
LeftTree DeleteMin1(LeftTree H);
LeftTree Insert1(ElementType X,LeftTree H);	
LeftTree CreateHeap();
void PreTrv(LeftTree H);
void SwapChild(LeftTree H);
struct TreeNode{
	ElementType Element;
	LeftTree Left;
	LeftTree Right;
	int Npl;
};
int main()
	{
		LeftTree H1, H2;
		LeftTree H; 
		
		printf("递归建树:\n\n");
		H1 = CreateHeap();
		H2 = CreateHeap();
		H = Merge(H1, H2);
		
		printf("\n左式堆合并后:\n\n");
		PreTrv(H);
		printf("\n\n"); 
		
		printf("插入数据后:\n\n");
		H = Insert1(1, H);
		PreTrv(H);
		
		H = DeleteMin1(H);
		printf("\n\n删除最小元素后: \n\n");
		PreTrv(H);
		
		return 0;
	}
void PreTrv(LeftTree H)//  前序遍历 
	{
		if(H != NULL){
			printf("%d ",H->Element);
			PreTrv(H->Left);
			PreTrv(H->Right);
		}	
	}	
LeftTree CreateHeap()  //递归建堆 
	{
		LeftTree H;
		int X;
		scanf("%d",&X);
		if(X == 0)
			H = NULL;
		else{
			H = (LeftTree)malloc(sizeof(struct TreeNode));
			H->Element = X;
			H->Left = CreateHeap();
			H->Right = CreateHeap();	
		}
			
		return H;	
	}	
    LeftTree Merge(LeftTree H1, LeftTree H2)  //合并驱动程序 
	{
		if(H1 == NULL)
			return H2;
		if(H2 == NULL)
			return H1;
		if(H1->Element < H2->Element){
			return Merge1(H1, H2);
		}
		else
			return Merge1(H2, H1);			
	}	
LeftTree Merge1(LeftTree H1, LeftTree H2)  //合并实际例程 
	{
		if(H1->Left == NULL)
			H1->Left = H2;
		else{
			H1->Right = Merge(H1->Right, H2);
			if(H1->Left->Npl < H1->Right->Npl ) //判断是否满足左式堆 
				SwapChild(H1);
			H1->Npl = H1->Right->Npl+1;	
		}	
		return H1;	
	}	
    void SwapChild(LeftTree H) // 交换左右子树 
	{
		LeftTree Tmp;
		Tmp = H->Left;
		H->Left = H->Right;
		H->Right = Tmp;	
	}	
    LeftTree Insert1(ElementType X,LeftTree H)  //插入就是特殊的 合并操作	
	{
		LeftTree SingleNode;
		SingleNode = (LeftTree)malloc(sizeof(struct TreeNode));
		if(SingleNode == NULL)
			{
				printf("Error");
				return NULL;
			}
		SingleNode->Element = X;
		SingleNode->Left = SingleNode->Right = NULL;
		H = Merge(SingleNode, H);
		return H;	
	}
    LeftTree DeleteMin1(LeftTree H)//删除最小节点后 其左右子树的 合并 
	{
		LeftTree L, R;
		if(IsEmpty(H)){
			printf("Error");
			return NULL;
		}
		L = H->Left;
		R = H->Right;
		free(H);
		return Merge(L, R);
			
	}	
    int IsEmpty(LeftTree H)
	{
		return H->Left == NULL && H->Right == NULL;
	}
