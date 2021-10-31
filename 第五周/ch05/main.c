#include <stdio.h>
#define MAX 16

int pre[MAX + 1]; //寻找父节点

void Initialize(int *S);
void InitializeH(int *S);
void InitializeS(int *S);
void SetUnion(int *S, int Root1, int Root2);
void SetUnionH(int *S, int Root1, int Root2);
void SetUnionS(int *S, int Root1, int Root2);
int Find(int X, int *S); //路径压缩

int main(){
    //进行路径压缩+按高度合并
    InitializeH(pre);
    SetUnionH(pre, 15, 16);
    SetUnionH(pre, 14, 15);
    SetUnionH(pre, 13, 15);
    SetUnionH(pre, 11, 12);
    SetUnionH(pre, 10, 11);
    SetUnionH(pre, 11, 9);
    SetUnionH(pre, 11, 8);
    SetUnionH(pre, 11, 15);
    Find(14, pre);
    printf("pre[16] = %d\n", pre[16]);
    printf("pre[14] = %d\n", pre[14]);

    //进行路径压缩+按大小排序
    InitializeS(pre);
    SetUnionS(pre, 15, 16);
    SetUnion(pre, 15, 14);
    SetUnionS(pre, 13, 12);
    SetUnion(pre, 13, 11);
    SetUnionS(pre, 15, 9);
    SetUnionS(pre, 15, 13);
    Find(11, pre);
    printf("pre[11] = %d\n", pre[11]);
    printf("pre[15] = %d\n", pre[15]);
    getchar();

}


void SetUnion(int *S, int Root1, int Root2) //任意合并
{
    S[Root2] = Root1;
}

void InitializeH(int *S) //按高度合并的初始化
{
    for(int i = MAX; i > 0; i--)
        S[i] = 0;
}

void InitializeS(int *S) //按大小合并的初始化
{
    for(int i = MAX; i > 0; i--)
        S[i] = -1;
}

void SetUnionH(int *S, int Root1, int Root2) //按高度合并
{
    if(S[Root2] < S[Root1])
            S[Root1] = Root2;
    else{
        if(S[Root2] == S[Root1])
            S[Root1]--;
        S[Root2] = Root1;
    }
}

void SetUnionS(int *S, int Root1, int Root2) //按大小合并
{
        int tmp = S[Root2];
        S[Root2] = Root1;
        S[Root1] += tmp;
}

int Find(int X, int *S) //路径压缩
{
    if(S[X] <= 0)
        return X;
    else 
        return S[X] = Find(S[X], S);
}
