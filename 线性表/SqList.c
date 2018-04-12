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

//����һ���յ����Ա�
Status InitList_Sq(SqList *L){
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem) exit(OVERFLOW); //�������ʧ��
	L->length=0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
} 

//��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
Status ListInsert_Sq(SqList *L,int i,ElemType e){
	//i�ĺϷ�ֵ 1<=i<=ListLength_Sq(L) + 1
	if(i<1 || i>(L->length+1)) {
		printf("iֵ���Ϸ�\n");
		return ERROR; //iֵ���Ϸ� 
	}
	if(L->length >= L->listsize){ //��ǰ�洢�ռ����������ӷ��� 
		ElemType *newbase = (ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);
		L->elem = newbase;
		L->listsize += LISTINCREMENT;
	} 
	ElemType *q = &(L->elem[i-1]);  //qΪ����λ��
	for(ElemType* p=&(L->elem[L->length-1]);p>=q;p--){
		*(p+1)=*p; // ����λ�ü��Ժ��Ԫ������
	} 	
	*q = e;
//	printf("�ڵ� %d ��Ԫ��ǰ���룺%d\n",i,*q);
	L->length++;
	return OK;  
} 

//��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
Status ListDelete_Sq(SqList* L,int i,ElemType* e){
	//i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)
	if(i<1 || i>L->length){
		printf("iֵ���Ϸ�\n");
		return ERROR; //iֵ���Ϸ� 
	}
	ElemType* p = &(L->elem[i-1]);
	*e = *p;
	ElemType* q = L->elem+L->length-1;
	for(++p;p<=q;p++) *(p-1)=*p;
	L->length--;
	return OK;
} 

//��˳�����Ա�L�в��ҵ�1��ֵ��e����compare()��Ԫ�ص�λ��
//���ҵ�����������L�е�λ�򣬷��򷵻�0 
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

//��֪˳�����Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
//����La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
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
	
	//����ɾ��Ԫ�� 
//	ElemType e;
//	ListDelete_Sq(&L,3,&e);
//	printf("%d\n",e);
//	for(int i=0;i<L.length;i++){
//		printf("%d ",*(L.elem+i));
//	}
	
	//�������� 
//	int(* p)(ElemType,ElemType) = &compare;
//	printf("λ��%d\n",LocateElem_Sq(L,200,p));

	
	//���Բ��� 
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
