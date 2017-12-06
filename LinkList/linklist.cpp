#include<stdio.h>
#include<stdlib.h>
#include "linklist.h"

void InitList_L(struct LNode * &L){
	L=(struct LNode *)malloc(sizeof(LNode));
	L->next=NULL;
}
Status ListInsert_L(struct LNode * &L, int i, ElemType e){
	struct LNode *p = L;//ָ��ͷָ��Ԫ��
	int k=0;
	while(p&&k<i-1){
		p=p->next;
		k++;
	}
	if(!p||k>i-1){
		return ERROR;
	}
	struct LNode *newNode = (struct LNode*)malloc(sizeof(LNode));
	if(newNode==NULL){
		return ERROR;
	}
	newNode->data=e;
	newNode->next=p->next;
	p->next=newNode;
	return OK;

}

Status ListDelete_L(struct LNode * &L, int i, ElemType &e){//�������Ҫɾ����һ��Ԫ����α�֤��������Ҫ��ͷָ�뿪ʼ������
	
	struct LNode *p=L;//ָ��ͷָ��
	int k=0;
	while(p&&k<i-1){
		p=p->next;
		k++;
	}
	if(!p||k>i-1){//Ҫ�жϵ�i��Ԫ���Ƿ�Ϊ��
		return ERROR;
	}
	struct LNode *q=p->next;//qָ���i��Ԫ��
	p->next=q->next;
	e=q->data;
	q->next=NULL;
	free(q);
	return OK;

}
Status visit_display_L(struct LNode * &L){
	printf("%d ",L->data);
	return OK;
}

Status ListTraverse_L(struct LNode * &L, Status (*visit)(struct LNode * &)){
	struct LNode *p=L->next;//ָ���һ��Ԫ��
	while(p!=NULL&&visit(p)){
		p=p->next;
	}
	return OK;
}

Status GetElem_L(struct LNode * &L, int i, ElemType &e){
	struct LNode *p=L->next;
	int k=1;
	while(p!=NULL&&k<i){
		p=p->next;
		k++;
	}
	if(!p||k>i){
		return ERROR;
	}
	e=p->data;
	return OK;

}

void MergeList_L(struct LNode * &La, struct LNode * &Lb, struct LNode * &Lc){
	struct LNode *pa,*pb,*pc;
	pc=Lc=La;
	pa=La->next;
	pb=Lb->next;
	while(pa!=NULL&&pb!=NULL){
		ElemType elemA=pa->data;
		ElemType elemB=pb->data;
		if(elemA<elemB){
//			printf("elemAС��elemB\n");
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}else{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	}
	if(pa){
		pc->next=pa;
	}
	if(pb){
//		printf("ָ��ʣ���pb");
		pc->next=pb;
	}
}

void main(){
	struct LNode *list;
	InitList_L(list);
	ListInsert_L(list,1,3);
	ListInsert_L(list,2,5);
	ListInsert_L(list,3,7);
	ElemType e;
	GetElem_L(list,1,e);
	printf("\n��һ��Ԫ�أ�%d\n",e);
//	printf("ɾ����һ��Ԫ��\n");
//	ListDelete_L(list,1,e);
	ListTraverse_L(list,&visit_display_L);

	struct LNode *listB;
	InitList_L(listB);
	ListInsert_L(listB,1,2);
	ListInsert_L(listB,2,4);
	ListInsert_L(listB,3,6);
	ListInsert_L(listB,4,8);
	printf("\n���listB:");
	ListTraverse_L(listB,&visit_display_L);
	struct LNode *listC;
	InitList_L(listC);
	MergeList_L(list,listB,listC);
	printf("\n���listC:");
	ListTraverse_L(listC,&visit_display_L);

}