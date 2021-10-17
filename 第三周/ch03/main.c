#include<stdlib.h>
#include"hashQuad.h"
#include<stdio.h>
#include<math.h>
#include<string.h>
#define MinTableSize 5
#define N 10000
int ranintArr[N];//这么大的数组放在全局变量上，如果放在main里就是放在程序的堆上，运行时再分配。放在外面就是编译时就分配在静态数据那。
 
extern int collitionCnt;
typedef int ElementType;
typedef unsigned int Index;
typedef Index Position;
 
struct HashTbl;
typedef struct HashTbl* HashTable;
 
HashTable initializeTable(int tableSize);
void destroyTable(HashTable h);
Position find_LinearProbing(ElementType key, HashTable h);
Position find_QuadraticProbing(ElementType key, HashTable h);
Position find_DoubleHashing(ElementType key, HashTable h);
HashTable insert(ElementType key, HashTable h,int type);
HashTable rehash(HashTable h,int type);
ElementType retrive(Position p,HashTable h);
int isLegitimate(Position pos, HashTable h);
 
enum KindOfEntry { Legitimate, Empty, Deleted };
 
int collitionCnt;
 
struct HashEntry {
	ElementType element;
	enum KindOfEntry info;
};
 
typedef struct HashEntry Cell;
 
struct HashTbl {
	int tableSize;
	int hasInsertedNum;
	Cell *theCells;//数组
};
 
static Position hash(ElementType key, int tableSize) {
	return key % (tableSize);
}
 
static Position hash2(ElementType key, int tableSize) {
	return 7 - (key % 7);
}
 
static int isPrime(int num) {
	for (int i = 2; i <= sqrt(num); i++)
		if (num%i == 0)
			return 0;
	return 1;
}
static int nextPrime(int num) {
	int i = num;
	while (!isPrime(i))
		i++;
	return i;
}
 
int isLegitimate(Position pos, HashTable h) {
	return h->theCells[pos].info == Legitimate;
}
 
 
HashTable initializeTable(int tableSize) {
	HashTable h;
	int i;
	if (tableSize < MinTableSize) {
		Error("Table size too small");
		return NULL;
	}
	h = malloc(sizeof(struct HashTbl));
	if (h == NULL)
		FatalError("Out of space!!!");
	h->tableSize = nextPrime(tableSize);
	h->theCells = malloc(sizeof(Cell)*h->tableSize);
	h->hasInsertedNum = 0;
	if (h->theCells == NULL)
		FatalError("Out of space!!!");
	for (i = 0; i < h->tableSize; i++) {
		h->theCells[i].info = Empty;
	}
	return h;
}
 
void destroyTable(HashTable h) {
	free(h->theCells);
	free(h);
}
 
Position find_LinearProbing(ElementType key, HashTable h) {
	Position currentPos = hash(key, h->tableSize);
	while (h->theCells[currentPos].info != Empty && h->theCells[currentPos].element != key) {
		currentPos = (currentPos + 1) % h->tableSize;
		collitionCnt++;
	}
	return currentPos;
}
 
Position find_QuadraticProbing(ElementType key, HashTable h) {
	Position currentPos = hash(key, h->tableSize);
	int collisionNum = 0;
	while (h->theCells[currentPos].info != Empty && h->theCells[currentPos].element != key) {
		++collisionNum;
		currentPos = (currentPos + collisionNum * 2 - 1) % h->tableSize;
		collitionCnt++;
	}
	return currentPos;
}
 
Position find_DoubleHashing(ElementType key, HashTable h) {
	Position currentPos = hash(key, h->tableSize);
	int i = 0;
	while (h->theCells[currentPos].info != Empty && h->theCells[currentPos].element != key) {
		currentPos += (++i * hash2(key, h->tableSize));
		currentPos = currentPos % h->tableSize;
		collitionCnt++;
	}
	return currentPos;
}
 
HashTable insert(ElementType key, HashTable h,int type) {
	if ((double)h->hasInsertedNum / h->tableSize > 0.5)
		h = rehash(h,type);
	Position pos;
	switch (type) {
	case 1:
		pos = find_LinearProbing(key, h);
		break;
	case 2:
		pos = find_DoubleHashing(key, h);
		break;
	case 3:
		pos = find_QuadraticProbing(key, h);
		break;
	default:
		Error("insert type error");
		break;
	}
	if (h->theCells[pos].info != Legitimate) {
		h->theCells[pos].element = key;
		h->theCells[pos].info = Legitimate;
		h->hasInsertedNum++;
	}
	return h;
}
 
HashTable rehash(HashTable h,int type) {
	HashTable newH = initializeTable(h->tableSize * 2);
	for (int i = 0; i < h->tableSize; i++)
		if (h->theCells[i].info == Legitimate)
			insert(h->theCells[i].element, newH,type);
	destroyTable(h);
	return newH;
}
 
 
 
ElementType retrive(Position p, HashTable h) {
	return h->theCells[p].element;
}
 
int main() {
	for (int i = 0; i < N; i++)
		ranintArr[i] = rand();
	
	HashTable h = initializeTable(200);
	collitionCnt = 0;
	for (int i = 0; i < N; i++) {
		h = insert(ranintArr[i], h,1);
	}
	printf("LinearProbing %d\n", collitionCnt);
	destroyTable(h);
 
	 h = initializeTable(200);
	collitionCnt = 0;
	for (int i = 0; i < N; i++) {
		h = insert(ranintArr[i], h,2);
	}
	printf("QuadraticProbing %d\n", collitionCnt);
	destroyTable(h);
 
h = initializeTable(200);
	collitionCnt = 0;
	for (int i = 0; i < N; i++) {
		h = insert(ranintArr[i], h, 3);
	}
	printf("DoubleHashing %d\n", collitionCnt);
	destroyTable(h);
}
