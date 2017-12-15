#include<stdio.h>
#include<stdlib.h>
#include "BiTNode.h"
#include "seqstack.h"


Status CreateBiTree(BiTree &T){
	//先序创建二叉树
//	printf("请输入一个根节点：\n");
	TElemType e;
	scanf("%d",&e);
	if(e==-1){
		T=NULL;
		return OK;
	}
	T=(BiTree)malloc(sizeof(BiTNode));
	T->data=e;
	printf("请输入%d的左孩子:",T->data);
	CreateBiTree(T->lChild);
	printf("请输入%d的右孩子:",T->data);
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
	//加一个标志 如果该节点的右节点已经访问过了，就直接输出
	SeqStack s;
	InitStack(s);
	BiTree p = T;
	int tag[100];
	int t=1;
	while(p!=NULL||!StackEmpty(s)){
		while(p!=NULL){
			//将所有左孩子入栈
			Push(s,p);
			p=p->lChild;
			tag[t++]=0;//所有的左孩子标志都置为0
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
	//后续遍历非递归算法
	SeqStack s;
	InitStack(s);
	BiTree p = T;
	int i=0;
	while(i++<10){//p!=NULL||!StackEmpty(s)){//问题出在哪里?访问右孩子的时候会造成死循环。
		//死循环的根源是？
		//右孩子的右孩子为NULL时，右孩子出栈打印，根出栈，指针指向右孩子，这时已经造成死循环。
		//如何避免？
		//设一个标志，如果该节点的右孩子已经访问过了就直接打印该节点
		if(p!=NULL){
			printf("%d进栈\n",p->data);
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
	printf("请输入根节点（-1代表节点为空）:");
	CreateBiTree(t);
//	PreOrderTraverse(t,&display);
	printf("\n");
//	InOrderTraverse(t,&display);
	printf("\n");
//	PostOrderTraverse(t,&display);
	printf("\n");
	PostOrderTraverse3(t,&display);
}