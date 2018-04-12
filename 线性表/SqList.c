#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "status.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;
typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

//构造一个空的线性表
Status InitList_Sq(SqList *L){
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem) exit(OVERFLOW); //储存分配失败
	L->length=0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
} 

//在顺序线性表L中第i个位置之前插入新的元素e
Status ListInsert_Sq(SqList *L,int i,ElemType e){
	//i的合法值 1<=i<=ListLength_Sq(L) + 1
	if(i<1 || i>(L->length+1)) {
		printf("i值不合法\n");
		return ERROR; //i值不合法 
	}
	if(L->length >= L->listsize){ //当前存储空间已满，增加分配 
		ElemType *newbase = (ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);
		L->elem = newbase;
		L->listsize += LISTINCREMENT;
	} 
	ElemType *q = &(L->elem[i-1]);  //q为插入位置
	for(ElemType* p=&(L->elem[L->length-1]);p>=q;p--){
		*(p+1)=*p; // 插入位置及以后的元素右移
	} 	
	*q = e;
//	printf("在第 %d 个元素前插入：%d\n",i,*q);
	L->length++;
	return OK;  
} 

//在顺序线性表L中删除第i个元素，并用e返回其值
Status ListDelete_Sq(SqList* L,int i,ElemType* e){
	//i的合法值为1<=i<=ListLength_Sq(L)
	if(i<1 || i>L->length){
		printf("i值不合法\n");
		return ERROR; //i值不合法 
	}
	ElemType* p = &(L->elem[i-1]);
	*e = *p;
	ElemType* q = L->elem+L->length-1;
	for(++p;p<=q;p++) *(p-1)=*p;
	L->length--;
	return OK;
} 

//在顺序线性表L中查找第1个值与e满足compare()的元素的位序
//若找到，返回其在L中的位序，否则返回0 
int LocateElem_Sq(SqList L,ElemType e, int (*compare)(ElemType,ElemType)){
	int i = 1;
	ElemType* p = L.elem;
	while(i<=L.length && !(*compare)(*p++,e)) i++;
	if(i<=L.length) return i;
	else return 0;
} 

int compare(ElemType a,ElemType b){
	if(a==b) return 1;
	else return 0;
}

//已知顺序线性表La和Lb的元素按值非递减排列
//并归La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
void MergeList_Sq(SqList La,SqList Lb,SqList *Lc){
	ElemType* pa = La.elem; ElemType* pb = Lb.elem;
	Lc->listsize = Lc->length = La.length+Lb.length;
	ElemType* pc = Lc->elem = (ElemType*)malloc(Lc->listsize*sizeof(ElemType));
	if(!pc) exit(OVERFLOW);
	ElemType* pa_last = pa+La.length -1;
	ElemType* pb_last = pb+Lb.length -1;
	while(pa<=pa_last && pb<=pb_last){
		if(*pa<=*pb) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while(pa<=pa_last) *pc++ = *pa++;
	while(pb<=pb_last) *pc++ = *pb++;
} 

int main(){
//	SqList L;
//	InitList_Sq(&L);
//	ListInsert_Sq(&L,1,100);
//	ListInsert_Sq(&L,2,200);
//	ListInsert_Sq(&L,1,300);
//	ListInsert_Sq(&L,2,10);
//	for(int i=0;i<L.length;i++){
//		printf("%d ",*(L.elem+i));
//	}
//	printf("\n");
	
	//测试删除元素 
//	ElemType e;
//	ListDelete_Sq(&L,3,&e);
//	printf("%d\n",e);
//	for(int i=0;i<L.length;i++){
//		printf("%d ",*(L.elem+i));
//	}
	
	//测试搜索 
//	int(* p)(ElemType,ElemType) = &compare;
//	printf("位序：%d\n",LocateElem_Sq(L,200,p));

	
	//测试并归 
	SqList La,Lb,Lc;
	InitList_Sq(&La);
	InitList_Sq(&Lb);
	ListInsert_Sq(&La,1,100);
	ListInsert_Sq(&La,2,200);
	ListInsert_Sq(&La,3,300);
	ListInsert_Sq(&La,4,400);
	
	ListInsert_Sq(&Lb,1,150);
	ListInsert_Sq(&Lb,2,250);
	ListInsert_Sq(&Lb,3,450);
	ListInsert_Sq(&Lb,4,500);
	ListInsert_Sq(&Lb,5,550);
	ListInsert_Sq(&Lb,6,600);
	
	MergeList_Sq(La,Lb,&Lc);
	
	for(int i=0;i<La.length;i++){
		printf("%d ",*(La.elem+i));
	}
	printf("\n");
	for(int i=0;i<Lb.length;i++){
		printf("%d ",*(Lb.elem+i));
	}
	printf("\n");
	for(int i=0;i<Lc.length;i++){
		printf("%d ",*(Lc.elem+i));
	}
	printf("\n");
	
	return 0;
}
