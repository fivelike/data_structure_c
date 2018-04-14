#include <stdio.h>
#include "status.h"

#define MAXSIZE 1000

typedef int ElemType;
typedef struct{
	ElemType data;
	int cur;
}Component,StaticLinkList[MAXSIZE]; //�α꣨Cursor��,0������ָ��

//��һά����space�и���������һ��������
Status InitList(StaticLinkList space){
	for(int i=0;i<MAXSIZE-1;i++){
		space[i].cur=i+1;
	}
	space[MAXSIZE-1].cur=0;
	return OK;
}

//�����ÿռ�����ǿգ��򷵻ط���Ľ���±꣬���򷵻�0
int Malloc_SLL(StaticLinkList space){
	int i = space[0].cur;
	if(space[0].cur) space[0].cur=space[i].cur;
	return i;
}

//���±�Ϊk�Ŀ��н����յ���������
void Free_SSL(StaticLinkList space,int k){
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//��̬����L�Ѵ��ڣ�����L�е����ݸ���
int ListLength(StaticLinkList L){
	int j=0;
	int i=L[MAXSIZE-1].cur;
	while(i){
		i=L[i].cur;
		j++;
	}
	return j;
} 

//��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e
Status ListInsert(StaticLinkList L,int i,ElemType e){
	int j,k;
	k=MAXSIZE-1;
	if(i<1 || i>ListLength(L)+1) return 0;
	j=Malloc_SLL(L);
	if(j){
		L[j].data=e;
		for(int l=1;l<=i-1;l++){
			k=L[k].cur; //kΪ��i��Ԫ��֮ǰ��λ�� 
		}
		L[j].cur= L[k].cur;
		L[k].cur=j;
		return OK;
	}
	return ERROR;
} 

//ɾ����L�еĵ�i������Ԫ��e
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


//��������е�����Ԫ��
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


