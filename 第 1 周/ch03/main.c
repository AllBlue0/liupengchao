typedef int PtrToNode ;
typedef PtrToNode List ;
typedef PtrToNode Position ;
 
//L为表头
//初始化
void InitializeCursorSpace(void)
 
//操作函数声明
List MakeEmpty(List L) ;
int IsEmpty(List L) ;
int IsLast(Position P, List L) ;
Positiom Find(ElementType X, List L) ;
void Delete(ElementType X, List L) ;
Position FindPrevios(ElementType X, List L) ;
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L) ;
Position First(List L) ;
Position Advance(Position P) ;
ElementType Retrieve(Position P) ;
 
struct Node
{
ElemenType Element ;
Position Next ;
}
 
struct Node CursorSpace[Spacesize] ;
Position CursorAlloc(void)//游标法中的malloc和free函数
{
Position P ;
P = CursorSpace[0].Next ;
CursorSpace[0].Next = CursorSpace[P].Next ;
 
return P ;
}
 
void CursorFree(Position P)
{
CursorSpace[P].Next = CursorSpace[0].Next ;
CursorSpace[0].Next = P ;
}
void InitializeCursorSpace(Void)//初始化
{
int i ;
for(i = 0;i < SpaceSize; i++)
{
CursorSpace[i].Next = i + 1; 
}
CursorSpace[i] = 0 ;
}
//判断链表是否为空和是否为尾
int IsEmpty(List L) //L为表头，CursorSpace数组为全局变量
{
return CursorSpace[L].Next == 0 ;
}
 
int IsLast(Position P)
{
return CursorSpace[P].Next == 0;
}
//Find函数 游标实现
Position Find(Element X,List L)
{
Position P ;
P = CursorSpace[L].Next ;
while(P && CursorSpace[P] != X)
P = CursorSpace[P].Next ;
 
return P ;
}
//Delete函数 游标实现
void Delete(ElementType X, List L)
{
Position P, TmpCell ;
P = FindPrevious(X,L) ;
if(!IsLast(P))
{
TmpCell = CursorSpace[P].Next ;
CursorSpace[P].Next = CursorSpace[TmpCell].Next ;
CursorFree(TmpCell) ;
}
}
//Insert函数 游标实现
void Insert(Element X, List L, Position P)
{
Position TmpCell ;
TmpCell = CursorAlloc() ;
if(TmpCell == 0)
{
printf("链表数组空间不足") ；
}
CursorCell[TmpCell].Element = X ;
CursorCell[TmpCell].Next = CursorSpace[P].Next ;
CursorSpace[P].Next = TmpCell ;
}
