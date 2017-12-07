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
	printf("%d ",e);
	return OK;
}

Status Pop(SeqStack &S, SElemType &e){
	//需判断是否是空栈
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

Status StackEmpty(SeqStack S){
	if(S.base==NULL){
		return ERROR;
	}
	if(S.base==S.top){
		return TRUE;
	}
	return FALSE;
}

Status checkBracket(char *ch){//遵从单一原则
	struct SeqStack s;
	InitStack(s);
	int i=0;
	while(*(ch+i)!='\0'){
		SElemType e;
		switch (*(ch+i)){
		case '(':
			printf("进栈\n");
			Push(s,1);
			break;
		case '[':
			Push(s,2);
			break;
		case '{':
			Push(s,3);
			break;
		case ')':		
			if(OK!=GetTop(s,e)){
				return ERROR;
			}
			if(e==1){
				Pop(s,e);
			}else{
				return ERROR;
			}
			break;
		case ']':
			if(OK!=GetTop(s,e)){
				return ERROR;
			}
			if(e==2){
				Pop(s,e);
			}else{
				return ERROR;
			}
			break;
		case '}':
			if(OK!=GetTop(s,e)){
				return ERROR;
			}
			if(e==3){
				Pop(s,e);
			}else{
				return ERROR;
			}
			break;
		default:
			break;
		}
		i++;
	}

	if (StackEmpty(s))
		return OK;
	else
		return ERROR;
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
	printf("栈顶元素：%d\n",GetTop(s,e));
	StackTraverse(s,&visit_display);
	char ch[8]={'[','(','[',']','[',']',')',']'};
	printf("括号表达式校验结果：%d\n",checkBracket(ch));
}