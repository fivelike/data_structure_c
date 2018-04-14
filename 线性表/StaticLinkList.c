#include <stdio.h>
#include "status.h"

#define MAXSIZE 1000

typedef int ElemType;
typedef struct{
	ElemType data;
	int cur;
}Component,StaticLinkList[MAXSIZE]; //游标（Cursor）,0代表无指向

//将一维数组space中各分量链成一备用链表
Status InitList(StaticLinkList space){
	for(int i=0;i<MAXSIZE-1;i++){
		space[i].cur=i+1;
	}
	space[MAXSIZE-1].cur=0;
	return OK;
}

//若备用空间链表非空，则返回分配的结点下标，否则返回0
int Malloc_SLL(StaticLinkList space){
	int i = space[0].cur;
	if(space[0].cur) space[0].cur=space[i].cur;
	return i;
}

//将下标为k的空闲结点回收到备用链表
void Free_SSL(StaticLinkList space,int k){
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//静态链表L已存在，返回L中的数据个数
int ListLength(StaticLinkList L){
	int j=0;
	int i=L[MAXSIZE-1].cur;
	while(i){
		i=L[i].cur;
		j++;
	}
	return j;
} 

//在L中第i个元素之前插入新的数据元素e
Status ListInsert(StaticLinkList L,int i,ElemType e){
	int j,k;
	k=MAXSIZE-1;
	if(i<1 || i>ListLength(L)+1) return 0;
	j=Malloc_SLL(L);
	if(j){
		L[j].data=e;
		for(int l=1;l<=i-1;l++){
			k=L[k].cur; //k为第i个元素之前的位置 
		}
		L[j].cur= L[k].cur;
		L[k].cur=j;
		return OK;
	}
	return ERROR;
} 

//删除在L中的第i个数据元素e
Status ListDelete(StaticLinkList L,int i){
	int j,k;
	if(i<1 || i>ListLength(L)) 
		return ERROR;
	k = MAXSIZE-1;
	for(j=1;j<=i-1;j++)
		k=L[k].cur;
	j=L[k].cur;
	L[k].cur=L[j].cur;
	Free_SSL(L,j);
	return OK;
} 


//输出链表中的所有元素
void PrintList(StaticLinkList L){
	int i = L[MAXSIZE-1].cur;
	while(i){
		printf("%d ",L[i].data);
		i = L[i].cur;
	}
	printf("\n");
} 

int main(){
	
	StaticLinkList space;
	InitList(space);
	ListInsert(space,1,3);
	ListInsert(space,2,4);
	ListInsert(space,1,2);
	ListInsert(space,1,1);
	ListInsert(space,5,5);
	ListInsert(space,5,6);
	PrintList(space);
	
	ListDelete(space,5);
		PrintList(space);
	return 0;
}


