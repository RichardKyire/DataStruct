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
	display_path(e);
	return OK;
}

Status Pop(SeqStack &S, SElemType &e){
	//���ж��Ƿ��ǿ�ջ
	if(S.base==S.top){
		printf("��ջ\n");
		return ERROR;
	}

	e=*(--S.top);
//	printf("ջ��Ԫ��{%d,%d}��ջ\n",e.seat.row,e.seat.col);
	return OK;
}

Status GetTop(SeqStack S, SElemType &e){
	if(S.base==S.top){
		return ERROR;
	}
	SElemType *p = S.top;
//	printf("{%d,%d}\n",p->seat.row,p->seat.row);
	e=*(S.top-1);
//	printf("���ջ��Ԫ��{%d,%d}\n",e.seat.row,e.seat.col);
	return OK;
}

Status StackEmpty(SeqStack S){
	if(S.base==NULL){
		return ERROR;
	}
	if(S.base==S.top){
		return TRUE;
	}
	return FALSE;
}

