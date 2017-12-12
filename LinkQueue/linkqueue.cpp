#include<stdio.h>
#include<stdlib.h>
#include "linkqueue.h"


Status InitQueue (LinkQueue &Q){
	//创建一个空的队列
	//头指针，尾指针
	QNode *head = (QNode *)malloc(sizeof(QNode));
	head->data=0;
	head->next=NULL;
	QNode *tail = head;
	Q.head=head;
	Q.tail=tail;
	return OK;
}
Status EnQueue(LinkQueue &Q, QElemType e){
	QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode));
	if(newNode==NULL){
		return OVERFLOW;
	}
	newNode->data=e;
	newNode->next=NULL;
	Q.tail->next=newNode;
	Q.tail=newNode;
	Q.head->data++;
	return OK;
}
Status DeQueue(LinkQueue &Q, QElemType &e){
	//判断队列是否为空
	if(Q.tail==Q.head){
		return ERROR;
	}
	QNode *p = Q.head->next;
	e=p->data;
	Q.head->next=p->next;
	if(Q.tail==p){
		Q.tail=Q.head;
	}
	free(p);
	Q.head->data--;
	return OK;
}
int QueueLength(LinkQueue Q){
	return Q.head->data;
}

Status QueueTraverse(LinkQueue Q, Status (*visit)(QElemType &e)){
	QNode *p = Q.head->next;
	while(p!=NULL){
		visit(p->data);
		p=p->next;
	}
	return OK;
}

Status visit_display(QElemType &e){
	printf("%d ",e);
	return OK;
}

Status GetHead(LinkQueue Q, QElemType &e){
	//判断队列是否为空
	if(Q.head==Q.tail){
		return ERROR;
	}
	e=Q.head->next->data;
	return OK;
}

void verifyQueue(){
	LinkQueue q;
	InitQueue(q);
	EnQueue(q,1);
	EnQueue(q,2);
	EnQueue(q,3);
	EnQueue(q,4);
	printf("个数:%d\n",QueueLength(q));
	QElemType e;
	DeQueue(q,e);
	DeQueue(q,e);
	DeQueue(q,e);
	GetHead(q,e);
	printf("队列头%d\n",e);
	printf("个数:%d\n",QueueLength(q));
	QueueTraverse(q,&visit_display);
}
Status QueueEmpty(LinkQueue Q){
	if(Q.head==Q.tail){
		return OK;
	}
	return ERROR;
}
void main(){
	verifyQueue();
}