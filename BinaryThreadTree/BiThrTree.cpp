#include<stdio.h>
#include "stdlib.h"
#include "BiThrTree.h"


Status CreateBiThrTree(BiThrTree &T){
	TElemType e;
	scanf("%d",&e);
	if(e==-1){
		T=NULL;
		return OK;
	}else{
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		T->data=e;
		T->LTag=Link;
		T->RTag=Link;
		printf("请输入%d的左节点:",T->data);
		CreateBiThrTree(T->lchild);
		printf("请输入%d的右节点:",T->data);
		CreateBiThrTree(T->rchild);
	}
	return OK;
}
BiThrTree pre;
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T){
	printf("");	//不知道什么原因，不加这一句就什么都显示不出来，真他妈的奇怪
	if (!(Thrt = (BiThrNode *)malloc(sizeof(BiThrTree)) ))	//建头结点
		return ERROR;
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)
		Thrt->lchild = Thrt;		//T为空树，则头结点左指针指向头结点
	else {
		Thrt->lchild = T;		//头结点左链指向根结点
		pre = Thrt;			//pre初始时指向头结点
		InThreading(T);		//中序遍历进行线索化
		pre->rchild = Thrt;		//最后一个结点线索化，最后一个结点的右链指向头结点
		pre->RTag = Thread;
		Thrt->rchild = pre;		//头结点的右链指向最后一个遍历的结点
	}
	return OK;

}
void InThreading(BiThrTree p){
	if(p!=NULL){
		InThreading(p->lchild);
		if(p->lchild==NULL){
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(pre->rchild==NULL){
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p;
		InThreading(p->rchild);
	}
}

//找后驱
BiThrTree findNextDriver(BiThrTree T){
	BiThrTree p;
	if(T->RTag==Thread){//如果右标识是线索，其右孩子是线索
		p=T->rchild;
	}else{//否则，后驱是遍历右子树访问的第一个节点
		p=T->rchild;
		while(p->LTag==Link){
			p=p->lchild;
		}
	}
	return p;
}

//找前驱
BiThrTree findPreDriver(BiThrTree T){
	BiThrTree p;
	if(T->LTag==Thread){//如果左标识是线索，其左孩子是线索
		p=T->lchild;
	}else{//否则，其往左遍历第一个元素是其左孩子
		p=T->lchild;
		while(p->LTag==Link){
			p=p->lchild;
		}
	}
	return p;
}

Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e)){
	//不用栈，非递归，中序遍历二叉树
	BiThrTree p = T->lchild;//指向根节点
	int i=0;
	while(/*i++<10){*/p!=T){
		while(p->LTag==Link){
			p=p->lchild;
		}
		visit(p->data);
		if(p->LTag==Thread&&p->rchild!=T){
			p=p->rchild;
			visit(p->data);
		}
		p=p->rchild;
	}
	return OK;
}

Status visitElemType(TElemType e){
	printf("%d ",e);
	return OK;
}
void main(){
	printf("dddd\n");
	BiThrTree t;
	CreateBiThrTree(t);
	BiThrTree head;
	InOrderThreading(head,t);
	InOrderTraverse_Thr(head,&visitElemType);
}