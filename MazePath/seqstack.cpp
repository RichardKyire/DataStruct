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
	//如果栈满了，扩栈
	//如何判断栈满？
	if(S.top-S.base>=S.stackSize){//理解两个相同类型的指针相减的含义
		S.base=(SElemType *)realloc(S.base,(S.stackSize+STACKINCREMENT)*sizeof(SElemType));
		if(S.base==NULL){//重新分配空间失败
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
	//需判断是否是空栈
	if(S.base==S.top){
		printf("空栈\n");
		return ERROR;
	}

	e=*(--S.top);
//	printf("栈顶元素{%d,%d}出栈\n",e.seat.row,e.seat.col);
	return OK;
}

Status GetTop(SeqStack S, SElemType &e){
	if(S.base==S.top){
		return ERROR;
	}
	SElemType *p = S.top;
//	printf("{%d,%d}\n",p->seat.row,p->seat.row);
	e=*(S.top-1);
//	printf("获得栈顶元素{%d,%d}\n",e.seat.row,e.seat.col);
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

