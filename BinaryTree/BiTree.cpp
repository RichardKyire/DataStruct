#include<stdio.h>
#include<stdlib.h>
#include "BiTNode.h"
#include "seqstack.h"


Status CreateBiTree(BiTree &T){
	//���򴴽�������
//	printf("������һ�����ڵ㣺\n");
	TElemType e;
	scanf("%d",&e);
	if(e==-1){
		T=NULL;
		return OK;
	}
	T=(BiTree)malloc(sizeof(BiTNode));
	T->data=e;
	printf("������%d������:",T->data);
	CreateBiTree(T->lChild);
	printf("������%d���Һ���:",T->data);
	CreateBiTree(T->rChild);
	return OK;
}
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e)){
	if(T!=NULL){
		if(OK==visit(T->data)){
		if(OK==PreOrderTraverse(T->lChild,visit)){
			 return PreOrderTraverse(T->rChild,visit);
			}
		}
		return ERROR;
	}else{
		return OK;
	}
}
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e)){
	if(T!=NULL){
		if(OK==InOrderTraverse(T->lChild,visit)){
			if(OK==visit(T->data)){
				return InOrderTraverse(T->rChild,visit);
			}
		}
		return ERROR;
	}else{
		return OK;
	}
}

Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)){
	if(T!=NULL){
		if(OK==PostOrderTraverse(T->lChild,visit)){
			if(OK==PostOrderTraverse(T->rChild,visit)){
				return 	visit(T->data);
			}

		}
		return ERROR;
	}else{
		return OK;
	}

}
Status display(TElemType e){
	printf("%d ",e);
	return OK;
}
Status PreOrderTraverse2(BiTree T, Status (*visit)(TElemType e)){
	SeqStack s;
	InitStack(s);
	BiTree p =T;
	int i=0;
	while(p!=NULL||!StackEmpty(s)){
		if(p!=NULL){
			visit(p->data);
			Push(s,p);
			p=p->lChild;
		}else{
			Pop(s,p);
			p=p->rChild;
		}	
	}
	return OK;
}
Status InOrderTraverse2(BiTree T, Status (*visit)(TElemType e)){
	SeqStack s;
	InitStack(s);
	BiTree p = T ;
	while(p!=NULL||!StackEmpty(s)){
		if(p!=NULL){
			Push(s,p);
			p = p->lChild;
		}else{
			Pop(s,p);
			visit(p->data);
			p=p->rChild;
		}
	}
	return OK;
}
Status PostOrderTraverse3(BiTree T, Status (*visit)(TElemType e)){
	//��һ����־ ����ýڵ���ҽڵ��Ѿ����ʹ��ˣ���ֱ�����
	SeqStack s;
	InitStack(s);
	BiTree p = T;
	int tag[100];
	int t=1;
	while(p!=NULL||!StackEmpty(s)){
		while(p!=NULL){
			//������������ջ
			Push(s,p);
			p=p->lChild;
			tag[t++]=0;//���е����ӱ�־����Ϊ0
		}
		while(!StackEmpty(s)&&1==tag[t-1]){
			Pop(s,p);
			visit(p->data);
			t--;
		}
		if(!StackEmpty(s)){
			tag[t-1]=1;
			GetTop(s,p);
			p=p->rChild;
		}else{
			break;
		}

	}
	return OK;
}
Status PostOrderTraverse2(BiTree T, Status (*visit)(TElemType e)){
	//���������ǵݹ��㷨
	SeqStack s;
	InitStack(s);
	BiTree p = T;
	int i=0;
	while(i++<10){//p!=NULL||!StackEmpty(s)){//�����������?�����Һ��ӵ�ʱ��������ѭ����
		//��ѭ���ĸ�Դ�ǣ�
		//�Һ��ӵ��Һ���ΪNULLʱ���Һ��ӳ�ջ��ӡ������ջ��ָ��ָ���Һ��ӣ���ʱ�Ѿ������ѭ����
		//��α��⣿
		//��һ����־������ýڵ���Һ����Ѿ����ʹ��˾�ֱ�Ӵ�ӡ�ýڵ�
		if(p!=NULL){
			printf("%d��ջ\n",p->data);
			Push(s,p);
			p=p->lChild;
		}else{
			GetTop(s,p);
			p=p->rChild;
			if(p==NULL){
				Pop(s,p);
				visit(p->data);
				Pop(s,p);
				p=p->rChild;
			}
			if(p->lChild==NULL&&p->rChild==NULL){
				visit(p->data);
				Pop(s,p);
			}

		}
	}
	return OK;
}
void main(){
	BiTree t;
	printf("��������ڵ㣨-1����ڵ�Ϊ�գ�:");
	CreateBiTree(t);
//	PreOrderTraverse(t,&display);
	printf("\n");
//	InOrderTraverse(t,&display);
	printf("\n");
//	PostOrderTraverse(t,&display);
	printf("\n");
	PostOrderTraverse3(t,&display);
}