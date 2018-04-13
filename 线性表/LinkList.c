#include <stdio.h> 
#include <stdlib.h>
#include "status.h"

typedef int ElemType;

//���Ա�ĵ�����洢�ṹ
 
typedef struct LNode{
	ElemType data;
	struct LNode* next;
}LNode ,*LinkList;

//������Ķ�ȡ
Status GetElem(LinkList L,int i,ElemType *e){
	int j = 1;
	LinkList p;
	p=L->next;
	while(p && j<i){
		p=p->next;
		j++;
	}
	if(!p || j>i){
		printf("�� %d ��Ԫ�ز�����",i);
		return ERROR;
	}
	*e = p->data;
	return OK;
} 

//������Ĳ��� 
Status ListInsert(LinkList *L,int i,ElemType e){
	int j =1;
	LinkList p,s;
	p=*L;
	while(p && j<i){
		p=p->next;
		j++;
	}
	if(!p || j>i){
		printf("�� %d ��Ԫ�ز�����",i);
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data=e;
	s->next = p->next;
	p->next = s;
	return OK;
}

//�������ɾ��
Status ListDelete(LinkList *L,int i,ElemType *e){
	int j=1;
	LinkList p,q;
	p=*L;
	while(p->next && j<i){
		p=p->next;
		j++;
	}
	if(!(p->next) || j>i){
		printf("��%d��Ԫ�ز�����\n",i);
		return ERROR;
	}
	q=p->next;
	p->next=q->next;
	*e=q->data;
	free(q);
	return OK;
}
 
//ͷ�巨����������ͷ���ĵ������Ա�L
void CreateListHead(LinkList *L,int n){
	LinkList p; 
	*L = (LinkList)malloc(sizeof(LNode)); 
	(*L)->next = NULL; //�Ƚ���һ����ͷ���ĵ�����
	for(int i=n;i>0;i--){
		p = (LinkList)malloc(sizeof(LNode)); //�����½��
		scanf("%d",&p->data);
		p->next = (*L)->next;
		(*L)->next = p; 
	}
} 

//β�巨
void CreateListTail(LinkList *L,int n){
	LinkList p,r;
	*L =(LinkList)malloc(sizeof(LNode));
	r=*L;
	for(int i=0;i<n;i++){
		p=(LNode *)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		r->next=p;
		r=p;
	}
	r->next=NULL;
}

//�����������ɾ��
Status ClearList(LinkList *L){
	LinkList p,q;
	p=(*L)->next;
	while(p){
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;
	return OK;
} 

//�������
void PrintList(LinkList L){
	LinkList p;
	p=L;
	while(p->next){
		printf("%d ",p->next->data);
		p = p->next; 
	}
	
	printf("\n");
} 

int main(){
	LinkList L;
	CreateListHead(&L,5);
	PrintList(L);
	
	ElemType e = 0; 
	GetElem(L,3,&e);
	printf(" ���Ի�ȡ ��3��Ԫ�أ�%d\n",e);
	
	ListInsert(&L,3,10);
	printf(" ���Բ���10 �ڵ�3��Ԫ��ǰ��%d\n",e);
	PrintList(L);
	
	ListDelete(&L,4,&e);
	printf(" ����ɾ�� ��4��Ԫ�أ�%d\n",e);
	PrintList(L);
	
	
	CreateListTail(&L,10);
	PrintList(L);
	
	int clearstatus = ClearList(&L);
	printf("��ձ�״̬��%d\n",clearstatus);
	PrintList(L);
	
	
}
