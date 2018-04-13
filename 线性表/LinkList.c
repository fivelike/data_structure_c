#include <stdio.h> 
#include <stdlib.h>
#include "status.h"

typedef int ElemType;

//线性表的单链表存储结构
 
typedef struct LNode{
	ElemType data;
	struct LNode* next;
}LNode ,*LinkList;

//单链表的读取
Status GetElem(LinkList L,int i,ElemType *e){
	int j = 1;
	LinkList p;
	p=L->next;
	while(p && j<i){
		p=p->next;
		j++;
	}
	if(!p || j>i){
		printf("第 %d 个元素不存在",i);
		return ERROR;
	}
	*e = p->data;
	return OK;
} 

//单链表的插入 
Status ListInsert(LinkList *L,int i,ElemType e){
	int j =1;
	LinkList p,s;
	p=*L;
	while(p && j<i){
		p=p->next;
		j++;
	}
	if(!p || j>i){
		printf("第 %d 个元素不存在",i);
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data=e;
	s->next = p->next;
	p->next = s;
	return OK;
}

//单链表的删除
Status ListDelete(LinkList *L,int i,ElemType *e){
	int j=1;
	LinkList p,q;
	p=*L;
	while(p->next && j<i){
		p=p->next;
		j++;
	}
	if(!(p->next) || j>i){
		printf("第%d个元素不存在\n",i);
		return ERROR;
	}
	q=p->next;
	p->next=q->next;
	*e=q->data;
	free(q);
	return OK;
}
 
//头插法，建立带表头结点的单链线性表L
void CreateListHead(LinkList *L,int n){
	LinkList p; 
	*L = (LinkList)malloc(sizeof(LNode)); 
	(*L)->next = NULL; //先建立一个带头结点的单链表
	for(int i=n;i>0;i--){
		p = (LinkList)malloc(sizeof(LNode)); //生成新结点
		scanf("%d",&p->data);
		p->next = (*L)->next;
		(*L)->next = p; 
	}
} 

//尾插法
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

//单链表的整张删除
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

//输出链表
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
	printf(" 测试获取 第3个元素：%d\n",e);
	
	ListInsert(&L,3,10);
	printf(" 测试插入10 在第3个元素前：%d\n",e);
	PrintList(L);
	
	ListDelete(&L,4,&e);
	printf(" 测试删除 第4个元素：%d\n",e);
	PrintList(L);
	
	
	CreateListTail(&L,10);
	PrintList(L);
	
	int clearstatus = ClearList(&L);
	printf("清空表状态：%d\n",clearstatus);
	PrintList(L);
	
	
}
