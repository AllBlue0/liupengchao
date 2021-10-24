#ifndef _BINQUEUE_H_
#define _BINQUEUE_H_
#define MaxTrees 100
#define Capacity 1000

struct BinNode;
struct Collection;
typedef int ElementType;
typedef struct BinNode *Position;
typedef Position BinTree;
typedef struct Collection *BinQueue;

#endif
#include<stdio.h>
#include<stdlib.h>

struct BinNode
{
    ElementType Element;
    Position LeftChild;
    Position NextSibling;
};
struct Collection
{
    int CurrentSize;
    BinTree TheTrees[MaxTrees];
};
BinTree CombineTrees(BinTree T1, BinTree T2)
{
    if (T1->Element > T2->Element)
        return CombineTrees(T2, T1);
    T2->NextSibling = T1->LeftChild;
    T1->LeftChild = T2;
    return T1;
}
BinQueue Merge(BinQueue H1, BinQueue H2)
{
    BinTree T1, T2, Carry = NULL;
    if (H1->CurrentSize + H2->CurrentSize > Capacity)
    {
        printf("ERROR!\n");
        return NULL;
    }
    H1->CurrentSize += H2->CurrentSize;
    for (int i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2)
    {
        T1 = H1->TheTrees[i];
        T2 = H2->TheTrees[i];
        switch (!!T1 + 2 * !!T2 + 4 * !!Carry)
        {
        case 0:
        case 1:
            break;
        case 2:
            H1->TheTrees[i] = T2;
            break;
        case 4:
            H1->TheTrees[i] = Carry;
            break;
        case 3:
            Carry = CombineTrees(T1, T2);
            H1->TheTrees[i] = H2->TheTrees[i] = NULL;
            break;
        case 5:
            Carry = CombineTrees(T1, Carry);
            H1->TheTrees[i]=NULL;
            break;
        case 6:
            Carry = CombineTrees(T2, Carry);
            H2->TheTrees[i] = NULL;
            break;
        case 7:
            H1->TheTrees[i] = Carry;
            Carry = CombineTrees(T1, T2);
            H2->TheTrees[i] = NULL;
            break;
        }
    }
    return H1;
}
int IsEmpty(BinQueue H)
{
    return H->CurrentSize == 0;
}
BinQueue Initialize()
{
    BinQueue H = (BinQueue)malloc(sizeof(Collection));
    H->CurrentSize = 0;
    return H;
}
ElementType DeleteMin(BinQueue H)
{
    int i, j;
    int MinTree;
    BinQueue DeletedQueue;
    Position DeletedTree, OldRoot;
    ElementType MinItem;
    if (IsEmpty(H))
    {
        printf("ERROR!\n");
        return 0;
    }
    MinItem = INT_MIN;
    for (i = 0; i < MaxTrees; i++)
    {
        if (H->TheTrees[i] && H->TheTrees[i]->Element < MinItem)
        {
            MinItem = H->TheTrees[i]->Element;
            MinTree = i;
        }
    }
    DeletedTree = H->TheTrees[MinTree];
    OldRoot = DeletedTree;
    DeletedTree = DeletedTree->LeftChild;
    free(OldRoot);
    DeletedQueue = Initialize();
    DeletedQueue->CurrentSize = (1 << MinTree) - 1;
    for (j = MinTree - 1; j >= 0; j--)
    {
        DeletedQueue->TheTrees[j] = DeletedTree;
        DeletedTree = DeletedTree->NextSibling;
        DeletedQueue->TheTrees[j]->NextSibling = NULL;
    }
    H->TheTrees[MinTree] = NULL;
    H->CurrentSize -= DeletedQueue->CurrentSize + 1;
    Merge(H, DeletedQueue);
    return MinItem;
}
