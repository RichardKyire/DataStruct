#include<stdio.h>
#include<stdlib.h>
#include "seqqueue.h"
Status InitQueue(SeqQueue &Q){
	Q.base = (QElemType *)malloc(MAXSIZE*sizeof(QElemType));
	if(Q.base==NULL){
		return OVERFLOW;
	}
	Q.contentSize=MAXSIZE;
	Q.length=0;
	Q.head=Q.tail=0;
	return OK;
}
Status EnQueue(SeqQueue &Q, QElemType e){
	//判断队列是否满
	printf("准备插入%d\n",e);
	if((Q.tail+1)%Q.contentSize==Q.head){//空出一个位置这样与判断队列是否为空  区分开来
		return ERROR;

	}
	*(Q.base+Q.tail) = e;
	printf("%d赋值给下标为%d\n",e,Q.tail);
	Q.tail=(Q.tail+1)%Q.contentSize;
//	printf("当前尾指针是%d\n",Q.tail);
	Q.length++;
//	printf("当前队列长度是%d\n",Q.length);
	return OK;
}
Status DeQueue(SeqQueue &Q, QElemType &e){
	//判断队列是否为空
	if(Q.tail==Q.head){
		return ERROR;
	}
	e=*(Q.base+Q.head);
	Q.head=(Q.head+1)%Q.contentSize;
	printf("%d出列\n",e);
	return OK;
}
Status QueueTraverse(SeqQueue Q, Status (*visit)(QElemType &e)){
	int h=Q.head;
	printf("头指针是%d\n",h);
	while(h!=Q.tail){
		visit(*(Q.base+h));
		h=(h+1)%Q.contentSize;
	}
	return OK;
}
Status VisitElemType(QElemType &e){
	printf("%d ",e);
	return OK;
}
void main(){
	printf("ddd\n");
	SeqQueue q ;
	InitQueue(q);
	EnQueue(q,1);
	EnQueue(q,2);
	EnQueue(q,3);
	EnQueue(q,4);
	EnQueue(q,5);
	EnQueue(q,6);
	QElemType e;
	DeQueue(q,e);
//	DeQueue(q,e);
	EnQueue(q,7);
	EnQueue(q,8);
	EnQueue(q,9);
	EnQueue(q,10);
	EnQueue(q,11);
	QueueTraverse(q,&VisitElemType);
	printf("--\n");
	int i=0;
	for(i;i<10;i++){
		printf("%d ",q.base[i]);
	}
}