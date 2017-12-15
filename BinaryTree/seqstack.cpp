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
	printf("�����Ϊ%d�����Ӵ�%c�ƶ���%c\n",n,x,z);
}

void hanoi(int n,char x,char y,char z){

	if(n==1){
		move(x,1,z);//�����Ϊ1�����Ӵ�x�ƶ���z
	}else{
		hanoi(n-1,x,z,y);//��n-1�����Ӵ�x�ƶ���y,z��Ϊ������
		move(x,n,z);
		hanoi(n-1,y,x,z);//��n-1�����Ӵ�y�ƶ���z,x��Ϊ������
	}

}
