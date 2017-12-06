#include<stdio.h>
#include<stdlib.h>
#include "seqstack.h"

Status InitStack(SeqStack &S){
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(S.base==NULL){
		return OVERFLOW;
	}
	S.top=S.base;
	S.stackSize=STACK_INIT_SIZE;
	return OK;
}

Status Push(SeqStack &S, SElemType e){
	//���ջ���ˣ���ջ
	//����ж�ջ����
	if(S.top-S.base>=S.stackSize){//���������ͬ���͵�ָ������ĺ���
		S.base=(SElemType *)realloc(S.base,(S.stackSize+STACKINCREMENT)*sizeof(SElemType));
		if(S.base==NULL){//���·���ռ�ʧ��
			return OVERFLOW;
		}
		S.stackSize+=STACKINCREMENT;
	}
	
	*(S.top++)=e;
	return OK;
}

Status StackTraverse(SeqStack S, Status (*visit)(SElemType)){

	while(S.base!=S.top){
		visit(*(S.base++));
	}
	return OK;
}
Status visit_display(SElemType e){
	printf("%d ",e);
	return OK;
}

Status Pop(SeqStack &S, SElemType &e){
	//���ж��Ƿ��ǿ�ջ
	if(S.base==S.top){
		return ERROR;
	}
	e=*--S.top;
	return OK;
}

Status GetTop(SeqStack S, SElemType &e){
	if(S.base==S.top){
		return ERROR;
	}
	e=*(S.top-1);
	return OK;
}
void main(){
	struct SeqStack s;
	InitStack(s);
	Push(s,1);
	Push(s,2);
	Push(s,3);
	Push(s,4);
	Push(s,5);
	Push(s,6);
	Push(s,7);
	Push(s,8);
	SElemType e;
	Pop(s,e);
	printf("%d\n",e);
	StackTraverse(s,&visit_display);
	printf("ջ��Ԫ�أ�%d\n",GetTop(s,e));
	StackTraverse(s,&visit_display);
}