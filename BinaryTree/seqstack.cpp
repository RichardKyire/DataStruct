#include<stdio.h>
#include<stdlib.h>
#include "bitnode.h"
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
	printf("%d ",e);
	return OK;
}

Status Pop(SeqStack &S, SElemType &e){
	//需判断是否是空栈
	if(S.base==S.top){
//		e=NULL;
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

Status StackEmpty(SeqStack S){
	if(S.base==NULL){
		return ERROR;
	}
	if(S.base==S.top){
		return TRUE;
	}
	return FALSE;
}





void move(char x,int n,char z){
	printf("将编号为%d的盘子从%c移动到%c\n",n,x,z);
}

void hanoi(int n,char x,char y,char z){

	if(n==1){
		move(x,1,z);//将编号为1的盘子从x移动到z
	}else{
		hanoi(n-1,x,z,y);//将n-1个盘子从x移动到y,z作为辅助塔
		move(x,n,z);
		hanoi(n-1,y,x,z);//将n-1个盘子从y移动到z,x作为辅助塔
	}

}
